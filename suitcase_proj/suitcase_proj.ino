// Communication between phone and bluetooth
signed char speedBytesFromPhone[4] = {0, 0, 0, 0}; 

bool movementStopped = false;

//

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
  Ser ial.begin(9600);  //Sets the data rate in bits per second (baud) for serial data transmission

//  // sets motor pins for motor 1
  pinMode(pwmMotor1Control, OUTPUT);  
  pinMode(motor1APin, OUTPUT);  
  pinMode(motor1BPin, OUTPUT);  

  // sets motor pins for motor 2
  pinMode(pwmMotor2Control, OUTPUT);  
  pinMode(motor2APin, OUTPUT);    
  pinMode(motor2BPin, OUTPUT);  

  Serial.println("starting...");
  moveForward(180);

  delay(1000);
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
  readBluetoothData();

  float speedMPH = convertPhoneBytesToSpeed();
  int signal = (int) convertPhoneBytesToSpeed();
  
  Serial.print("The signal is....");
  Serial.print(signal);
  Serial.println("!!!!");
   
  switch (signal) {
    case -1:
      Serial.println("STOP MOVING!!!");
      stopMoving();
      break;
    case -2:
      Serial.println("YOU CAN START MOVING!!!");
      // for the demo
      moveForward(255);
      movementStopped = false;
      break;
    case -3:
      // TODO: implement this
      Serial.println("STOP MOVING???!!!");
      stopMoving();
      break;
     case -4:
      //TODO: implement this
      Serial.println("YOU CAN START MOVING???!!!");
      movementStopped = false;
      break;
    default:
      Serial.println("Maybe I'll move?");
      if (!movementStopped) {
        Serial.println("Yep!!");
//        float speed = convertSpeedToPWM(speedMPH);
        moveForward(255);
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

  movementStopped = true;
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
  int i = 3;
  
  while(Serial.available() > 0)  // Send data only when you receive data:
  {
    Serial.println("READING FROM PHONE");
    signed char singleByteFromPhone = Serial.read();
    Serial.println(singleByteFromPhone);
    speedBytesFromPhone[i--] = singleByteFromPhone;
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
float convertSpeedToPWM(float speed) {
  return 255.0;
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
