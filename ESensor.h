#include <Arduino.h>
#include <MQTTClient.h>

class ESensor {
   public:
    ESensor(byte pin = 0, String _sensorName = "sensor", MQTTClient* mqttObj = 0);
    void init(byte pin, String _sensorName);
    int get(); // получить, сохранить и вернуть текущий статус датчика
    int isSwitched(); // Проверка на изменения состояния, вернет true если состояние датчика изменилось
    int isTriggered(); // Проверка на включение датчика (например для выключателей) вернет true если датчик был включен
    int pVal, val;
    String sensorName;

   private:
    byte _pin;
    MQTTClient *_mqttObj;  // вспомогательная ссылка для приема объекта mqtt
};