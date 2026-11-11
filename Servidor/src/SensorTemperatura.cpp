#include "../include/SensorTemperatura.h"
#include <iostream>
SensorTemperatura::SensorTemperatura(int i,std::string u,double l,double t):Sensor(i,u,l),umbral(t){}
void SensorTemperatura::procesarLectura(){
    std::cout<<"[TEMP] "<<*this<<" C";
    if(lectura > umbral) std::cout<<" --> ALERTA";
    std::cout<<'\n';
}
