#include <Arduino.h>
#include <U8g2lib.h>
#include <Wire.h>

U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

String serialString = "";
String gpuUsage = "00";
String gpuTemp = "00";
String cpuUsage = "00";
String cpuTemp = "00";


void setup(void) {
  Serial.begin(115200);
  u8g2.begin();
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_6x10_tf);
  u8g2.drawUTF8(0,10, "Waiting...");  
  u8g2.sendBuffer(); 
  Serial.write("ready");
}

void loop(void) {
  while (Serial.available() > 0) {   
    serialString = String(Serial.readString());

    gpuUsage = serialString.substring(0,2);
    gpuTemp = serialString.substring(2,4);
    cpuUsage = serialString.substring(4,6);
    cpuTemp = serialString.substring(6,8);
    
    u8g2.clearBuffer();
  
    u8g2.setFont(u8g2_font_inb30_mr);
    u8g2.drawUTF8(0,30, gpuUsage.c_str());
    u8g2.drawUTF8(0,64, gpuTemp.c_str());
    u8g2.drawUTF8(64,30, cpuUsage.c_str());
    u8g2.drawUTF8(64,64, cpuTemp.c_str());
  
    u8g2.setFont(u8g2_font_6x10_tf);
    u8g2.drawUTF8(52,7, "G");
    u8g2.drawUTF8(116,7, "C");
    u8g2.drawUTF8(52,30, "%");
    u8g2.drawUTF8(52,64, "°C");
    u8g2.drawUTF8(116,30, "%");
    u8g2.drawUTF8(116,64, "°C");
    
    u8g2.sendBuffer(); 
  }
}
