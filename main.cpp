/**
 * @author clark
 * @email haixuanwo_clark@hotmail.com
 * @date 2020-08-03
 */
#include "common_include.h"
#include "log.h"
#include "mqtt.h"
#include "tinyxml2.h"
#include "json.hpp"
#include "sqlite.h"
#include <string.h>

int log_test()
{
    char buf[] = {"fpx is rabish"};
	while(1)
	{
        TRACE_INFO("cao ni daye [%d]:%s", 2025, buf);
		sleep(1);
	}
}

int mqtt_test()
{
    char buf[] = {"cao l ni ma de ig"};
    MqttAttr_S mqttAttr;

    strcpy(mqttAttr.IP, "192.168.1.119");
    mqttAttr.keepalive = 60;
    mqttAttr.port = 1883;
    mqttAttr.mid = 0;
    mqttAttr.qos = 2;

    snprintf(mqttAttr.pub_topic, sizeof(mqttAttr.pub_topic), "test/topic");
    snprintf(mqttAttr.sub_topic, sizeof(mqttAttr.pub_topic), "test/topic");

    CMqtt mqtt(mqttAttr);
    mqtt.init_mqtt();

    while(1)
    {
        mqtt.async_loop();
        mqtt.push_data(buf, strlen(buf));
        sleep(1);
    }
}

int main(int argc, char *argv[])
{
    mqtt_test();
    return 0;
}

