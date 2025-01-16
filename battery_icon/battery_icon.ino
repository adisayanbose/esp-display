#include <U8g2lib.h> // Library for working with the display

// Initialize the display with SPI pins (SCK = 13, MOSI = 11, CS = 10, DC = 8, RST = 9)
U8G2_ST7567_ENH_DG128064_1_4W_SW_SPI u8g2(U8G2_R0, /* clock=*/ 18, /* data=*/ 23, /* cs=*/ 5, /* dc=*/ 4, /* reset=*/ 2); 


void setup() {
  u8g2.begin();         // Initialize the display// Set a more visible contrast level (128 is a good starting point)
}

void loop() {
  drawBatteryIcon(75,u8g2);  // Draw a battery icon with 75% charge
  delay(3000);          // Wait 3 seconds before redrawing
}

void drawBatteryIcon(int charge,U8G2 &u8g2) {
  u8g2.firstPage();
  do {
  // Battery dimensions and position
  int x = 6;           // X-coordinate of the top-left corner
  int y = 5;           // Y-coordinate of the top-left corner
  int width = 20;       // Width of the battery body
  int height = 15;      // Height of the battery body
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
   } while (u8g2.nextPage());
   // Transfer the buffer to the display
}
