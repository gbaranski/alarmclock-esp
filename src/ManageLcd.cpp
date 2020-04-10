//
// Created by Grzegorz Baranski on 02/04/2020.
//

#include "ManageLcd.h"
#include <WString.h>


#ifndef ALARMCLOCK_ESP_MANAGETIME_H
#include "ManageTime.h"
ManageTime lcdTimeManager;
#endif

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

#ifndef ALARMCLOCK_ESP_MANAGESENSOR_H
#include "ManageSensor.h"
ManageSensor lcdSensorManager;
#endif

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

int lcdMode = 1;

bool ManageLcd::setupLcd() {
    Wire.begin(5,4);
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
void ManageLcd::printTextLcd(String lcdText, int fontSize){
    clearLcd();
    display.setTextSize(fontSize);
    display.print(lcdText);
    display.display();
}



void ManageLcd::clearLcd() {
    display.setTextColor(WHITE);
    display.setCursor(0, 0);
    display.clearDisplay();

    display.display();
}



void ManageLcd::changeLcdMode(){
    lcdMode++;
}

int ManageLcd::getLcdMode() {
    return lcdMode;
}

void ManageLcd::refreshLcd() {
    clearLcd();
    switch (lcdMode) {
        case 4:
        case 1:
            lcdMode = 1;
            display.setTextSize(1);
            display.println("Current time");
            display.setTextSize(2);
            display.println(lcdTimeManager.getTime());
            break;
        case 2:
            display.setTextSize(1);
            display.println("Remaining time");
            display.setTextSize(2);
            display.println(lcdTimeManager.getFormattedRemainingTime());
            break;
        case 3:
            display.setTextSize(1);
            display.println("Alarm time: " + lcdTimeManager.getAlarmTime());
            display.println("Temperature: " + String(lcdSensorManager.getDhtTemperature()));
            display.println("Humidity: " + String(lcdSensorManager.getDhtHumidity()) + "%");
            display.println("Heat index:" + String(lcdSensorManager.getHeatIndex()));
            break;
    }
    display.display();
}



