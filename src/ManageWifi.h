//
// Created by Grzegorz Baranski on 01/04/2020.
//

#ifndef ALARMCLOCK_ESP_MANAGEWIFI_H
#define ALARMCLOCK_ESP_MANAGEWIFI_H

#ifndef WSTRING_H
#include <WString.h>
#endif


class ManageWifi {
public:
    bool setupWifiConnection();
    void setupServerHandling();
    String getLocalIp();
};


#endif //ALARMCLOCK_ESP_MANAGEWIFI_H
