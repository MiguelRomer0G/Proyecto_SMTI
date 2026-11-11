#ifndef RED_H
#define RED_H
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdexcept>
#include <string>
#include <cstring>
class Winsock {
public:
    Winsock(){ WSADATA d; int e=WSAStartup(MAKEWORD(2,2),&d); if(e) throw std::runtime_error("WSAStartup: "+std::to_string(e)); }
    ~Winsock(){WSACleanup();}
    Winsock(const Winsock&)=delete;
    Winsock& operator=(const Winsock&)=delete;
};
inline void errorRed(const std::string& op){throw std::runtime_error(op+". Codigo Winsock: "+std::to_string(WSAGetLastError()));}
class SocketSeguro {
    SOCKET fd;
public:
    explicit SocketSeguro(SOCKET s):fd(s){}
    ~SocketSeguro(){if(fd!=INVALID_SOCKET) closesocket(fd);}
    SocketSeguro(const SocketSeguro&)=delete;
    SocketSeguro& operator=(const SocketSeguro&)=delete;
};
inline void timeoutSocket(SOCKET s){
    DWORD t=15000;
    if(setsockopt(s,SOL_SOCKET,SO_RCVTIMEO,reinterpret_cast<const char*>(&t),sizeof(t))==SOCKET_ERROR) errorRed("Timeout recv");
    if(setsockopt(s,SOL_SOCKET,SO_SNDTIMEO,reinterpret_cast<const char*>(&t),sizeof(t))==SOCKET_ERROR) errorRed("Timeout send");
}
inline void enviarTodo(SOCKET s,const void* data,int total){
    const char* p=static_cast<const char*>(data);
    int pos=0;
    while(pos<total){int n=send(s,p+pos,total-pos,0); if(n==SOCKET_ERROR) errorRed("send"); if(n==0) throw std::runtime_error("Envio incompleto"); pos+=n;}
}
inline void recibirTodo(SOCKET s,void* data,int total){
    char* p=static_cast<char*>(data);
    int pos=0;
    while(pos<total){int n=recv(s,p+pos,total-pos,0); if(n==SOCKET_ERROR) errorRed("recv"); if(n==0) throw std::runtime_error("Cliente desconectado o trama incompleta"); pos+=n;}
}
#endif
