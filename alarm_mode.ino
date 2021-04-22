//switch alarm mode to opposite of what it currently is when called.
void toggle_alarm_mode() {
  if (alarm_mode == 1) {
    //switch it from what it currently is
    alarm_mode = 0;
  }
  else if (alarm_mode == 0) {
    alarm_mode = 1;
  }
  //change the string version to match the binary.
  update_alarm_mode_string();
}

void update_alarm_mode_string() {
  if (alarm_mode == 0) {
    alarm_mode_string = "OFF";
  }
  else if (alarm_mode == 1) {
    alarm_mode_string = "ON";
  }
}
