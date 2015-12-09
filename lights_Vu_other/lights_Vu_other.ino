/* This was a UV Meter (via Headphone Output)
 * --------------
 * I got some code from this guy's site
 * Javier Lander
 * www.mrlndr.com
 * 
 * It's been heavliy modified since though. I know it's ugly, I just wanted it to work.
 * 
 * Eventually I'd like to add some pots for handling some of the variables.
 */

int pinArray[] = {2, 3, 4, 5, 6, 7, 11, 12}; //static array of pins used for output
int pinCount = sizeof(pinArray); //pretty self explanitory
int cycleArray[] = {2, 3, 4, 5, 6, 7, 11, 12}; // array used to cycle through pins so we never have the same bottom light
int count = 0;
int sensorValue = 0;
int countmax = 0;
int knockSensor = A0;
int sample; //stores the values added up to be averaged out
int bottom = 0;
int top = 12; //number of values to be averaged to kind of smooth out the flickering

const int minVal = 1; //the minimum value that will trigger the lights
const int led1Top = 8;
const int led2Top = 16;
const int led3Top = 24;
const int led4Top = 32;
const int led5Top = 40;
const int led6Top = 48;
const int led7Top = 53;
const int led8Top = 57; // the top value range for the last light

void setup(){
  // initialize the serial communications:
  Serial.begin(9600);

  // Set my I/O ports up
  for (count=0; count<pinCount; count++) {
    pinMode(pinArray[count], OUTPUT);
  }

}
void loop() {
  // read in the signal from the headphone jack.
  sensorValue = analogRead(knockSensor);

  // this gets the first light pin in the cycler
  int first = cycleArray[0];

  // turn off all the lights
  for (count=pinCount;count > 0;count--) {
   digitalWrite(pinArray[count-1], LOW);
  }

  // if we haven't gotten enough values for our average yet
  if(countmax < top){
    // add another
    sample += sensorValue;
    countmax++;
  }else{ // we've got enough of a sample so we can average it
    sensorValue = floor(sample / top);

    // reset the sample and counter
    sample = 0;
    countmax = 0;

    // cycle through our cycle array moving the low value to the top and everything else down one
    for(int cycleCount = 0; cycleCount < sizeof(cycleArray); cycleCount++){
      int next = cycleCount + 1;

      if(next >= sizeof(cycleArray)){
        cycleArray[cycleCount] = first;
      }else{
        cycleArray[cycleCount] = cycleArray[next];
      }
    }

  // turn on the first light 
  if (sensorValue < led1Top && sensorValue > minVal) {
    digitalWrite(cycleArray[0], HIGH);
  }
  // turn on the second light
  if (sensorValue < led2Top && sensorValue >= led1Top) {
    digitalWrite(cycleArray[1], HIGH);
  }
  // turn on the third light
  if (sensorValue < led3Top && sensorValue >= led2Top) {
    digitalWrite(cycleArray[2], HIGH);
  }
  // turn on the fourth light
  if (sensorValue < led4Top && sensorValue >= led3Top) {
    digitalWrite(cycleArray[3], HIGH);
  }
  // turn on the fifth light
  if (sensorValue < led5Top && sensorValue >= led4Top) {
    digitalWrite(cycleArray[4], HIGH);
  }
  // turn on the sixth light
  if (sensorValue < led6Top && sensorValue >= led5Top) {
    digitalWrite(cycleArray[5], HIGH);
  } 
  // turn on the seventh light
  if (sensorValue < led7Top && sensorValue >= led6Top) {
    digitalWrite(cycleArray[6], HIGH);
  }
  // turn on the eighth light
  if (sensorValue < led8Top && sensorValue >= led7Top) {
    digitalWrite(cycleArray[7], HIGH);
  } 

  // if our volume level is high enough turn on all the lights and hold them for a bit
  // doesn't always turn on all the lights for some reason.
  if (sensorValue > led8Top){
     Serial.println(sensorValue);
    for (count=0;count < pinCount;count++) {
     digitalWrite(pinArray[count], HIGH);
    }
    delay(500);
  }

     Serial.println(sensorValue);
  
  }

  // this can be used to mess with how long your lights are on
  //delay(5);
}
