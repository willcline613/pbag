void update_accel_data() {
    Serial.print('\n');
    Serial.print("accelerometer update called");
    Serial.print('\n');
    Wire.beginTransmission(MPU);
    Wire.write(0x3B);
    
    //supposed to format accel data to +/- 2G
    Wire.write(0x1B);
    Wire.write(0b00000000);
    
    Wire.endTransmission(false);
    Wire.requestFrom(MPU,14,true);  
    AcX=Wire.read()<<8|Wire.read();    
    AcY=Wire.read()<<8|Wire.read();  
    AcZ=Wire.read()<<8|Wire.read();

    accel_x = AcX + x_offset;
    accel_y = AcY + y_offset;
    accel_z = AcZ + z_offset;

    roll = atan2(accel_y , accel_z) * 57.3;
    pitch = atan2((- accel_x) , sqrt(accel_y * accel_y + accel_z * accel_z)) * 57.3;
}

void serial_print_accel_data() {
  Serial.print(F("Roll: "));
  Serial.println(angle_roll_output);

  
  Serial.print(F("Pitch: "));
  Serial.println(angle_pitch_output);
}
