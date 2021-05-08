void activate_alarm() {
  
  if (hit_count < max_hit_count){
    update_accel_data();
    serial_print_accel_data();
    serial_print_hit_data();
  
    //Big hit:
    if (accel_x>1700 or accel_x<-1800 or accel_y>1500 or accel_y<-2200) {
      big += 1;
      //beep when big hit is triggered
      digitalWrite(beeper_pin, LOW);
      delay(500);
      digitalWrite(beeper_pin, HIGH);

      /* extra feature for serial monitor to show which type of hit was triggered.
      if ((accel_x>7.9 or accel_x<-11) and (accel_y>9.3  or accel_y<-9.3)) {
        Serial.print(F("big accel_x and accel_y")); }
      else if (accel_x>7.9 or accel_x<-11) {
        Serial.print(F("big accel_x")); }
      else if (accel_y>8 or accel_y<-8) {
        Serial.print(F("big accel_y")); }
      */
    }        
    //Med hit:
    else if (accel_x>1400 or accel_x<-1500 or accel_y>1200 or accel_y<-1900) {
      med += 1;
       /*
      if (accel_x>5.5 or accel_x<-7.7) {
        Serial.print(F("med accel_x")); }
      else if (accel_y>7 or accel_y<-7) {
        Serial.print(F("med accel_y")); }
    */
    }
    //Small hit
    else if (accel_x>1250 or accel_x<-1350 or accel_y>1100 or accel_y<-1700) {
      small += 1;
        /*
      if (accel_x>4 or accel_x<-6) {
          Serial.print(F("small accel_x")); }
      else if (accel_y>5 or accel_y<-5) {
          Serial.print(F("small accel_y")); }
       */
    }
    else {
      Serial.println(F("Hits were below minimum on this iteration of the activate_alarm loop")); }
    
    hit_count = big*3 + med*2 + small;

    //turn off constant alarm sound once the bag is initially hit/triggered
    if (hit_count > max_hit_count) {
      Serial.println(F("first hit on bag"));
        digitalWrite(beeper_pin, HIGH); }
        
  }

  else {
  disable_alarm();
  reset_bag_hit_data();
  }
}
