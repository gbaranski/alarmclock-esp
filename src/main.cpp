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

void setup() {
    Serial.begin(9600);
    wifiManager.setupWifiConnection();
    wifiManager.setupServerHandling();
    mainTimeManager.setupNtp();

}
void loop() {
    mainTimeManager.updateTime();
    delay(1000);
}