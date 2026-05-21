#include <Servo.h>

//Config
int baseJumpDelay = 100;
int restingPos = 1330;

//Jump Program
long jumpList[] = {};
long jumpLengthList[] = {};

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