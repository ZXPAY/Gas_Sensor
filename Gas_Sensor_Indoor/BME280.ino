/*
 * bme280_example.ino
 * Example sketch for bme280
 *
 * Copyright (c) 2016 seeed technology inc.
 * Website    : www.seeedstudio.com
 * Author     : Lambor, CHN
 * Create Time:
 * Change Log :
 *
 * The MIT License (MIT)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */


void BMP280_setup()
{
  if(!bme280.init()){
    //Serial.println("Device error!");
  }
}

void Update_BMP280()
{
  float pressure;

//  //get and print temperatures
//  Serial.print("Temp: ");
//  Serial.print(bme280.getTemperature());
//  Serial.println("C");//The unit for  Celsius because original arduino don't support speical symbols
//  
//  //get and print atmospheric pressure data
//  Serial.print("Pressure: ");
//  Serial.print(pressure = bme280.getPressure());
//  Serial.println("Pa");
//
//  //get and print altitude data
//  Serial.print("Altitude: ");
//  Serial.print(bme280.calcAltitude(pressure));
//  Serial.println("m");
//
//  //get and print humidity data
//  Serial.print("Humidity: ");
//  Serial.print(bme280.getHumidity());
//  Serial.println("%");
//  
//  Serial.println("\n");//add a line between output of different times.
//  delay(1000);
  
  bmp280_data[0] = bme280.getTemperature();
  pressure = bme280.getPressure();
  bmp280_data[1] = pressure;
  bmp280_data[2] = bme280.calcAltitude(pressure);
  bmp280_data[3] = bme280.getHumidity();
  
  dataArray[0] = bme280.getTemperature();
  dataArray[1] = bme280.getHumidity();
  dataArray[2] = bme280.getPressure();
}
