const int ENA=3, ENB=10;
const int IN1=2, IN2=6, IN3=5, IN4=4;
const int ir_left=11, ir_left_mid=12, ir_right_mid=9, ir_right=8;
const int lspeed=200;
const int rspeed=200;
int A = 0, B = 0, C = 0, D = 0;
int E;
int s1, s2, s3, s4;
int previous, current;

void forward();
void stop();
void left();
void right();
void sharpLeft();
void sharpRight();

void whiteLineFollower(int s1, int s2, int s3, int s4);
void blackLineFollower(int s1, int s2, int s3, int s4);
void readSensors();

void setup() 
{
  Serial.begin(9600);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ir_left, INPUT);
  pinMode(ir_left_mid, INPUT);
  pinMode(ir_right_mid, INPUT);
  pinMode(ir_right, INPUT);
    //white=0
    //black=1
  }

void loop()
{
  s1 = digitalRead(ir_left);
  s2 = digitalRead(ir_left_mid);
  s3 = digitalRead(ir_right_mid);
  s4 = digitalRead(ir_right);

  current = 1000*s1 + 100*s2 + 10*s3 + s4;
  
  E = 1000*A + 100*B + 10*C + D;
  switch(E)
  {
    case 0000:
    whiteLineFollower(s1, s2, s3, s4);
    if(!s1 && s2 && s3 && !s4) //0110
      A = 1;
    break;

    case 1000:
      blackLineFollower(s1, s2, s3, s4); //Default
      if(s1 && !s2 && !s3 && s4) //1001
      {
        while(true)
          {
            int S1 = digitalRead(ir_left);
            int S2 = digitalRead(ir_left_mid);
            int S3 = digitalRead(ir_right_mid);
            int S4 = digitalRead(ir_right);
            whiteLineFollower(S1, S2, S3, S4);
            if(!S1 && !S2 && !S3 && !S4) //0000
              left(); // for Phi
            if(!S1 && S2 && S3 && !S4) //0110
              break;
          }
      }
      if(s1 && s2 && s3 && s4) //1111
        sharpLeft();
      if(previous == 0110 && current == 0011)
        B = 1; // B checkpoint 
      break;

    case 1100:
      blackEdgeFollower(s1, s2, s3, s4);
      if(previous == 0011 && current == 0110)
      {
        while(true)
          {
            int S1 = digitalRead(ir_left);
            int S2 = digitalRead(ir_left_mid);
            int S3 = digitalRead(ir_right_mid);
            int S4 = digitalRead(ir_right);
            blackLineFollower(S1, S2, S3, S4);
            if(previous == 0110 && current == 1100) // C4 to D1
            {
              C = 1;
              break;
            }
          }
      }
      break;

    case 1110:
    while(true)
      {
        int S1 = digitalRead(ir_left);
        int S2 = digitalRead(ir_left_mid);
        int S3 = digitalRead(ir_right_mid);
        int S4 = digitalRead(ir_right);
        if(S1 && S2 && !S3 && !S4) //1100
          forward();
        else if(!S1 && !S2 && !S3 && !S4)
        {
          while(true)
          {
            int S1 = digitalRead(ir_left);
            int S2 = digitalRead(ir_left_mid);
            int S3 = digitalRead(ir_right_mid);
            int S4 = digitalRead(ir_right);

            analogWrite(ENA,130);
            analogWrite(ENB,130);
            digitalWrite(IN1,LOW);
            digitalWrite(IN2,HIGH);
            digitalWrite(IN3,LOW);
            digitalWrite(IN4,HIGH);

            if(S1 && S2 && !S3 && !S4) // back to line
            break;
          }
        }
        
        if(S1 && !S2 && !S3 && S4) // 1001
          break;
      }
    whiteLineFollower(s1, s2, s3, s4);
    break;

    default:
      stop();
  }
    previous = current;
}

