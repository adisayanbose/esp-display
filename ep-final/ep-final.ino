#include <Arduino.h>
#include <U8g2lib.h>
#include <SPI.h>


U8G2_ST7567_ENH_DG128064_1_4W_SW_SPI u8g2(U8G2_R0, /* clock=*/ 18, /* data=*/ 23, /* cs=*/ 5, /* dc=*/ 4, /* reset=*/ 2); 

void setup(void) {
  u8g2.begin();
}

void loop(void) {
  u8g2.firstPage();
  do {
     u8g2.drawFrame(5, 0, 122, 64);
     drawBluetoothSymbol(u8g2);
  } while (u8g2.nextPage());
  delay(1000);
}

void drawBluetoothSymbol(U8G2 &u8g2) {

    // Center of the display (128x64), position the symbol around the center
    int centerX = 114; // X-coordinate of the center
    int centerY = 12; // Y-coordinate of the center
    int size = 7;     // Half of the 15x15 size for scaling


    u8g2.drawBox(centerX - 1, centerY - size, 1, 2 * size);
    // Top arrow (rightward diagonal)
    u8g2.drawLine(centerX, centerY - size, centerX + size, centerY - size / 2); // Diagonal line
 

    // Bottom arrow (rightward diagonal)
    u8g2.drawLine(centerX, centerY + size, centerX + size, centerY + size / 2); // Diagonal line

    // Cross lines (X shape)
    u8g2.drawLine(centerX + size, centerY - size / 2, centerX - size, centerY + size / 2); // Top-left diagonal
    u8g2.drawLine(centerX + size, centerY + size / 2, centerX - size, centerY - size / 2); // Bottom-left diagonal

}
