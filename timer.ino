void timer() {
  if ( (current_hour == alarm_hour) and (current_min == alarm_min) and (current_sec <= min_sec_threshold)  ) {
      //call alarm function if alarm time matches current time
      Serial.println(F("current time matches alarm time."));
      //Serial.flush();
      //Serial.begin(9600);
      if (hit_count < max_hit_count) {
        //reset auto disable alarm variable right before start of when current_loop begins
        auto_disable_alarm_prev = millis();
        //turn on alarm song to be turned off later after first bag hit
        send_command_to_MP3_player(play_first_song, 6);
        //turn on led pin to be turned off later
        digitalWrite(led_pin, HIGH);
        current_loop = "activate_alarm";
        current_screen = "progress_bar_screen";
        //call calibration of mpu right as alarm starts right before it starts to read out roll and pitch data.
        mpu_6050_initialize();
      }
   }
}
