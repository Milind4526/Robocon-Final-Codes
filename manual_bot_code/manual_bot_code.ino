
//Code For Blue Mode
#include<avr/wdt.h>
#include <EEPROM.h>
//#include <PS4USB.h>
#include <XBOXUSB.h>
#include <SPI.h>
#include<Wire.h>
#include<string.h>
#include<math.h>

//  ps4 variable
USB Usb;
//PS4USB PS4(&Usb);
XBOXUSB Xbox(&Usb);
//
int frd = 37, ltd = 35, rtd = 31, fra = 11, lta = 9, rta = 8;
float imu_values[1000];
float angle[] = {0.0, 1.37, 2.74, 4.11, 5.48, 6.85, 8.22, 9.61, 10.92, 12.24, 13.55, 14.87, 16.18, 17.5, 18.83, 20.13, 21.43, 22.73, 24.03, 25.32, 26.62, 27.92, 29.25, 30.5, 31.75, 33.0, 34.25, 35.5, 36.75, 38.0, 39.3, 40.47, 41.63, 42.79, 43.95, 45.12, 46.28, 47.44, 48.6, 49.74, 51.03, 52.31, 53.59, 54.87, 56.15, 57.44, 58.72, 60.0, 61.67, 63.33, 65.0, 66.67, 68.33, 70.0, 71.19, 72.38, 73.57, 74.76, 75.95, 77.14, 78.33, 79.6, 80.61, 81.62, 82.63, 83.64, 84.65, 85.66, 86.67, 87.68, 88.69, 89.67, 90.78, 91.89, 93.0, 94.11, 95.22, 96.33, 97.44, 98.56, 99.67, 100.76, 101.85, 102.93, 104.02, 105.11, 106.2, 107.28, 108.37, 109.49, 110.51, 111.52, 112.53, 113.54, 114.55, 115.56, 116.57, 117.58, 118.59, 119.63, 120.55, 121.46, 122.37, 123.29, 124.2, 125.11, 126.03, 126.94, 127.85, 128.77, 129.68, 130.59, 131.49, 132.4, 133.3, 134.21, 135.11, 136.02, 136.92, 137.83, 138.73, 139.63, 140.55, 141.47, 142.4, 143.32, 144.24, 145.16, 146.08, 147.0, 147.93, 148.85, 149.79, 150.63, 151.48, 152.32, 153.16, 154.01, 154.85, 155.7, 156.54, 157.38, 158.23, 159.07, 159.92, 160.73, 161.54, 162.36, 163.17, 163.98, 164.8, 165.61, 166.42, 167.24, 168.05, 168.86, 169.69, 170.47, 171.24, 172.02, 172.79, 173.57, 174.34, 175.12, 175.89, 176.67, 177.44, 178.22, 178.99, 179.75, 180.58, 181.4, 182.23, 183.06, 183.88, 184.71, 185.54, 186.36, 187.19, 188.02, 188.84, 189.69, 190.47, 191.25, 192.03, 192.81, 193.59, 194.38, 195.16, 195.94, 196.72, 197.5, 198.28, 199.06, 199.84, 200.65, 201.46, 202.28, 203.09, 203.9, 204.72, 205.53, 206.34, 207.15, 207.97, 208.78, 209.7, 210.3, 210.9, 211.5, 212.1, 212.69, 213.29, 213.89, 214.49, 215.09, 215.69, 216.29, 216.89, 217.49, 218.08, 218.68, 219.28, 219.83, 220.69, 221.55, 222.4, 223.26, 224.12, 224.98, 225.84, 226.7, 227.55, 228.41, 229.32, 230.12, 230.92, 231.72, 232.52, 233.33, 234.13, 234.93, 235.73, 236.53, 237.33, 238.13, 238.93, 239.58, 240.86, 242.15, 243.44, 244.72, 246.01, 247.3, 248.58, 249.9, 250.9, 251.9, 252.9, 253.9, 254.9, 255.9, 256.9, 257.9, 258.9, 259.92, 260.76, 261.61, 262.46, 263.31, 264.15, 265.0, 265.85, 266.69, 267.54, 268.39, 269.18, 270.09, 271.0, 271.92, 272.83, 273.74, 274.66, 275.57, 276.48, 277.4, 278.31, 279.19, 280.14, 281.1, 282.06, 283.01, 283.97, 284.93, 285.89, 286.84, 287.8, 288.76, 289.69, 290.72, 291.75, 292.78, 293.81, 294.85, 295.88, 296.91, 297.94, 298.97, 300.0, 301.0, 302.0, 303.0, 304.0, 305.0, 306.0, 307.0, 308.0, 309.0, 310.0, 311.12, 312.25, 313.37, 314.49, 315.62, 316.74, 317.87, 318.88, 320.12, 321.38, 322.62, 323.88, 325.12, 326.38, 327.62, 328.94, 330.12, 331.29, 332.47, 333.65, 334.82, 336.0, 337.18, 338.35, 339.54, 340.69, 341.84, 342.99, 344.14, 345.29, 346.44, 347.59, 348.74, 349.87, 351.15, 352.44, 353.72, 355.0, 356.28, 357.56};


