void MQ5_setup() {
    pinMode(MQ5_pin, INPUT);
}

void Update_MQ5() {
  static int CNT = 0, R0_sum;
  float sensor_volt;
  float RS_air; //  Get the value of RS via in a clear air
  float sensorValue;
  float RS_gas; // Get value of RS in a GAS
  float ratio; // Get ratio RS_GAS/RS_air
  
  sensorValue = analogRead(MQ5_pin);
  sensor_volt = sensorValue/1024*5.0;
    
  if(millis() - MQ5_Start_time > 120000 && (MQ5_flag == false)){
    RS_air = (5.0-sensor_volt)/sensor_volt; // omit *RL
    R0 = RS_air/6.5; // The ratio of RS/R0 is 6.5 in a clear air from Graph (Found using WebPlotDigitizer)
    R0_sum += R0;
    
    CNT += 1;
    if(CNT > 200){
      R0 = R0_sum / 200;
      MQ5_flag = true;
    }
  }
  else if(MQ5_flag == true){
    RS_gas = (5.0-sensor_volt)/sensor_volt; // omit *RL
    ratio = RS_gas/R0;  // ratio = RS/R0;
    // Need : RS_gas, R0
    // ratio is 6.5
    // pow(10, ((log10(ratio) - 0.75)/((-0.397))));
    MQ5_data[0] = pow(10, ((log10(ratio) - 0.75)/((-0.397))));
    MQ5_data[1] = R0;
  }
  else{
    MQ5_data[0] = 0;
    MQ5_data[1] = 0;
  }

//  Serial.print("time: ");
//  Serial.print(CNT);
//  Serial.print(" ,R0 = ");
//  Serial.print(R0);
//  Serial.print(", sensor_volt = ");
//  Serial.print(sensor_volt);
//  Serial.print(" ,RS_ratio = ");
//  Serial.print(RS_gas);
//  Serial.print(" ,Rs/R0 = ");
//  Serial.print(ratio);
//  Serial.print(" ,PPM");
//  Serial.println(MQ5_data[1]);
//  delay(100);

}
