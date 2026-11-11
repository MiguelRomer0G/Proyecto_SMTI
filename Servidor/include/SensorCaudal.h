#ifndef SENSOR_CAUDAL_H
#define SENSOR_CAUDAL_H
#include "Sensor.h"
class SensorCaudal:public Sensor {
    double umbral;
public:
    SensorCaudal(int i,std::string u,double l,double t=5.0);
    void procesarLectura() override;
};
#endif
