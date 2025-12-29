//--------------------------

pinMode(L_IN1, OUTPUT);
pinMode(L_IN2, OUTPUT);
pinMode(R_IN1, OUTPUT);
pinMode(R_IN2, OUTPUT);
pinMode(ENA, OUTPUT);
pinMode(ENB, OUTPUT);
//Motor functions
void forward() 
{
  digitalWrite(L_IN1, HIGH);
  digitalWrite(L_IN2, LOW);
  digitalWrite(R_IN1, HIGH);
  digitalWrite(R_IN2, LOW);
  analogWrite(ENA, speed);
  analogWrite(ENB, speed);
}
void turnLeft() 
{
  digitalWrite(L_IN1, HIGH);
  digitalWrite(L_IN2, LOW);
  analogWrite(ENA, 0);
  digitalWrite(R_IN1, HIGH);
  digitalWrite(R_IN2, LOW);
  analogWrite(ENB, speed);
}
void turnRight() 
{
  digitalWrite(L_IN1, HIGH);
  digitalWrite(L_IN2, LOW);
  analogWrite(ENA, speed);
  digitalWrite(R_IN1, HIGH);
  digitalWrite(R_IN2, LOW);
  analogWrite(ENB, 0);
}
void stopRobot() 
{
  digitalWrite(L_IN1, LOW);
  digitalWrite(L_IN2, LOW);
  digitalWrite(R_IN1, LOW);
  digitalWrite(R_IN2, LOW);
}

void hardBreak()
{
  digitalWrite(L_IN1, HIGH);
  digitalWrite(L_IN2, HIGH);
  digitalWrite(R_IN1, HIGH);
  digitalWrite(R_IN2, HIGH);
}  

// ---------------------------

pinMode(trigPin, OUTPUT); 
pinMode(echoPin, INPUT);

int getDistance() // Ultrasonic sensor 
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  long duration = pulseIn(echoPin, HIGH, 30000);
  int distance = duration * 0.034 / 2;
  return distance;
}

//-----------------------------

