void set_datetime(int h, int m, int s) {
  rtc.setTime(h, m, s);     // Set the time
  //uncomment below code to set DOW and date.
  //rtc.setDOW(THURSDAY);     // Set Day-of-Week
  //rtc.setDate(4, 1, 2021);   // Set the date
}
