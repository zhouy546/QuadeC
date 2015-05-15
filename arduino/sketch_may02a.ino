int relayPin = 9;
int valvePin = 10;
#define aqPin 0
#define gasPin 1

const int numReadings = 10;

int readings[numReadings];      // the readings from the analog input
int readIndex = 0;              // the index of the current reading
int total = 0;                  // the running total
int average = 0;                // the average


void setup (){
  Serial.begin(9600);
  pinMode(relayPin, OUTPUT);
  pinMode(valvePin, OUTPUT);
  
  for (int thisReading = 0; thisReading < numReadings; thisReading++)
    readings[thisReading] = 0;
}

void loop (){
  int aqVal = analogRead(aqPin);
 // int gasVal = analogRead(gasPin);
  //Serial.print(gasVal);
  //Serial.print(" ");
//  Serial.println(aqVal);
  delay(10);
  
  total= total - readings[readIndex];         
  // read from the sensor:  
  readings[readIndex] = aqVal; 
  // add the reading to the total:
  total= total + readings[readIndex];       
  // advance to the next position in the array:  
  readIndex = readIndex + 1;                    

  // if we're at the end of the array...
  if (readIndex >= numReadings)              
    // ...wrap around to the beginning: 
    readIndex = 0;                           

  // calculate the average:
  average = total / numReadings;         
  // send it to the computer as ASCII digits
  Serial.print(average); 
  Serial.print(" ");  
  delay(1);
    
//digitalWrite(relayPin, HIGH); 

  if (average >= 20) {
    digitalWrite(relayPin, HIGH);
  } else {
    digitalWrite(relayPin, LOW);
  }
  
  if (average < 50) {
    digitalWrite(valvePin, HIGH);
  } else {
    digitalWrite(valvePin, LOW);
  }
  
//  if (gasVal >= 15) {
//    digitalWrite(relayPin, HIGH);
//  } else {
//    digitalWrite(relayPin, LOW);
//  }
}
