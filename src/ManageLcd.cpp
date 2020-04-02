//
// Created by Grzegorz Baranski on 02/04/2020.
//

#include "ManageLcd.h"
#include <WString.h>


#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#ifndef SCREEN_WIDTH
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#endif

#ifndef SCREEN_HEIGHT
#define SCREEN_HEIGHT 32 // OLED display height, in pixels
#endif

#ifndef lcd_address
#define lcd_address 0x3C
#endif



#ifndef OLED_RESET
#define OLED_RESET -1
#endif

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

bool ManageLcd::setupLcd() {
    if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
        Serial.println("SSD1306 allocation failed");
        return false;
    }
    delay(1000);
    display.clearDisplay();
    display.setTextColor(WHITE);
    display.setTextSize(1);
    display.println("Check it out on github.com/gbaranski");
    display.display();
    delay(1000);
    return true;
}
void ManageLcd::printTextLcd(String lcdText){
    Serial.println("321");
    display.print(lcdText);
    display.display(); // <--- THIS ONE CAUSE CRASH
    delay(1000);
}

void ManageLcd::clearLcd() {
    display.clearDisplay();
    display.display();
}



