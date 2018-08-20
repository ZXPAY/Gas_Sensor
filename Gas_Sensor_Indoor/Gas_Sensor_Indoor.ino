#include <SPI.h>
#include <SD.h>
#include <SoftwareSerial.h>
#include "Seeed_BME280.h"
#include <Wire.h>
#include <Streaming.h>
#include "MQ7.h"
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <Timer.h>

Timer dust;

//Timer sendUplinkCmd_Clock;

#define Send_BT_Confidence 3

// Set the LCD address to 0x27 for a 16 chars and 2 line display
// 0x27, 0x3f => different LCD
LiquidCrystal_I2C lcd(0x27, 16, 2);

//open flag
boolean opf = false;

// GPS
#include <TinyGPS.h>
TinyGPS gps;
SoftwareSerial mySerial(10,11);
boolean gps_flag = false;
float latitude, longitude;   // 緯度, 經度
unsigned long age;    // Fix  Date

// Buzzer Define
#define Buzzer_pin 8

// H Bridge
#define HB1_pin 6
#define HB2_pin 7
#define HB3_pin 9

BME280 bme280;

byte cmd[9] = {0xFF,0x01,0x86,0x00,0x00,0x00,0x00,0x00,0x79};
unsigned char response[9]; 
//int ppm;
unsigned long ppm, th, tl, ppm2, ppm3 = 0;

#define pwmPin 5   // CO2 MH-Z19
//#define dustpin 7   // dust sensor
#define chipSelect 4
#define MQ5_pin A0
#define MQ7_pin A1

MQ7 mq7(MQ7_pin,5.0);

float bmp280_data[4] = {0,0,0,0};
float dust_data[1] = {0};
float gps_data[2] = {0,0};
float MH_Z19_data[2] = {0,0};
float MQ5_data[2] = {0,0}; 
float MQ7_data[1] = {0};

unsigned long MQ5_Start_time = millis();
boolean MQ5_flag = false;
float R0; 

// Dust Sensor
//unsigned long starttime;
//unsigned long sampletime_ms = 2000;//sampe 30s&nbsp;;
//unsigned long lowpulseoccupancy = 0;
SoftwareSerial DustSerial(12,13);
int incomeByte[7];
int data;
int z=0;
int sum;
float V0;
float concentration = 0.0;
float DustC = 0.0; 
float DustAC = 0.0; 
float Dust_Data[30] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
int Data_count = 0;
unsigned long Dust_Start_time;
boolean Dust_flag = false;


unsigned long last_time = 0;
unsigned int time_save = 6000;   // 60 seconds

// Lora Setup
uint16_t DLCount = 0;
//uint16_t ULCount01 = 0;
//uint16_t ULCount02 = 0;
uint16_t ULCount[] = {0,0,0,0,0,0,0,0,0};
unsigned long Lora_Sending_Time;
int lora_cnt = 0;


float dataArray[9] = {0,0,0,0,0,0,0,0,0};
uint8_t txAckArray[64];
boolean classModeLock = false;
boolean joinNetLock = false;
boolean startLock = false;
char* DataType[] = {"TS:","HS:","AS:","CS:","IS:","LS:","MS:","DS:","NS:"};


// Print data time define (LCD)
unsigned long t1;
unsigned long tt;
int LCD_flag = 0;

// 警戒宣告，分為三個警告
byte PM_Warning = 0;   // 50, 100, 150
byte CO_Warning = 0;   // 35, 50, 125
byte CO2_Warning = 0;  // 700, 1000, 2500
byte LPG_Warning = 0;  // 1000, 1500, 2500


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
//  SD_setup();
  dust_setup();
  BMP280_setup();
//  MQ5_setup();
//  MH_Z19_setup();
  Lora_setup();
  GPS_setup();
  dust.every(5000,Update_Dust);
//  tgps.every(60000, Update_GPS);
//  BT_setup();
  Buzzer_setup();
  HBridge_setup();

  lcd.begin();
  lcd.backlight();
  Silence();
  Serial.println("Setup OK !");
}

void loop() {
  // put your main code here, to run repeatedly:
  dust.update();
//  Update_Dust();
//  Update_MQ5();
  Update_BMP280();
//  Update_MQ7();
//  Update_MH_Z19();
  Update_GPS();
//  tgps.update();
  Check_Warning();   // whether open the fan or window

if(millis() - t1 > 5000){
  if(LCD_flag==0) LCD_flag=1;
  else if(LCD_flag==1) LCD_flag=2;
  else if(LCD_flag==2) LCD_flag=0;
  t1 = millis();
  lcd.clear();
}

if(millis() - tt > 1000){
  Serial.print("TS:"); Serial.print(dataArray[0]);Serial.print(",");
  Serial.print("HS:"); Serial.print(dataArray[1]);Serial.print(",");
  Serial.print("AS:"); Serial.print(dataArray[2]);Serial.print(",");
  Serial.print("CS:"); Serial.print(dataArray[3]);Serial.print(",");
  Serial.print("IS:"); Serial.print(dataArray[4]);Serial.print(",");
  Serial.print("LS:"); Serial.print(dataArray[5]);Serial.print(",");
  Serial.print("MS:"); Serial.print(dataArray[6]);Serial.print(",");
  Serial.print("opf:"); Serial.println(opf);
//  Serial.print("MS:"); Serial.println(dataArray[6]);
  Serial.println("=============================================");
  tt = millis();
}


  switch(LCD_flag){
    case 0:
        lcd.setCursor(0,0); lcd.print("TS:"); lcd.print(dataArray[0]);
        lcd.setCursor(8,0); lcd.print("HS:"); lcd.print(dataArray[1]);
        lcd.setCursor(0,1); lcd.print("AS:"); lcd.print(dataArray[2]);
    break;
    case 1:
        lcd.setCursor(0,0); lcd.print("CS:"); lcd.print(dataArray[3]);
        lcd.setCursor(8,0); lcd.print("IS:"); lcd.print(dataArray[4]);
        lcd.setCursor(0,1); lcd.print("LS:"); lcd.print(dataArray[5]);
        lcd.setCursor(8,1); lcd.print("MS:"); lcd.print(dataArray[6]);
    break;
    case 2:
        lcd.setCursor(0,0); lcd.print("GPS:"); lcd.print(dataArray[7]);
        lcd.print(","); lcd.print(dataArray[8]);
        lcd.setCursor(0,1); lcd.print("PC2L:");
        lcd.print(PM_Warning); lcd.print(",");
        lcd.print(CO_Warning); lcd.print(",");
        lcd.print(CO2_Warning); lcd.print(",");
        lcd.print(LPG_Warning);

    break;
    default:
        Serial.println("No LCD flag found ...");
    break;
  }


  if(millis() - last_time > time_save){
//    Write_to_SD();
    last_time = millis();
  }
  
  sendUplinkCmd();
    if(classModeLock){
      if (Serial1 .available()) {
          delay(5);
          getMsg();
      }
    }

//    Serial.println("Run ...");
  
}
