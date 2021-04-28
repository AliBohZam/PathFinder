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
#define debug(x)    Serial.print(x)
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
  bool sensors[16];
  sensors[0] = analogRead(A0) > THRESHOLD;
  sensors[1] = analogRead(A1) > THRESHOLD;
  sensors[2] = analogRead(A2) > THRESHOLD;
  sensors[3] = analogRead(A3) > THRESHOLD;
  sensors[4] = analogRead(A4) > THRESHOLD;
  sensors[5] = analogRead(A5) > THRESHOLD;
  sensors[6] = analogRead(A6) > THRESHOLD;
  sensors[7] = analogRead(A7) > THRESHOLD;
  sensors[8] = analogRead(A8) > THRESHOLD;
  sensors[9] = analogRead(A9) > THRESHOLD;
  sensors[10] = analogRead(A10) > THRESHOLD;
  sensors[11] = analogRead(A11) > THRESHOLD;
  sensors[12] = analogRead(A12) > THRESHOLD;
  sensors[13] = analogRead(A13) > THRESHOLD;
  sensors[14] = analogRead(A14) > THRESHOLD;
  sensors[15] = analogRead(A15) > THRESHOLD;

  debug(sensors[0]);
  debug(sensors[1]);
  debug(sensors[2]);
  debug(sensors[3]);
  debug(sensors[4]);
  debug(sensors[5]);
  debug(sensors[6]);
  debug(sensors[7]);
  debug(sensors[8]);
  debug(sensors[9]);
  debug(sensors[10]);
  debug(sensors[11]);
  debug(sensors[12]);
  debug(sensors[13]);
  debug(sensors[14]);
  debugln(sensors[15]);

  if (sensors[7])       move(180, 255);
  else if (sensors[8])  move(255, 180);
  else if (sensors[6])  move(120, 255);
  else if (sensors[9])  move(255, 120);
  else if (sensors[5])  move(60, 255);
  else if (sensors[10]) move(255, 60);
  else if (sensors[4])  move(0, 255);
  else if (sensors[11]) move(255, 0);
  else if (sensors[3])  move(-60, 255);
  else if (sensors[12]) move(255, -60);
  else if (sensors[2])  move(-120, 255);
  else if (sensors[13]) move(255, -120);
  else if (sensors[1])  move(-180, 255);
  else if (sensors[14]) move(255, -180);
  else if (sensors[0])  move(-255, 255);
  else if (sensors[15]) move(255, -255);
}
