//
// Created by Grzegorz Baranski on 10/04/2020.
//

#include "ManageSensor.h"
#include <DHT.h>
#include <Adafruit_Sensor.h>

#define DHTPIN 13
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

void ManageSensor::setupSensors()
{
    dht.begin();
}

float ManageSensor::getDhtTemperature()
{
    return dht.readTemperature();
}

float ManageSensor::getDhtHumidity()
{
    return dht.readHumidity();
}

float ManageSensor::getHeatIndex()
{
    return dht.computeHeatIndex(dht.readTemperature(), dht.readHumidity(), false);
}

void ManageSensor::refreshDht()
{
    dht.readTemperature();
}
