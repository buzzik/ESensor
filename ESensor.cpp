#include "ESensor.h"

#include <Arduino.h>
#include <MQTTClient.h>

ESensor::ESensor(byte pin, String _sensorName, MQTTClient *mqttObj) {
    _pin = pin;
    sensorName = _sensorName;
    _mqttObj = mqttObj;
    pinMode(_pin, INPUT);
    
}

int ESensor::get() { 
    pVal = val;
    val = digitalRead(_pin);
    return val;
}

int ESensor::isSwitched() { 
    String state = "OFF";
    get();
    if (pVal != val) {
        _mqttObj->publish("/" + sensorName + "/state", (String)val);
        return true;
    } else {
        return false;
    }
}

int ESensor::isTriggered() {  
    if (isSwitched() && val == HIGH) {
        return true;
    } else {
        return false;
    }
}
