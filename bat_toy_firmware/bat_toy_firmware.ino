
//#include <Adafruit_MPU6050.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_Sensor.h>
#include <OneButton.h>

//#include "mpu6050_init.h" 
//we use tacko li brary for mpu
#include "mpu6050ic.h"
#include "MXC6655XA.h"

Adafruit_SSD1306 mydisplay = Adafruit_SSD1306(128, 64, &Wire);

//pins def
#define acc_int    10
#define mpu_int    9
#define dbg_led    15
//buttons
#define rst_btn    18
#define on_off_btn 23

//onebutton initialization
    OneButton btn = OneButton(
    rst_btn,  // Input pin for the button
    true,        // Button is active LOW
    true         // Enable internal pull-up resistor
     );
  
///////variables////////////
int flips    = 0;
int spins    = 0;
int halfspin = 0;
int face     = 0; //face == 0 means faceup , face == 1 means facedown
int currentface = 0;//will be read when reset is pressed
int levelcompleted = 0;

int level = 0; //double click reset to select the level of desire

void handleClick();
void handlelongpress();
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
  //MPU INITIALIZATION
      mpu_init();
  //MXC INITIALIZATION
      MXC_init();

    pinMode(acc_int, INPUT);
    pinMode(mpu_int, INPUT);
    
    pinMode(rst_btn, INPUT_PULLUP);
    pinMode(on_off_btn, INPUT_PULLUP);
    
    pinMode(dbg_led, OUTPUT);


    btn.attachClick(handleClick); 
      
    btn.attachDoubleClick([]() {
    if(level <= 3 ) level++;
    else{ level = 0;}
    });

    btn.attachLongPressStart(handlelongpress);
}

void loop() {
  //TODO
/*
1 . CODE TO DETECT SUDDEN START OF MOVEMENT AND SUDDEN STOP OF MOVEMEN
2. READ THE CURRENT ANDLE AND POSITION AND KEP TRACK OF THE CHANGE IN ANGLES AS THE PBJECT IS IN MOTION
3. DETECT WHETHER FACE UP OR DOWN AFTER LANDING OR OTHERWISE

*/

   btn.tick();
int moved = 0;
int halt = 0;
  //GETTING ACCELERATIONS DATA
      MXCgetData();
 //COMPARE DATA TO SEE MOVEMENT
 
    if(fabs(mxc_data.mxc_accel_x) >1.5 || fabs(mxc_data.mxc_accel_y)>1.5){
      Serial.println("Moving....");
      moved = 1;
      halt = 0;
      }
     else{
        halt = 1; 
      }
    
  //HELPER
/*
1.BACK FLIP ARE PIVOTED ON THE Y-AXIS SO THE X- AXIS IS THE ONE OF INTEREST AND WHAT WE WILL BE MEASURING TO CHECK FOR BACK FLIP
2.SPINNING IS PIVOTED ON THE X-AXIS AND THUS WE WILL BE CHECKING THE Y AXIS TO DETERMINE THE NUMBER OF SPINS....
NOTE :I SPIN == IF(START VALUE - CURRENT VALUE)>360...WE LL CHECK OVER FLOW IF THEY OCCUR - REQUIRE DIGGING DOCUMENTATION OF LIBS
*/
   getangles(); //reading the angles function and storing them in a global struct
   //accessing the global struct values locally
   float angleD_x = fabs(angle.angle_x); //making sure all angles are positive thus eliminating directional properties
   float angleD_y = fabs(angle.angle_x); //making sure all angles are positive thus eliminating directional properties
   float angleD_z = fabs(angle.angle_x); //making sure all angles are positive thus eliminating directional properties

   //angles returned are from 0-360 and beyond
   //we do comparrisons to check if the reading are within ur ranges
   if(angleD_x>350)
   {
    //if we record a full rotation in the x-axis then we have these backroll/ flippping
    flips = 1;
    resetangle(1);//pass in 1 , 2 or 3 to reset x , y or z azis angle measurements- this avoids measuring values far out of range of 360degrees
    
   }

   if (angleD_y > 170){
    halfspin = 1;
    }
   else if(angleD_y > 350)
   {
    //if we record a full rotation in the x-axis then we have these backroll/ flippping
    spins = 1;
    halfspin = 0;
    resetangle(2);//pass in 1 , 2 or 3 to reset x , y or z azis angle measurements- this avoids measuring values far out of range of 360degrees
    resetangle(3);
   }

  //now to determine if we are facing up or down with the help of the ACCELERATION IN Z-AXIS
  if(moved == 1 && halt == 1){//ensure there was movement and then it stopped
    float side = getaccelz();// when face up g is -ve and vice versa
    face = side < 0 ? 0 : 1 ;
    //then we get the completed level
    String infos = Levels ();
  }
  
//OTHERS 
/*
DETECT BUTTON PRESS - RESET
SLEEP AND WAKEUP FUNCTIONS
*/
}

String Levels (){
  
  if( flips==1 && spins==0 && (currentface == face) && level == 1){
    levelcompleted = 1;
    return "level 1 Complete";
    }
   else if(flips==1 && spins==1 && (currentface == face)&& level == 2 && levelcompleted >= 1){
    levelcompleted = 2;
   return "level 2 Complete";
   }

   else if(flips==1 && halfspin==1 && (currentface != face) && level == 3 && levelcompleted >= 2){
    levelcompleted = 3;
   return "level 3 Complete";
   }
   else if( level == 0)return "Select Level..";
   else if( (level == 2 || level == 3 ) && levelcompleted != 1 ) return "Please finish Level 1";
   else if( (level == 3 ) && levelcompleted != 2 ) return "Please finish Level 2";

   else{
     return "level ^_^ FAILED!!!";
    }
  }

void handleClick(){
    //reset values of spins and flips displayed
    resetangle(1);
    resetangle(2);
    resetangle(3);
    flips    = 0;
    spins    = 0;
    halfspin = 0;
    float side = getaccelz();
    currentface = side < 0 ? 0 : 1 ;
   }
 void handlelongpress(){
  //reset the levels to zero
  levelcompleted =0;
  }
