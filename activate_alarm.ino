void activate_alarm() {
  update_mpu_6050_data();
  
  if (hit_count < max_hit_count){
    serial_print_mpu_6050_data();
    serial_print_hit_data();
  
    //Big hit:
    if ( (outputX < 1.3) or (outputY < -9.6) or (outputY > 9.6) ){
      big += 1;
      //play sound effect when big hit is triggered
      //send_command_to_MP3_player(play_second_song, 6);

      /* extra feature for serial monitor to show which type of hit was triggered.
      if ((angle_roll_output>7.9 or angle_roll_output<-11) and (angle_pitch_output>9.3  or angle_pitch_output<-9.3)) {
        Serial.print(F("big angle_roll_output and angle_pitch_output")); }
      else if (angle_roll_output>7.9 or angle_roll_output<-11) {
        Serial.print(F("big angle_roll_output")); }
      else if (angle_pitch_output>8 or angle_pitch_output<-8) {
        Serial.print(F("big angle_pitch_output")); }
      */
    }        
    //Med hit:
    else if ( (outputX < 2.5) or (outputY < -8) or (outputY > 8) ) {
      med += 1;
       /*
      if (angle_roll_output>5.5 or angle_roll_output<-7.7) {
        Serial.print(F("med angle_roll_output")); }
      else if (angle_pitch_output>7 or angle_pitch_output<-7) {
        Serial.print(F("med angle_pitch_output")); }
    */
    }
    //Small hit
    else if ( (outputX < 7.2) or (outputY < -6.5) or (outputY > 6.5) ) {
      small += 1;
        /*
      if (angle_roll_output>4 or angle_roll_output<-6) {
          Serial.print(F("small angle_roll_output")); }
      else if (angle_pitch_output>5 or angle_pitch_output<-5) {
          Serial.print(F("small angle_pitch_output")); }
       */
    }
    else {
      Serial.println(F("Hits were below minimum on this iteration of the activate_alarm loop")); }
    
    hit_count = big*3 + med*2 + small;
    unweighted_hit_count = big + med + small;

    if (unweighted_hit_count == 1) {
      first_hit += 1;
      if (first_hit == 1) {
        Serial.println(F("first hit on bag"));
        send_command_to_MP3_player(play_third_song, 6); 
      }
    }

        
  }

  else {
  disable_alarm();
  reset_bag_hit_data();
  }
}
