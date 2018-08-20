void MH_Z19_setup() {
  Serial2.begin(9600);
  pinMode(pwmPin, INPUT);
}

void Update_MH_Z19() {
//  Serial2.listen();

//  Serial2.write(cmd,9);
//  Serial2.readBytes(response, 9);
//  unsigned int responseHigh = (unsigned int) response[2];
//  unsigned int responseLow = (unsigned int) response[3];
//  ppm = (256*responseHigh)+responseLow;
  
//  Serial.print("0:");Serial.print((unsigned int) response[0]);Serial.print(",");
//  Serial.print("1:");Serial.print((unsigned int) response[1]);Serial.print(",");
//  Serial.print("High:");Serial.print(responseHigh);Serial.print(",");
//  Serial.print("Low:");Serial.print(responseLow);Serial.print(",");
//  Serial.print("4:");Serial.print((unsigned int) response[4]);Serial.print(",");
//  Serial.print("5:");Serial.print((unsigned int) response[5]);Serial.print(",");
//  Serial.print("6:");Serial.print((unsigned int) response[6]);Serial.print(",");
//  Serial.print("7:");Serial.print((unsigned int) response[7]);Serial.print(",");
//  Serial.print("8:");Serial.print((unsigned int) response[8]);Serial.print(",");
  Serial.print("ppm:");Serial.print(ppm);Serial.print(",");
  Serial.print("ppm3:");Serial.println(ppm3);
  
//  if(ppm<5000){
//    ppm3 = ppm;
//    }

  //CO2 via pwm
  do {
    th = pulseIn(pwmPin, HIGH, 1004000) / 1000;
    tl = 1004 - th;
    ppm2 = 2000 * (th-2)/(th+tl-4);
    ppm3 = 5000 * (th-2)/(th+tl-4);
  } while (th == 0);

  MH_Z19_data[0] = ppm;
  MH_Z19_data[1] = ppm3;

//  if(ppm>5000){
//    dataArray[4] = ppm3;
//    }
//  else if(ppm<5000){
//    dataArray[4] = ppm;
//    }
  dataArray[4] = ppm3;

  if(dataArray[4] > 2500) CO2_Warning = 4;
  else if(dataArray[4] > 1000) CO2_Warning = 3;
  else if(dataArray[4] > 800) CO2_Warning = 2;
  else if(dataArray[4] >= 600 && dataArray[4] < 800) CO2_Warning = 1;
  else CO2_Warning = 0;

//  Serial.print(responseHigh);
//  Serial.print(",");
//  Serial.print(responseLow);
//  Serial.print(",");
//  Serial.print(ppm);
//  Serial.print(",");
//  Serial.print(th);
//  Serial.print(",");
//  Serial.print(ppm2);
//  Serial.print(",");
//  Serial.println(ppm3);
//  delay(1000);
  Serial2.flush();
}

