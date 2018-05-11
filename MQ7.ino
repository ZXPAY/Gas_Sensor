void MQ7_setup()
{
  pinMode(MQ7_pin, INPUT);
}
void Update_MQ7()
{
  int val;
  val=analogRead(MQ7_pin);//Read Gas value from analog 0
//  Serial.println(val,DEC);//Print the value to serial port
//  delay(100);
  MQ7_data[0] = val;
  
}

