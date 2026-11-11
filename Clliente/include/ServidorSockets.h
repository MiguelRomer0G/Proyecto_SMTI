#ifndef SERVIDOR_SOCKETS_H
#define SERVIDOR_SOCKETS_H
#include "Red.h"
#include "Sensor.h"
#include "ListaGen.h"
class ServidorSMTI {
    SOCKET servidor=INVALID_SOCKET;
    ListaGen<Sensor*>& lista;
public:
    explicit ServidorSMTI(ListaGen<Sensor*>& l):lista(l){}
    ~ServidorSMTI(){if(servidor!=INVALID_SOCKET)closesocket(servidor);}
    ServidorSMTI(const ServidorSMTI&)=delete;
    ServidorSMTI& operator=(const ServidorSMTI&)=delete;
    void iniciar();
    void recibirCliente();
};
#endif
