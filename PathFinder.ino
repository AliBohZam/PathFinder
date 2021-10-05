/***********************************************************************
Copyright (c) 2020-2021 Ali Bohloolizamani

Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files (the
"Software"), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject to
the following conditions:

The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
***********************************************************************/
#include <EEPROM.h>

#define EN1 2
#define EN2 3
#define IN1 50
#define IN2 51
#define IN3 52
#define IN4 53
#define BUZZER 23
#define BUTTON 22

#define ADC_MAX (1 << 10) - 1
#define ADC_MIN 0

#define MRF(pwm) \
  digitalWrite(IN1, LOW); \
  digitalWrite(IN2, HIGH); \
  analogWrite(EN1, pwm);
#define MRB(pwm) \
  digitalWrite(IN1, HIGH); \
  digitalWrite(IN2, LOW); \
  analogWrite(EN1, pwm);
#define MRS() \
  digitalWrite(IN1, HIGH); \
  digitalWrite(IN2, HIGH); \
  analogWrite(EN1, 255);
#define MLF(pwm) \
  digitalWrite(IN3, HIGH); \
  digitalWrite(IN4, LOW); \
  analogWrite(EN2, pwm);
#define MLB(pwm) \
  digitalWrite(IN3, LOW); \
  digitalWrite(IN4, HIGH); \
  analogWrite(EN2, pwm);
#define MLS() \
  digitalWrite(IN3, HIGH); \
  digitalWrite(IN4, HIGH); \
  analogWrite(EN2, 255);

#define DEBUG
#undef DEBUG

#ifdef DEBUG
#define debugbegin(x) Serial.begin(x)
#define debugln(x)    Serial.println(x)
#define debug(x)      Serial.print(x)
#else
#define debugbegin(x)
#define debugln(x)
#define debug(x)
#endif

int thresholds[16] = { ADC_MAX + ADC_MIN / 2, ADC_MAX + ADC_MIN / 2, ADC_MAX + ADC_MIN / 2, ADC_MAX + ADC_MIN / 2,
                       ADC_MAX + ADC_MIN / 2, ADC_MAX + ADC_MIN / 2, ADC_MAX + ADC_MIN / 2, ADC_MAX + ADC_MIN / 2,
                       ADC_MAX + ADC_MIN / 2, ADC_MAX + ADC_MIN / 2, ADC_MAX + ADC_MIN / 2, ADC_MAX + ADC_MIN / 2,
                       ADC_MAX + ADC_MIN / 2, ADC_MAX + ADC_MIN / 2, ADC_MAX + ADC_MIN / 2, ADC_MAX + ADC_MIN / 2 };