//       motor configuration:
//---------------------------------------------
//     | motor2(fld,fla)   |   motor1(frd,fra) |
//---------------------------------------------
//     | motor3(bld,bla)   |   motor4(brd,bra) |
//---------------------------------------------


float last_imu_value = 0.0, present_imu_value = 0.0;
float lastYaw = 0.0;
//

int yflag = 0;

//kinematics matrix variable
float a11 = -0.33, a12 = 0.58, a13 = 0.33;
float a21 = -0.33, a22 = -0.58, a23 = 0.33;
float a31 = 0.67, a32 = 0, a33 = 0.33;

//float a11 = -0.585, a12 = 0, a13 = 0.4142;
//float a21 = 0.2928, a22 = -0.7071, a23 = 0.2928;
//float a31 = 0.2928, a32 = 0.7071, a33 = 0.2928;
//


//imu variable
#define BUFF_SIZE 40
char buff[BUFF_SIZE];
float comp_ref_yaw, ref_yaw, first_ref_yaw, xx = 0, map_diff = 0;
String yaw_string, pitch_string, roll_string;
//

float w = 0, x = 0, y = 0; //inverse kinemaatics variables

float xl = 0, yr = 0;

void (* resetFunc)(void) = 0;

void setup()
{
  Wire.begin();
  Serial.begin(112500);
  motorSetup();
  //  ps4_setup();
  xbox_setup();
  imusetup();
}

