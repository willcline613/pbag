void disable_alarm() {
  //stop currently playing mp3
  send_command_to_MP3_player(pause, 4);
  
  //print final hit breakdown/data
  serial_print_hit_data();
  
  //reset current loop to timer();
  current_loop = "timer";

  //call main screen function to reset to main screen
  main_screen();
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
  //could implement high score feature for big hits or within minigames that be saved to EEPROM
  hit_count = 0;
  unweighted_hit_count = 0;
  big = 0;
  med = 0;
  small = 0;

  hit_count_progress_bar_ammount = 0;

  first_hit = 0;

  
}
