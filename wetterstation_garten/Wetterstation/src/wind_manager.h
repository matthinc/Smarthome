#include <Arduino.h>

#ifndef WIND_MANAGER_H
#define WIND_MANAGER_H

#define PIN D7

class WindManager {
    public:
        void init() {
            pinMode(PIN, INPUT);
            pinMode(PIN, INPUT_PULLUP);
        }
        void loop() {
            int current = digitalRead(PIN);
            if (current != status) {
                status = current;
                ++counter;
            }
        }
        int get() {
            return counter;
        }
        void reset() {
            counter = 0;
        }
        int getAndReset() {
            int counterCopy{counter};
            counter = 0;
            return counterCopy;
        }
    private:
        int status{0};
        int counter{0};
};

#endif