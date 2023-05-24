#include <Pixy.h>

// Define the pins for the motor driver board
#define motorA1 8
#define motorA2 9
#define motorB1 10
#define motorB2 11

// Initialize the Pixy1 camera
Pixy pixy;

void setup() {
  // Initialize the motor driver board pins as output
  pinMode(motorA1, OUTPUT);
  pinMode(motorA2, OUTPUT);
  pinMode(motorB1, OUTPUT);
  pinMode(motorB2, OUTPUT);

  // Start the Pixy1 camera
  pixy.init();

  // Start serial communication at 9600 baud
  Serial.begin(9600);
}

void loop() {
  static bool reached_first_object = false;// not in gpt code

  // Read the color code of the object being tracked
  uint16_t blocks = pixy.getBlocks();

  // If a block is found, move the motors based on its position
  if (blocks) {
    // Access the first block using a pointer syntax
    Block *block = &pixy.blocks[0];

    int16_t x = block->x;
    int16_t y = block->y;
    int16_t error = x - 160;  // 160 is the center of the screen

    // Adjust the speed and direction of the motors based on the error
    int16_t speed = abs(error) / 2;
    int16_t turn = map(abs(error), 0, 160, 0, 255);

    if (error <= 20 && error >= -20) {
      // Move forward or backward based on the object size
      if (block->width > 50) {
        // Stop the robot after reaching the first object
        if (!reached_first_object) {
          analogWrite(motorA1, 0);
          analogWrite(motorA2, 0);
          analogWrite(motorB1, 0);
          analogWrite(motorB2, 0);
          reached_first_object = true;
        } else {
          // Wait for a new object to be detected before moving again
          reached_first_object = false;
        }
      } else { // move forward
        analogWrite(motorA1, 100);
        analogWrite(motorA2, 00);
        analogWrite(motorB1, 100);
        analogWrite(motorB2, 00);
      }
    } else if (error > 20 && error <150) {
      // Turn right
      analogWrite(motorA1, speed);
      analogWrite(motorA2, 0);
      analogWrite(motorB1, 0);
      analogWrite(motorB2, turn);
    } 
    else if(error < -20 && error >-150){
      // Turn left
      analogWrite(motorA1, 0);
      analogWrite(motorA2, turn);
      analogWrite(motorB1, speed);
      analogWrite(motorB2, 0);
    }
    else {// i thnik it should be out the if (block)
      analogWrite(motorA1, 0);
      analogWrite(motorA2, 0);
      analogWrite(motorB1, 0);
      analogWrite(motorB2, 0);
    }

    // Print the error, speed, and turn values to the serial monitor
    Serial.print("Error: ");
    Serial.print(error);
    Serial.print(", Speed: ");
    Serial.print(speed);
    Serial.print(", Turn: ");
    Serial.println(turn);
  }
}
