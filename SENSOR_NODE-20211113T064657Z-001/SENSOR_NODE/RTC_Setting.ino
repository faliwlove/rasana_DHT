void rtc_setup(){
  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }

  if (rtc.lostPower()) {
    Serial.println("RTC lost power, lets set the time!");
    // following line setthe RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  }
}

void time_RTC(){
  
    DateTime now = rtc.now();
    
    rtc_year = (now.year());
    rtc_month = (now.month());
    rtc_date = (now.day());
    rtc_day = (daysOfTheWeek[now.dayOfTheWeek()]);
    rtc_hour = (now.hour());
    rtc_minute = (now.minute());
    rtc_second = (now.second());

  clock_time = (rtc_hour + ":" + rtc_minute + ":" + rtc_second);
  lcd_time = (rtc_hour + ":" + rtc_minute);
  clock_day = (daysOfTheWeek[now.dayOfTheWeek()]);
  clock_date = (rtc_date + "/" + rtc_month + "/" +rtc_year);
  clock_now = clock_day + "," + clock_date + "," + clock_time;
}
