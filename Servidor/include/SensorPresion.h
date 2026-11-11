#ifndef SENSOR_PRESION_H
#define SENSOR_PRESION_H
#include "Sensor.h"
class SensorPresion:public Sensor {
    double umbral;
public:
    SensorPresion(int i,std::string u,double l,double t=10.0);
    void procesarLectura() override;
};
#endif