void loop()
{

  Usb.Task();

  //  if (PS4.connected())
  //  {
  //    PS4.setLed(Yellow);
  //    if (PS4.getAnalogHat(LeftHatX) > 137 || PS4.getAnalogHat(LeftHatX) < 117 || PS4.getAnalogHat(LeftHatY) > 137 || PS4.getAnalogHat(LeftHatY) < 117 || PS4.getAnalogHat(RightHatX) > 137 || PS4.getAnalogHat(RightHatX) < 117 || PS4.getAnalogHat(RightHatY) > 137 || PS4.getAnalogHat(RightHatY) < 117)
  //    {
  //      if (PS4.getAnalogHat(RightHatY) > 157 || PS4.getAnalogHat(RightHatY) < 97)
  //      {
  //        x = PS4.getAnalogHat(RightHatY);
  //        Serial.println(" ");
  //        Serial.print(" x: ");
  //        Serial.print(x);
  //        x = map(x, 0, 255, -255, 255);
  //      }
  //      else
  //        x = 0;
  //
  //      if ( PS4.getAnalogHat(RightHatX) > 157 || PS4.getAnalogHat(RightHatX) < 97) {
  //        y = PS4.getAnalogHat(RightHatX);
  //        Serial.println(" ");
  //        Serial.print(" y: ");
  //        Serial.print(y);
  //        y = map(y, 0, 255, 255, -255);
  //      }
  //      else y = 0;
  //
  //      x > 255 ? 255 : x;
  //      x < -255 ? -255 : x;
  //      y > 255 ? 255 : y;
  //      y < -255 ? -255 : y;
  //      Serial.print(" x: ");
  //      Serial.print(x);
  //      Serial.print("  y: ");
  //      Serial.print(y);
  //
  //    }
  //
  //    else
  //    {
  //      x = 0;
  //      y = 0;
  //    }
  //
  //
  //    if (PS4.getButtonPress(TRIANGLE))
  //    {
  //      resetFunc();
  //      delay(100);
  //    }
  //
  //
  //
  //    if (PS4.getButtonPress(L2) or PS4.getButtonPress(R2)) {
  //      if (PS4.getButtonPress(L2))
  //      {
  //        ref_yaw = ref_yaw - 3;
  //        Serial.println("L2");
  //      }
  //      else if (PS4.getButtonPress(R2))
  //      {
  //        ref_yaw = ref_yaw + 3;
  //        Serial.println("R2");
  //      }
  //    }
  //  }


  if (Xbox.Xbox360Connected)
  {

    if (Xbox.getAnalogHat(LeftHatX) > 3000 || Xbox.getAnalogHat(LeftHatX) < -3000 || Xbox.getAnalogHat(LeftHatY) > 3000 || Xbox.getAnalogHat(LeftHatY) < -3000 || Xbox.getAnalogHat(RightHatX) > 3000 || Xbox.getAnalogHat(RightHatX) < -3000 || Xbox.getAnalogHat(RightHatY) > 3000 || Xbox.getAnalogHat(RightHatY) < -3000)
    {
      if (Xbox.getAnalogHat(LeftHatY) > 5000 || Xbox.getAnalogHat(LeftHatY) < -5000)
      {
        xl = Xbox.getAnalogHat(LeftHatY);
        x = map(xl, -32768, 32767, 0, 255);
        Serial.println(" ");
        Serial.print(" x: ");
        Serial.print(x);
        x = map(x, 0, 255, 155, -155);
      }
      else
        x = 0;

      if ( Xbox.getAnalogHat(RightHatX) > 5000 || Xbox.getAnalogHat(RightHatX) < -5000) {
        yr = Xbox.getAnalogHat(RightHatX);
        y = map(yr, -32768, 32767, 0, 255);
        Serial.println(" ");
        Serial.print(" y: ");
        Serial.print(y);
        y = map(y, 0, 255, -155, 155);
      }
      else y = 0;

      x > 255 ? 255 : x;
      x < -255 ? -255 : x;
      y > 255 ? 255 : y;
      y < -255 ? -255 : y;
      Serial.print(" x: ");
      Serial.print(x);
      Serial.print("  y: ");
      Serial.print(y);

    }

    else
    {
      x = 0;
      y = 0;
    }


    //    if (PS4.getButtonPress(TRIANGLE))
    //    {
    //      resetFunc();
    //      delay(100);
    //    }
    //
    //
    //
    //    if (PS4.getButtonPress(L2) or PS4.getButtonPress(R2)) {
    //      if (PS4.getButtonPress(L2))
    //      {
    //        ref_yaw = ref_yaw - 3;
    //        Serial.println("L2");
    //      }
    //      else if (PS4.getButtonPress(R2))
    //      {
    //        ref_yaw = ref_yaw + 3;
    //        Serial.println("R2");
    //      }
    //    }

    if (Xbox.getButtonClick(Y))
    {
      resetFunc();
      delay(100);
    }


    if (Xbox.getButtonPress(L2) || Xbox.getButtonPress(R2)) {
      if (Xbox.getButtonPress(L2))
      {
        ref_yaw = ref_yaw - 3;
        Serial.println("L2");
        yflag = 1;
      }
      else if (Xbox.getButtonPress(R2))
      {
        ref_yaw = ref_yaw + 3;
        Serial.println("R2");
        yflag = 2;
      }
    }
    else yflag = 0;

  }



  else
  {
    Serial.println("not connected");
    Serial.println();
    Serial.println();
    Serial.println(); Serial.println();
    Serial.println();
    x = 0;
    y = 0;
    w = 0;
  }

  if (ref_yaw < 0)ref_yaw = ref_yaw + 360;
  else if (ref_yaw > 360)ref_yaw = ref_yaw - 360;

  xx = x;
  x = (y * sin(0.017456 * (ref_yaw - first_ref_yaw))) - xx * cos(0.017456 * (ref_yaw - first_ref_yaw));
  y = y * cos(0.017456 * (ref_yaw - first_ref_yaw)) + xx * sin(0.017456 * (ref_yaw - first_ref_yaw));

  if (x < -255) {
    map_diff = x + 255;
    y = y - (y / x) * map_diff;
  }
  else if (x > 255) {
    map_diff = x - 255;
    y = y - (y / x) * map_diff;
  }

  if (y < -255) {
    map_diff = y + 255;
    x = x - (x / y) * map_diff;
  }
  else if (y > 255) {
    map_diff = y - 255;
    x = x - (x / y) * map_diff;
  }



  w = pidW();
  invKinematics();
  pwmAndDirectionCalc();
  motion();
  //displayPidXValues();
  //displayPidWValues();
  displayMotionValues();
  //  getImuValue();
  //  w = pidW();
  //  invKinematics();
  //  displayMotionValues();
  //  pwmAndDirectionCalc();
  Serial.println();
  Serial.println();
  Serial.println();
  Serial.println();
}

