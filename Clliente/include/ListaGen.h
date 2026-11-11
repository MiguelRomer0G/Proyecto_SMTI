#ifndef LISTAGEN_H
#define LISTAGEN_H
#include <memory>
#include <type_traits>
#include <stdexcept>
// Lista propietaria de punteros polimorficos. No admite copias.
template<class T> class ListaGen {
    static_assert(std::is_pointer<T>::value,"Usar punteros");
    struct Nodo {T dato; Nodo* siguiente; Nodo(T d,Nodo* s):dato(d),siguiente(s){}};
    Nodo* head=nullptr;
public:
    ListaGen()=default;
    ListaGen(const ListaGen&)=delete;
    ListaGen& operator=(const ListaGen&)=delete;
    ~ListaGen(){while(head){Nodo* n=head;head=head->siguiente;delete n->dato;delete n;}}
    void insertar(std::unique_ptr<typename std::remove_pointer<T>::type> dato){
        if(!dato) throw std::runtime_error("Sensor nulo");
        Nodo* n=new Nodo(dato.get(),head); dato.release(); head=n;
    }
    T buscarPorId(int id) const {for(Nodo* n=head;n;n=n->siguiente) if(n->dato->getId()==id)return n->dato;return nullptr;}
    void procesarTodo() const {for(Nodo* n=head;n;n=n->siguiente)n->dato->procesarLectura();}
};
#endif
