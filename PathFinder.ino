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
#define THRESHOLD 512

#define DEBUG

#ifdef DEBUG
#define debugbegin(x) Serial.begin(x)
#define debugln(x)    Serial.println(x)
#define debug(x)      Serial.print(x)
#else
#define debugbegin(x)
#define debugln(x)
#define debug(x)
#endif

void setup() {
  debugbegin(9600);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(EN1, OUTPUT);
  pinMode(EN2, OUTPUT);
}

void move(int ML, int MR) {
  if (MR > 0) {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    analogWrite(EN1, MR);
  } else if (MR == 0) {
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, HIGH);
    analogWrite(EN1, 255);
  } else {
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    analogWrite(EN1, -MR);
  }

  if (ML > 0) {
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    analogWrite(EN2, ML);
  } else if (ML == 0) {
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, HIGH);
    analogWrite(EN2, 255);
  } else {
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
    analogWrite(EN2, -ML);
  }
}

void loop() {
  debug(analogRead(A0) > THRESHOLD);
  debug(analogRead(A1) > THRESHOLD);
  debug(analogRead(A2) > THRESHOLD);
  debug(analogRead(A3) > THRESHOLD);
  debug(analogRead(A4) > THRESHOLD);
  debug(analogRead(A5) > THRESHOLD);
  debug(analogRead(A6) > THRESHOLD);
  debug(analogRead(A7) > THRESHOLD);
  debug(analogRead(A8) > THRESHOLD);
  debug(analogRead(A9) > THRESHOLD);
  debug(analogRead(A10) > THRESHOLD);
  debug(analogRead(A11) > THRESHOLD);
  debug(analogRead(A12) > THRESHOLD);
  debug(analogRead(A13) > THRESHOLD);
  debug(analogRead(A14) > THRESHOLD);
  debugln(analogRead(A15) > THRESHOLD);

  if (analogRead(A7) > THRESHOLD)       move(180, 255);
  else if (analogRead(A8) > THRESHOLD)  move(255, 180);
  else if (analogRead(A6) > THRESHOLD)  move(120, 255);
  else if (analogRead(A9) > THRESHOLD)  move(255, 120);
  else if (analogRead(A5) > THRESHOLD)  move(60, 255);
  else if (analogRead(A10) > THRESHOLD) move(255, 60);
  else if (analogRead(A4) > THRESHOLD)  move(0, 255);
  else if (analogRead(A11) > THRESHOLD) move(255, 0);
  else if (analogRead(A3) > THRESHOLD)  move(-60, 255);
  else if (analogRead(A12) > THRESHOLD) move(255, -60);
  else if (analogRead(A2) > THRESHOLD)  move(-120, 255);
  else if (analogRead(A13) > THRESHOLD) move(255, -120);
  else if (analogRead(A1) > THRESHOLD)  move(-180, 255);
  else if (analogRead(A14) > THRESHOLD) move(255, -180);
  else if (analogRead(A0) > THRESHOLD)  move(-255, 255);
  else if (analogRead(A15) > THRESHOLD) move(255, -255);
}
