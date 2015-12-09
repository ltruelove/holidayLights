/* UV Meter (via Headphone Output)
 * --------------
 *
 * @author: Javier Lander
 * @hardware: Javier Lander
 * www.mrlndr.com
 * twitter: @mrlndr
 */

int pinArray[] = {2, 3, 4, 5, 6, 7, 11, 12};
int pinCount = sizeof(pinArray);
int cycleArray[] = {2, 3, 4, 5, 6, 7, 11, 12};
int count = 0;
int timer = 10;
int sensorValue = 0;
int countmax = 0;
int knockSensor = A0;
int val = 0;
int statePin = LOW;
int THRESHOLD = 100;
int sample;
int bottom = 0;
int top = 12;

const int minVal = 1;
const int led1Top = 8;
const int led2Top = 16;
const int led3Top = 24;
const int led4Top = 32;
const int led5Top = 40;
const int led6Top = 48;
const int led7Top = 53;
const int led8Top = 57;

void setup(){
  // initialize the serial communications:
  Serial.begin(9600);
  
  for (count=0; count<pinCount; count++) {
    pinMode(pinArray[count], OUTPUT);
  }

}
void loop() {
  
  sensorValue = analogRead(knockSensor);

  int first = cycleArray[0];
     
  for (count=pinCount;count > 0;count--) {
   digitalWrite(pinArray[count-1], LOW);
  }
  
  if(countmax < top){
    sample += sensorValue;
    countmax++;
  }else{
    sensorValue = floor(sample / top);
    sample = 0;
    countmax = 0;

    for(int cycleCount = 0; cycleCount < sizeof(cycleArray); cycleCount++){
      int next = cycleCount + 1;

      if(next >= sizeof(cycleArray)){
        cycleArray[cycleCount] = first;
      }else{
        cycleArray[cycleCount] = cycleArray[next];
      }
    }

    
  if (sensorValue < led1Top && sensorValue > minVal) {
  digitalWrite(cycleArray[0], HIGH);
}
  if (sensorValue < led2Top && sensorValue >= led1Top) {
  digitalWrite(cycleArray[1], HIGH);
}
  if (sensorValue < led3Top && sensorValue >= led2Top) {
  digitalWrite(cycleArray[2], HIGH);
}
  if (sensorValue < led4Top && sensorValue >= led3Top) {
  digitalWrite(cycleArray[3], HIGH);
}
  if (sensorValue < led5Top && sensorValue >= led4Top) {
  digitalWrite(cycleArray[4], HIGH);
}
  if (sensorValue < led6Top && sensorValue >= led5Top) {
  digitalWrite(cycleArray[5], HIGH);
} 
  if (sensorValue < led7Top && sensorValue >= led6Top) {
  digitalWrite(cycleArray[6], HIGH);
}
  if (sensorValue < led8Top && sensorValue >= led7Top) {
  digitalWrite(cycleArray[7], HIGH);
} 

  if (sensorValue > led8Top){
     Serial.println(sensorValue);
    for (count=0;count < pinCount;count++) {
     digitalWrite(pinArray[count], HIGH);
    }
    delay(500);
  }

     Serial.println(sensorValue);
  
  }
  //delay(5);
}
