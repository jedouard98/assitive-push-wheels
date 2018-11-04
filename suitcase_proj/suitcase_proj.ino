//byte speedBytesFromPhone[4] = {51, 51, -93, 64}; 
signed char speedBytesFromPhone[4] = {0, 0, -129, 67}; 


byte testBytes[4] = {0, 0, 0, 0}; 


//Motor 1 Control
int pwmMotor1Control = 9;
int motor1APin = 8;
int motor1BPin = 7;

//Motor 2 Control 
int pwmMotor2Control = 6;
int motor2APin = 5;
int motor2BPin = 4;

//Variable for storing received data
void setup() 
{
  Serial.begin(9600);  //Sets the data rate in bits per second (baud) for serial data transmission

//  // sets motor pins for motor 1
  pinMode(pwmMotor1Control, OUTPUT);  
  pinMode(motor1APin, OUTPUT);  
  pinMode(motor1BPin, OUTPUT);  

  // sets motor pins for motor 2
  pinMode(pwmMotor2Control, OUTPUT);  
  pinMode(motor2APin, OUTPUT);    
  pinMode(motor2BPin, OUTPUT);  
}

void loop()
{
  demoTest();

//  convertSpeedToBytesAndPrint(255);
  
  // read new information from iphone
//  readBluetoothData();

  //convert information from iphone to speed
//  float speed = convertPhoneBytesToSpeed();

  // drive straight
//  moveForward(speed);
  
  // read in information from stepper motors
//    readEncoderrData();

  //calculate appropriate speed
  //  calculateSpeed();

}

void demoTest() {
  Serial.println("starting...");
  moveForward(255);

//  delay(3000);

  readBluetoothData();

  int i = 0;
  while(i < 4)  // Send data only when you receive data:
  {
    Serial.println(speedBytesFromPhone[i++]);
    delay(500);
  }

  float a = convertPhoneBytesToSpeed();
  Serial.print("This is the float converted: ");
  Serial.println(a);

  if (convertPhoneBytesToSpeed() < 0) {
    delay(3000);
    stopMoving();
    while (true) {
      Serial.println("YO!");
    }
  }
}

void stopMoving() {
  digitalWrite(motor1APin, LOW);
  digitalWrite(motor1BPin, LOW);
  analogWrite(pwmMotor1Control, 0);

  digitalWrite(motor2APin, LOW);
  digitalWrite(motor2BPin, LOW);
  analogWrite(pwmMotor2Control, 0);

}

void moveForward(int speed) {
  digitalWrite(motor1APin, LOW);
  digitalWrite(motor1BPin, HIGH);
  analogWrite(pwmMotor1Control, speed);

  digitalWrite(motor2APin, HIGH);
  digitalWrite(motor2BPin, LOW);
  analogWrite(pwmMotor2Control, speed);
}

// Read information from phone if there is new information
void readBluetoothData() {
  int i = 0;
  while(Serial.available() > 0)  // Send data only when you receive data:
  {
    signed char singleByteFromPhone = Serial.read();
    Serial.println(singleByteFromPhone);
    speedBytesFromPhone[i++] = singleByteFromPhone;
    delay(1000);
  }
}

// Read information from stepper motors

// TODO: implement this!
void readEncoderData() {
}

void readEncoderAData() {
}

void readEncoderBData() {
}

// Read information from stepper motors
// TODO: implement this!
void convertSpeedToPWM() {
}
//

//void convertSpeedToBytesAndPrint(float speed) {
//  signed char *b = (signed char *)&speed;
//  for (int i = 0; i < 4; i++) {
//    int a = (signed char) b[i];
//    Serial.println(a);
//  } 
//  Serial.println();
//}

// Convert bytes to int
float convertPhoneBytesToSpeed() {
  //convert phone bytes to a float num
  float speed;
  memcpy(&speed, speedBytesFromPhone, sizeof(float));  
//  Serial.println(speed);
  return speed;
}
