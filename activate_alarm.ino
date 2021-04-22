void activate_alarm() {
  
  if (hit_count < max_hit_count){
    update_accel_data();
    serial_print_accel_data();
    serial_print_hit_data();
  
    //Big hit:
    if (pitch>7.9 or pitch<-11 or roll>9.3 or roll<-9.3) {
      big += 1;
      //beep when big hit is triggered
      digitalWrite(beeper_pin, LOW);
      delay(500);
      digitalWrite(beeper_pin, HIGH);
      
      if ((pitch>7.9 or pitch<-11) and (roll>9.3  or roll<-9.3)) {
        Serial.print(F("big pitch and roll")); }
      else if (pitch>7.9 or pitch<-11) {
        Serial.print(F("big pitch")); }
      else if (roll>8 or roll<-8) {
        Serial.print(F("big roll")); }
    }        
    //Med hit:
    else if (pitch>5.5 or pitch<-7.7 or roll>7 or roll<-7) {
      med += 1;
        
      if (pitch>5.5 or pitch<-7.7) {
        Serial.print(F("med pitch")); }
      else if (roll>7 or roll<-7) {
        Serial.print(F("med roll")); }
    }
    //Small hit
    else if (pitch>4 or pitch<-6 or roll>5 or roll<-5) {
      small += 1;
        
      if (pitch>4 or pitch<-6) {
          Serial.print(F("small pitch")); }
      else if (roll>5 or roll<-5) {
          Serial.print(F("small roll")); }
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
  //call lazy loop to reset looping.
  timer();
  }
}
