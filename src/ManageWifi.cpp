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

#ifndef ALARMCLOCK_ESP_MANAGETIME_H
#include "ManageTime.h"
ManageTime timeManager;
#define ALARMCLOCK_ESP_MANAGETIME_H
#endif


#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>

AsyncWebServer server(80);
const char* PARAM_MESSAGE = "message";



bool ManageWifi::setupWifiConnection() {
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    if(WiFi.waitForConnectResult() != WL_CONNECTED) {
        Serial.printf("Wifi failed");
        return false;
    }
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
    return true;
}

void notFound(AsyncWebServerRequest *request) {
    request->send(404, "text/plain", "Not found");
}


void ManageWifi::setupServerHandling() {

    server.on("/getTimeData", HTTP_GET, [] (AsyncWebServerRequest *request) {
        request->send(200, "text/plain", R"({"currentTime":")" + timeManager.getTime() + "\"}");
        Serial.print("received/get");
    });
    server.on("/setAlarm", HTTP_GET, [](AsyncWebServerRequest * request) {
    if(request->hasParam("time")) {
        AsyncWebParameter* p = request->getParam("time");
        Serial.printf("Received %s with value %s from IP: \n", p->name().c_str(), p->value().c_str());
        Serial.println(request->client()->remoteIP());
        request->send(200, "text/plain", "OK");

    }
    });
    server.onNotFound(notFound);
    server.begin();
}
