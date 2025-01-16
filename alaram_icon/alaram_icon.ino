#include <U8g2lib.h>

// Initialize the display
U8G2_ST7567_ENH_DG128064_1_4W_SW_SPI u8g2(U8G2_R0, /* clock=*/ 18, /* data=*/ 23, /* cs=*/ 5, /* dc=*/ 4, /* reset=*/ 2);

// Bell icon bitmap (16x15 pixels - adjusted for byte alignment)
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

void setup() {
  u8g2.begin();             // Initialize the display
  u8g2.setContrast(180);    // Add contrast setting (adjust if needed)
}

void loop() {
  u8g2.firstPage();
  do {
    // Draw a frame to see the display boundaries (optional, for testing)
    // u8g2.drawFrame(0, 0, 128, 64);
    drawNotificationIcon();
  } while (u8g2.nextPage());
  delay(1000);
}

void drawNotificationIcon() {
  // Keep original position but adjust width to 16 for proper byte alignment
      
}