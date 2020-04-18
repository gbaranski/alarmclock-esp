//
// Created by Grzegorz Baranski on 01/04/2020.
//

#ifndef ALARMCLOCK_ESP_MANAGETIME_H
#define ALARMCLOCK_ESP_MANAGETIME_H

#ifndef WSTRING_H
#define WSTRING_H
#include <WString.h>
#endif


class ManageTime {
public:
    String getTime();
    String getAlarmTime();
    void setupNtp();
    void updateTime();
    void saveAlarmTime(String data);
    String getFormattedRemainingTime();
    bool isNowAlarmTime();
};


#endif //ALARMCLOCK_ESP_MANAGETIME_H
