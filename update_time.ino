void update_time() {
    datetime_data = rtc.getTime();
    current_hour = datetime_data.hour;
    current_min = datetime_data.min;
    current_sec = datetime_data.sec;
}

//lcd.prints a 0 if whatever is called in num parameter is less than 10 
void print_leading_zero(int num) {
  if (num < 10) {
    lcd.print(F("0"));
  }
}
//does same thing but to serial monitor
void serial_print_leading_zero(int num) {
  if (num < 10) {
    Serial.print(F("0"));
  }
}

void print_leading_space(int num) {
  if (num < 10) {
    lcd.print(F(" "));
  }
}

void print_AM_or_PM(int hr) {
  //print AM or PM depending on the military time hour.
  if (hr >= 12) {
    lcd.print(F("PM"));
  }
  else if (hr < 12) {
    lcd.print(F("AM"));
  }
}

void serial_print_AM_or_PM(int hr) {
  //print AM or PM depending on the military time hour.
  if (hr >= 12) {
    Serial.print(F("PM"));
  }
  else if (hr < 12) {
    Serial.print(F("AM"));
  }
}

void print_12hr_hour(int hr) {
  int twelve_hr_hour;
  if (hr == 0) {
    twelve_hr_hour = 12;
  }
  else if (hr > 12 and hr != 0) {
    twelve_hr_hour = hr - 12;
  }
  else if (hr <= 12) {
    twelve_hr_hour = hr;
  }
  print_leading_space(twelve_hr_hour);
  lcd.print(twelve_hr_hour);
}

void serial_print_12hr_hour(int hr) {
  int twelve_hr_hour;
  if (hr == 0) {
    twelve_hr_hour = 12;
  }
  else if (hr > 12 and hr != 0) {
    twelve_hr_hour = hr - 12;
  }
  else if (hr <= 12) {
    twelve_hr_hour = hr;
  }
  Serial.print(twelve_hr_hour);
}
