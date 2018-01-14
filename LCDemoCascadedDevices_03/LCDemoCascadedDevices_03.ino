//We always have to include the library
//#include "Serial.h"

#include "LedControl.h"
//Added the LED & Key TM1628 Library to allow for control of the demo modes
#include <TM1638.h>

#define MODULES 1 //4

/*
  Now we need a LedControl to work with.
 ***** These pin numbers will probably not work with your hardware *****
  pin 12 is connected to the DataIn
  pin 11 is connected to the CLK
  pin 10 is connected to LOAD
 ***** Please set the number of devices you have *****
  But the maximum default of 8 MAX72XX wil also work.
*/
LedControl lc = LedControl(12, 11, 10, 3);
int devices;

// define a modules
TM1638 modules[] = {
  TM1638(9, 8, 7),
  TM1638(9, 8, 6),
  TM1638(9, 8, 5),
  TM1638(9, 8, 4)
};

/* we always wait a bit between updates of the display */
unsigned long delaytime = 5;

const char string[] = "0123456789ABCDEF";
int base = 0;
int counter = 0;

/*
  This time we have more than one device.
  But all of them have to be initialized
  individually.
*/
void setup() {
  //we have already set the number of devices when we created the LedControl
  devices = lc.getDeviceCount();
  //we have to init all devices in a loop
  for (int address = 0; address < devices; address++) {
    /*The MAX72XX is in power-saving mode on startup*/
    lc.shutdown(address, false);
    /* Set the brightness to a medium values */
    lc.setIntensity(address, 8);
    /* and clear the display */
    lc.clearDisplay(address);
  }
  Serial.begin(9600);
}

void columnScan() {
  //we have to init all devices in a loop
  for (int row = 0; row < 8; row++) {
    for (int col = 0; col < 8; col++) {
      for (int address = 0; address < devices; address++) {
        delay(delaytime);
        lc.setLed(address, row, col, true);
        delay(delaytime);
        lc.setLed(address, row, col, false);
      }
    }
  }
}

void columnScanEach() {
  //we have to init all devices in a loop
  for (int address = 0; address < devices; address++) {
    for (int row = 0; row < 8; row++) {
      for (int col = 0; col < 8; col++) {
        delay(delaytime);
        lc.setLed(address, row, col, true);
        delay(delaytime);
        lc.setLed(address, row, col, false);
      }
    }
  }
}

void rowScan() {
  //we have to init all devices in a loop
  for (int col = 0; col < 8; col++) {
    for (int row = 0; row < 8; row++) {
      for (int address = 0; address < devices; address++) {
        delay(delaytime);
        lc.setLed(address, row, col, true);
        delay(delaytime);
        lc.setLed(address, row, col, false);
      }
    }
  }
}

void rowScanEach() {
  //we have to init all devices in a loop
  for (int address = 0; address < devices; address++) {
    for (int col = 0; col < 8; col++) {
      for (int row = 0; row < 8; row++) {
        delay(delaytime);
        lc.setLed(address, row, col, true);
        delay(delaytime);
        lc.setLed(address, row, col, false);
      }
    }
  }
}

void randomBoard(int address, int density) {
  lc.setIntensity(0, random(5));
  for (int row = 0; row < 8; row++) {
    for (int col = 0; col < 8; col++) {
      lc.setLed(address, row, col, random(density) == 0);
    }
  }
  lc.setIntensity(0, 8);
}

void randomBoardSequential(int n, int density) {
  for (int k = 0; k < n; k++) {
    for (int address = 0; address < devices; address++) {
      randomBoard(address, density);
    }
  }
}

void randomly(int delaytime, int n) {
  lc.setIntensity(0, random(5));
  for (int k = 0; k < n; k++) {
    for (int address = 0; address < devices; address++) {
      int row = random(8);
      int col = random(8);
      lc.setLed(address, row, col, random(2));
    }
    delay(delaytime);
  }
  lc.setIntensity(0, 8);
}

void squares(int address, int state) {
  for (int k = 0; k < 8; k++) {
    for (int row = 0; row <= k; row++) {
      for (int col = 0; col <= k; col++) {
        lc.setLed(address, row, col, state);
      }
      delay(delaytime);
    }
    delay(delaytime);
  }
}

