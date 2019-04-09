#include <OneWire.h>
#include <Arduino.h>
#include <DallasTemperature.h>

#ifndef TEMPERATURE_MANAGER_T
#define TEMPERATURE_MANAGER_T

#define PIN D6
#define NUM 2

class TemperatureManager {
    public:
        TemperatureManager(): oneWire(PIN), sensors(&oneWire) {}
        void init() {
            sensors.begin();
            for (int i = 0; i < NUM; i++) {
                sensors.getAddress(adresses[i], i);
            }
        }
        void read() {
            sensors.requestTemperatures();
        }
        float get(int at) {
            return sensors.getTempC(adresses[at]);
        }
    private:
        OneWire oneWire;
        DallasTemperature sensors;
        DeviceAddress adresses[NUM];
};

#endif