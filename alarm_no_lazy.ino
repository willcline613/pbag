//things to implement for finished prototype:

//set big/med/small roll pitch triggers to reasonabable ammount
//mp3 audio output
//finished app template with print to bluetooth button
//bluetooth arduino code function

//cool features that could be added later on:

//progress bar for disabling alarm on lcd
//games(workouts)
//high scores
//cheating detector for games
//improved app design or extra features

//scrolling over current time on alarm time menu could prematurely activate alarm



#include <DS3231.h>
#include<Wire.h> // https://dronebotworkshop.com electronic level with gy521
#include <LiquidCrystal_I2C.h>
#include <EEPROM.h>



// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);

//set pin numbers
//beeper_pin changed for now, so it's not beeping during testing
int beeper_pin = 12;
int led_pin = 13;
int mid_btn_pin = 2;
int up_btn_pin = 5;
int down_btn_pin = 4;

String direction_btn_polling;

// Init the DS3231 using the hardware interface
DS3231  rtc(SDA, SCL);

//declare millis time interval and previous(timekeeping) variables

long update_time_and_timer_interval = 1100;
const unsigned long activate_alarm_interval = 500;
long debounce_interval = 200;    // the debounce time; increase if the output flickers
long auto_return_to_mainscreen_interval = 15000;
long auto_disable_alarm_interval = 300000;
long serial_info_update_interval = 5000;
long main_screen_update_interval = 60000;

long update_time_and_timer_prev = 0;
unsigned long activate_alarm_prev = 0;
long up_debounce_prev = 0;  // the last time the output pin was toggled
long mid_debounce_prev = 0;
long down_debounce_prev = 0;
long auto_return_to_mainscreen_prev = 0;
long main_screen_update_prev = 0;
long serial_info_update_prev = 0;
long auto_disable_alarm_prev = 0;


//declare other rtc variables
Time datetime_data;

int current_hour;
int current_min;
int current_sec;;
String current_time;
String current_alarm_time;

//keep track of which screen was last printed and last loop called
String current_screen = "main_screen";
String current_loop = "timer";

//set alarm time(will be retrieved from EEPROM)
int alarm_hour;
int alarm_min;

//alarm mode(will be retrieved from EEPROM)
int alarm_mode = 1;

String alarm_mode_string;

//ammount of seconds into the alarm minute until activate alarm is no longer triggered.
int min_sec_threshold = 5;

//declare gy521 variables
int16_t AcX, AcY, AcZ, Tmp, GyX, GyY, GyZ;
const int MPU = 0x69;

int x_offset = 80;
int y_offset = -1890;
int z_offset = 6650;

float roll;
float pitch;
float accel_x;
float accel_y;
float accel_z;

//declare activate_alarm variables
int hit_count = 0;
int max_hit_count = 120;
int big = 0;
int med = 0;
int small = 0;

void setup()
{
  // Setup Serial connection
  Serial.begin(115200);
  Serial.println(F("serial has begun"));

  serial_print_AM_or_PM(alarm_hour);

  // Initialize the rtc object
  rtc.begin();
  Serial.println(F("rtc begun"));

  //uncomment below to call set_datetime(hour,min,sec)/////////////////
  //set_datetime(4, 23, 55);

  //initialize current time values with rtc data
  update_time();

  //get most recent values for certain things from EEPROM storage
  //alarm_hour = 18;
  //alarm_min = 56;
  //alarm_mode = 1;
  //EEPROM_write_time();
  EEPROM_init();
  //let alarm_mode_string reflect the binary version of alarm_mode stored in EEPROM.
  update_alarm_mode_string();
  
   // set up the LCD's number of columns and rows:
  lcd.init();
  Serial.println(F("lcd initiated"));

  //set LCD backlight
  lcd.backlight();
  //call LCD main_screen to start
  main_screen();
  Serial.println(F("main lcd screen function called"));

  //sets beeper pin to output
  pinMode(beeper_pin, OUTPUT);    // sets the digital pin 11 as output
  //reset beeper to off at start of program in case it was on.
  digitalWrite(beeper_pin, HIGH);
  Serial.println(F("beeper pin set"));
  //sets led pin to output
  pinMode(led_pin, OUTPUT);
  digitalWrite(led_pin, LOW);


  // initialize the pushbutton pins as an input:
  pinMode(up_btn_pin, INPUT);
  pinMode(down_btn_pin, INPUT);
  pinMode(mid_btn_pin, INPUT);
  Serial.println(F("button pins initialized"));
  
  //sets up accelerometer stuff ??
  Wire.begin();

  //sequence of commands that awakens gy521 from sleep mode
  Wire.beginTransmission(MPU);  
  Wire.write(0x6B); // PWR_MGMT_1 register
  Wire.write(0); // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
  
  Serial.println(F("wire begin function called"));
}

void loop() {
  
  
 //update time less than every second
 if (millis() - update_time_and_timer_prev >= update_time_and_timer_interval) {
    update_time();

    update_time_and_timer_prev = millis();

    //call timer every split seccond right after time updates if that is the designated current loop.
    if (current_loop == "timer") {
      timer();
    }
    else {
      Serial.println(current_loop);
    }
 }

 if (millis() - serial_info_update_prev >= serial_info_update_interval) {
    serial_print_time_info();

    serial_info_update_prev = millis();
 }
 
 if ( (millis() - up_debounce_prev > debounce_interval) and (digitalRead(up_btn_pin) == HIGH) and (direction_btn_polling == "ON") ) {
    up_btn();

    Serial.println(F("Up btn pressed"));
    
    up_debounce_prev = millis();
 }
 
 if ( (millis() - mid_debounce_prev > debounce_interval) and (digitalRead(mid_btn_pin) == HIGH) ) {
    mid_btn();

    mid_debounce_prev = millis();
 }

  if ( (millis() - down_debounce_prev > debounce_interval) and (digitalRead(down_btn_pin) == HIGH) and (direction_btn_polling == "ON") ) {
    Serial.println(F("Down btn pressed"));
    down_btn();

    down_debounce_prev = millis();
 }
 

 
  if ( (millis() - activate_alarm_prev >= activate_alarm_interval) and (current_loop == "activate_alarm") ) {
    //activate alarm call every time activate_alarm_interval time passes.
    activate_alarm();

    activate_alarm_prev = millis();
  }



 if ( (millis() - main_screen_update_prev >= main_screen_update_interval) and (current_sec == 0) and (current_screen == "main_screen") ) {
    main_screen();
    Serial.print('\n');
    Serial.println(F("Main Screen updated"));

    main_screen_update_prev = millis();
 }

 if ( (millis() - auto_return_to_mainscreen_prev >= auto_return_to_mainscreen_interval) and (current_screen != "main_screen") ) {
    main_screen();
    Serial.println(F("Auto returned to mainscreen")); 
  
 }

 if ( (millis() - auto_disable_alarm_prev >= auto_disable_alarm_interval) and (current_loop == "activate_alarm") ) {
    Serial.println(F("Alarm auto disabled"));
    disable_alarm();
 }
}
