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

#ifndef ALARMCLOCK_ESP_MANAGESENSOR_H
#include "ManageSensor.h"
ManageSensor mainSensorManager;
#endif



unsigned long previousMillis = 0;        // will store last time LED was updated
const int modePushButton = 19;
const int additionalPushButton = 27;

void setup() {

    Serial.begin(9600);
    pinMode(modePushButton, INPUT_PULLUP);
    pinMode(additionalPushButton, INPUT_PULLUP);
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
    mainSensorManager.setupSensors();

}

bool lastModeButtonState = false;
bool lastAdditionalButtonState = false;

void loop() {
    wifiManager.handleServer();

    int modeButtonState = digitalRead(modePushButton);

    if(modeButtonState == LOW && !lastModeButtonState) {
        Serial.println("Pressed mode button");
        mainLcdManager.changeLcdMode();
        delay(200);
        lastModeButtonState = true;
    }
    if(modeButtonState == HIGH) {
        lastModeButtonState = false;
    }

    int additionalButtonState = digitalRead(additionalPushButton);

    if(additionalButtonState == LOW && !lastAdditionalButtonState) {
        Serial.println("Pressed additional button");
        lastAdditionalButtonState = true;
    }
    if(additionalButtonState== HIGH) {
        lastAdditionalButtonState = false;
    }

    if (millis() - previousMillis >= 1000) {
        previousMillis = millis();
        mainTimeManager.updateTime();
        mainLcdManager.refreshLcd();
        Serial.println("Updating");
    }
}