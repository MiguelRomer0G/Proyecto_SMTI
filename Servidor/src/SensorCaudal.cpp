#include "../include/SensorCaudal.h"
#include <iostream>
SensorCaudal::SensorCaudal(int i,std::string u,double l,double t):Sensor(i,u,l),umbral(t){}
void SensorCaudal::procesarLectura(){
    std::cout<<"[CAUDAL] "<<*this<<" L/min";
    if(lectura < umbral) std::cout<<" --> ALERTA";
    std::cout<<'\n';
}
