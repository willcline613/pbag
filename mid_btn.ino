//interrupt pin trigger of middle button. Needs to activate polling loops for other two buttons as well as change screen.
//how can I use a loop to poll without screwing up millis() lazy loop or mills() attentive loop from continuing to poll properly?
//would 2 middle buttons be more useful so that you don't have to press the middle one as many times to get back to main screen?
void mid_btn() {
  Serial.println(F("mid btn function triggered"));
  //when mid button triggered, first determine what screen you are currently on in order to know which screen to move to next. Use this info to change it to the thing that ought to be next in line.
  screen_toggle();
  
  /*activate updown button polling if current screen is anything but mainscreen, and turn it off if on mainscreen.
  IMPORTANT that this part of the code come after "screen_toggle" which updates the current_screen
  uses direction_btn_polling variable set to on or off to meet condition for if statement within polling loop().
   */
  
  if (current_screen == "main_screen") {
    direction_btn_polling = "OFF";
  }
  else {
    direction_btn_polling = "ON";
  }
  
}

void screen_toggle() {
  if (current_screen == "main_screen") {
    //is changing current_screen variable here redundant since when the screen function is called, it changes that variable within the function?
    current_screen = "alarm_set_hour_screen";
    alarm_set_hour_screen();

    auto_return_to_mainscreen_prev = millis();
  }
  else if (current_screen == "alarm_set_hour_screen") {
    current_screen = "alarm_set_min_screen";
    alarm_set_min_screen();

    auto_return_to_mainscreen_prev = millis();
  }
  else if (current_screen == "alarm_set_min_screen") {
    current_screen = "alarm_set_mode_screen";
    alarm_set_mode_screen();

    auto_return_to_mainscreen_prev = millis();
  }
  else if (current_screen == "alarm_set_mode_screen") {
    current_screen = "main_screen";
    main_screen();

    auto_return_to_mainscreen_prev = millis();
  }
}
