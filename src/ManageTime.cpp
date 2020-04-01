//
// Created by Grzegorz Baranski on 01/04/2020.
//

#include "ManageTime.h"

#ifndef WSTRING_H
#define WSTRING_H
#include <WString.h>
#endif

#ifndef ALARMCLOCK_ESP_CONFIG_H
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

void ManageTime::saveAlarmTime(String data) {

}
