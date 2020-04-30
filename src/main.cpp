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

#ifndef ALARMCLOCK_ESP_OTA_H
#include "OTA.h"
Ota manageOta;
#endif


unsigned long previousMillis = 0;        // will store last time LED was updated
const int modePushButton = 19;
const int additionalPushButton = 27;
const int sirenOutput = 23;



void setup() {

    Serial.begin(9600);
    pinMode(modePushButton, INPUT_PULLUP);
    pinMode(additionalPushButton, INPUT_PULLUP);
    pinMode(sirenOutput, OUTPUT);
    digitalWrite(sirenOutput, 0);
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
    manageOta.setupOta();
}

bool lastModeButtonState = false;
bool lastAdditionalButtonState = false;
bool isAlarmOff = false;

void loop() {
    wifiManager.handleServer();
    manageOta.handleOta();
    
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
        delay(200);
        lastAdditionalButtonState = true;
        isAlarmOff = true;
    }
    if(additionalButtonState== HIGH) {
        lastAdditionalButtonState = false;
    }

    if(mainTimeManager.isNowAlarmTime()) {
        if(!isAlarmOff) {
            digitalWrite(sirenOutput, 1);
        }else {
            digitalWrite(sirenOutput, 0);
        }
    }else
    {
        isAlarmOff = false;
        digitalWrite(sirenOutput, 0);
    }

    if (millis() - previousMillis >= 1000) {
        previousMillis = millis();
        mainTimeManager.updateTime();
        mainLcdManager.refreshLcd();
    }
}