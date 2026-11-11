#ifndef SENSOR_TEMPERATURA_H
#define SENSOR_TEMPERATURA_H
#include "Sensor.h"
class SensorTemperatura:public Sensor {
    double umbral;
public:
    SensorTemperatura(int i,std::string u,double l,double t=80.0);
    void procesarLectura() override;
};
#endif
