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

#ifndef ALARMCLOCK_ESP_MANAGELCD_H
#include <ManageLcd.h>
ManageLcd timeLcdManager;
#endif

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);

String alarmTime = "12:30";

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
String parseTimeToSeconds(String time) {
    time.remove(0,6);
    return time;
}

String formatDoubleDigit(String number)
{
    return number.toInt() < 10 ? "0" + number : number;
}


int parseTimeToTotalSeconds(String time) {
    return parseTimeToHour(time).toInt() * 3600 + parseTimeToMinute(time).toInt() * 60 + parseTimeToSeconds(time).toInt();
}

void ManageTime::saveAlarmTime(String data) {
    Serial.println("fulltime" + data);
    Serial.println("Hour:" + parseTimeToHour(data));
    Serial.println("Minute:" + parseTimeToMinute(data));
    alarmTime = data;
}

String ManageTime::getAlarmTime() {
    return alarmTime;
}


String ManageTime::getFormattedRemainingTime() {
    int totalRemainingSeconds = parseTimeToTotalSeconds(alarmTime + ":00") - parseTimeToTotalSeconds(timeClient.getFormattedTime());
    int remainingSeconds = totalRemainingSeconds % 60;
    int remainingMinutes = (totalRemainingSeconds / 60) % 60;
    int remainingHours = totalRemainingSeconds / 3600;

    if(remainingHours <= 0 && remainingMinutes <= 0 && remainingSeconds <= 0) {
        remainingHours = remainingHours + 23;
        remainingMinutes = remainingMinutes + 59;
        remainingSeconds = remainingSeconds + 59;
    }
    return formatDoubleDigit(String(remainingHours))  + ":" + formatDoubleDigit(String(remainingMinutes)) + ":" + formatDoubleDigit(String(remainingSeconds));
}
