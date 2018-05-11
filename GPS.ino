void GPS_setup() {
  // put your setup code here, to run once:
  SoftSerial.begin(9600);
}

void Update_GPS() {
  float latitude, longitude;   // 緯度, 經度
  unsigned long date, time, fix_age;
  // put your main code here, to run repeatedly:
  if(SoftSerial.available()){
     while (SoftSerial.available()){
      char c = SoftSerial.read();
      //Serial.write(c); // uncomment this line if you want to see the GPS data flowing
      if (gps.encode(c)) // Did a new valid sentence come in?
        gps_flag = true;
    }
  }
  if(gps_flag){
    gps.f_get_position(&latitude, &longitude, &age);
    latitude == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : latitude, 6;
    longitude == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : longitude, 6;
    gps.get_datetime(&date, &time, &fix_age);
//    Serial.print("Position: ");
//    Serial.print("latitude: ");Serial.print(latitude);Serial.print(" ");// print latitude
//    Serial.print("longitude: ");Serial.println(longitude); // print longitude
    gps_flag = false;
    gps_data[0] = latitude;
    gps_data[1] = longitude;
    
  }
}

