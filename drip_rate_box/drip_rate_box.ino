#include <Arduino.h>
#include <U8g2lib.h>
#include <SPI.h>
U8G2_ST7567_ENH_DG128064_1_4W_SW_SPI u8g2(U8G2_R0, /* clock=*/ 18, /* data=*/ 23, /* cs=*/ 5, /* dc=*/ 4, /* reset=*/ 2); 

int drip_factor=2;
void setup(void) {
  u8g2.begin();
}

void loop(void) {
  u8g2.firstPage();
  do {
    drawNumberBox(0,23,u8g2);
  } while (u8g2.nextPage());
  delay(1000);
}

void drawNumberBox(int topLeftX,int topLeftY,U8G2 &u8g2) {
    // Set font for numbers
    u8g2.setFont(u8g_font_6x10);
    
    // Calculate center position based on top-left coordinates
    int boxCenterX = topLeftX + 20;  // Center is 20 pixels right of top-left X
    
    // Draw numbers with vertical spacing of 12 pixels
    // Draw "10"
    int textWidth = u8g2.getStrWidth("10");
    u8g2.drawStr(boxCenterX - (textWidth/2), topLeftY + 10, "10");
    if (drip_factor == 1) {
      u8g2.drawFrame(boxCenterX - (textWidth/2) - 2, (topLeftY + 10) - 9, textWidth + 4, 11);  
    }
    // Draw "15"
    textWidth = u8g2.getStrWidth("15");
    u8g2.drawStr(boxCenterX - (textWidth/2), topLeftY + 22, "15");
    if (drip_factor == 2) {
      u8g2.drawFrame(boxCenterX - (textWidth/2) - 2, (topLeftY + 22) - 9, textWidth + 4, 11);
    } 
    // Draw "20"
    textWidth = u8g2.getStrWidth("20");
    u8g2.drawStr(boxCenterX - (textWidth/2), topLeftY + 34, "20");
    if (drip_factor == 3) {
      u8g2.drawFrame(boxCenterX - (textWidth/2) - 2, (topLeftY + 34) - 9, textWidth + 4, 11);
    }
}
