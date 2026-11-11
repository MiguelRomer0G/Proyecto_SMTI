#include "../include/ServidorSockets.h"
#include "../include/Protocolo.h"
#include "../include/ExcepcionesSMTI.h"
#include "../include/SensorTemperatura.h"
#include "../include/SensorPresion.h"
#include "../include/SensorCaudal.h"
#include <iostream>
#include <cmath>
#include <utility>
void ServidorSMTI::iniciar(){
    servidor=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
    if(servidor==INVALID_SOCKET)errorRed("socket");
    sockaddr_in addr={}; addr.sin_family=AF_INET;addr.sin_port=htons(8080);addr.sin_addr.s_addr=htonl(INADDR_LOOPBACK);
    if(bind(servidor,reinterpret_cast<sockaddr*>(&addr),sizeof(addr))==SOCKET_ERROR)errorRed("bind puerto 8080");
    if(listen(servidor,5)==SOCKET_ERROR)errorRed("listen");
    std::cout<<"[SMTI] Escuchando en 127.0.0.1:8080"<<std::endl;
}
void ServidorSMTI::recibirCliente(){
    SOCKET c=accept(servidor,nullptr,nullptr);
    if(c==INVALID_SOCKET)errorRed("accept");
    SocketSeguro cierre(c);timeoutSocket(c);
    MuestraSensor m={};recibirTodo(c,&m,sizeof(m));
    if(!std::memchr(m.tipo,0,sizeof(m.tipo)))throw ErrorSMTI("Tipo sin terminador");
    if(m.idSensor<=0 || !std::isfinite(m.valor))throw ErrorSMTI("Muestra invalida");
    std::string tipo=m.tipo;
    std::unique_ptr<Sensor> s;
    if(tipo=="TEMP")s.reset(new SensorTemperatura(m.idSensor,"Remoto",m.valor));
    else if(tipo=="PRESION")s.reset(new SensorPresion(m.idSensor,"Remoto",m.valor));
    else if(tipo=="CAUDAL")s.reset(new SensorCaudal(m.idSensor,"Remoto",m.valor));
    else throw ErrorSMTI("Tipo desconocido");
    lista.insertar(std::move(s));
    const char ack[]="ACK SMTI\n";enviarTodo(c,ack,9);
    std::cout<<"[SMTI] Muestra almacenada."<<std::endl;
}
