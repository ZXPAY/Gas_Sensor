/*
  SD card datalogger

 This example shows how to log data from three analog sensors
 to an SD card using the SD library.

 The circuit:
 * analog sensors on analog ins 0, 1, and 2
 * SD card attached to SPI bus as follows:
 ** MOSI - pin 11
 ** MISO - pin 12
 ** CLK - pin 13
 ** CS - pin 4 (for MKRZero SD: SDCARD_SS_PIN)

 created  24 Nov 2010
 modified 9 Apr 2012
 by Tom Igoe

 This example code is in the public domain.

 */


void SD_setup() {
  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    return;
  }
  //Serial.println("card initialized.");
}

void Write_to_SD() {
  String dataString = "";
  String dataString2 = "";
  File dataFile = SD.open("GasTest.txt", FILE_WRITE);

  // if the file is available, write to it:
  dataString += String(millis());

  dataString += ",Data,";
  for(int i=0;i<9;i++){
   dataString += String(dataArray[i]);
   dataString += ",";  
  }
  
//  dataString += ",BMP280,";
//  for(int i=0;i<4;i++){
//   dataString += String(bmp280_data[i]);
//   dataString += ",";  
//  }
//  
//  dataString += "dust,";
//  dataString += dust_data[0];
//  dataString += ","; 
//
//  dataString += "gps,";
//  for(int i=0;i<2;i++){
//   dataString += String(gps_data[i]);
//   dataString += ",";  
//  }
//  
//  dataString += "MH,";
//  dataString += MH_Z19_data[0];
//  dataString += ","; 
//  dataString += MH_Z19_data[1];
//  dataString += ","; 
//
//  dataString += "MQ5,";
//  dataString += MQ5_data[0];
//  dataString += ","; 
//  dataString += MQ5_data[1];
//  dataString += ","; 
//
//  dataString += "MQ7,";
//  dataString += MQ7_data[0];
//  dataString += ",";   
  
  dataString += "Warning,";
  dataString += String(PM_Warning);
  dataString += ",";   
  dataString += String(CO_Warning);
  dataString += ",";   
  dataString += String(CO2_Warning);
  dataString += ",";   
  dataString += String(LPG_Warning);
  dataString += ",";   
  
  if (dataFile) {
    dataFile.println(dataString);
    dataFile.close();
    Serial.println(dataString);
  }
  // if the file isn't open, pop up an error:
  else {
    Serial.println("error opening...");
  }
}









