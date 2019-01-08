//byte speedBytesFromPhone[4] = {51, 51, -93, 64}; 
signed char speedBytesFromPhone[4] = {0, 0, -128, -68}; 


byte testBytes[4] = {0, 0, 0, 0}; 

//Algorithm details
float WEIGHT_OF_PHONE = .8;
float WEIGHT_OF_ENCODERS = .2;
float lastMillis = 0;

int encoderLastPos = 0;
int encoderCurrentPos = 0;

//Motor 1 Control
int pwmMotor1Control = 9;
int motor1APin = 8;
int motor1BPin = 7;

//Encoder 1 Read
int encoder1PinA = 13;
int encoder1PinB = 12;
int encoder1PinALast = LOW;
int encoder1Pos = 0;

//Motor 2 Control 
int pwmMotor2Control = 6;
int motor2APin = 5;
int motor2BPin = 4;

//Encoder 2 Read
int encoder2PinA = A4;
int encoder2PinB = A5;
int encoder2PinALast = LOW;
int encoder2Pos = 0;

// Suitcase state
bool movementStopped = false;


//Variable for storing received data
void setup() 
{
  Serial.begin(9600);  //Sets the data rate in bits per second (baud) for serial data transmission

  // sets motor pins for motor 1
  pinMode(pwmMotor1Control, OUTPUT);  
  pinMode(motor1APin, OUTPUT);  
  pinMode(motor1BPin, OUTPUT);  

  // get encoders 1 read
  pinMode (encoder1PinA, INPUT);
  pinMode (encoder1PinB, INPUT);

  // sets motor pins for motor 2
  pinMode(pwmMotor2Control, OUTPUT);  
  pinMode(motor2APin, OUTPUT);    
  pinMode(motor2BPin, OUTPUT);

  // get encoders 2 read
  pinMode (encoder2PinA, INPUT);
  pinMode (encoder2PinB, INPUT);
}

void loop()
{
  // read new information from phone
  readBluetoothData();

  // read in the speed and signal
  float speedMPH = convertPhoneBytesToSpeed();
  int signal = (int) speedMPH;

  Serial.print("Speed From Phone: ");
  Serial.println(speedMPH);

  readEncoderData();
  
  // Convert the signal!
  switch (signal) {
    
    case -1:
      Serial.println("Phone Signal: -1");
      Serial.println("Stop Moving.");
      stopMoving();
      movementStopped = true;
      break;
      
    case -2:
      Serial.println("Phone Signal: -2");
      Serial.println("Start Moving.");
      movementStopped = false;
      encoderCurrentPos = 0;
      encoderLastPos = 0;
      //testing
      moveForward(255);
      delay(200);
      break;
      
    case -3:
      Serial.println("Phone Signal: -3");
      Serial.println("Stop Moving.");
      movementStopped = true;
      stopMoving();
      break;
      
     case -4:
      Serial.println("Phone Signal: -4");
      Serial.println("Start Moving.");
      movementStopped = false;
      encoderCurrentPos = 0;
      encoderLastPos = 0;
      //testing
      moveForward(255);
      delay(200);
      break;
      
    default:
      if (!movementStopped) {

        Serial.println("Calculating Speed...");
        
        // information from phone
        int speedPWM = convertSpeedToPWM(speedMPH);
        Serial.print("Phone Speed PWM: ");
        Serial.println(speedPWM);

        // caculated from encoders
        float currentMillis = millis();
        int encoderSpeed = (encoderCurrentPos - encoderLastPos) / (currentMillis - lastMillis);

        Serial.print("Encoder Speed: ");
        Serial.println(encoderSpeed);

        //suitcase is not moving
//        if (encoderSpeed < 1) {
//          stopMoving();
//        }
//        else {
          moveForward(speedPWM);
//        }

        encoderLastPos = encoderCurrentPos;
        lastMillis = currentMillis;
        
        delay(200);
      }
  }
}

int convertSpeedToPWM(int speedMPH) {
  if (speedMPH > 3) {
    return 255; 
  }
  else {
    return (int) map(speedMPH, 0, 3.0, 0, 255);
  }
}

void readEncoderData() {
  //calculate encoder information
  int n = digitalRead(encoder1PinA);
  if ((encoder1PinALast == LOW) && (n == HIGH)) {
    if (digitalRead(encoder1PinB) == LOW) {
      encoder1Pos--;
    } else {
      encoder1Pos++;
    }
    Serial.print (encoder1Pos);
    Serial.print ("/n");
  }
  encoder1PinALast = n;
  
  n = digitalRead(encoder2PinA);
  if ((encoder2PinALast == LOW) && (n == HIGH)) {
    if (digitalRead(encoder2PinB) == LOW) {
      encoder2Pos--;
    } else {
      encoder2Pos++;
    }
    Serial.print (encoder1Pos);
    Serial.print ("/n");
  }
  encoder2PinALast = n;  

  //get current Position
  encoderCurrentPos = max(encoder1Pos, encoder2Pos);
  encoder1Pos = encoderCurrentPos;
  encoder2Pos = encoderCurrentPos;
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
  int i = 3;
  while(Serial.available() > 0 && i >= 0)  // Send data only when you receive data:
  {
    signed char singleByteFromPhone = Serial.read();
    Serial.println(singleByteFromPhone);
    speedBytesFromPhone[i--] = singleByteFromPhone;
    delay(1000);
  }

  while(Serial.available()) {
    Serial.read();
  }
}

// Convert bytes to int
float convertPhoneBytesToSpeed() {
  //convert phone bytes to a float num
  float speed;
  memcpy(&speed, speedBytesFromPhone, sizeof(float));  
  return speed;
}
