//
// Created by Grzegorz Baranski on 01/04/2020.
//

#include "ManageWifi.h"

#ifndef ARDUINO_H
#include <Arduino.h>
#endif

#ifndef ALARMCLOCK_ESP_CONFIG_H
#include "config.h"
#endif


#ifndef ALARMCLOCK_ESP_MANAGELCD_H
#include "ManageLcd.h"
ManageLcd lcdManager;
#endif

#ifndef ALARMCLOCK_ESP_MANAGESENSOR_H
#include "ManageSensor.h"
ManageSensor sensorManager;
#endif


#ifndef ALARMCLOCK_ESP_MANAGETIME_H
#include "ManageTime.h"
ManageTime wifiTimeManager;
#endif

#include <WiFi.h>
#include <WebServer.h>
WebServer server(serverPort);

bool ManageWifi::setupWifiConnection() {
    WiFi.begin(ssid, password);
    if(WiFi.waitForConnectResult() != WL_CONNECTED) {
        Serial.printf("Wifi failed");
        return false;
    }
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
    server.begin();
    return true;
}


void handle404() {
    server.send(404, "text/plain", "Not found");
}

void handleGetESPData() {
    String espOutput =
            R"({"currentTime":")" + wifiTimeManager.getTime() +
            R"(","alarmTime":")" + wifiTimeManager.getAlarmTime() +
            R"(","remainingTime":")" + wifiTimeManager.getFormattedRemainingTime() +
            R"(","temperature":")" + sensorManager.getDhtTemperature() +
            R"(","humidity":")" + sensorManager.getDhtHumidity() +
            R"(","heatIndex":")" + sensorManager.getHeatIndex() +
            "\"}";
    Serial.println(espOutput);
    server.send(200, "application/json", espOutput);
}
void handleSetAlarm() {
    if(server.hasArg("time")) {
        server.send(200, "text/plain", "Alarm set to" + server.arg("time"));
        lcdManager.printTextLcd("New request!\nAlarm is set to " + server.arg("time") + "\nFrom IP " + server.client().remoteIP().toString(), 1);
        wifiTimeManager.saveAlarmTime(server.arg("time"));
        delay(2000);
    } else {
        server.send(400,"text/plain", "NO ARG \"TIME\"");
    }
}

void ManageWifi::setupServerHandling() {
    server.onNotFound(handle404);
    server.on("/getESPData", handleGetESPData);
    server.on("/setAlarm", handleSetAlarm);
}


String ManageWifi::getLocalIp() {
    return WiFi.localIP().toString();
}

void ManageWifi::handleServer() {
    server.handleClient();
}

