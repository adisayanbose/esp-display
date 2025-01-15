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
    u8g2.drawFrame(5, 0, 128, 64);
    u8g2.setFont(u8g2_font_ncenB10_tr);
    u8g2.drawStr(15, 20, "Hello World!");
  } while (u8g2.nextPage());
  delay(1000);
}
