#include <ESP8266WiFi.h>
#include <MQTT.h>

#include "secrets.h";

#ifndef DATA_MANAGER_H
#define DATA_MANAGER_H

#define HOST "matthi.net"
#define CLIENT "__garten_client"

#define T_LOG "/log"
#define T_DATA "/data"

class MqttManager {
    public:
        void init() {
            WiFi.begin(SSID, PSK);
            client.begin(HOST, net);
            connect();
        }
        bool manageConnection() {
            client.loop();
            if (!client.connected()) {
                connect();
                return true;
            }
            return false;
        }
        void log(const char* message) {
            client.publish(T_LOG, message);
        }
        void publishData(char* topic, float value) {
            client.publish(topic, String(value));
        }
        void publishData(char* topic, int value) {
            client.publish(topic, String(value));
        }
        void publishData(char* topic, char* value) {
            client.publish(topic, value);
        }
    private:
        void connect() {
            while (WiFi.status() != WL_CONNECTED)
                delay(500);
            while (!client.connect(CLIENT, USER, PASSWORD))
                delay(500);
        }

        WiFiClient net;
        MQTTClient client;

};

#endif