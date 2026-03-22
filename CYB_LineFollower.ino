const int ENA=3, ENB=10;
const int IN1=2, IN2=6, IN3=5, IN4=4;
const int ir_left=11, ir_left_mid=12, ir_right_mid=9, ir_right=8;
const int lspeed=200;
const int rspeed=200;
int A = 0, B = 0, C = 0, D = 0;
int s1, s2, s3, s4;

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
  while(A == 0 && B == 0 && C == 0 && D == 0)
  {
    readSensors();
    whiteLineFollower(s1, s2, s3, s4);
    if(!s1 && s2 && s3 && !s4)
      A = 1;
  } // A checkpoint

  while(A == 1 && B == 0 && C ==0 && D == 0)
    {
      readSensors();
      blackLineFollower(s1, s2, s3, s4); //Default
      if(s1 && !s2 && !s3 && s4)
      {
        while(true)
          {
            readSensors();
            whileLineFollower(s1, s2, s3, s4);
            if(!s1 && !s2 && !s3 && !s4) //0000
              left(); // for Phi
            if(!s1 && s2 && s3 && !s4) //0110
              break;
          }
      }
      if(!s1 && !s2 && !s3 && !s4) //0000
      {
        sharpLeft();
        B = 1;
      }
    } // B checkpoint 

    while(A == 1 && B == 1 && C ==0 && D == 0)
      {
        
      }
}










  
  
