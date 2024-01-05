import csv
from datetime import datetime

leds = 1

# Define the get_tunisian_time function
def get_tunisian_time(time):
    # ... (include the full code of the get_tunisian_time function here) ...
    global leds
    DRAJ = ["","درج","درجين","ربع","أربعة","خمسة","نص","سبعة","أربعة","ربع","درجين","درج",""]
    SEAA = ["نص الليل","ماضي ساعة","الساعتين","ماضي تلاثة","الأربعة","الخمسة","الستة","السبعة","الثمنية","التسعة","العشرة","الحداش","الأول"]
    ZID_SEAA = [0,0,0,0,0,0,0,0,1,1,1,1,1]
    DRAJ_PREFIXE = ["","و","و","و","و","و","و","و","غير","غير","غير","غير",""]
    KHAREJ_WALA_MA_HARRARCH = ["ما حررش","ما حررش","","","خارج","خارج"]
    now = time
    secondes_tawa = int(now.strftime("%S"))
    minutes_tawa = int(now.strftime("%M"))
    heures_tawa = int(now.strftime("%H"))
    drajj_tawa = ((minutes_tawa*60) + secondes_tawa + 150) // 300
    kharej_wala_ma_harrarch_tawa = minutes_tawa - (drajj_tawa*5) + 3
    heures_tawa = heures_tawa + ZID_SEAA[drajj_tawa]
    if heures_tawa != 12:
        heures_tawa = heures_tawa % 12
    tn_seaa = SEAA[heures_tawa]
    tn_prefixe_draj = DRAJ_PREFIXE[drajj_tawa]
    if tn_prefixe_draj != "": leds +=1
    tn_draj = DRAJ[drajj_tawa]
    if tn_draj != "": leds +=1
    tn_kharej_wala_ma_harrarch = KHAREJ_WALA_MA_HARRARCH[kharej_wala_ma_harrarch_tawa]
    if tn_kharej_wala_ma_harrarch != "": leds +=1
    #print(tn_seaa, tn_prefixe_draj, tn_draj, tn_kharej_wala_ma_harrarch)
    tunisian_time = tn_seaa + ' ' + tn_prefixe_draj + ' ' + tn_draj + ' ' + tn_kharej_wala_ma_harrarch
    return tunisian_time

# Open a new CSV file for writing
with open('tunisian_time_plus.csv', 'w', newline='') as csvfile:
    # Create a CSV writer
    writer = csv.writer(csvfile)
    # Write the header row
    writer.writerow(['Time', 'Tunisian Time', 'Leds'])

    # Loop through all the seconds in a day
    for i in range(24*60*60):
        leds = 1
        # Convert the current second to a time object
        time = datetime.fromtimestamp(i)
        # Get the Tunisian time for the current time
        tunisian_time = get_tunisian_time(time)
        # Write the current time and the Tunisian time to the CSV file
        writer.writerow([str(time.time()), tunisian_time, leds])
