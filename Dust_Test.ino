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

void dust_setup() {
  pinMode(dustpin,INPUT);
  starttime = millis();//get the current time;
}

void Update_Dust() {
  unsigned long duration;
  float ratio = 0;
  duration = pulseIn(dustpin, LOW);
// Serial.println(duration);
  lowpulseoccupancy = lowpulseoccupancy+duration;

  if ((millis()-starttime) >= sampletime_ms)//if the sampel time = = 30s
  {
    ratio = lowpulseoccupancy/(sampletime_ms*10.0);  // Integer percentage 0=&gt;100
    dust_data[0] = 1.1*pow(ratio,3)-3.8*pow(ratio,2)+520*ratio+0.62; // using spec sheet curve
   
//    Serial.print("  ,concentration = ");
//    Serial.print(concentration);
//    Serial.println(" pcs/0.01cf");
//    Serial.println("\n");
    lowpulseoccupancy = 0;
    starttime = millis();
  }
}
