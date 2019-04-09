#include <Arduino.h>
#include <Timer.h>

#include "data_manager.h";
#include "temperature_manager.h";
#include "wind_manager.h";

MqttManager mqtt;
TemperatureManager temp;
WindManager wind;

Timer timer;

void publishData() {
  mqtt.log("timer::event");
  temp.read();

  mqtt.publishData("/tmp1", temp.get(0));
  mqtt.publishData("/tmp2", temp.get(1));
  mqtt.publishData("/wind", wind.getAndReset());
}

void setup() {
  temp.init();
  mqtt.init();
  wind.init();
  mqtt.log("system::start");

  timer.every(60000, publishData);
}

void loop() {
  mqtt.manageConnection();
  timer.update();
  wind.loop();
}
