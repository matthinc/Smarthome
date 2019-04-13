#include <Arduino.h>
#include <Timer.h>

#include "data_manager.h";
#include "temperature_manager.h";
#include "wind_manager.h";

#define DELAY 30000

MqttManager mqtt;
TemperatureManager temp;
WindManager wind;

void publishData() {
  mqtt.log((String("timer::event ") + String(millis())).c_str());
  temp.read();

  mqtt.publishData("/tmp1", temp.get(0));
  mqtt.publishData("/tmp2", temp.get(1));
  mqtt.publishData("/wind", static_cast<float>(wind.getAndReset()));
}

void setup() {
  temp.init();
  mqtt.init();
  wind.init();
  mqtt.log("system::start");
}

void loop() {
  static unsigned long lastMeasure = 0 - DELAY;

  if (mqtt.manageConnection()) {
    mqtt.log("system::reconnect");
  }

  wind.loop();

  unsigned long now = millis();
  if (now - lastMeasure >= DELAY) {
      lastMeasure += DELAY;
      publishData();
  }
}
