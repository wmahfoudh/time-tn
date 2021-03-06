#include <IotWebConf.h>
#include "uTimerLib.h"
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <NeoPixelBus.h>

// WiFi related decarations
const char thingName[] = "TnClock";
const char wifiInitialApPassword[] = "welovetn";

// Length of a number in bytes when saved to the ESP8266 EEPROM
#define NUMBER_LEN 5

// CONFIG_VERSION should be modified if config structure was changed
#define CONFIG_VERSION "slan"

// When GPIO CONFIG_PIN is pulled to ground on startup, the clock will use the initial password to build an AP (case of lost password)
#define CONFIG_PIN 4

// Color and saturation
#define colorSaturation 255
RgbColor white(colorSaturation);

// The number of pixels in the clock is 25, from 0 to 24, the pin is GPIO3
const uint16_t PixelCount = 25; 
const uint8_t PixelPin = 3;

// Status indicator pin. First it will light up, on Wifi connection it will blink, when connected to the Wifi it will turn off
#define STATUS_PIN LED_BUILTIN

// Callback methods
void configSaved();
void wifiConnected();
boolean formValidator();

// Server related declarations
DNSServer dnsServer;
WebServer server(80);

// Variables that will hold parameters to be stored in the EEPROM
char timeZoneValue[NUMBER_LEN];
char UpdateInterval[NUMBER_LEN];
char setHoursValue[NUMBER_LEN];
char setMinutesValue[NUMBER_LEN];
char setSecondsValue[NUMBER_LEN];
char maxBrightness[NUMBER_LEN];

// Global variables, these are initially read from saved parameters
int globalHours = 0;
int globalMinutes = 0;
int globalSeconds = 0;
long utcOffsetInSeconds = 0;
int globalUpdateInterval = 0;
int globalUpdateCurrentValue = 0;
String globalTimeTN = "";
int globalMaxBrightness = 100;

//mask variable used to hold the sum of masked lit pixels
long unsigned globalTimePixel = 0;

// Declating the pixels
NeoPixelBus<NeoGrbFeature, Neo800KbpsMethod> strip(PixelCount, PixelPin);

// NTPClient dectarations
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", utcOffsetInSeconds, globalUpdateInterval*58);
  
// Tables used to convert the time into a Tunisian time string
String DRAJ[13] = { "", "درج", "درجين", "ربع", "أربعة", "خمسة", "نص", "سبعة", "أربعة", "ربع", "درجين", "درج", "" };
String SEAA[13] = { "نص الليل", "ماضي ساعة", "الساعتين", "ماضي تلاثة", "الأربعة", "الخمسة", "الستة", "السبعة", "الثمنية", "التسعة", "العشرة", "الحداش", "الأول" };
int ZID_SEAA[13] = { 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1 };
String DRAJ_PREFIXE[13] = { "", "و", "و", "و", "و", "و", "و", "و", "غير", "غير", "غير", "غير", "" };
String KHAREJ_WALA_MA_HARRARCH[6] = { "ما حررش", "ما حررش", "", "", "خارج", "خارج" };

// Tables used for masking lit cells
long unsigned iDRAJ[13] = { 0, 262144, 2097152, 1048576, 65536, 4194304, 131072, 524288, 65536, 1048576, 2097152, 262144, 0 };
long unsigned iSEAA[13] = { 32, 10, 512, 6, 128, 2048, 8192, 256, 4096, 16, 64, 1024, 1 };
long unsigned iDRAJ_PREFIXE[13] = { 0, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 16384, 16384, 16384, 16384, 0 };
long unsigned iKHAREJ_WALA_MA_HARRARCH[6] = { 16777216, 16777216, 0, 0, 8388608, 8388608 };

// Layout of the configuration page
IotWebConf iotWebConf(thingName, &dnsServer, &server, wifiInitialApPassword, CONFIG_VERSION);
IotWebConfSeparator separator_time = IotWebConfSeparator("Time settings");
IotWebConfParameter timezomeparam = IotWebConfParameter("Time zone", "timeZone", timeZoneValue, NUMBER_LEN, "number", "e.g. 5.75", "0", "step='0.25'");
IotWebConfParameter updateinterval = IotWebConfParameter("Update interval", "updateInterval", UpdateInterval, NUMBER_LEN, "number", "0..1440 minutes, 0 for no update", NULL, "min='0' max='1440' step='1'");
IotWebConfParameter hoursparam = IotWebConfParameter("Set hour", "setHour", setHoursValue, NUMBER_LEN, "number", "0..24", NULL, "min='0' max='23' step='1'");
IotWebConfParameter minutesparam = IotWebConfParameter("Set minute", "setMinute", setMinutesValue, NUMBER_LEN, "number", "0..59", NULL, "min='0' max='59' step='1'");
IotWebConfParameter secondsparam = IotWebConfParameter("Set second", "setSecond", setSecondsValue, NUMBER_LEN, "number", "0..59", NULL, "min='0' max='59' step='1'");
IotWebConfSeparator separator_clock = IotWebConfSeparator("Clock settings");
IotWebConfParameter maxbrightness = IotWebConfParameter("Max brightness", "maxBrightness", maxBrightness, NUMBER_LEN, "number", "0..255", NULL, "min='0' max='255' step='1'");

