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
#include "Time.h"

#include <string.h>

int log_test()
{
    char buf[] = {"fpx is rabish"};
	while(1)
	{
        CLOG_INFO("cao ni daye [%d]:%s", 2025, buf);
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

void time_test()
{
    CTime T;
    int year    = 0;
    int mon     = 0;
    int day     = 0;
    int hour    = 0;
    int min     = 0;
    int second  = 0;

    while(1)
    {
        //CLOG_INFO("T --- now time [%d] secs\n", T.get_UTC_seconds());
        //CLOG_INFO("T --- now time [%ld] nanosecs\n", T.get_UTC_nanoseconds()/1000000000);
        //CLOG_INFO("T --- now time [%ld] usecs\n", T.get_UTC_useconds());

        /*T.get_local_date(year, mon, day, hour, min, second);
        CLOG_INFO("T --- local year[%d] mon[%d] day[%d] hour[%d] min[%d] second[%d]\n", year, mon, day, hour, min, second);

        struct tm tmp;
        memset(&tmp, 0, sizeof(tmp));

        tmp.tm_year = year - 1900;
        tmp.tm_mon = mon - 1;
        tmp.tm_mday = day;
        tmp.tm_hour  = hour;
        tmp.tm_min = min;
        tmp.tm_sec = second;
        CLOG_INFO("T --- TIME[%d] time[%d]\n", T.get_local_time_frome_date(&tmp), time(nullptr));*/

        T.start();
        sleep(1);
        CLOG_INFO("T --- interval time[%ld]", T.stop());
    }
}

int main(int argc, char *argv[])
{
    time_test();
    return 0;
}

