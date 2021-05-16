void update_mpu_6050_data() {
  outputX = mpu6050.readAccelX();
  outputY = mpu6050.readAccelY();
  outputZ = mpu6050.readAccelZ();
}

void mpu_6050_initialize() {
    if (mpu6050.wakeup()) {
        Serial.println("wakeup success");
    } else {
        Serial.println("wakeup failed");
    }
}


void serial_print_mpu_6050_data() {
  Serial.print(F("AccelX: "));
  Serial.println(outputX);

  
  Serial.print(F("AccelY: "));
  Serial.println(outputY);

  Serial.print(F("AccelZ: "));
  Serial.println(outputZ);
}
