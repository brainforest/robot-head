#include <Servo.h>
#include <LedControl.h>
 
#include <MD_Parola.h>
#include <MD_MAX72XX.h>
Servo servo0;
Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;
Servo servo5;
// Define the number of devices and the hardware type
#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES 4

// Define the pins for the MAX7219

#define DATA_PIN 8
#define CS_PIN 9
#define CLK_PIN 10

// Create a new instance of the MD_MAX72XX library
MD_MAX72XX ledMatrix = MD_MAX72XX(HARDWARE_TYPE, DATA_PIN, CLK_PIN, CS_PIN, MAX_DEVICES);



boolean eye_opened = 0;

void open_eye() {
  eye_opened = 1;
  servo2.write(-180);
  servo3.write(135);
  servo4.write(180);
  servo5.write(45);
  delay(250);
}

void close_eye() {
  eye_opened = 0;
  servo2.write(90);
  servo3.write(90);
  servo4.write(90);
  servo5.write(90);
  delay(250);
}

void eye_left() {
  // eye left
  servo0.write(90 + 25);
  delay(250);
}

void eye_rigth() {
  // eye right
  servo0.write(90 - 25);
  delay(250);
}

void eye_netural_leftrigh() {
  // eye neutral
  servo0.write(90);
  delay(250);

}

void eye_up() {
  //eye up
  servo1.write(90 + 30);
  delay(500);
}

void eye_down() {

  //eye dowm
  servo1.write(90 - 30);
  delay(500);

}

void eye_netural_updown() {
  // eye netral
  servo1.write(90);
  delay(500);
}


// Blink Eye (from open to close)
void blink_eye() {
  if (eye_opened == 0) {
    open_eye();
    close_eye();
    open_eye();
    close_eye();
    open_eye();
  } else {
    close_eye();
    open_eye();
    close_eye();
    open_eye();
  }
}

void initial() {
  // Set all servos to the neutral position (90 degrees)
  eye_opened = 0;
  servo0.write(90);
  servo1.write(90);
  servo2.write(90);
  servo3.write(90);
  servo4.write(90);
  servo5.write(90);
}

 

void setup() {
  servo0.attach(0);
  servo1.attach(1);
  servo2.attach(2);
  servo3.attach(3);
  servo4.attach(4);
  servo5.attach(5);

   initial();

  initial();
  delay(1000);

  // Initialize the LED matrix
  ledMatrix.begin();
  ledMatrix.control(MD_MAX72XX::INTENSITY, 15);  // Set the brightness (0-15)
  ledMatrix.clear();   // Clear the display


 
}

void agiz() {
  
    // Perform the Knight Rider effect
  for (int i = 8; i < 32 - 9; i++) {
    ledMatrix.clear();

    // Light up the LEDs for the "eyes"
    for (int j = 0; j < 8; j++) {
      ledMatrix.setPoint(2, i, true);  // Left eye
      ledMatrix.setPoint(2, i + 1, true);
      ledMatrix.setPoint(3, i, true);  // Left eye
      ledMatrix.setPoint(3, i + 1, true);
      ledMatrix.setPoint(4, i, true);
      ledMatrix.setPoint(4, i + 1, true);

      ledMatrix.setPoint(5, i, true);  // Right eye
      ledMatrix.setPoint(5, i + 1, true);
    }

  }

  for (int i = 32 - 9; i > 9; i--) {
    ledMatrix.clear();

    // Light up the LEDs for the "eyes"
    for (int j = 0; j < 8; j++) {
      ledMatrix.setPoint(2, i, true);  // Left eye
      ledMatrix.setPoint(2, i + 1, true);
      ledMatrix.setPoint(3, i, true);  // Left eye
      ledMatrix.setPoint(3, i + 1, true);
      ledMatrix.setPoint(4, i, true);
      ledMatrix.setPoint(4, i + 1, true);

      ledMatrix.setPoint(5, i, true);  // Right eye
      ledMatrix.setPoint(5, i + 1, true);
    }

  }
}

void animate() {
   
  // No need to do anything in the loop
  open_eye();

  delay(100);
  blink_eye();
  delay(100);

/*
  eye_left();
  delay(500);
  eye_rigth();
  eye_netural_leftrigh();
  eye_left();
  delay(500);
  eye_rigth();
  eye_netural_leftrigh();
  delay(500);
  //eye_up();
  delay(500);
  //eye_down();
  delay(500);
  //eye_netural_updown();
  delay(500);

  close_eye();
  open_eye();
  close_eye();
  open_eye();
  close_eye();
  open_eye();*/


  //initial();
  //delay(100);

}


void loop() {
  unsigned long previousMillis = 0;
    unsigned long previousMillisAgiz = 0;
  unsigned long previousMillisAnimate = 0;
  const long agizInterval = 500; // Interval for mouth animation (milliseconds)
  const long animateInterval = 2000; // Interval for eye animation (milliseconds)

  while (true) {

     unsigned long currentMillis = millis();
    // Run the mouth animation every agizInterval milliseconds
    if (currentMillis - previousMillisAgiz >= agizInterval) {
      agiz();
      previousMillisAgiz = currentMillis;
    }

    // Run the eye animation every animateInterval milliseconds
    if (currentMillis - previousMillisAnimate >= animateInterval) {
      animate();
      previousMillisAnimate = currentMillis;
    }

    // Allow other tasks or processes to run during the loop
    // You can add additional code here if needed

    // Delay to give other tasks or processes time to run
    delay(10); // Adjust this delay as needed
  }
}
