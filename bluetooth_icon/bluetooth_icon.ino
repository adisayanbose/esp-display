#include "U8glib.h" // Library for working with the display

// Initialize the display with SPI pins (SCK = 13, MOSI = 11, CS = 10, A0 = 9, RST = 8)
U8GLIB_NHD_C12864 u8g(13, 11, 10, 8, 9);

void setup() {
  Serial.begin(9600);
  u8g.setContrast(180); // Set a more visible contrast level (128 is a good starting point)
}

void loop() {
  drawBluetoothSymbol();
  delay(3000); // Wait 3 seconds before drawing again
}

void drawBluetoothSymbol() {
  Serial.print("hi");
  u8g.firstPage();
  do {
    // Center of the display (128x64), position the symbol around the center
    int centerX = 64; // X-coordinate of the center
    int centerY = 32; // Y-coordinate of the center
    int size = 7;     // Half of the 15x15 size for scaling

    // Vertical line of the Bluetooth "B"
    u8g.drawBox(centerX - 1, centerY - size, 3, 2 * size); // Thicker vertical line

    // Top arrow (rightward diagonal)
    u8g.drawLine(centerX, centerY - size, centerX + size, centerY - size / 2); // Diagonal line
    u8g.drawBox(centerX + size - 1, centerY - size / 2 - 1, 3, 3); // Thicker arrow tip

    // Bottom arrow (rightward diagonal)
    u8g.drawLine(centerX, centerY + size, centerX + size, centerY + size / 2); // Diagonal line
    u8g.drawBox(centerX + size - 1, centerY + size / 2 - 1, 3, 3); // Thicker arrow tip

    // Cross lines (X shape)
    u8g.drawLine(centerX + size, centerY - size / 2, centerX - size, centerY + size / 2); // Top-left diagonal
    u8g.drawLine(centerX + size, centerY + size / 2, centerX - size, centerY - size / 2); // Bottom-left diagonal
    
  } while (u8g.nextPage());
}
