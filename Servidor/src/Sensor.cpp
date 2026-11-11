#include "../include/Sensor.h"
#include <iostream>
Sensor::Sensor(int i,std::string u,double l):id(i),ubicacion(u),lectura(l){}
Sensor::~Sensor(){std::cout<<"[DESTRUCTOR] Sensor "<<id<<" liberado.\n";}
int Sensor::getId() const{return id;}
std::ostream& operator<<(std::ostream& o,const Sensor& s){return o<<"ID: "<<s.id<<" | Ubicacion: "<<s.ubicacion<<" | Lectura: "<<s.lectura;}
