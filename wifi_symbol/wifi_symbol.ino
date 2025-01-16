#include <Arduino.h>
#include <U8g2lib.h>
#include <SPI.h>
U8G2_ST7567_ENH_DG128064_1_4W_SW_SPI u8g2(U8G2_R0, /* clock=*/ 18, /* data=*/ 23, /* cs=*/ 5, /* dc=*/ 4, /* reset=*/ 2); 


void setup() {
  u8g2.begin(); 
}
void loop() {
  drawWiFiSemiCircles(u8g2);
  delay(3000);
}
void drawWiFiSemiCircles(U8G2 &u8g2) {
  u8g2.firstPage();
  do {
    // Scaled-down semi-circles for the WiFi symbol
    drawSemiCircle(100, 10, 7,u8g2); // Outer semi-circle
    drawSemiCircle(100, 10, 5,u8g2); // Middle semi-circle
    drawSemiCircle(100, 10, 3,u8g2); // Inner semi-circle
    // Scaled-down small circle at the center
    u8g2.drawDisc(100, 10, 1); // Center disc
  } while (u8g2.nextPage());
}

void drawSemiCircle(int cx, int cy, int r,U8G2 &u8g2) {
  // Draw semi-circle using line approximation
  for (int angle = 30; angle <= 150; angle += 10) { // Only 0 to 180 degrees
    float radians = angle * 3.14159 / 180.0;       // Convert degrees to radians
    int x1 = cx + r * cos(radians);
    int y1 = cy - r * sin(radians);               // Subtract to flip Y-axis for display
    int x2 = cx + r * cos(radians + 10 * 3.14159 / 180.0);
    int y2 = cy - r * sin(radians + 10 * 3.14159 / 180.0);
    u8g2.drawLine(x1, y1, x2, y2);                 // Draw the segment
    u8g2.setColorIndex(1);
  }
}
