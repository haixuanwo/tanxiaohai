/**
 * @author clark
 * @email haixuanwo_clark@hotmail.com
 * @date 2020-08-30
 * @brief mqtt库的中间层接口
 */

#include "mqtt.h"
#include "log.h"
#include <string.h>

MqttAttr_S *CMqtt::mqttAttr = NULL;

CMqtt::CMqtt(MqttAttr_S &_mqttAttr)
{
    mqttAttr = new MqttAttr_S;
    *mqttAttr = _mqttAttr;
}

int CMqtt::init_mqtt()
{
    int ret = mosquitto_lib_init();
    if (MOSQ_ERR_SUCCESS != ret)
    {
        CLOG_DEBUG("mosquitto_connect error");
        return -1;
    }

    mosq = mosquitto_new(nullptr, true, nullptr);
	if(!mosq)
    {
        CLOG_DEBUG("mosquitto_new error");
        return -1;
    }

    mosquitto_message_callback_set(mosq, &CMqtt::message_callback);
    mosquitto_connect_callback_set(mosq, &CMqtt::connect_callback);

    if (0 != strlen(mqttAttr->user_name) && 0 != strlen(mqttAttr->passwd))
    {
        mosquitto_username_pw_set(mosq, mqttAttr->user_name, mqttAttr->passwd);
    }

    ret = mosquitto_connect(mosq, mqttAttr->IP, mqttAttr->port, mqttAttr->keepalive);
    if (MOSQ_ERR_SUCCESS != ret)
    {
        CLOG_DEBUG("mosquitto_connect error");
        return -1;
    }

    CLOG_DEBUG("init_mqtt success");
}

void CMqtt::message_callback(struct mosquitto *mosq, void *obj, const struct mosquitto_message *msg)
{
    CLOG_DEBUG("%s:%s", (char *)msg->topic, (char *)msg->payload);
}

void CMqtt::connect_callback(struct mosquitto *mosq, void *obj, int rc)
{
    if (rc)
    {
        // 连接错误，退出程序
        CLOG_DEBUG("on_connect error!\n");
    }
    else
    {
        // 订阅主题
        // 参数：句柄、id、订阅的主题、qos
        if (MOSQ_ERR_SUCCESS != mosquitto_subscribe(mosq, NULL, mqttAttr->sub_topic, mqttAttr->qos))
            CLOG_DEBUG("Set the topic error!\n");
        else
            CLOG_DEBUG("subscribe topic %s success\n", mqttAttr->sub_topic);
    }
}

int CMqtt::push_data(char *dataBuf, int dataLen)
{
    int ret = mosquitto_publish(mosq, NULL, mqttAttr->pub_topic, dataLen, dataBuf, mqttAttr->qos, false);
    if (MOSQ_ERR_SUCCESS != ret)
    {
        CLOG_DEBUG("mosquitto_publish error");
        return -1;
    }
    return 0;
}

int CMqtt::sync_loop()
{
    // 此函数阻塞
    mosquitto_loop_forever(mosq, -1, 1);
}

int CMqtt::async_loop()
{
    // 需要循环调用
    mosquitto_loop(mosq, -1, 1);
}

int CMqtt::thread_loop()
{
    // 开启一个线程不停的调用 mosquitto_loop()来处理网络信息
    mosquitto_loop_start(mosq);
}

CMqtt::~CMqtt()
{
    mosquitto_lib_cleanup();

    delete mqttAttr;
    mqttAttr = NULL;
}

