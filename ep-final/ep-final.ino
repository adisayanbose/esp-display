#include <Arduino.h>
#include <U8g2lib.h>
#include <SPI.h>


U8G2_ST7567_ENH_DG128064_1_4W_SW_SPI u8g2(U8G2_R0, /* clock=*/ 18, /* data=*/ 23, /* cs=*/ 5, /* dc=*/ 4, /* reset=*/ 2); 

const unsigned char BELL_BITMAP[] PROGMEM = {
  0xF0, 0x01,  
  0xF8, 0x03, 
  0xFC, 0x07,    
  0xFC, 0x07, 
  0xFC, 0x07,    
  0xFC, 0x07,   
  0xFC, 0x07,   
  0xFF, 0x1F,
  0xFF, 0x1F,  
  0xFF, 0x1F,   
  0x00, 0x00,  
  0xF0, 0x01,   
  0xF8, 0x03,   
  0xF8, 0x03,  
  0xF0, 0x01,   
};

int drip_factor=2;
int flowrate=90;
void setup(void) {
  u8g2.begin();
}

void loop(void) {
  u8g2.firstPage();
  do {
     u8g2.drawFrame(5, 0, 122, 64);
     u8g2.drawLine(0, 20, 128,20); 
     u8g2.drawLine(45, 20, 45,64);
     drawBatteryIcon(75,u8g2);
     drawBluetoothSymbol(u8g2);
     drawWiFiSemiCircles(u8g2);
     drawDropIcon(u8g2);
     drawText(flowrate,u8g2);
     drawNumberBox(0,23,u8g2);
     u8g2.drawXBMP(70, 3, 16, 15, BELL_BITMAP);
  } while (u8g2.nextPage());
  delay(1000);
}

void drawBluetoothSymbol(U8G2 &u8g2) {

    // Center of the display (128x64), position the symbol around the center
    int centerX = 114; // X-coordinate of the center
    int centerY = 10; // Y-coordinate of the center
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

void drawBatteryIcon(int charge,U8G2 &u8g2) {
  // Battery dimensions and position
  int x =10;           // X-coordinate of the top-left corner
  int y = 4;           // Y-coordinate of the top-left corner
  int width = 23;       // Width of the battery body
  int height = 13;      // Height of the battery body
  int capWidth = 3;     // Width of the battery cap

  // Calculate the width of the charge level
  int chargeWidth = (charge * (width - 4)) / 100; // Subtract 4 for padding


  // Draw the battery body (outer rectangle)
  u8g2.drawFrame(x, y, width, height);

  // Draw the battery cap
  u8g2.drawBox(x + width, y + height / 4, capWidth, height / 2);

  // Draw the charge level
  if (charge > 0) {
    u8g2.drawBox(x + 2, y + 2, chargeWidth, height - 4);
  }
}

void drawWiFiSemiCircles(U8G2 &u8g2) {
    // Scaled-down semi-circles for the WiFi symbol
    drawSemiCircle(96, 14, 9,u8g2); // Outer semi-circle
    drawSemiCircle(96, 14, 6,u8g2); // Middle semi-circle
    drawSemiCircle(96, 14, 3,u8g2); // Inner semi-circle
    // Scaled-down small circle at the center
    u8g2.drawDisc(96, 14, 1); // Center disc
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

void drawDropIcon(U8G2 &u8g2) {
    // Drop dimensions and position
    int centerX = 72; // X-coordinate of the center of the drop
    int centerY = 42; // Y-coordinate of the center of the drop
    int width = 20;   // Width of the drop
    int height = 30;  // Height of the drop

    // Draw the pointed tip of the drop (triangle-like)
    u8g2.drawTriangle(centerX, centerY - height / 2, centerX - width / 2, centerY, centerX + width / 2, centerY);

    // Draw the rounded bottom part of the drop (circle or arc)
    u8g2.drawDisc(centerX, centerY + height / 6, width / 2, U8G2_DRAW_ALL);
}

void drawText(int flowrate,U8G2 &u8g2) {
    u8g2.setFont(u8g2_font_ncenB14_tr);
    u8g2.setCursor(90, 50);
    u8g2.print(flowrate);
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