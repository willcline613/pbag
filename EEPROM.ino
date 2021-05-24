void EEPROM_init() {
  //alarm hour address is 0
  alarm_hour = EEPROM.read(0);
  
  //alarm min address is 1
  alarm_min = EEPROM.read(1);

  //alarm mode address is 2
  alarm_mode = EEPROM.read(2);
}

void EEPROM_write_time() {
  EEPROM.write(0, alarm_hour);
  EEPROM.write(1, alarm_min);
  EEPROM.write(2, alarm_mode);
}
