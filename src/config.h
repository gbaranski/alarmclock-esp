//
// Created by Grzegorz Baranski on 01/04/2020.
//

#ifndef ALARMCLOCK_ESP_CONFIG_H
#define ALARMCLOCK_ESP_CONFIG_H


#ifndef wifiCredentials
const char *ssid = "Nigeria";
const char *password = "hondamsx125";
const int serverPort = 80;
const String ipAddress = "192.168.1.10:5000";
#define wifiCredentials
#endif

#endif //ALARMCLOCK_ESP_CONFIG_H


