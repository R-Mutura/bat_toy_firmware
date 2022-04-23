# bat_toy_firmware

The repo contains all the firmware codes for the project and instructions on how to load them to the hardware

## Requirements
1) Set up the IDE, for this application you will need to download the Arduino ide [here](https://www.arduino.cc/en/software) if you don't have it already installed for your distributions
2) Instal the board support package for ESP32 by goint to ` Tools > Board:xx > Board Manager`. In the search bar type ESP32 and select install ESP32 by Espressid Systems.  3) Now select TinyPico from ` Tools > Board:xx > ESP32 Arduino > TinyPico`
 
 Once done proceed to the next instructions.
## Download the files 
4)  Download all the files on the `Code`:arrow_down_small: on this platform, In your downloads you will get the a folder :file_folder:  `bat_toy_firmware`this will have:
 - bat_toy_firmware.ino
 - mpu6050_init.h
 - mpu6050ic.h
 - MXC6655XA.h and
 - Libraries zip file -this contains all the related libraries used in the project
 ## Library Installation
5)  On library installation unzip the folder :file_folder: `libraries` in the DISHWASHER arduino :file_folder:, copy and paste all the folders to your directory `documents/arduino/library` folder :file_folder:
6)  Open the `bat_toy_firmware.ino`  on `bat_toy_firmware`folder :file_folder: with the downloaded ide, compile and upload to the hardware `(procedure on how to use the ide is on the tutorial link)`:link:    [tutorial](https://www.youtube.com/watch?v=nL34zDTPkcs&t=3s)

# Uploading the codes  :arrow_up:
You can buy the FTDI from here :link: [buy ftdi](https://www.amazon.com/HiLetgo-FT232RL-Converter-Adapter-Breakout/dp/B00IJXZQ7C/ref=sr_1_3?keywords=FTDI&qid=1650483928&sr=8-3)
or here 
 :link: [buy usbasp](https://www.amazon.com/CP2102-Module-Converter-Downloader-Compatible/dp/B092YMT52G_)

1) Insert the FTDI programmer cable socket onto UART headers. ...
2) Open Arduino IDE software. ...
3) Next, call out the source code. ...
4) Select “FTDI” from the Tools > Programmer menu.
5) Select “Upload using Programmer” from the File menu.

You can also explore more from the following tutorial :link:[How to Use FTDI Programmer to upload Code](https://www.youtube.com/watch?v=JYchUapoqzc)

## Debugging 
To see the serial data as sent or received from either of the boards we can use the FTDI programmer or any USB to TTL converter so that you can have access to a serial port. Check out the headers on the board for uart communications 

## Operation of bat_toy

![Bat Toy_5](https://user-images.githubusercontent.com/85989401/164313673-c9fc2fa7-dc00-43d8-b73d-02b5f9d99b8e.png)


![Bat Toy_1](https://user-images.githubusercontent.com/85989401/164313743-d3925834-eb23-4f5f-8454-727115c4af4c.png)

1. Load the battery socket with cr2032 batteries
2. Make sure the toy is on a flat surface and Let it initalize for about 5 seconds. THis enables calibration of the toy for proper measurements
3. Now the toy is ready for use. 
4. Select a level by double pressing the reset button
5. flip the toy around and play to complete the different levels

The reset button is used to reset the values after every round.
- Press once to reset the number of spins and flips to zero
- Long press to reset level to Zero
- Double press to select level

On/Off button is used to turn on and off the toy.
### HAVE FUN
