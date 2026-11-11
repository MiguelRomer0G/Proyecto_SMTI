#include "../include/Red.h"
#include "../include/Protocolo.h"
#include <iostream>
int main(){
    int resultado=0;
    try {
        Winsock red;
        const char* tipos[]={"TEMP","PRESION","CAUDAL"};
        double valores[]={92.5,12.3,3.2};
        for(int i=0;i<3;++i){
            SOCKET c=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
            if(c==INVALID_SOCKET)errorRed("socket");
            SocketSeguro cierre(c);timeoutSocket(c);
            sockaddr_in addr={};addr.sin_family=AF_INET;addr.sin_port=htons(8080);addr.sin_addr.s_addr=htonl(INADDR_LOOPBACK);
            if(connect(c,reinterpret_cast<sockaddr*>(&addr),sizeof(addr))==SOCKET_ERROR)errorRed("connect: inicia primero el servidor");
            MuestraSensor m;std::memset(&m,0,sizeof(m));m.idSensor=101+i;m.valor=valores[i];std::strcpy(m.tipo,tipos[i]);
            enviarTodo(c,&m,sizeof(m));
            char ack[9];recibirTodo(c,ack,9);
            std::cout<<"Enviado "<<tipos[i]<<": "<<valores[i]<<" | ";std::cout.write(ack,9);
        }
    }catch(const std::exception& e){std::cerr<<"[ERROR] "<<e.what()<<std::endl;resultado=1;}
    std::cout<<"Presiona ENTER para cerrar."<<std::endl;std::cin.get();return resultado;
}
