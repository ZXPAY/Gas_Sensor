/*
 * CO 
 * https://www.detectcarbonmonoxide.com/co-health-risks/
 */
void MQ7_setup()
{
  
}
void Update_MQ7()
{
  MQ7_data[0] = mq7.getPPM();
  dataArray[3] = mq7.getPPM();
  if(dataArray[3] > 100) CO_Warning = 4;
  else if(dataArray[3] > 50) CO_Warning = 3;
  else if(dataArray[3] > 20) CO_Warning = 2;
  else if(dataArray[3] > 10 && dataArray[3] < 20) CO_Warning = 1;
  else CO_Warning = 0;
}

