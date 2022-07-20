import 'package:intl/intl.dart';

class TimeTnCalc {
  static const drajList = [
    '',
    'درج',
    'درجين',
    'ربع',
    'أربعة',
    'خمسة',
    'نص',
    'سبعة',
    'أربعة',
    'ربع',
    'درجين',
    'درج',
    ''
  ];

  static const seaaList = [
    'نص الليل',
    'ماضي ساعة',
    'الساعتين',
    'ماضي تلاثة',
    'الأربعة',
    'الخمسة',
    'الستة',
    'السبعة',
    'الثمنية',
    'التسعة',
    'العشرة',
    'لحداش',
    'الأول'
  ];

  static const zidSeaaList = [0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1];

  static const drajPrefixList = [
    '',
    'و',
    'و',
    'و',
    'و',
    'و',
    'و',
    'و',
    'غير',
    'غير',
    'غير',
    'غير',
    ''
  ];

  static const kharejWalaMaHarrarchList = [
    'ما حررش',
    'ما حررش',
    '',
    '',
    'خارج',
    'خارج'
  ];

  static String eval(String timeString) {
    int localHour;
    int localMinute;
    int localSecond;
    int localDraj;
    int localKarejWallaMaHarrarch;
    String finalHour;
    String finalDrajPrefix;
    String finalDraj;
    String finalKharejWallaMaHarrarch;
    DateTime timeValue = DateFormat('H:m:s').parse(timeString);
    localHour = timeValue.hour;
    localMinute = timeValue.minute;
    localSecond = timeValue.second;
    localDraj = ((localMinute * 60) + localSecond + 150) ~/ 300;
    localKarejWallaMaHarrarch = localMinute - (localDraj * 5) + 3;
    localHour += zidSeaaList[localDraj];
    if (localHour != 12) {
      localHour %= 12;
    }
    finalHour = seaaList[localHour];
    finalDrajPrefix = drajPrefixList[localDraj];
    finalDraj = drajList[localDraj];
    finalKharejWallaMaHarrarch =
        kharejWalaMaHarrarchList[localKarejWallaMaHarrarch];
    return '$finalHour $finalDrajPrefix $finalDraj $finalKharejWallaMaHarrarch';
  }
}
