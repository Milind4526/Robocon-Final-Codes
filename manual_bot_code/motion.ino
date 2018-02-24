//       motor configuration:
//---------------------------------------------
//     | motor2(fld,fla)   |   motor1(frd,fra) |
//---------------------------------------------
//     | motor3(bld,bla)   |   motor4(brd,bra) |
//---------------------------------------------

// motion variable variable
int  d1, d2, d3;
float s1, s2, s3; // speed variables of motor
int sp = 1;
//Base Motor Pins

//

void invKinematics()//speed of motors
{
  s1 = -sp * ((a11 * y) + (a12 * x) + (a13 * w));
  s2 = -sp * ((a21 * y) + (a22 * x) + (a23 * w));
  s3 = -sp * ((a31 * y) + (a32 * x) + (a33 * w));
}

void pwmAndDirectionCalc()
{
  //direction calculations
  d1 = s1 > 0 ? 1 : 0;
  d2 = s2 > 0 ? 1 : 0;
  d3 = s3 > 0 ? 1 : 0;

  s1 = abs(s1);
  s2 = abs(s2);
  s3 = abs(s3);

  s1 = s1 > 255 ? 255 : s1;
  s2 = s2 > 255 ? 255 : s2;
  s3 = s3 > 255 ? 255 : s3;

}

void motion()/// commands the motors to drive
{

  digitalWrite(frd, d1);
  digitalWrite(ltd, d2);
  digitalWrite(rtd, d3);
  analogWrite(fra, s1);
  analogWrite(lta, s2);
  analogWrite(rta, s3);
}


void stopp(bool flag)
{
  digitalWrite(frd, d1);
  digitalWrite(ltd, d2);
  digitalWrite(rtd, d3);
  if (!flag) s1 = s2 = s3 = 0;
  for (int i = 0; i < 500; i++)
  {
    s1 -= 10;
    s1 = (s1 <= 0) ? 0 : s1;
    s2 -= 10;
    s2 = (s2 <= 0) ? 0 : s2;
    s3 -= 10;
    s3 = (s3 <= 0) ? 0 : s3;
    if (s1 == 0 || s2 == 0 || s3 == 0) {
      s1 = s2 = s3 = 0;
      break;
    }
    analogWrite(fra, s1);
    analogWrite(lta, s2);
    analogWrite(rta, s3);
  }
  analogWrite(fra, 0);
  analogWrite(lta, 0);
  analogWrite(rta, 0);
}

void displayMotionValues()
{
  Serial.print("x=");
  Serial.print(x);
  Serial.print(" y=");
  Serial.print(y);
  Serial.print(" w=");
  Serial.print(w);
  Serial.print(" s1=");

  Serial.print(s1);
  Serial.print(" s2=");
  Serial.print(s2);
  Serial.print(" s3=");
  Serial.print(s3);
  Serial.print(" d1=");
  Serial.print(d1);
  Serial.print(" d2=");
  Serial.print(d2);
  Serial.print(" d3=");
  Serial.print(d3);
}
void motion_check()/// checks the order of motors
{
  Serial.println("forward right");
  digitalWrite(frd, 1);
  analogWrite(fra, 125);
  delay(1000);
  digitalWrite(frd, 1);
  analogWrite(fra, 0);
  delay(1000);
  digitalWrite(frd, 0);
  analogWrite(fra, 125);
  delay(1000);
  digitalWrite(frd, 0);
  analogWrite(fra, 0);
  Serial.println("forward left");


  Serial.println("backward right");
  digitalWrite(ltd, 1);
  analogWrite(lta, 125);
  delay(1000);
  digitalWrite(ltd, 1);
  analogWrite(lta, 0);
  delay(1000);
  digitalWrite(ltd, 0);
  analogWrite(lta, 125);
  delay(1000);
  digitalWrite(ltd, 0);
  analogWrite(lta, 0);
  delay(1000);

  Serial.println("backward left");
  digitalWrite(rtd, 1);
  analogWrite(rta, 125);
  delay(1000);
  digitalWrite(rtd, 1);
  analogWrite(rta, 0);
  delay(1000);
  digitalWrite(rtd, 0);
  analogWrite(rta, 125);
  delay(1000);
  digitalWrite(rtd, 0);
  analogWrite(rta, 0);
  delay(1000);

}
