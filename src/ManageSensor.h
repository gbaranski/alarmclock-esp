//
// Created by Grzegorz Baranski on 10/04/2020.
//

#ifndef ESP_ALARMCLOCK_MANAGESENSOR_H
#define ESP_ALARMCLOCK_MANAGESENSOR_H

class ManageSensor
{
public:
    void setupSensors();
    float getDhtTemperature();
    float getDhtHumidity();
    float getHeatIndex();
    void refreshDht();
};

#endif //ESP_ALARMCLOCK_MANAGESENSOR_H
