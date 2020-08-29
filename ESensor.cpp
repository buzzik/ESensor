#include "ESensor.h"

#include <Arduino.h>
#include <MQTTClient.h>

ESensor::ESensor(byte pin, String _sensorName, MQTTClient *mqttObj, bool isPulledUp) {
    _pin = pin;
    sensorName = _sensorName;
    _mqttObj = mqttObj;
    _isPulledUp = isPulledUp;
    if (isPulledUp)
    {
        pinMode(_pin, INPUT_PULLUP);
    } else {
        pinMode(_pin, INPUT);
    }
    
    
    
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
