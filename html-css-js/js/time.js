// Time conversion function: converts standard time to Tunisian Arabic format
function timeTnCalc(timeString) {
  // Arrays for Tunisian Arabic time components
  const drajList = [
    '', 'درج', 'درجين', 'ربع', 'أربعة', 'خمسة', 'نص',
    'سبعة', 'أربعة', 'ربع', 'درجين', 'درج', ''
  ];
  const seaaList = [
    'نص الليل', 'ماضي ساعة', 'الساعتين', 'ماضي تلاثة', 'الأربعة',
    'الخمسة', 'الستة', 'السبعة', 'الثمنية', 'التسعة',
    'العشرة', 'لحداش', 'الأول'
  ];
  const zidSeaaList = [0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1];
  const drajPrefixList = [
    '', 'و', 'و', 'و', 'و', 'و',
    'و', 'و', 'غير', 'غير', 'غير', 'غير', ''
  ];
  const kharejWalaMaHarrarchList = [
    'ما حررش', 'ما حررش', '', '', 'خارج', 'خارج'
  ];

  // Parse time components
  const [hourStr, minuteStr, secondStr] = timeString.split(':');
  let localHour = parseInt(hourStr, 10);
  let localMinute = parseInt(minuteStr, 10);
  let localSecond = parseInt(secondStr, 10);

  // Calculate Tunisian time components
  const localDraj = Math.floor(((localMinute * 60) + localSecond + 150) / 300);
  const localKarejWallaMaHarrarch = localMinute - (localDraj * 5) + 3;
  localHour += zidSeaaList[localDraj];
  
  // Adjust hour to 12-hour format
  if (localHour !== 12) {
    localHour = localHour % 12;
  }
  
  // Compose final time string
  const finalHour = seaaList[localHour];
  const finalDrajPrefix = drajPrefixList[localDraj];
  const finalDraj = drajList[localDraj];
  const finalKharejWallaMaHarrarch = kharejWalaMaHarrarchList[localKarejWallaMaHarrarch];

  return (
    finalHour + ' ' +
    finalDrajPrefix + ' ' +
    finalDraj + ' ' +
    finalKharejWallaMaHarrarch
  ).trim();
}

// Updates both time displays (Tunisian and 24-hour format)
function updateTime() {
  const now = new Date();
  const hour = String(now.getHours()).padStart(2, '0');
  const minute = String(now.getMinutes()).padStart(2, '0');
  const second = String(now.getSeconds()).padStart(2, '0');
  
  const timeString = `${hour}:${minute}:${second}`;
  
  // Update Tunisian time display
  document.getElementById('timeNowText').textContent = timeTnCalc(timeString);
  // Update 24-hour time display
  document.getElementById('timeNow').textContent = timeString;
}

// Initialize time display and update every second
setInterval(updateTime, 1000);
updateTime();

// Copy time text to clipboard when copy button is clicked
document.getElementById('copyButton').addEventListener('click', function() {
  const timeText = document.getElementById('timeNowText').textContent;
  navigator.clipboard.writeText(timeText).then(function() {
    // Visual feedback on successful copy
    const button = document.getElementById('copyButton');
    button.style.backgroundColor = '#4CAF50';
    setTimeout(() => {
      button.style.backgroundColor = '#FFC107';
    }, 500);
  }).catch(function(err) {
    console.error('Failed to copy text: ', err);
  });
});
