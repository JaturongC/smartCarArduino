
/** Mr. Jaturong Chaleeyuth
 *  Date : 29 August 2016
**/

# include <Servo.h>

#define ECHOPIN 11        // Pin to receive pulse 
#define TRIGPIN 10        // Pin to transmit pulse
#define SERVO 12          // Pin of servo motor

/* motor */
int E1 = 6;
int M1 = 7;   // Left wheel
int E2 = 5;
int M2 = 4;   // Right wheel

Servo myServo;

int detectObject;   // keep a distance value

void setup() {
  Serial.begin(115200);
  
  pinMode(M1, OUTPUT);
  pinMode(M2, OUTPUT);
  pinMode(13, OUTPUT);
  myServo.attach(SERVO);
}

void loop() {
  
  initial();
  // Checking distance (cm.)
  detectObject = calculateDistance();
  
  if(detectObject <= 12) {  // There is obstacle in front of at less than 8 cm. or not?
      backward();
      Break();

      makeDecision(random(1,5));  // Decision that will turn left/right or u-turn left/right.
      Break();
      forward();
  }
  else {
      forward();
  }
}

void initial() {
    myServo.write(90);
    forward();
}

void forward(){
    digitalWrite(M1, LOW);
    digitalWrite(M2, LOW);
    analogWrite(E1, 100); // PWM speed control of left wheel
    analogWrite(E2, 115); // PWM speed control of right wheel
    // Becaus of, speed of both side it's not equal.
    // Serial.println("Forward");
}

void backward(){
    digitalWrite(M1, HIGH);
    digitalWrite(M2, HIGH);
    analogWrite(E1, 120);  
    analogWrite(E2, 130);
    delay(1000);
    // Serial.println("Backward");
}

void Break(){
    analogWrite(E1, 0);  
    analogWrite(E2, 0);
    delay(1000);
    // Serial.println("Break");
}

void makeDecision(int select){
    switch(select){
      case 1:   // Turn L
           digitalWrite(M1, HIGH);
           digitalWrite(M2, LOW);
           analogWrite(E1, 0); 
           analogWrite(E2, 130);
           delay(1675);
          break;
      case 2:   // Turn R
          digitalWrite(M1, LOW);
          digitalWrite(M2, HIGH);
          analogWrite(E1, 120);  
          analogWrite(E2, 0);
          delay(1675);
         break;
      case 3:   // U-turn L
           digitalWrite(M1, HIGH);
           digitalWrite(M2, LOW);
           analogWrite(E1, 0); 
           analogWrite(E2, 130);
           delay(2375);
          break;
      case 4:   // U-turn R
          digitalWrite(M1, LOW);
          digitalWrite(M2, HIGH);
          analogWrite(E1, 120);  
          analogWrite(E2, 130);
          delay(2375);
         break; 
    }
}

int calculateDistance() {
    int distance;
    float duration;
    
    digitalWrite(TRIGPIN, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIGPIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIGPIN, LOW);
  
    duration = pulseIn(ECHOPIN, HIGH);
    distance = duration * 0.034 / 2;    // unit centimatre
    delay(500);
    return distance;
}

