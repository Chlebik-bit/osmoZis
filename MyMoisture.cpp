/**The MIT License (MIT)

Copyright (c) 2019 by Radim Keseg

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "MyMoisture.h"

#include "Arduino.h" //not sure why but here it is needed

#define MEASURE_COUNT 5
float MyMoisture::measure(){
   Serial.print("Moisture: ");
   float value_moisture = 0;
   for(int i=0; i<MEASURE_COUNT; i++){
     digitalWrite(MEASURING, LOW);
     value_moisture+= analogRead(SENSE_PIN);
     delay(50);
   }
   value_moisture/=MEASURE_COUNT;

//experimentally checked range
   if(value_moisture<MIN_RANGE) value_moisture=MIN_RANGE;
   if(value_moisture>MAX_RANGE) value_moisture=MAX_RANGE;
   value_moisture = (1.0f-(value_moisture - MIN_RANGE)/(MAX_RANGE - MIN_RANGE))*100;
   
   Serial.print(value_moisture);Serial.println("%");
   delay(100);
   digitalWrite(MEASURING, HIGH);

   return last_mois = value_moisture;
}

float MyMoisture::getLastMeasured(){
  return last_mois;
}

