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

#define EN1 2
#define EN2 3
#define IN1 50
#define IN2 51
#define IN3 52
#define IN4 53

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

#define THRESHOLD 750

void setup() {
  debugbegin(9600);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(EN1, OUTPUT);
  pinMode(EN2, OUTPUT);
}

unsigned int counter = 0;

void loop() {
  bool sensors[15];
  sensors[0]  = analogRead(A0 ) > THRESHOLD;
  sensors[1]  = analogRead(A1 ) > THRESHOLD;
  sensors[2]  = analogRead(A2 ) > THRESHOLD;
  sensors[3]  = analogRead(A3 ) > THRESHOLD;
  sensors[4]  = analogRead(A4 ) > THRESHOLD;
  sensors[5]  = analogRead(A5 ) > THRESHOLD;
  sensors[6]  = analogRead(A6 ) > THRESHOLD;
  sensors[7]  = analogRead(A7 ) > THRESHOLD;
  sensors[8]  = analogRead(A8 ) > THRESHOLD;
  sensors[9]  = analogRead(A9 ) > THRESHOLD;
  sensors[10] = analogRead(A10) > THRESHOLD;
  sensors[11] = analogRead(A11) > THRESHOLD;
  sensors[12] = analogRead(A12) > THRESHOLD;
  sensors[13] = analogRead(A13) > THRESHOLD;
  sensors[14] = analogRead(A14) > THRESHOLD;
  debug((sensors[0])? "1" : "0");
  debug((sensors[1])? "1" : "0");
  debug((sensors[2])? "1" : "0");
  debug((sensors[3])? "1" : "0");
  debug((sensors[4])? "1" : "0");
  debug((sensors[5])? "1" : "0");
  debug((sensors[6])? "1" : "0");
  debug((sensors[7])? "1" : "0");
  debug((sensors[8])? "1" : "0");
  debug((sensors[9])? "1" : "0");
  debug((sensors[10])? "1" : "0");
  debug((sensors[11])? "1" : "0");
  debug((sensors[12])? "1" : "0");
  debug((sensors[13])? "1" : "0");
  debug((sensors[14])? "1" : "0");
  debugln("");
  //while(1){
  //  debugln(String(analogRead(A12)));
  //}

  if (sensors[0] && sensors[1] && sensors[2] && sensors[3] && sensors[4] && sensors[5] && sensors[6] && sensors[7] && sensors[8] && sensors[9] && sensors[10] && sensors[11] && sensors[12] && sensors[13] && sensors[14]) {
    if (++counter > 10) {
      while(1) {
        MLS()
        MRS()
      }
    }
  } else {
    counter = 0;
  }

  if (sensors[7]) {
    MLF(255)
    MRF(255)
  } else if (sensors[8]) {
    MLF(255)
    MRF(150)
  } else if (sensors[6]) {
    MLF(150)
    MRF(255)
  } else if (sensors[9]) {
    MLF(255)
    MRF(70)
  } else if (sensors[5]) {
    MLF(70)
    MRF(255)
  } else if (sensors[10]) {
    MLF(255)
    MRS()
  } else if (sensors[4]) {
    MLS()
    MRF(255)
  } else if (sensors[11]) {
    MLF(255)
    MRB(90)
  } else if (sensors[3]) {
    MLB(90)
    MRF(255)
  } else if (sensors[12]) {
    MLF(255)
    MRB(180)
  } else if (sensors[2]) {
    MLB(180)
    MRF(255)
  } else if (sensors[13]) {
    MLF(255)
    MRB(225)
  } else if (sensors[1]) {
    MLB(225)
    MRF(255)
  } else if (sensors[14]) {
    MLF(255)
    MRB(255)
  } else if (sensors[0]) {
    MLB(255)
    MRF(255)
  }
}