void stop()
{
  analogWrite(ENA, 200);
  analogWrite(ENB, 200);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void forward()
{
  analogWrite(ENA, 200);
  analogWrite(ENB, 200);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void left()
{
   while(true)
  {
    int S1 = digitalRead(ir_left);
    int S2 = digitalRead(ir_left_mid);
    int S3 = digitalRead(ir_right_mid);
    int S4 = digitalRead(ir_right);

    analogWrite(ENA,130);
    analogWrite(ENB,180);
    digitalWrite(IN1,HIGH);
    digitalWrite(IN2,LOW);
    digitalWrite(IN3,LOW);
    digitalWrite(IN4,HIGH);

    if((!S1 && S2 && S3 && !S4)|| (S1 && !S2 && !S3 && S4)) // 10001 or 0110
      break;
  }
}

void right()
{
  while(true)
  {
    int S1 = digitalRead(ir_left);
    int S2 = digitalRead(ir_left_mid);
    int S3 = digitalRead(ir_right_mid);
    int S4 = digitalRead(ir_right);

    analogWrite(ENA,180);
    analogWrite(ENB,130);
    digitalWrite(IN1,HIGH);
    digitalWrite(IN2,LOW);
    digitalWrite(IN3,LOW);
    digitalWrite(IN4,HIGH);

    if((!S1 && S2 && S3 && !S4)|| (S1 && !S2 && !S3 && S4)) // back to line
      break;
  }
}

void sharpLeft()
{
  while(true)
  {
    int S1 = digitalRead(ir_left);
    int S2 = digitalRead(ir_left_mid);
    int S3 = digitalRead(ir_right_mid);
    int S4 = digitalRead(ir_right);

    analogWrite(ENA,130);
    analogWrite(ENB,130);
    digitalWrite(IN1,LOW);
    digitalWrite(IN2,HIGH);
    digitalWrite(IN3,LOW);
    digitalWrite(IN4,HIGH);

    if((!S1 && S2 && S3 && !S4)|| (S1 && !S2 && !S3 && S4)) // back to line
      break;
  }
}

void sharpRight()
{
  while(true)
  {
    int S1 = digitalRead(ir_left);
    int S2 = digitalRead(ir_left_mid);
    int S3 = digitalRead(ir_right_mid);
    int S4 = digitalRead(ir_right);

    analogWrite(ENA,130);
    analogWrite(ENB,130);
    digitalWrite(IN1,HIGH);
    digitalWrite(IN2,LOW);
    digitalWrite(IN3,HIGH);
    digitalWrite(IN4,LOW);

    if((!S1 && S2 && S3 && !S4)|| (S1 && !S2 && !S3 && S4)) // back to line
      break;
  }
}

void blackEdgeFollower(int s1, int s2, int s3, int s4)
{
  if(!s1 && !s2 && s3 && s4)
  {
    while(true)
  {
    int S1 = digitalRead(ir_left);
    int S2 = digitalRead(ir_left_mid);
    int S3 = digitalRead(ir_right_mid);
    int S4 = digitalRead(ir_right);

    analogWrite(ENA,180);
    analogWrite(ENB,130);
    digitalWrite(IN1,HIGH);
    digitalWrite(IN2,LOW);
    digitalWrite(IN3,LOW);
    digitalWrite(IN4,HIGH);

    if(S1 && S2 && S3 && !S4) //0001
      break;
  }
  }
  else if(s1 && s2 && !s3 && !s4)
  {
    while(true)
  {
    int S1 = digitalRead(ir_left);
    int S2 = digitalRead(ir_left_mid);
    int S3 = digitalRead(ir_right_mid);
    int S4 = digitalRead(ir_right);

    analogWrite(ENA,130);
    analogWrite(ENB,180);
    digitalWrite(IN1,HIGH);
    digitalWrite(IN2,LOW);
    digitalWrite(IN3,LOW);
    digitalWrite(IN4,HIGH);

    if(S1 && S2 && S3 && !S4) // back to line
      break;
  }
  }
  else if(!s1 && s2 && s3 && s4)
    forward();
  else if(s1 && !s2 && !s3 && !s4)
  {
    while(true)
  {
    int S1 = digitalRead(ir_left);
    int S2 = digitalRead(ir_left_mid);
    int S3 = digitalRead(ir_right_mid);
    int S4 = digitalRead(ir_right);

    analogWrite(ENA,130);
    analogWrite(ENB,130);
    digitalWrite(IN1,LOW);
    digitalWrite(IN2,HIGH);
    digitalWrite(IN3,LOW);
    digitalWrite(IN4,HIGH);

    if(S1 && S2 && S3 && !S4) // back to line
      break;
  }
  }
  else if(!s1 && !s2 && !s3 && s4)
  {
    while(true)
  {
    int S1 = digitalRead(ir_left);
    int S2 = digitalRead(ir_left_mid);
    int S3 = digitalRead(ir_right_mid);
    int S4 = digitalRead(ir_right);

    analogWrite(ENA,130);
    analogWrite(ENB,130);
    digitalWrite(IN1,HIGH);
    digitalWrite(IN2,LOW);
    digitalWrite(IN3,HIGH);
    digitalWrite(IN4,LOW);

    if(S1 && S2 && S3 && !S4) // back to line
      break;
  }
  }
}

void whiteLineFollower(int s1, int s2, int s3, int s4)
{
  if(s1 && !s2 && !s3 && s4)
    forward();
  else if(s1 && !s2 && !s3 && !s4)
    sharpRight();
  else if(!s1 && !s2 && s3 && s4)
    left();
  else if(!s1 && !s2 && !s3 && s4)
    sharpLeft();
  else if(s1 && s2 && !s3 && !s4)
    right();
  else if(!s1 && !s2 && !s3 && !s4)
    sharpRight();
}

void blackLineFollower(int s1, int s2, int s3, int s4)
{
  if(!s1 && s2 && s3 && !s4)
    forward();
  else if(!s1 && s2 && s3 && s4)
    sharpRight();
  else if(s1 && s2 && s3 && !s4)
    sharpLeft();
  else if(s1 && s2 && !s3 && !s4)
    left();
  else if(!s1 && !s2 && s3 && s4)
    right();
  else if(s1 && s2 && s3 && s4)
    sharpRight();
}
