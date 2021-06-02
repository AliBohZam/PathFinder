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
#define EN1 2
#define EN2 3
#define IN1 50
#define IN2 51
#define IN3 52
#define IN4 53

#define S0THRESHOLD (S0BLACK + S0WHITE)/2
#define S1THRESHOLD (S1BLACK + S1WHITE)/2
#define S2THRESHOLD (S2BLACK + S2WHITE)/2
#define S3THRESHOLD (S3BLACK + S3WHITE)/2
#define S4THRESHOLD (S4BLACK + S4WHITE)/2
#define S5THRESHOLD (S5BLACK + S5WHITE)/2
#define S6THRESHOLD (S6BLACK + S6WHITE)/2
#define S7THRESHOLD (S7BLACK + S7WHITE)/2
#define S8THRESHOLD (S8BLACK + S8WHITE)/2
#define S9THRESHOLD (S9BLACK + S9WHITE)/2
#define S10THRESHOLD (S10BLACK + S10WHITE)/2
#define S11THRESHOLD (S11BLACK + S11WHITE)/2
#define S12THRESHOLD (S12BLACK + S12WHITE)/2
#define S13THRESHOLD (S13BLACK + S13WHITE)/2
#define S14THRESHOLD (S14BLACK + S14WHITE)/2
#define S15THRESHOLD (S15BLACK + S15WHITE)/2

#define MRF(pwm) {digitalWrite(IN1, LOW);  digitalWrite(IN2, HIGH); analogWrite(EN1, pwm);}
#define MRB(pwm) {digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);  analogWrite(EN1, pwm);}
#define MRS()    {digitalWrite(IN1, HIGH); digitalWrite(IN2, HIGH); analogWrite(EN1, 255);}
#define MLF(pwm) {digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);  analogWrite(EN2, pwm);}
#define MLB(pwm) {digitalWrite(IN3, LOW);  digitalWrite(IN4, HIGH); analogWrite(EN2, pwm);}
#define MLS()    {digitalWrite(IN3, HIGH); digitalWrite(IN4, HIGH); analogWrite(EN2, 255);}

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

// Calibrate these
#define S0BLACK 724
#define S0WHITE 300
#define S1BLACK 724
#define S1WHITE 300
#define S2BLACK 724
#define S2WHITE 300
#define S3BLACK 724
#define S3WHITE 300
#define S4BLACK 724
#define S4WHITE 300
#define S5BLACK 724
#define S5WHITE 300
#define S6BLACK 724
#define S6WHITE 300
#define S7BLACK 724
#define S7WHITE 300
#define S8BLACK 724
#define S8WHITE 300
#define S9BLACK 724
#define S9WHITE 300
#define S10BLACK 724
#define S10WHITE 300
#define S11BLACK 724
#define S11WHITE 300
#define S12BLACK 724
#define S12WHITE 300
#define S13BLACK 724
#define S13WHITE 300
#define S14BLACK 724
#define S14WHITE 300
#define S15BLACK 724
#define S15WHITE 300

void setup() {
  debugbegin(9600);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(EN1, OUTPUT);
  pinMode(EN2, OUTPUT);
}

void loop() {
  debug(analogRead(A0) + " ");
  debug(analogRead(A1) + " ");
  debug(analogRead(A2) + " ");
  debug(analogRead(A3) + " ");
  debug(analogRead(A4) + " ");
  debug(analogRead(A5) + " ");
  debug(analogRead(A6) + " ");
  debug(analogRead(A7) + " ");
  debug(analogRead(A8) + " ");
  debug(analogRead(A9) + " ");
  debug(analogRead(A10) + " ");
  debug(analogRead(A11) + " ");
  debug(analogRead(A12) + " ");
  debug(analogRead(A13) + " ");
  debug(analogRead(A14) + " ");
  debugln(analogRead(A15));

  if (analogRead(A7) > S7THRESHOLD) {
    MLF(180)
    MRF(255)
  } else if (analogRead(A8) > S8THRESHOLD) {
    MLF(255)
    MRF(180)
  } else if (analogRead(A6) > S6THRESHOLD) {
    MLF(120)
    MRF(255)
  } else if (analogRead(A9) > S9THRESHOLD) {
    MLF(255)
    MRF(120)
  } else if (analogRead(A5) > S5THRESHOLD) {
    MLF(60)
    MRF(255)
  } else if (analogRead(A10) > S10THRESHOLD) {
    MLF(255)
    MRF(60)
  } else if (analogRead(A4) > S4THRESHOLD) {
    MLS()
    MRF(255)
  } else if (analogRead(A11) > S11THRESHOLD) {
    MLF(255)
    MRS()
  } else if (analogRead(A3) > S3THRESHOLD) {
    MLB(60)
    MRF(255)
  } else if (analogRead(A12) > S12THRESHOLD) {
    MLF(255)
    MRB(60)
  } else if (analogRead(A2) > S2THRESHOLD) {
    MLB(120)
    MRF(255)
  } else if (analogRead(A13) > S13THRESHOLD) {
    MLF(255)
    MRB(120)
  } else if (analogRead(A1) > S1THRESHOLD) {
    MLB(180)
    MRF(255)
  } else if (analogRead(A14) > S14THRESHOLD) {
    MLF(255)
    MRB(180)
  } else if (analogRead(A0) > S0THRESHOLD) {
    MLB(255)
    MRF(255)
  } else if (analogRead(A15) > S15THRESHOLD) {
    MLF(255)
    MRB(255)
  }
}
