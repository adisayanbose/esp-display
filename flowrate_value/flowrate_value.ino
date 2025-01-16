#include <Arduino.h>
#include <U8g2lib.h>
#include <SPI.h>


U8G2_ST7567_ENH_DG128064_1_4W_SW_SPI u8g2(U8G2_R0, /* clock=*/ 18, /* data=*/ 23, /* cs=*/ 5, /* dc=*/ 4, /* reset=*/ 2); 


int flowrate=69;

void setup() {
  u8g2.begin(); // Set a more visible contrast level (128 is a good starting point)
}

void loop() {

  drawText(flowrate,u8g2); // Call the function to draw text
  delay(3000); // Wait 3 seconds before redrawing
}

void drawText(int flowrate,U8G2 &u8g2) {
  u8g2.firstPage();
  do {
    u8g2.setFont(u8g2_font_ncenB14_tr);
    u8g2.setCursor(0, 15);
    u8g2.print(flowrate);
  } while (u8g2.nextPage());
}
