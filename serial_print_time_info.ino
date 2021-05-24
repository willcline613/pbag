void serial_print_time_info() {
    Serial.print('\n');
    Serial.print(F("Current sec: "));
    Serial.println(current_sec);

    Serial.print(F("Current time: "));
    serial_print_12hr_hour(current_hour);
    Serial.print(F(":"));
    serial_print_leading_zero(current_min);
    Serial.print(current_min);
    Serial.print(F(" "));
    serial_print_AM_or_PM(current_hour);
    Serial.print('\n');
    
    Serial.print(F("alarm time: "));
    serial_print_12hr_hour(alarm_hour);
    Serial.print(F(":"));
    serial_print_leading_zero(alarm_min);
    Serial.print(alarm_min);
    Serial.print(F(" "));
    serial_print_AM_or_PM(alarm_hour);
    Serial.print('\n');

    Serial.print(F("current_loop: "));
    Serial.println(current_loop);

    Serial.print(F("current_screen: "));
    Serial.println(current_screen);

    if ( (current_hour == alarm_hour) and (current_min == alarm_min) and (current_sec > min_sec_threshold) ){
      Serial.println(F("Current hour and min match alarm, but seconds are beyond."));
    }
}
