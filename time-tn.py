# Ce programme revoie l'heure en Tunisien
from datetime import datetime

DRAJ = ["","درج","درجين","ربع","أربعة","خمسة","نص","سبعة","أربعة","ربع","درجين","درج",""]
SEAA = ["نص الليل","ماضي ساعة","الساعتين","ماضي تلاثة","الأربعة","الخمسة","الستة","السبعة","الثمنية","التسعة","العشرة","الحداش","الأول"]
ZID_SEAA = [0,0,0,0,0,0,0,0,1,1,1,1,1]
DRAJ_PREFIXE = ["","و","و","و","و","و","و","و","غير","غير","غير","غير",""]
KHAREJ_WALA_MA_HARRARCH = ["ما حررش","ما حررش","","","خارج","خارج"]

def main():
    now = datetime.now()
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
    tn_draj = DRAJ[drajj_tawa]
    tn_kharej_wala_ma_harrarch = KHAREJ_WALA_MA_HARRARCH[kharej_wala_ma_harrarch_tawa]

    print(tn_kharej_wala_ma_harrarch, tn_draj, tn_prefixe_draj, tn_seaa)
    print(tn_seaa, tn_prefixe_draj, tn_draj, tn_kharej_wala_ma_harrarch)

if __name__== "__main__":
    main()
