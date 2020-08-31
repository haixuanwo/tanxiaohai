/**
 * @author clark
 * @email haixuanwo_clark@hotmail.com
 * @date 2020-08-30
 * @brief mqtt库的中间层接口
 */

#ifndef MQTT_H_
#define MQTT_H_

extern "C"
{
#include "mosquitto.h"
}

typedef struct{
    char IP[16];
    int port;
    int keepalive;
    int mid;    // 设备ID
    int qos;    // 质量
    char sub_topic[1024];
    char pub_topic[1024];
    char user_name[64];
    char passwd[64];
}MqttAttr_S;

class CMqtt
{
public:
    CMqtt(MqttAttr_S &_mqttAttr);
    int init_mqtt();
    int push_data(char *dataBuf, int dataLen);
    static void message_callback(struct mosquitto *mosq, void *obj, const struct mosquitto_message *msg);
    static void connect_callback(struct mosquitto *mosq, void *obj, int rc);
    int async_loop();
    int sync_loop();
    int thread_loop();
    ~CMqtt();
private:
    static MqttAttr_S *mqttAttr;
    struct mosquitto *mosq;
};

/*
单元测试
1、通过主题发布数据[ok]
2、通过主题接收数据[ok]
*/
#endif

