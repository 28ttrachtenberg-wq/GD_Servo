#include <Servo.h>

//Config
int baseJumpDelay = 100;
int restingPos = 1330;

//Jump Program
long jumpList[] = {0, 1500000, 1500000, 1500000, 3000000, 1500000, 700000, 700000, 900000, 700000, 2700000, 700000, 1800000, 1500000, 1200000, 800000, 9000000, 1400000, 1000000, 2000000, 4250000, 3300000, 2200000, 3500000, 1000000, 1800000, 1000000, 1200000, 800000, 800000, 700000, 700000, 900000, 2600000, 1500000, 1000000, 500000, 4500000, 700000, 1100000, 2700000, 1000000, 2700000, 1300000, 2500000, 800000, 1400000, 800000, 2000000};
long jumpLengthList[] = {1, 1, 1, 10, 5, 1, 1, 1, 1, 20, 1, 1, 5, 5, 1, 17.5, 5, 7.5, 7.5, 15, 5, 10, 25, 1, 1, 5, 5, 1, 1, 1, 1, 1, 15, 1, 1, 1, 35, 1, 1, 20, 5, 20, 10, 18, 5, 10, 3, 10, 10};

//Other Vars
Servo jumper;
bool running = false;
int jumpNumber = 0;
long lastJumpTime = 0;
long startTime = 0;
int jumpLength = 1;

void setup() {
  // Sets up servo and input pins
  jumper.attach(9);
  pinMode(2, INPUT_PULLUP);
  Serial.begin(9600);
  Serial.flush();
  Serial.println(lastJumpTime);
  jumper.writeMicroseconds(restingPos);
}

void jump(){
  //Commands the Servo to jump, then return to its resting position
  jumper.writeMicroseconds(1290);
  delay(baseJumpDelay * jumpLength);
  jumper.writeMicroseconds(restingPos);
  Serial.println("jump");
  Serial.println(lastJumpTime);
  Serial.println(jumpNumber);
}

void loop() {
  // Checks if the starting button is pressed
  if(running == false){
    running = not(digitalRead(PIN2));
    if(digitalRead(PIN2) == true){
      startTime = micros();
    }
  }
  //Calls the jump function when the elapsed time is equal to the jump time set in the array
  else if(micros() >= lastJumpTime + jumpList[jumpNumber] + startTime){
    lastJumpTime = lastJumpTime + jumpList[jumpNumber];
    jumpLength = jumpLengthList[jumpNumber];
    jumpNumber ++;
    jump();
  }
  // Ends the program when the level is done
  if(jumpNumber >= (sizeof(jumpList) / sizeof(long))){
      running = false;
      jumpNumber = 0;
      lastJumpTime = 0;
      Serial.println("end");
  }
}