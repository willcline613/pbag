void disable_alarm() {
  //how do the beepers in this case translate to music? IDK
  //would this small delay be problematic? Won't really need it when replace music anyways.
  //turns on alarm for 5 seconds at end to indicate it has ended.
  digitalWrite(beeper_pin, LOW);
  delay(3500);
  digitalWrite(beeper_pin, HIGH);

  //print final hit breakdown/data
  serial_print_hit_data();
  
  //beeper oficially off
  digitalWrite(beeper_pin, HIGH);
  //led off also
  digitalWrite(led_pin, LOW);

  //reset current loop to timer();
  current_loop = "timer";
}

void serial_print_hit_data() {;
  Serial.print('\n');
  Serial.println(F("Hit-data breakdown:"));
  Serial.print(F("hit count: "));
  Serial.println(hit_count);
  Serial.print(F("big: "));
  Serial.println(big);
  Serial.print(F("med: "));
  Serial.println(med);
  Serial.print(F("small: "));
  Serial.println(small);
}

void reset_bag_hit_data() {
  //Where do I want the reset? hit_count must't interfere with gating entree to this "current_loop"
  //could implement high score feature for big hits or within minigames that be saved to EEPROM
  hit_count = 0;
  big = 0;
  med = 0;
  small = 0;
}
