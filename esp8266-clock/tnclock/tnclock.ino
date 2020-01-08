#include <IotWebConf.h>
#include "uTimerLib.h"

// -- Initial name of the Thing. Used e.g. as SSID of the own Access Point.
const char thingName[] = "TnClock";

// -- Initial password to connect to the Thing, when it creates an own Access Point.
const char wifiInitialApPassword[] = "welovetn";

#define NUMBER_LEN 5

// -- Configuration specific key. The value should be modified if config structure was changed.
#define CONFIG_VERSION "x29decal"

// -- When CONFIG_PIN is pulled to ground on startup, the Thing will use the initial
//      password to buld an AP. (E.g. in case of lost password)
#define CONFIG_PIN D2

// -- Status indicator pin.
//      First it will light up (kept LOW), on Wifi connection it will blink,
//      when connected to the Wifi it will turn off (kept HIGH).
#define STATUS_PIN LED_BUILTIN

// -- Callback method declarations.
void configSaved();
boolean formValidator();

DNSServer dnsServer;
WebServer server(80);

char timeZoneValue[NUMBER_LEN];
char UpdateInterval[NUMBER_LEN];
char setHoursValue[NUMBER_LEN];
char setMinutesValue[NUMBER_LEN];
char setSecondsValue[NUMBER_LEN];
char maxBrightness[NUMBER_LEN];

int globalHours = 0;
int globalMinutes = 0;
int globalSeconds = 0;
long utcOffsetInSeconds = 0;
int globalMaxBrightness = 0;
int globalUpdateInterval = 0;

IotWebConf iotWebConf(thingName, &dnsServer, &server, wifiInitialApPassword, CONFIG_VERSION);
IotWebConfSeparator separator_time = IotWebConfSeparator("Time settings");
IotWebConfParameter timezomeparam = IotWebConfParameter("Time zone", "timeZone", timeZoneValue, NUMBER_LEN, "number", "e.g. 5.75", "0", "step='0.25'");
IotWebConfParameter updateinterval = IotWebConfParameter("Update period", "updateInterval", UpdateInterval, NUMBER_LEN, "number", "0..59 minutes", NULL, "min='1' max='59' step='1'");
IotWebConfParameter hoursparam = IotWebConfParameter("Set hour", "setHour", setHoursValue, NUMBER_LEN, "number", "0..24", NULL, "min='0' max='23' step='1'");
IotWebConfParameter minutesparam = IotWebConfParameter("Set minute", "setMinute", setMinutesValue, NUMBER_LEN, "number", "0..59", NULL, "min='0' max='59' step='1'");
IotWebConfParameter secondsparam = IotWebConfParameter("Set second", "setSecond", setSecondsValue, NUMBER_LEN, "number", "0..59", NULL, "min='0' max='59' step='1'");
IotWebConfSeparator separator_clock = IotWebConfSeparator("Clock settings");
IotWebConfParameter maxbrightness = IotWebConfParameter("Max brightness", "maxBrightness", maxBrightness, NUMBER_LEN, "number", "0..255", NULL, "min='0' max='255' step='1'");

void setup() 
{
  Serial.begin(115200);
  Serial.println();
  Serial.println("Starting up...");
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
  iotWebConf.getApTimeoutParameter()->visible = true;
  // -- Initializing the configuration.
  iotWebConf.init();
  // -- Set up required URL handlers on the web server.
  server.on("/", handleRoot);
  server.on("/config", []{ iotWebConf.handleConfig(); });
  server.onNotFound([](){ iotWebConf.handleNotFound(); });
  TimerLib.setInterval_s(each_second_function, 1);
  if (init_globals(atof(timeZoneValue), atoi(setHoursValue), atoi(setMinutesValue), atoi(setSecondsValue), atoi(UpdateInterval), atoi(maxBrightness)))
  {
    Serial.println("Parameters successfully initialized.");
  }
  else
  {
    Serial.println("One or more parameter are out of range.");
  }
}

void loop() 
{
  // -- doLoop should be called as frequently as possible.
  iotWebConf.doLoop();
}

void handleRoot()
{
  // -- Let IotWebConf test and handle captive portal requests.
  if (iotWebConf.handleCaptivePortal())
  {
    // -- Captive portal request were already served.
    return;
  }
  String s = "<!DOCTYPE html><html lang=\"en\"><head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1, user-scalable=no\"/>";
  s += "<title>TimeTN Parameters</title></head><body>TimeTN Parameters";
  s += "<ul>";
  s += "<li>Time zone: ";
  s += atof(timeZoneValue);
  s += "</li>";
  s += "<li>Current time: ";
  s += globalHours;
  s += ":";
  s += globalMinutes;
  s += ":";
  s += globalSeconds;      
  s += "</li>";
  s += "<li>Max brightness: ";
  s += globalMaxBrightness;
  s += "</li>";
  s += "<li>Update interval: ";
  s += globalUpdateInterval;
  s += "</li>";    
  s += "</ul>";
  s += "Go to <a href='config'>configure page</a> to change values.";
  s += "</body></html>\n";
  server.send(200, "text/html", s);
}

void configSaved()
{
  Serial.println("Configuration was updated.");
}

boolean init_globals(float tz, int h, int m, int s, int ui, int mb)
{
  if ((tz <= 14) or (tz >= -12) and (h <= 23) and (h >= 0) and (m <= 59) and (m >= 0) and (s <= 59) and (s >= 0) and (ui <= 59) and (ui >= 0) and (mb <= 255) and (mb >= 0))
  {
    globalHours = h;
    globalMinutes = m;
    globalSeconds = s;
    utcOffsetInSeconds = tz * 3600;
    globalMaxBrightness = mb;
    globalUpdateInterval = ui;
    return true;
  }
  else
  {
    return false;
  }
}

boolean formValidator()
{
  Serial.println("Validating form.");
  boolean valid = init_globals(atof(server.arg(timezomeparam.getId()).c_str()), atoi(server.arg(hoursparam.getId()).c_str()), atoi(server.arg(minutesparam.getId()).c_str()), atoi(server.arg(secondsparam.getId()).c_str()), atoi(server.arg(updateinterval.getId()).c_str()), atoi(server.arg(maxbrightness.getId()).c_str()));
  if (valid)
  {
    Serial.println("Parameters successfully set.");
  }
  else
  {
    Serial.println("One or more parameter are out of range.");
  }
  return valid;
}

void each_second_function()
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
    }
  }
  else
  {
    globalSeconds += 1;
  }
  Serial.print(globalHours);
  Serial.print(":");
  Serial.print(globalMinutes);
  Serial.print(":");
  Serial.println(globalSeconds);
}
