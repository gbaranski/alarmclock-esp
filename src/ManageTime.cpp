//
// Created by Grzegorz Baranski on 01/04/2020.
//

#include "ManageTime.h"

#ifndef WSTRING_H
#define WSTRING_H
#include <WString.h>
#endif

#ifndef ALARMCLOCK_ESP_CONFIG_H
#define ALARMCLOCK_ESP_CONFIG_H
#include "config.h"
#endif

#include <NTPClient.h>
#include <WiFiUdp.h>

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);


void ManageTime::setupNtp() {
    timeClient.begin();
}

void ManageTime::updateTime() {
    timeClient.update();
}

String ManageTime::getTime() {
    return timeClient.getFormattedTime();
}

String parseTimeToHour(String time) {
    time.remove(2);
    return time;
}

String parseTimeToMinute(String time) {
    time.remove(0,3);
    return time;
}

void ManageTime::saveAlarmTime(String data) {
    Serial.println("fulltime" + data);
    Serial.println("Hour:" + parseTimeToHour(data));
    Serial.println("Minute:" + parseTimeToMinute(data));
}