void squares2(int address, int state) {
  for (int k = 7; k >= 0; k--) {
    for (int row = 7; row >= k; row--) {
      for (int col = 7; col >= k; col--) {
        lc.setLed(address, row, col, state);
      }
      delay(delaytime);
    }
    delay(delaytime);
  }
}

void repeatSquares(int n) {
  for (int k = 0; k < n; k++) {
    squares(0, 1);
    //    squares(1, 1);
    squares(0, 0);
    //    squares(1, 0);
  }
}

void repeatSquares2(int n) {
  for (int k = 0; k < n; k++) {
    squares2(0, 1);
    squares2(1, 1);
    squares2(0, 0);
    squares2(1, 0);
  }
}

void repeatSquaresDiag(int n) {
  for (int k = 0; k < n; k++) {
    squares (0, 1);
    squares2(0, 0);
    squares (1, 1);
    squares2(1, 0);

    squares2(0, 1);
    squares (0, 0);
    squares2(1, 1);
    squares (1, 0);
  }
}

void squaresAll(int state) {
  for (int k = 0; k < 8; k++) {
    for (int row = 0; row <= k; row++) {
      for (int col = 0; col <= k; col++) {
        for (int address = 0; address < devices; address++) {
          lc.setLed(address, row, col, state);
        }
      }
      delay(delaytime);
    }
    delay(delaytime);
  }
}

void squaresAll2(int state) {
  for (int k = 7; k >= 0; k--) {
    for (int row = 7; row >= k; row--) {
      for (int col = 7; col >= k; col--) {
        for (int address = 0; address < devices; address++) {
          lc.setLed(address, row, col, state);
        }
      }
      delay(delaytime);
    }
    delay(delaytime);
  }
}

void repeatSquaresAll(int n) {
  for (int k = 0; k < n; k++) {
    squaresAll(1);
    squaresAll(0);
  }
}

void repeatSquaresAll2(int n) {
  for (int k = 0; k < n; k++) {
    squaresAll2(1);
    squaresAll2(0);
  }
}

void repeatSquaresAllDiag(int n) {
  for (int k = 0; k < n; k++) {
    squaresAll (1);
    squaresAll2(0);

    squaresAll2(1);
    squaresAll (0);
  }
}

void LCLoop() {
  TMLoop(); Serial.println ("columnScan()"); columnScan();
  TMLoop(); Serial.println ("rowScan()"); rowScan();
  TMLoop(); Serial.println ("randomly(delaytime / 2, 1000)"); randomly(delaytime / 2, 1000);
  TMLoop(); Serial.println ("repeatSquares (3)"); repeatSquares (3);
  TMLoop(); Serial.println ("repeatSquares2(3)"); repeatSquares2(3);
  TMLoop(); Serial.println ("repeatSquaresAll (3"); repeatSquaresAll (3);
  TMLoop(); Serial.println ("repeatSquaresAll2(3)"); repeatSquaresAll2(3);
  TMLoop(); Serial.println ("columnScanEach()"); columnScanEach();
  TMLoop(); Serial.println ("rowScanEach()"); rowScanEach();
  TMLoop(); Serial.println ("randomBoardSequential(1000, 18)"); randomBoardSequential(1000, 18);
  TMLoop(); Serial.println ("repeatSquaresDiag(3)"); repeatSquaresDiag(3);
  TMLoop(); Serial.println ("repeatSquaresAllDiag(3)"); repeatSquaresAllDiag(3);
}

void TMLoop() {
  /* for (int i = 0; i < MODULES; i++) {
     const char* pos = string + base + (i * 8);

     if (pos >= string && pos + 8 < string + sizeof(string)) {
       modules[i].setDisplayToString(pos);
     } else {
       modules[i].clearDisplay();
     }
    }

    base++;

    if (base == sizeof(string) - 8) {
     base = -MODULES * 8;
    }\*/
  //  modules[0].setLEDs(random(256));
  modules[0].setLEDs(counter % 256);
  modules[0].setDisplayToHexNumber(counter, 1 << 5);
  counter++;

}

void loop() {
  LCLoop();
}

