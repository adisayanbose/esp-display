#include <Arduino.h>
#include <U8g2lib.h>
#include <SPI.h>


U8G2_ST7567_ENH_DG128064_1_4W_SW_SPI u8g2(U8G2_R0, /* clock=*/ 18, /* data=*/ 23, /* cs=*/ 5, /* dc=*/ 4, /* reset=*/ 2); 


void setup() {
   u8g2.begin();
}

void loop() {
  drawDropIcon(u8g2); // Draw the drop icon
  delay(3000);    // Wait 3 seconds before redrawing
}

void drawDropIcon(U8G2 &u8g2) {
  u8g2.firstPage();
  do {
    // Drop dimensions and position
    int centerX = 55; // X-coordinate of the center of the drop
    int centerY = 38; // Y-coordinate of the center of the drop
    int width = 20;   // Width of the drop
    int height = 30;  // Height of the drop

    // Draw the pointed tip of the drop (triangle-like)
    u8g2.drawTriangle(centerX, centerY - height / 2, centerX - width / 2, centerY, centerX + width / 2, centerY);

    // Draw the rounded bottom part of the drop (circle or arc)
    u8g2.drawDisc(centerX, centerY + height / 6, width / 2, U8G2_DRAW_ALL);

  } while (u8g2.nextPage());
}
