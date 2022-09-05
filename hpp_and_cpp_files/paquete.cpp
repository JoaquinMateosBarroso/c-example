#include "paquete.hpp"
using namespace umalcc;

namespace umalcc{
    Paquete::~Paquete(){}
    Paquete::Paquete() : id(), n_plazas(0), precio(0){}
    Paquete::Paquete(const std::string& c, int pl, int pr) : id(c), n_plazas(pl), precio(pr){}
    Paquete::Paquete(const Paquete& o) : id(o.id), n_plazas(o.n_plazas), precio(o.precio){}
    Paquete& Paquete::operator=(const Paquete& o){
        if(this!=&o){
            id=o.id;
            n_plazas=o.n_plazas;
            precio=o.precio;
        }
        return *this;
    }
    bool Paquete::error() const{
        return (id.empty() || precio<0);
    }
    std::string Paquete::obtener_codigo() const{
        return id;
    }
    int Paquete::obtener_plazas() const{
        return n_plazas;
    }
    int Paquete::obtener_precio() const{
        return precio;
    }
    void Paquete::modificar_plazas(int p, bool& ok){
        if(p>=0){
            n_plazas=p;
            ok=true;
        }
        else{
            ok=false;
        }
    }
    void Paquete::modificar_precio(int p, bool& ok){
        if(p>=0){
            precio=p;
            ok=true;
        }
        else{
            ok=false;
        }        
    }
    void Paquete::mostrar()const{
        std::cout << id << ' ' << n_plazas << ' ' << precio;
    }
}