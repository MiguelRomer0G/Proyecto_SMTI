#include "../include/SensorPresion.h"
#include <iostream>
SensorPresion::SensorPresion(int i,std::string u,double l,double t):Sensor(i,u,l),umbral(t){}
void SensorPresion::procesarLectura(){
    std::cout<<"[PRESION] "<<*this<<" bar";
    if(lectura > umbral) std::cout<<" --> ALERTA";
    std::cout<<'\n';
}
