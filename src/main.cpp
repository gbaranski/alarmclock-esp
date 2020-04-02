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

void setup() {
    Serial.begin(9600);
    if(!mainLcdManager.setupLcd())
        while(true){
            Serial.println("SSD1306 allocation failed");
            delay(1000);
        }
    wifiManager.setupWifiConnection();
    mainLcdManager.clearLcd();
    mainLcdManager.printTextLcd("IP: " + wifiManager.getLocalIp());
    wifiManager.setupServerHandling();
    mainTimeManager.setupNtp();


    delay(1000);
}
void loop() {
    mainTimeManager.updateTime();
    delay(1000);
}