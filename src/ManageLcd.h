//
// Created by Grzegorz Baranski on 02/04/2020.
//

#ifndef ALARMCLOCK_ESP_MANAGELCD_H
#define ALARMCLOCK_ESP_MANAGELCD_H

#include <WString.h>

class ManageLcd {
public:
    bool setupLcd();
    void printTextLcd(String lcdText, int fontSize);
    void clearLcd();
};


#endif //ALARMCLOCK_ESP_MANAGELCD_H
