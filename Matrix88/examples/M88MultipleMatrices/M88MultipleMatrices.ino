//We always have to include the library
#include "Matrix88.h"

/*
 Now we need a Matrix to work with.
 ***** Check these pin numbers are compatible with your device *****
 pin 13 is connected to the DataIn 
 pin 12 is connected to the CLK 
 pin 11 is connected to LOAD 
 ***** Please set the number of devices you have *****
 But the maximum default of 8 MAX72XX wil also work.
 */
Matrix88 M88=Matrix88(13,12,11,8);

/* we always wait a bit between updates of the display */
unsigned long delaytime=500;

/* 
 All matrices must be individually initialized .
 */
void setup() {
  // The Matrix88 class sets the number of devices when it is created
  int devices=lc.getDeviceCount();
  //we have to init all devices in a loop
  for(int address=0;address<devices;address++) {
    /*The MAX72XX is in power-saving mode on startup*/
    lc.shutdown(address,false);
    /* Set the brightness to a medium values */
    lc.setIntensity(address,8);
    /* and clear the display */
    lc.clearDisplay(address);
  }
}

void loop() { 
  //read the number cascaded devices
  int devices=lc.getDeviceCount();
  
  //we have to init all devices in a loop
  for(int row=0;row<8;row++) {
    for(int col=0;col<8;col++) {
      for(int address=0;address<devices;address++) {
        delay(delaytime);
        lc.setLed(address,row,col,true);
        delay(delaytime);
        lc.setLed(address,row,col,false);
      }
    }
  }
}
