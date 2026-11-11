#include "../include/ServidorSockets.h"
#include <iostream>
#include <limits>
int main(){
    int resultado=0;
    try {
        Winsock red;
        ListaGen<Sensor*> lista;
        ServidorSMTI servidor(lista);
        servidor.iniciar();
        std::cout<<"Ahora ejecuta el cliente. Esperando 3 muestras..."<<std::endl;
        for(int i=0;i<3;++i)servidor.recibirCliente();
        std::cout<<"--- PROCESAMIENTO POLIMORFICO ---\n";
        lista.procesarTodo();
    }catch(const std::exception& e){std::cerr<<"[ERROR] "<<e.what()<<std::endl;resultado=1;}
    std::cout<<"Presiona ENTER para cerrar."<<std::endl;
    std::cin.get();
    return resultado;
}
