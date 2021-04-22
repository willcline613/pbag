//remember to include functionality of automatically returning to main_screen after a long enough interval.

void main_screen() {
  lcd.clear();
  //update current screen to reflect where we are at:
  current_screen = "main_screen";
  
  //line 1 prints the current time by using hour and minute variables
  lcd.setCursor(4, 0);
  print_12hr_hour(current_hour);
  lcd.print(F(":"));
  //if statement to print leading zero if needed.
  print_leading_zero(current_min);
  lcd.print(current_min);
  //space and then AM or PM
  lcd.print(F(" "));
  print_AM_or_PM(current_hour);

  //line 2 prints the current alarm time
  lcd.setCursor(0, 1);
  lcd.print(F("Alarm"));
  if (alarm_mode == 0) {
    lcd.print(F(" "));
    lcd.print(alarm_mode_string);
  }
  //prints current alarm time if alarm mode is on.
  //sits at 16 characters in case of 11 or 12 with no spaces.
  if (alarm_mode == 1) {
    lcd.print(F(":"));
    print_12hr_hour(alarm_hour);
    lcd.print(F(":"));
    print_leading_zero(alarm_min);
    lcd.print(alarm_min);
    lcd.print(F(" "));
    print_AM_or_PM(alarm_hour);
  }
}

//is it even neccessary to have whole different function for alarm_set_hour and set min, or could I just use an if,else statement to toggle through the current_screens?
//I'm currently keeping two separate functions bc it will pro0bably make it easier in the case that I have the hour or minute digit blink b/c two totally different sets of strings would need to be printed.
void alarm_set_hour_screen() {
  lcd.clear();
  current_screen = "alarm_set_hour_screen";
  Serial.print(F("current screen: "));
  Serial.println(current_screen);

  lcd.setCursor(0,0);
  lcd.print(F("Set Alarm Hour:"));
  
  lcd.setCursor(4,1);
  print_12hr_hour(alarm_hour);
  lcd.print(F(":"));
  print_leading_zero(alarm_min);
  lcd.print(alarm_min);
  lcd.print(F(" "));
  print_AM_or_PM(alarm_hour);

  EEPROM_write_time();
}

void alarm_set_min_screen() {
  lcd.clear();
  current_screen = "alarm_set_min_screen";
  Serial.print(F("current screen: "));
  Serial.println(current_screen);


  lcd.setCursor(0,0);
  lcd.print(F("Set Alarm Min:"));
  
  lcd.setCursor(4,1);
  print_12hr_hour(alarm_hour);
  lcd.print(F(":"));
  print_leading_zero(alarm_min);
  lcd.print(alarm_min);
  lcd.print(F(" "));
  print_AM_or_PM(alarm_hour);
}

void alarm_set_mode_screen() {
  lcd.clear();
  current_screen = "alarm_set_mode_screen";
  Serial.print(F("current screen: "));
  Serial.println(current_screen);

  lcd.setCursor(0,0);
  lcd.print(F("Set Alarm Mode:"));
  
  lcd.setCursor(6,1);
  lcd.print(alarm_mode_string);
}