// -- Javascript block added to the header.
const char CUSTOMHTML_SCRIPT_INNER[] PROGMEM = "\n\
document.addEventListener('DOMContentLoaded', function(event) {\n\
  let elements = document.querySelectorAll('input[type=\"password\"]');\n\
  for (let p of elements) {\n\
    let btn = document.createElement('INPUT'); btn.type = 'button'; btn.value = '🔓'; btn.style.width = 'auto'; p.style.width = '83%'; p.parentNode.insertBefore(btn,p.nextSibling);\n\
    btn.onclick = function() { if (p.type === 'password') { p.type = 'text'; btn.value = '🔒'; } else { p.type = 'password'; btn.value = '🔓'; } }\n\
  };\n\
});\n";
// -- HTML element will be added inside the body element.
const char CUSTOMHTML_BODY_INNER[] PROGMEM = "<div><img src='data:image/png;base64, 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'/></div>\n";

// Methods override to inject new html format
class CustomHtmlFormatProvider : public IotWebConfHtmlFormatProvider
{
protected:
  String getScriptInner() override
  {
    return
      IotWebConfHtmlFormatProvider::getScriptInner() +
      String(FPSTR(CUSTOMHTML_SCRIPT_INNER));
  }
  String getBodyInner() override
  {
    return
      String(FPSTR(CUSTOMHTML_BODY_INNER)) +
      IotWebConfHtmlFormatProvider::getBodyInner();
  }
};
// -- An instance must be created from the class defined above.
CustomHtmlFormatProvider customHtmlFormatProvider;

void setup() 
{
  Serial.begin(115200);
  Serial.println();
  Serial.println("TnClock Starting...");
  iotWebConf.setStatusPin(STATUS_PIN);
  iotWebConf.setConfigPin(CONFIG_PIN);
  iotWebConf.addParameter(&separator_time);
  iotWebConf.addParameter(&timezomeparam);
  iotWebConf.addParameter(&updateinterval);
  iotWebConf.addParameter(&hoursparam);
  iotWebConf.addParameter(&minutesparam);
  iotWebConf.addParameter(&secondsparam);
  iotWebConf.addParameter(&separator_clock);
  iotWebConf.addParameter(&maxbrightness);
  iotWebConf.setConfigSavedCallback(&configSaved);
  iotWebConf.setFormValidator(&formValidator);
  iotWebConf.setWifiConnectionCallback(&wifiConnected);
  iotWebConf.getApTimeoutParameter()->visible = true;
  // -- Applying the new HTML format to IotWebConf.
  iotWebConf.setHtmlFormatProvider(&customHtmlFormatProvider);
  // -- Initializing the configuration.
  iotWebConf.init();
  // -- Set up required URL handlers on the web server
  server.on("/", handleRoot);
  server.on("/config", []{ iotWebConf.handleConfig(); });
  server.on("/raw", handleRaw);
  server.onNotFound([](){ iotWebConf.handleNotFound(); });
  timeClient.begin();
  TimerLib.setInterval_s(timerTick, 1);
  if (initGlobals(atof(timeZoneValue), atoi(setHoursValue), atoi(setMinutesValue), atoi(setSecondsValue), atoi(UpdateInterval), atoi(maxBrightness)))
  { Serial.println("Parameters successfully initialized"); } else { Serial.println("One or more parameter are out of range"); }
  // Initializing Neopixels data line 
  while (!Serial); // wait for serial attach
  Serial.println();
  Serial.println("Initializing Neopixels...");
  Serial.flush();
  // this resets all the neopixels to an off state
  strip.Begin();
  strip.Show();
  Serial.println();
  Serial.println("Running...");
}

void loop() 
{
  // The loop
  iotWebConf.doLoop();
}

void handleRaw()
{
  // Returns time in plain text, can be used as a web service
  server.send(200, "text/html; charset=UTF-8", globalTimeTN);
}

void handleRoot()
{
  // -- Let IotWebConf test and handle captive portal requests.
  if (iotWebConf.handleCaptivePortal())
  {
    // -- Captive portal request were already served.
    return;
  }
  String s = "<!DOCTYPE html><html lang=\"en\"><head><meta http-equiv=\"refresh\" content=\"5\">";
  s += "<title>Welcome to TnClock</title>";
  s += "<style>@font-face {font-family: NotoKufiArabic; src: url(//fonts.googleapis.com/earlyaccess/notokufiarabic.css);}";
  s += "* {font-family: 'Noto Kufi Arabic', sans-serif;}</style></head><body style='background-color:#ffd700;'>";
  s += "<p style='font-size:8vw; font-weight: Bold; text-align:center'>";
  s += globalTimeTN;
  s += "</p>";
  s += "</body></html>\n";
  server.send(200, "text/html; charset=UTF-8", s);
}

