//
// Created by Grzegorz Baranski on 01/04/2020.
//

#ifndef ALARMCLOCK_ESP_MANAGEWIFI_H
#define ALARMCLOCK_ESP_MANAGEWIFI_H


class ManageWifi {
    public:
        bool setupWifiConnection();
        void setupServerHandling();
};


#endif //ALARMCLOCK_ESP_MANAGEWIFI_H
