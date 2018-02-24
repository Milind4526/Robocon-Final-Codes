
// 10235 is rong bay




#define encoder0PinA  2
#define encoder0PinB  3

unsigned long t1 = 0;
//t1 = millis();
int q = 0;

volatile long previous, encoder0Pos = 0;
volatile long newposition;
volatile long oldposition = 0;
//unsigned long newtime, t1;
unsigned long oldtime = 0;
double vel; byte counter = 0;
long temp;
byte a, b; byte flag = 0;
void doEncoder();

byte srp = 6; //
int rpm_count = 0;
int sped = 100;
byte srd = 7; //
byte direct = HIGH;
float pwm1 = 0;
byte sp = 70;
//byte c=0;
byte relay1 = 9;
//byte stopper=8;//
int pwm = 5;
int dir = 8;
// byte ir=38;
//byte last_sp=120;
byte last_sp1 = 20; //
//byte kp=100;
 byte pos; //
// byte temp_pos;

int c = 0;

float rev = 0;
float tick = 2370; // Count when the ball is released 135 ticks per revolution

byte relay_state = HIGH;

void arm(int z)
{
  if (z == 1)
  {
    digitalWrite(srp, HIGH);
    digitalWrite(srd, HIGH);

  }
  else if (z == 2)
  {
    digitalWrite(srp, HIGH);
    digitalWrite(srd, LOW);
    //delay(1000);

  }
  else if (z == 3)
  {
    analogWrite(srp, 255);
    digitalWrite(srd, HIGH);
  }
  else if (z == 4)
  {
    digitalWrite(srp, HIGH);
    digitalWrite(srd, LOW);
  }
}


void motion (byte d, byte s)
{
  analogWrite(pwm, s);
  digitalWrite(dir, d);

}

void pnuematic(byte s)
{
  if (s == 1)
  {
    digitalWrite(9 , HIGH);
  }
  if (s == 0)
  {
    digitalWrite(9 , LOW);
  }
}



void setup() {
  // put your setup code here, to run once:
  Serial.begin (115200);
  pinMode(encoder0PinA, INPUT);
  digitalWrite(encoder0PinA, HIGH);       // turn on pullup resistor
  pinMode(encoder0PinB, INPUT);
  digitalWrite(encoder0PinB, HIGH);       // turn on pullup resistor
  attachInterrupt(0, doEncoder, RISING);  // encoDER ON PIN 2
  // attachInterrupt(1, doEncoder, CH);  // encoDER ON PIN 3
  //Serial.println("start");                // a personal quirk
  oldtime = micros();
  oldposition = encoder0Pos;
  // Serial.print("oldTime: ");
  //Serial.println(oldtime);
  int t1 = millis();

  pinMode(srp, OUTPUT);
  pinMode(srd, OUTPUT);
  pinMode(pwm, OUTPUT);
  pinMode(dir, OUTPUT);
  pinMode(9 , OUTPUT);
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);
  arm(1);
  pnuematic(0);
}

void loop()
{
  Serial.print(" pwm ");
  Serial.print(pwm1);

  Serial.print("      encoder0pos ");
  Serial.println(encoder0Pos);

  if (encoder0Pos > 200)
  {
    pnuematic(1);
  }


  if (encoder0Pos > tick)
  {
    //if(c == 0)
    arm(2);
    //else
    //arm(4);
    pwm1 -= 5;
    pwm1 = pwm1 < 10 ? 0 : pwm1;
    motion(direct, pwm1);
    // c++;

  }
  //  else if (c == 2)
  //  {
  //    motion(direct,120);
  //    delay(300);
  //    motion(direct, 60);
  //    delay(300);
  //    motion(direct,0);
  //    c = 33;
  //
  //  }
  else
  {
    arm(3);
    pwm1 += 0.5;
    pwm1 = pwm1 > 120 ? 120 : pwm1;
    motion(direct, pwm1);
  }

}






void doEncoder()
{
  a = digitalRead(encoder0PinA);
  b = digitalRead(encoder0PinB);
  if (a == b) {
    encoder0Pos++;
  } else {
    encoder0Pos--;
  }


}



