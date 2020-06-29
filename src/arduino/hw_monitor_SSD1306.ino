#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define NUMFLAKES     10 // Number of snowflakes in the animation example

#define LOGO_HEIGHT   16
#define LOGO_WIDTH    16

void setup() {
  Serial.begin(115200);

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  
  display.setTextSize(4); 
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.print("ready");
  display.display();
  Serial.write("ready");
  
}

String serialString = "";

void loop() {  
  display.setTextColor(SSD1306_WHITE);
  
  while (Serial.available() > 0) {   
    serialString = String(Serial.readString());
    display.clearDisplay();
    display.setCursor(0, 0);
    display.setTextSize(serialString.substring(0,1).toInt());
    display.print(serialString.substring(1));
    display.display();
  }
}
