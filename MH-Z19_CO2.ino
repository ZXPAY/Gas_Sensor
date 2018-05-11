void MH_Z19_setup() {
  Serial.begin(9600);
  pinMode(pwmPin, INPUT);
}

void Update_MH_Z19() {
  Serial.write(cmd,9);
  Serial.readBytes(response, 9);
  unsigned int responseHigh = (unsigned int) response[2];
  unsigned int responseLow = (unsigned int) response[3];
  ppm = (256*responseHigh)+responseLow;

//  //CO2 via pwm
  do {
    th = pulseIn(pwmPin, HIGH, 1004000) / 1000;
    tl = 1004 - th;
    ppm2 = 2000 * (th-2)/(th+tl-4);
    ppm3 = 5000 * (th-2)/(th+tl-4);
  } while (th == 0);

  MH_Z19_data[0] = ppm;
  MH_Z19_data[1] = ppm3;

//Serial.print(responseHigh);
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

}

