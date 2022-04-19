
#include <Adafruit_MPU6050.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_Sensor.h>

//#include "mpu6050_init.h" 
//we use tacko li brary for mpu
#include "mpu6050ic.h"
#include "MXC6655XA.h"

Adafruit_SSD1306 mydisplay = Adafruit_SSD1306(128, 64, &Wire);



void setup() {
  // put your setup code here, to run once:
 
 
  Serial.begin(115200);
  while (!Serial)
  delay(10); // will pause Zero, Leonardo, etc until serial console opens
  
    
    //initialize display
    if (!mydisplay.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for (;;)
      ; // Don't proceed, loop forever
    }
    mydisplay.display();
    delay(500); // Pause for 0.5 seconds
    mydisplay.setTextSize(1);
    mydisplay.setTextColor(WHITE);
    mydisplay.setRotation(0);
    mpu_init();
    
}

void loop() {
  // put your main code here, to run repeatedly:

}
