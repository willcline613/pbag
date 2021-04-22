void timer() {
  if ( (current_hour == alarm_hour) and (current_min == alarm_min) and (current_sec <= min_sec_threshold)  ) {
      //call alarm function if alarm time matches current time
      Serial.println(F("current time matches alarm time."));
      //Serial.flush();
      //Serial.begin(9600);
      if (hit_count < 30) {
        current_loop = "activate_alarm";
        //reset auto disable alarm variable right at start of when current_loop begins
        auto_disable_alarm_prev = millis();
        //turn on beeper to be turned off later 
        digitalWrite(beeper_pin, LOW);
      }
   }
}