void setup() {
  debugbegin(9600);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(EN1, OUTPUT);
  pinMode(EN2, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  if (digitalRead(BUTTON) == HIGH) {
    buzz();
    calibrate();
  } else {
    for (int i = 0; i < 16; i++) {
      thresholds[i] = ((EEPROM.read(2 * i + 1)) << 8) + EEPROM.read(2 * i);
    }
  }
}

void buzz() {
  digitalWrite(BUZZER, HIGH);
  delay(25);
  digitalWrite(BUZZER, LOW);
}

void calibrate() {
  unsigned int minimums[16] = { ADC_MAX, ADC_MAX, ADC_MAX, ADC_MAX, ADC_MAX, ADC_MAX, ADC_MAX, ADC_MAX,
                                ADC_MAX, ADC_MAX, ADC_MAX, ADC_MAX, ADC_MAX, ADC_MAX, ADC_MAX, ADC_MAX };
  unsigned int maximums[16] = { ADC_MIN, ADC_MIN, ADC_MIN, ADC_MIN, ADC_MIN, ADC_MIN, ADC_MIN, ADC_MIN,
                                ADC_MIN, ADC_MIN, ADC_MIN, ADC_MIN, ADC_MIN, ADC_MIN, ADC_MIN, ADC_MIN };
  unsigned int counter = 0;
  boolean flag = true;
  while (true) {
    int sensors[16] = { analogRead(A0 ), analogRead(A1 ), analogRead(A2 ), analogRead(A3 ),
                        analogRead(A4 ), analogRead(A5 ), analogRead(A6 ), analogRead(A7 ),
                        analogRead(A8 ), analogRead(A9 ), analogRead(A10), analogRead(A11),
                        analogRead(A12), analogRead(A13), analogRead(A14), analogRead(A15) };
    for (int i = 0; i < 16; i++) {
      if (sensors[i] > maximums[i]) {
        maximums[i] = sensors[i];
      }
      if (sensors[i] < minimums[i]) {
        minimums[i] = sensors[i];
      }
    }
    if (counter == 255) {
      counter = 0;
      buzz();
      if (flag == true) {
        flag = false;
        MLF(150)
        MRB(150)
      } else {
        flag = true;
        MLB(150)
        MRF(150)
      }
      for (int i = 0; i < 16; i++) {
        int threshold = (minimums[i] + maximums[i]) / 2;
        EEPROM.update(2 * i, threshold & 0xff);
        EEPROM.update(2 * i + 1, (threshold & 0xff00) >> 8);
      }
    } else {
      counter++;
    }
  }
}

void loop() {
  debugln("S0 : " + String(analogRead(A0 )) + " " + String(thresholds[0 ]));
  debugln("S1 : " + String(analogRead(A1 )) + " " + String(thresholds[1 ]));
  debugln("S2 : " + String(analogRead(A2 )) + " " + String(thresholds[2 ]));
  debugln("S3 : " + String(analogRead(A3 )) + " " + String(thresholds[3 ]));
  debugln("S4 : " + String(analogRead(A4 )) + " " + String(thresholds[4 ]));
  debugln("S5 : " + String(analogRead(A5 )) + " " + String(thresholds[5 ]));
  debugln("S6 : " + String(analogRead(A6 )) + " " + String(thresholds[6 ]));
  debugln("S7 : " + String(analogRead(A7 )) + " " + String(thresholds[7 ]));
  debugln("S8 : " + String(analogRead(A8 )) + " " + String(thresholds[8 ]));
  debugln("S9 : " + String(analogRead(A9 )) + " " + String(thresholds[9 ]));
  debugln("S10: " + String(analogRead(A10)) + " " + String(thresholds[10]));
  debugln("S11: " + String(analogRead(A11)) + " " + String(thresholds[11]));
  debugln("S12: " + String(analogRead(A12)) + " " + String(thresholds[12]));
  debugln("S13: " + String(analogRead(A13)) + " " + String(thresholds[13]));
  debugln("S14: " + String(analogRead(A14)) + " " + String(thresholds[14]));
  debugln("S15: " + String(analogRead(A15)) + " " + String(thresholds[15]));
  debugln("");

  if (analogRead(A7) > thresholds[7]) {
    MLF(180)
    MRF(255)
  } else if (analogRead(A8) > thresholds[8]) {
    MLF(255)
    MRF(180)
  } else if (analogRead(A6) > thresholds[6]) {
    MLF(120)
    MRF(255)
  } else if (analogRead(A9) > thresholds[9]) {
    MLF(255)
    MRF(120)
  } else if (analogRead(A5) > thresholds[5]) {
    MLF(60)
    MRF(255)
  } else if (analogRead(A10) > thresholds[10]) {
    MLF(255)
    MRF(60)
  } else if (analogRead(A4) > thresholds[4]) {
    MLS()
    MRF(255)
  } else if (analogRead(A11) > thresholds[11]) {
    MLF(255)
    MRS()
  } else if (analogRead(A3) > thresholds[3]) {
    MLB(60)
    MRF(255)
  } else if (analogRead(A12) > thresholds[12]) {
    MLF(255)
    MRB(60)
  } else if (analogRead(A2) > thresholds[2]) {
    MLB(120)
    MRF(255)
  } else if (analogRead(A13) > thresholds[13]) {
    MLF(255)
    MRB(120)
  } else if (analogRead(A1) > thresholds[1]) {
    MLB(180)
    MRF(255)
  } else if (analogRead(A14) > thresholds[14]) {
    MLF(255)
    MRB(180)
  } else if (analogRead(A0) > thresholds[0]) {
    MLB(255)
    MRF(255)
  } else if (analogRead(A15) > thresholds[15]) {
    MLF(255)
    MRB(255)
  }
}
