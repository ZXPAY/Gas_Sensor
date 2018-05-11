#include <SPI.h>
#include <SD.h>
#include <SoftwareSerial.h>
#include <TinyGPS.h>
#include "Seeed_BME280.h"
#include <Wire.h>

BME280 bme280;

//SoftwareSerial mySerial(2, 3); // RX, TX   // CO2 sensor
SoftwareSerial SoftSerial(8, 9);  // GPS
TinyGPS gps;



boolean gps_flag = false;
unsigned long age;    // Fix  Date


byte cmd[9] = {0xFF,0x01,0x86,0x00,0x00,0x00,0x00,0x00,0x79};
unsigned char response[9]; 
//int ppm;
unsigned long ppm, th, tl, ppm2, ppm3 = 0;

#define pwmPin 5   // CO2 MH-Z19
#define dustpin 7   // dust sensor
#define chipSelect 4
#define MQ5_pin A0
#define MQ7_pin A1

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
unsigned long starttime;
unsigned long sampletime_ms = 2000;//sampe 30s&nbsp;;
unsigned long lowpulseoccupancy = 0;

unsigned long last_time = 0;
int time_save = 30000;   // 10 seconds

void setup() {
  // put your setup code here, to run once:
  
  SD_setup();
  dust_setup();
  BMP280_setup();
  MH_Z19_setup();
  GPS_setup();
  
}

void loop() {
  // put your main code here, to run repeatedly:

  Update_Dust();
  Update_MQ5();
  Update_BMP280();
  Update_MQ7();
  Update_GPS();
  Update_MH_Z19();


  if(millis() - last_time > time_save){
    Write_to_SD();
    last_time = millis();
  }
  
  
}
