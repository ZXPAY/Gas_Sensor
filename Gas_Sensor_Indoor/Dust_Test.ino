// Watch video here: https://www.youtube.com/watch?v=a8r4CeQopfY

/* 
 Connection:
 
 JST Pin 1 (Black Wire)  => Arduino GND
 JST Pin 3 (Red wire)    => Arduino 5VDC
 JST Pin 4 (Yellow wire) => Arduino Digital Pin 8

 Green Led connected to Arduino D7
 Yellow Led connected to Arduino D6
 Red Led connected to Arduino D5
 
 
Dust Sensor possible application:
- Applications of customer
- Air quality sensor
- Dustlessness workshop
- Cigarette detector
*/

/*
Sensor is to create Digital (Lo Pulse) output to Particulate Matters (PM). Lo Pulse Occupancy time (LPO time) is in proportion
to PM concentration. The output is for PM whose size is around 1 micro meter or larger. We can use the sensor to detect the dust in clean room.
Minimum detect particle: 1um
http://www.seeedstudio.com/wiki/Grove_-_Dust_Sensor
 Grove - Dust Sensor Demo v1.0
 Interface to Shinyei Model PPD42NS Particle Sensor
 Program by Christopher Nafis 
 Written April 2012
 
 http://www.seeedstudio.com/depot/grove-dust-sensor-p-1050.html
 http://www.sca-shinyei.com/pdf/PPD42NS.pdf
 */
// <20000  少灰塵
// 20000   多灰塵
// 315000  超多灰塵

// 
// 0.01cf=283mL

void dust_setup() {
  DustSerial.begin(2400);
  Dust_Start_time = millis();
  }

void Update_Dust() {
   Get_DustData();
//  Serial.print("Data_count:");Serial.print(Data_count);Serial.println();
  if(millis() - Dust_Start_time > 2000){
    Data_count+=1;
    Serial.print("Data_count:");Serial.print(Data_count);Serial.println();
    if(Data_count <= 30){
      Serial.println("1");
      Dust_Data[Data_count-1] = concentration;
      Dust_Data[Data_count-1] = V0;
      for(int i=0;i<30;i++){
          Serial.print(Dust_Data[i]);
          Serial.print("|");
          DustC += Dust_Data[i];
      }
      Serial.println();
      
      DustAC =  DustC/30;
      DustAC = 285.71*DustAC;
      dataArray[6] = DustAC;
      Serial.print("DustC:");Serial.print(DustC);Serial.println();
      Serial.print("DustAC:");Serial.print(DustAC);Serial.println();
      DustC = 0;
      DustAC = 0;
    }
    else if(Data_count > 30){
      Serial.println("2");
      for(int j=0;j<29;j++){
        Dust_Data[j] = Dust_Data[j+1];
        Serial.print(Dust_Data[j]);
        Serial.print("|");
        DustC += Dust_Data[j];
//        if(j==28){
//          Dust_Data[29] = V0;}
      }
  //    Dust_Data[29] = concentration;
      Dust_Data[29] = V0;
      Serial.print(Dust_Data[29]);
      Serial.println();
      DustC += Dust_Data[29];
      DustAC =  DustC/30;
      DustAC = 285.71*DustAC;
      dataArray[6] = DustAC;
      Serial.print("DustC:");Serial.print(DustC);Serial.println();
      Serial.print("DustAC:");Serial.print(DustAC);Serial.println();
      DustC = 0;
      DustAC = 0; 
      }
    Dust_Start_time = millis();
    
//    dataArray[6] = dust_data[0];
    if(dataArray[6] > 250) PM_Warning = 4;
    else if(dataArray[6] > 200) PM_Warning = 3;
    else if(dataArray[6] > 120) PM_Warning = 2;
    else if(dataArray[6] > 50 && dataArray[6] <120) PM_Warning = 1;
    else PM_Warning = 0;
    
    }
  
  }

void Get_DustData(){
  DustSerial.listen();
  delay(50);
    if (DustSerial.available()){
      
      data=DustSerial.read();
      if(data == 170){
        z=0;
        incomeByte[z]=data;
      }
      else{
        z++;
        incomeByte[z]=data;
      }
  
      if(z==6){
        sum=incomeByte[1]+ incomeByte[2]+ incomeByte[3] + incomeByte[4];
        if(incomeByte[5]==sum && incomeByte[6]==255){
          for(int k=0;k<7;k++){
          } 
          float vo=(incomeByte[1]*256.0+incomeByte[2])/1024.0*5.00;
          V0 = vo;
          float c=vo*700;
          concentration = c;
            }
          else{
            z=0;
            DustSerial.flush();
            data='/0';
            for(int m=0;m<7;m++){
              incomeByte[m]=0;
            }
           }
          z=0;
          }
    }
}

//void dust_setup() {
//  pinMode(dustpin,INPUT);
//  starttime = millis();//get the current time;
//}

//void Update_Dust() {
//  unsigned long duration;
//  float ratio = 0;
//  duration = pulseIn(dustpin, LOW);
//// Serial.println(duration);
//  lowpulseoccupancy = lowpulseoccupancy+duration;
//
//  if ((millis()-starttime) >= sampletime_ms)//if the sampel time = = 30s
//  {
//    ratio = lowpulseoccupancy/(sampletime_ms*10.0);  // Integer percentage 0=&gt;100
//    dust_data[0] = 1.1*pow(ratio,3)-3.8*pow(ratio,2)+520*ratio+0.62; // using spec sheet curve unit:pcs/0.01cf
//    dust_data[0] = dust_data[0]*0.0015593735;   // unit:ug/m3
//   
////    Serial.print("  ,concentration = ");
////    Serial.print(dust_data[0]);
////    Serial.println(" pcs/0.01cf");
////    Serial.println("\n");
//    lowpulseoccupancy = 0;
//    starttime = millis();
//    dataArray[6] = dust_data[0];
//    if(dataArray[6] > 30) PM_Warning = 4;
//    else if(dataArray[6] > 15) PM_Warning = 3;
//    else if(dataArray[6] > 10) PM_Warning = 2;
//    else if(dataArray[6] > 3 && dataArray[6] <10) PM_Warning = 1;
//    else PM_Warning = 0;
//  }
//}
