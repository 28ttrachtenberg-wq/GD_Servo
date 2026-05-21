#include <Servo.h>

//Config
int baseJumpDelay = 100;
int restingPos = 1330;

//Jump Program
long jumpList[] = {0, 1300000, 400000, 1100000, 300000, 1200000, 300000, 1250000, 700000, 3000000, 800000, 1000000, 600000, 1300000, 1000000, 1180000, 800000, 1300000, 2000000, 450000, 450000, 850000, 450000, 1700000, 400000, 950000, 400000, 600000, 700000, 1200000, 600000, 550000, 550000, 550000, 400000, 400000, 1500000, 4500000, 2000000, 1500000, 1250000, 1700000, 800000, 400000, 650000, 400000, 1200000, 1200000, 400000, 400000, 800000, 500000, 3400000, 2800000, 1000000, 800000, 800000, 600000, 400000, 700000, 1200000, 3500000, 600000, 400000, 500000, 1000000, 1300000, 800000, 400000, 500000, 350000, 500000, 1900000, 700000, 600000, 600000, 2600000, 1500000, 400000, 400000, 1300000, 1000000, 1500000, 500000, 600000, 400000, 900000, 900000, 600000, 600000};
long jumpLengthList[] = {1, 1, 1, 1, 1, 1, 10, 1, 20, 1, 1, 5, 1, 5, 5, 1, 5, 5, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 20, 10, 10.5, 1, 10, 5, 1, 1, 1, 1, 10, 1, 1, 1, 1, 17.5, 20, 1, 1, 1, 1, 1, 1, 1, 15, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 15, 1, 1, 1, 12.5, 10, 1, 1, 1, 5, 1, 1, 1, 1, 1, 5, 1, 1, 1};

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