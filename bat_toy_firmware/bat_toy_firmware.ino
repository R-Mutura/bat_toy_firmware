
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
  //TODO
/*
1 . CODE TO DETECT SUDDENT START OF MOVEMENT AND SUDDEN STOP OF MOVEMEN
2. rEAD THE CURRENT ANDLE AND POSITION AND KEP TRACK OF THE CHANGE IN ANGLES AS THE PBJECT IS IN MOTION
3. DETECT WHETHER FACE UP OR DOWN AFTER LANDING OR OTHERWISE

*/

  //HELPER
/*
1.BACK FLIP ARE PIVOTED ON THE Y-AXIS SO THE X- AXIS IS THE ONE OF INTEREST AND WHAT WE WILL BE MEASURING TO CHECK FOR BACK FLIP
2.SPINNING IS PIVOTED ON THE X-AXIS AND THUS WE WILL BE CHECKING THE Y AXIS TO DETERMINE THE NUMBER OF SPINS....
NOTE :I SPIN == IF(START VALUE - CURRENT VALUE)>360...WE LL CHECK OVER FLOW IF THEY OCCUR - REQUIRE DIGGING DOCUMENTATION OF LIBS
*/

//OTHERS 
/*
DETECT BUTTON PRESS - RESET
SLEEP AND WAKEUP FUNCTIONS
*/
}
