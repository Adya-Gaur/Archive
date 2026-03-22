const int ENA=3;
  const int ENB=10;
  const int IN1=2;
  const int IN2=6;
  const int IN3=5;
  const int IN4=4;
  const int ir_left=11;
  const int ir_left_mid=12;
  const int ir_right_mid=9;
  const int ir_right=8;
  const int lspeed=200;
  const int rspeed=200;
  int A=0, B=0, C=0, D=0;
  void moveForward(int Lspeed = lspeed, int Rspeed = rspeed);
void sharpLeft(int Lspeed = lspeed, int Rspeed = rspeed);
void sharpRight(int Lspeed = lspeed, int Rspeed = rspeed);
void turnLeft();
void turnRight();

  void setup() {
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
    
    int s1 = digitalRead(ir_left);
    int s2 = digitalRead(ir_left_mid);
    int s3 = digitalRead(ir_right_mid);
    int s4 = digitalRead(ir_right);
    Serial.print(s1);
    Serial.print(s2);
    Serial.print(s3);
    Serial.println(s4);
    delay(1000);
    int E=1000*A +100*B + 10*C + D;
    switch (E)
    {
      case 0000 :
      if(s1 && !s2 && !s3 && s4)
        moveForward();
      else if(s1 && s2 && !s3 &&!s4)
        right();
      else if(!s1 && !s2 && s3 && s4)
        left();
      else if(s1 && !s2 && !s3 &&!s4)
        sharpRight();
      else if(!s1 && !s2 && !s3 && s4)
        sharpLeft();
      if(s1 && !s2 &&!s3 && s4)
        A = 1;
      break;

      case 1000:
      if(!s1 && s2 && s3 && !s4)
        moveForward();
      else if(!s1 && s2 && s3 && s4)
        sharpRight();
      else if(s1 && s2 && s3 && !s4)
        sharpLeft();
      else if(s1 && s2 && s3 && s4)
        sharpRight();
      while(!s2 && !s3)
      {
        moveForward();
      }
      if(!s1 && !s2 && s3 && s4)
      {
        sharpRight();
        sharpLeft();
        B = 1;
      }
      break;

      case 1100:
      if (!s1 && s2 && s3 && s4)
        moveForward();
      if(s1 && !s2 && !s3 && !s4)
      {
        sharpLeft();
        sharpRight();
        if(s1 && s2 && s3 && !s4)
          moveForward();
      }

      if(!s1 && !s2 && !s3 && s4)
      {
        sharpRight();
        sharpLeft();
        if(!s1 && s2 && s3 && s4)
          moveForward();
      }

      if(!s1 && s2 && !s3 && !s4)
        left();
        if(!s1 && s2 && s3 && !s4)
        moveForward();
      else if(!s1 && s2 && s3 && s4)
        sharpRight();
      else if(s1 && s2 && s3 && !s4)
        sharpLeft();
      else if(s1 && s2 && s3 && s4)
        sharpRight();
      
      //if(!s1 && s2 && !s3 && !s4)
      //{
      break;  
      


   // }
  }
}

void moveForward(int Lspeed=lspeed, int Rspeed=rspeed){
      analogWrite(ENA,Lspeed);
      analogWrite(ENB,Rspeed);
      digitalWrite(IN1,HIGH);
      digitalWrite(IN2,LOW);
      digitalWrite(IN3,LOW);
      digitalWrite(IN4,HIGH);
      
    }


void sharpLeft(int Lspeed=lspeed, int Rspeed=rspeed)
{
      analogWrite(ENA,Lspeed);
      analogWrite(ENB,Rspeed);
      digitalWrite(IN1,HIGH);
      digitalWrite(IN2,LOW);
      digitalWrite(IN3,LOW);
      digitalWrite(IN4,HIGH);
            while (true){
              int s1=digitalRead(ir_left);
    int s4=digitalRead(ir_right);
    int s2=digitalRead(ir_left_mid);
    int s3=digitalRead(ir_right_mid);
        if (s2==s3 && s4!=s1 && s3!=s4)

          analogWrite(ENA,lspeed-70);
          analogWrite(ENB,rspeed-70);
          digitalWrite(IN1,HIGH);
          digitalWrite(IN2,LOW);
          digitalWrite(IN3,HIGH);
          digitalWrite(IN4,LOW);}
    delay(2500);
}

void sharpRight(int Lspeed=lspeed, int Rspeed=rspeed)
{
    analogWrite(ENA,Lspeed);
      analogWrite(ENB,Rspeed);
      digitalWrite(IN1,HIGH);
      digitalWrite(IN2,LOW);
      digitalWrite(IN3,LOW);
      digitalWrite(IN4,HIGH);
            while (true){
              int s1=digitalRead(ir_left);
    int s4=digitalRead(ir_right);
    int s2=digitalRead(ir_left_mid);
    int s3=digitalRead(ir_right_mid);
        if (s2==s3 && s4!=s1 && s3==s4)

          analogWrite(ENA,lspeed-70);
          analogWrite(ENB,rspeed-70);
          digitalWrite(IN1,LOW);
          digitalWrite(IN2,HIGH);
          digitalWrite(IN3,LOW);
          digitalWrite(IN4,HIGH);}
    delay(2500);

}

void right()
{
     analogWrite(ENA,lspeed-70);
      analogWrite(ENB,rspeed-130);
      digitalWrite(IN1,HIGH);
      digitalWrite(IN2,LOW);
      digitalWrite(IN3,LOW);
      digitalWrite(IN4,HIGH);
     delay(2500);
}

void left()
{
     analogWrite(ENA,lspeed-130);
      analogWrite(ENB,rspeed-70);
      digitalWrite(IN1,HIGH);
      digitalWrite(IN2,LOW);
      digitalWrite(IN3,LOW);
      digitalWrite(IN4,HIGH);
     delay(2500);
}
