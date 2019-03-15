/* 
 * This file is part of the VolumeWanager project (https://github.com/ErwanDouaille/VolumeWanager).
 * Copyright (c) 2018 Douaille Erwan.
 * 
 * This program is free software: you can redistribute it and/or modify  
 * it under the terms of the GNU General Public License as published by  
 * the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but 
 * WITHOUT ANY WARRANTY; without even the implied warranty of 
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU 
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License 
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

const int nbPotentiometer = 4;
int outputValues[nbPotentiometer];

void setup() {
  Serial.begin(9600);
}

void loop() {
  for(int i = 0; i < nbPotentiometer; i++)
  {
    int sensorValue = analogRead(i);
    int outputValue = map(sensorValue, 0, 1023, 0, 100);
    if (outputValue > outputValues[i] + 1 || outputValue < outputValues[i] - 1 )
    {
      outputValues[i] = outputValue;
      Serial.print("id=");
      Serial.print(i);
      Serial.print(" value=");
      Serial.println(outputValue);    
    } 
  }
  delay(100);
}