void configSaved()
{
  // Config successfully updated (Callback)
  Serial.println("Configuration updated");
}

void makeTimeTN()
{
  // Convert global time variables into a Tunisian time string
  long unsigned new_TimePixel = 0;
  int drajj_tawa = ((globalMinutes * 60) + globalSeconds + 150) / 300;
  int kharej_wala_ma_harrarch_tawa = globalMinutes - (drajj_tawa * 5) + 3;
  int heures_tawa = globalHours + ZID_SEAA[drajj_tawa];
  if (heures_tawa != 12) { heures_tawa = (heures_tawa % 12); }
  String tn_seaa = SEAA[heures_tawa];
  new_TimePixel += iSEAA[heures_tawa];
  String tn_prefixe_draj = DRAJ_PREFIXE[drajj_tawa];
  new_TimePixel += iDRAJ_PREFIXE[drajj_tawa];
  String tn_draj = DRAJ[drajj_tawa];
  new_TimePixel += iDRAJ[drajj_tawa];
  String tn_kharej_wala_ma_harrarch = KHAREJ_WALA_MA_HARRARCH[kharej_wala_ma_harrarch_tawa];
  new_TimePixel += iKHAREJ_WALA_MA_HARRARCH[kharej_wala_ma_harrarch_tawa];
  String new_Time = tn_seaa;
  if (tn_prefixe_draj != "") { new_Time += " " + tn_prefixe_draj; }
  if (tn_draj != "") { new_Time += " " + tn_draj; }
  if (tn_kharej_wala_ma_harrarch != "") { new_Time += " " + tn_kharej_wala_ma_harrarch; }
  if (new_Time != globalTimeTN) { updateTimeTN(new_Time, new_TimePixel); }
}

void updateTimeTN(String inputTime, long unsigned inputTimePixel)
{
  // Triggered only when the text of the Tunisian time changes to avoid useless updates
  globalTimeTN = inputTime;
  globalTimePixel = inputTimePixel;
  long unsigned mask = 1;
  for (int i = 0; i < 25; i++) 
  {
    if ((globalTimePixel & mask) == mask)  { strip.SetPixelColor(i, white); }
    mask = mask << 1;
  }
  strip.Show();
}

void getInternetTime()
{
  // Getting time from NTP server and update global time variables
  Serial.println("Retrieving NTP time...");
  timeClient.update();
  globalHours = timeClient.getHours();
  globalMinutes = timeClient.getMinutes();
  globalSeconds = timeClient.getSeconds();
  globalUpdateCurrentValue = 0;
}

boolean initGlobals(float tz, int h, int m, int s, int ui, int mb)
{
  // Initialize global variables if passed parameters are okay
  if ((tz <= 14) or (tz >= -12) and (h <= 23) and (h >= 0) and (m <= 59) and (m >= 0) and (s <= 59) and (s >= 0) and (ui <= 1440) and (ui >= 0) and (mb <= 255) and (mb >= 0))
  {
    globalHours = h;
    globalMinutes = m;
    globalSeconds = s;
    utcOffsetInSeconds = tz * 3600;
    globalMaxBrightness = mb;
    globalUpdateInterval = ui;
    timeClient.setUpdateInterval(globalUpdateInterval * 60);
    timeClient.setTimeOffset(utcOffsetInSeconds);
    return true;
  }
  else { return false; }
}

void wifiConnected()
{
  // Wifi is connected (Callback), initializes time
  Serial.println("WiFi connected, updating time...");
   if (globalUpdateInterval != 0) { getInternetTime(); }
}

boolean formValidator()
{
  Serial.println("Validating form.");
  boolean valid = initGlobals(atof(server.arg(timezomeparam.getId()).c_str()), atoi(server.arg(hoursparam.getId()).c_str()), atoi(server.arg(minutesparam.getId()).c_str()), atoi(server.arg(secondsparam.getId()).c_str()), atoi(server.arg(updateinterval.getId()).c_str()), atoi(server.arg(maxbrightness.getId()).c_str()));
  if (valid)
  { Serial.println("Parameters successfully set"); } else { Serial.println("One or more parameter are out of range"); }
  return valid;
}

void timerTick()
{
  if (globalSeconds==59)
  {
    globalSeconds = 0;
    if (globalMinutes==59)
    {
      globalMinutes = 0;
      if (globalHours==23)
      {
        globalHours = 0;
      }
      else
      {
        globalHours += 1;
      }
    }
    else
    {
      globalMinutes += 1;
      globalUpdateCurrentValue += 1;
    }
  }
  else
  {
    globalSeconds += 1;
  }
  if ((globalUpdateCurrentValue == globalUpdateInterval) and (globalUpdateInterval != 0)) { getInternetTime(); }
  makeTimeTN();
  Serial.print(globalHours);
  Serial.print(":");
  Serial.print(globalMinutes);
  Serial.print(":");
  Serial.print(globalSeconds);
  Serial.print(" ");
  Serial.println(globalTimeTN);
  Serial.print("Lit pixels: ");
  Serial.println(globalTimePixel);
}
