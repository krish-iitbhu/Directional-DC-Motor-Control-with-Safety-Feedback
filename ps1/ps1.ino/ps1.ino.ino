const int clkPin = 2;
const int dtPin = 3;

volatile int encoderPos = 0;
int lastClkState;

const int potPin = A0;

const int switchPin1 = 4;
const int switchPin2 = 5;

const int nMosLeft = 6;
const int pMosLeft = 7;
const int pMosRight = 8;
const int nMosRight = 9;
 
const int currentSensePin = A2;
const float voltageAtZeroCurrent = 2.5; // V
const float sensitivity = 0.06;         // V per A (60 mV/A for WCS1500)
const float overcurrentThreshold = 5.0; // Amps, adjust as needed
 
float readCurrentWCS1500() {
  float voltage = analogRead(currentSensePin) * (5.0 / 1023.0);
  float current = (voltage - voltageAtZeroCurrent) / sensitivity;
  return current;
}
void readEncoder() {
  bool currentClk = digitalRead(clkPin);
  bool currentDt = digitalRead(dtPin);

  if (currentDt != currentClk) {
    encoderPos++;
    Serial.println(" clockwise");
  } else {
    encoderPos--;
      Serial.println(" counter clockwise");
  }
}

void setup() {

  pinMode(clkPin, INPUT);
  pinMode(dtPin, INPUT);
  
  Serial.begin(9600);
  lastClkState = digitalRead(clkPin);
  pinMode(potPin, INPUT);
  pinMode(switchPin1, INPUT_PULLUP);
  pinMode(switchPin2, INPUT_PULLUP);

  pinMode(pMosLeft, OUTPUT);
  pinMode(nMosLeft, OUTPUT);
  pinMode(pMosRight, OUTPUT);
  pinMode(nMosRight, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(clkPin), readEncoder, CHANGE);
}

void loop() {
  
  float motorCurrent = readCurrentWCS1500();

  if (abs(motorCurrent) > overcurrentThreshold) {
      // Stop
  digitalWrite(nMosLeft, LOW);
  digitalWrite(pMosLeft, HIGH);
  digitalWrite(nMosRight, LOW);
  digitalWrite(pMosRight, HIGH);

    Serial.println("Safety Cutoff: Overcurrent Detected!");
   
    
  }
  static int lastReported = 0;
  
float angle = (encoderPos * 360.0) /(2* 24);//as countsPerRevolution of this dc motor is 24
  if (lastReported != encoderPos) {
    Serial.print("Position: ");
    Serial.print(encoderPos);
     Serial.print(",angle: ");
     Serial.print(angle);

    lastReported = encoderPos;
  }



  // Read potentiometer and convert to PWM (0-255)
  int potValue = analogRead(potPin);
  int speedPWM = map(potValue, 0, 1023, 0, 255);

  // Read switch inputs
  bool sw1 = digitalRead(switchPin1);
  bool sw2 = digitalRead(switchPin2);

if (sw1 == LOW && sw2 == HIGH) {
  // Clockwise Rotation
  analogWrite(nMosRight, speedPWM);
  digitalWrite(pMosLeft, LOW);    // Turn ON via inverter
  digitalWrite(nMosLeft, LOW);   // OFF
  digitalWrite(pMosRight, HIGH); } // OFF

 else if (sw1 == HIGH && sw2 == LOW) {
  // Counter-Clockwise Rotation
  analogWrite(nMosLeft, speedPWM);
  digitalWrite(pMosRight, LOW);   // Turn ON via inverter
  digitalWrite(nMosRight,LOW );    // OFF
  digitalWrite(pMosLeft, HIGH);   // OFF
} 
else {
  // Stop
  digitalWrite(nMosLeft, LOW);
  digitalWrite(pMosLeft, HIGH);
  digitalWrite(nMosRight, LOW);
  digitalWrite(pMosRight, HIGH);
}



}
