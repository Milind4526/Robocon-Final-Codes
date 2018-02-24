//////////////////////////////////////////////////////MOTOR & PNUMATICS/////////////////////////////////////////////////////////////
#define m_p 10
#define m_d 6
///klklklklkl
#define pnu_p 8
#define pnu_d 4
////////////////////////////////////////////////////////ENCODER///////////////////////////////////////////////////////////// 
#define encoder0PinA 2
#define encoder0PinB 3
volatile long encoder0Pos=0;
int a,b;
long ticks, t1=0,t2=0,last_ticks;
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int flag_1=0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
//////////////////////////////////////////////////////////MOTER//////////////////////////////////////////////////////////////////////
 pinMode(m_p,OUTPUT);
 pinMode(m_d,OUTPUT);
 pinMode(pnu_p,OUTPUT);
 pinMode(pnu_d,OUTPUT);
/////////////////////////////////////////////////////ENCODER SETUP/////////////////////////////////////////////////////////////
  pinMode(encoder0PinA,INPUT);
  digitalWrite(encoder0PinA,HIGH);
  pinMode(encoder0PinB,INPUT);
  digitalWrite(encoder0PinB,HIGH);
  attachInterrupt(0,doEncoder,RISING);
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

void doEncoder(){
  a=digitalRead(encoder0PinA);
  b=digitalRead(encoder0PinB);
  if(a==b)encoder0Pos++;
  else encoder0Pos--;
}
void wind()
{
  analogWrite(m_p,150);
  digitalWrite(m_d,0);
}
void unwind()
{
  analogWrite(m_p,40);
  digitalWrite(m_d,1); 
}
void ruk()
{
  analogWrite(m_p,0);
}
void pnumaticsO()
{
  
  analogWrite(pnu_p,250);
  digitalWrite(pnu_d,0);

}
void pnumaticsF()
{
  
  digitalWrite(pnu_p,LOW);
  digitalWrite(pnu_d,1);
  

}
void fek()
{
  
  
    wind();
    delay(1800);
 
    ruk();
    pnumaticsF();
    delay(5300);
    
    unwind();
    delay(1000);
    ruk();
    delay(3000);
    pnumaticsO();
    delay(1000);

}
void loop() {
  // put your main code here, to run repeatedly:
delay(5000);
 Serial.println(encoder0Pos);
 fek();
// pnumaticsO();
// delay(2000);
// pnumaticsF();
// delay(2000);

}
