float emaFilter(float newValue, float alpha, float prev) 
{
  prev = alpha * newValue + (1 - alpha) * prev;
  return prev;
}

int rawIR;
float irFiltered = 0;
float alphaIR = 0.2;
void loop() 
{
  rawIR = analogRead(A0);
  float smoothIR = emaFilter(rawIR, alphaIR, irFiltered);
  Serial.print(rawIR);
  Serial.print(" ");
  Serial.println(smoothIR);
}


long readUltrasonic() 
{
  long a = pulseIn(echoPin, HIGH);
  delayMicroseconds(2000);
  long b = pulseIn(echoPin, HIGH);
  delayMicroseconds(2000);
  long c = pulseIn(echoPin, HIGH);
  if (a > b) swap(a, b);
  if (b > c) swap(b, c);
  if (a > b) swap(a, b);
  return b;  // median
}
float ultraFiltered = 0;
float alphaUltra = 0.15;

void loop() {
  long raw = readUltrasonic();
  float smooth = emaFilter(raw, alphaUltra, ultraFiltered);

  Serial.println(smooth);
}










