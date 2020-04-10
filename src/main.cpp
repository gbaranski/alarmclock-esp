#ifndef ARDUINO_H
#include <Arduino.h>
#endif

#ifndef ALARMCLOCK_ESP_MANAGETIME_H
#include "ManageTime.h"
ManageTime mainTimeManager;
#define ALARMCLOCK_ESP_MANAGETIME_H
#endif

#ifndef ALARMCLOCK_ESP_MANAGEWIFI_H
#include "ManageWifi.h"
ManageWifi wifiManager;
#endif

#ifndef ALARMCLOCK_ESP_MANAGELCD_H
#include <ManageLcd.h>
ManageLcd mainLcdManager;
#endif



unsigned long previousMillis = 0;        // will store last time LED was updated
const int modePushButton = 19;

void setup() {

    Serial.begin(9600);
    pinMode(modePushButton, INPUT_PULLUP);

    if(!mainLcdManager.setupLcd())
        while(true){
            Serial.println("SSD1306 allocation failed");
            delay(1000);
        }
    wifiManager.setupWifiConnection();
    mainTimeManager.setupNtp();
    mainLcdManager.clearLcd();
    mainLcdManager.printTextLcd("IP: " + wifiManager.getLocalIp(), 1);
    wifiManager.setupServerHandling();



}

bool lastModeButtonState = false;


void loop() {
    wifiManager.handleServer();
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= 1000) {
        previousMillis = currentMillis;
        mainTimeManager.updateTime();
        mainLcdManager.refreshLcd();
    }

    int modeButtonState = digitalRead(modePushButton);

    if(modeButtonState == LOW && !lastModeButtonState) {
        Serial.println("Pressed");
        mainLcdManager.changeLcdMode();
        delay(300);
        lastModeButtonState = true;
    }
    if(modeButtonState == HIGH) {
        lastModeButtonState = false;
    }
}