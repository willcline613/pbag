//get rid of debounce from buttons using millis()
void up_btn() {
    //up button activated:
    // change certain variable upwards depending on what screen you currently are on or if on alarm mode screen, toggle_alarm_mode()
    //after variable change, reprint corresponding current screen
    if (current_screen == "alarm_set_hour_screen") {
      if (alarm_hour >= 23) {
        alarm_hour = 0;
      }
      else {
        alarm_hour += 1;
      }

      alarm_set_hour_screen();
    }
    else if (current_screen == "alarm_set_min_screen") {
      if (alarm_min >= 59) {
        alarm_min = 0;
      }
      else {
        alarm_min += 1;
      }
      alarm_set_min_screen();
    }
    else if (current_screen == "alarm_set_mode_screen") {
      toggle_alarm_mode();
      alarm_set_mode_screen();
    }
    //write updated time variables to eeprom in case device turns off
    EEPROM_write_time();
}

void down_btn() {
  //if digital read senses that button is pressed down, should activate following code:
    //down button activated:
    // change certain variable downwards depending on what screen you currently are on or if on alarm mode screen, toggle_alarm_mode()
    //after variable change, reprint corresponding current screen
    if (current_screen == "alarm_set_hour_screen") {
      if (alarm_hour <= 0) {
        alarm_hour = 23;
      }
      else {
        alarm_hour -= 1;
      }
      
      alarm_set_hour_screen();
    }
    else if (current_screen == "alarm_set_min_screen") {
      if (alarm_min <= 0) {
        alarm_min = 23;
      }
      else {
        alarm_min -= 1;
      }
      
      alarm_set_min_screen();
    }
    else if (current_screen == "alarm_set_mode_screen") {
      toggle_alarm_mode();
      alarm_set_mode_screen();
    }
    
    EEPROM_write_time();
}
