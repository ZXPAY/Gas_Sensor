void GPS_setup(){
  mySerial.begin(9600);
}

void Update_GPS(){
//  mySerial.begin(9600);
  mySerial.listen();
   if(mySerial.available()){
     while (mySerial.available()){
      char c = mySerial.read();
      Serial.write(c); // uncomment this line if you want to see the GPS data flowing
      if (gps.encode(c)) // Did a new valid sentence come in?
        gps_flag = true;
    }
  }
  if(gps_flag){
    gps.f_get_position(&latitude, &longitude, &age);
    latitude == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : latitude, 6;
    longitude == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : longitude, 6;
//    Serial.print("Position: ");
//    Serial.print("latitude: ");Serial.print(latitude);Serial.print(" ");// print latitude
//    Serial.print("longitude: ");Serial.println(longitude); // print longitude
    dataArray[7] = latitude;
    dataArray[8] = longitude;
    gps_flag = false;
  }
}

