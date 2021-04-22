void update_accel_data() {
    Serial.print('\n');
    Serial.print("accelerometer update called");
    Serial.print('\n');
    Wire.beginTransmission(MPU);
    Wire.write(0x3B);  
    Wire.endTransmission(false);
    Wire.requestFrom(MPU,12,true);  
    AcX=Wire.read()<<8|Wire.read();    
    AcY=Wire.read()<<8|Wire.read();  
    AcZ=Wire.read()<<8|Wire.read();

    accel_x = AcX/x_multiplier;
    accel_y = AcY/y_multiplier;
    accel_z = AcZ/z_multiplier;

    //delete later
    Serial.print(accel_x);

    roll = atan2(accel_y , accel_z) * 57.3;
    pitch = atan2((- accel_x) , sqrt(accel_y * accel_y + accel_z * accel_z)) * 57.3;

    //delete later
    Serial.print(roll);
}

void serial_print_accel_data() {
  Serial.print(F("Roll: "));
  Serial.println(roll);

  
  Serial.print(F("Pitch: "));
  Serial.println(pitch);
}
