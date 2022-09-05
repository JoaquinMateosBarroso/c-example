#include "agviajes.hpp"
#include <cassert>
#include <fstream>
#include <string>

using namespace umalcc;

namespace umalcc{
    AgViajes::~AgViajes(){
        eliminar_paquetes();
        eliminar_clientes();
    }
    AgViajes::AgViajes() : paquetes(NULL), clientes(NULL){}
    AgViajes::AgViajes(const AgViajes &o) : paquetes(duplicar_paquetes(o.paquetes)), clientes(duplicar_clientes(o.clientes)){
    }
    AgViajes& AgViajes::operator=(const AgViajes& o){
        if(this!=&o){
            paquetes=duplicar_paquetes(o.paquetes);
            clientes=duplicar_clientes(o.clientes);
        }
        return *this;
    }
    void AgViajes::leer_paquetes(const std::string& fich_paquetes, bool& ok){
        eliminar_paquetes();
        ok=false;
        std::ifstream fich;
        fich.open(fich_paquetes.c_str());
        if(!fich.fail()){
            std::string identificacion, msg;
            int plazas, precio, i;
            getline(fich, identificacion, ' ');
            paquetes=new estructura_paquetes;
            nodo_paquetes ptr=paquetes;
            while(!fich.eof() && !fich.fail()){
                fich >> plazas;
                fich >> precio;
                ptr->paquete=Paquete(identificacion, plazas, precio);
                fich >> i;
                fich.ignore();
                for(int j=0; j<i; ++j){
                    getline(fich, msg, '\n');
                    ptr->opiniones.push_back(msg);
                }
                getline(fich, identificacion, ' ');
                if(!fich.eof()){
                    ptr->sig = new estructura_paquetes;
                    ptr=ptr->sig;
                }
            }
            ptr->sig=NULL;
            ok=fich.eof()||!fich.fail();
            fich.close();
        }
    }
    void AgViajes::leer_clientes(const std::string& fich_clientes, bool& ok){
        eliminar_clientes();
        ok=false;
        std::ifstream fich;
        fich.open(fich_clientes.c_str());
        if(!fich.fail()){
            std::string nombre, identificacion;
            int dinero, i;
            std::vector <std::string> aux;
            getline(fich, nombre, ' ');
            clientes=new estructura_clientes;
            nodo_clientes ptr=clientes;
            while(!fich.eof()){
                fich >> dinero;
                ptr->cliente=Cliente(nombre, dinero);
                fich >> i;
                fich.ignore();
                ptr->num_reservas=i;
                aux.clear();
                for(int j=0; j<i-1; ++j){
                    getline(fich, identificacion, ' ');
                    aux.push_back(identificacion);
                }
                getline(fich, identificacion);
                aux.push_back(identificacion);
                ptr->paquetes=meter_paquetes_en_vector_string(aux);    //La creacion y uso de este método se debe a dos causas; para empezar, a pesar de que ocupe más RAM por tener que crear el vector auxiliar, es un proceso algo más rápido que insertar los identificadores según se leen. El otro motivo es seguir para ensayando con los vectores, pues es algo visto recientemente en clase de lo que viene bien aprender
                getline(fich, nombre, ' ');
                if(!fich.eof()){
                    ptr->sig = new estructura_clientes;
                    ptr=ptr->sig;
                }
            }
            ok=fich.eof()||!fich.fail();
            ptr->sig=NULL;
            fich.close();
        }
    }
    //El formato es el del fichero "paquetes.txt"
    void AgViajes::guardar_paquetes(const std::string& fich_paquetes, bool& ok)const{
        ok=false;
        std::ofstream fich;
        fich.open(fich_paquetes);
        if(!fich.fail()){
            if(paquetes!=NULL){
                nodo_paquetes ptr = paquetes;
                while (ptr!=NULL){
                    fich << ptr->paquete.obtener_codigo() <<' ' << ptr->paquete.obtener_plazas() <<' '<< ptr->paquete.obtener_precio() << '\n' << ptr->opiniones.size();
                    for(unsigned i=0; i<ptr->opiniones.size(); ++i){
                        fich << '\n' << ptr->opiniones[i];
                    }
                    fich << '\n';
                    ptr=ptr->sig;
                }
            }
            fich.close();
            ok=true;
        }
    }
    //El formato es el del fichero "clientes.txt"
    void AgViajes::guardar_clientes(const std::string& fich_clientes, bool& ok)const{
        ok=false;
        std::ofstream fich;
        fich.open(fich_clientes.c_str());
        if(!fich.fail()){
            if(paquetes!=NULL){
                nodo_clientes ptr = clientes;
                while (ptr!=NULL){
                    fich << ptr->cliente.obtener_nombre() <<' ' << ptr->cliente.obtener_dinero() <<' '<< ptr->num_reservas;
                    for(unsigned i=0; i<ptr->paquetes.size(); ++i){
                        fich << ' ' << ptr->paquetes[i]->paquete.obtener_codigo();
                    }
                    fich << '\n';
                    ptr=ptr->sig;
                }
            }
            fich.close();
            ok=true;
        }
    }
    void AgViajes::nueva_reserva(const std::string& nombre, const std::string& cod, bool& ok){
        ok=false;
        nodo_clientes ptr1=buscar_cliente(nombre);
        nodo_paquetes ptr2 = buscar_paquete(cod);
        if(ptr1!=NULL && ptr2!=NULL){
            ok=true;
            ++ptr1->num_reservas;
            ptr1->paquetes.push_back(ptr2);
        }
    }
    void AgViajes::eliminar_reserva(const std::string& nombre, const std::string& cod, bool& ok)const{
        nodo_clientes ptr1=buscar_cliente(nombre);
        ok=false;
        if(ptr1!=NULL){
            Vector_Paquetes::iterator i=ptr1->paquetes.begin();
            while(i!=ptr1->paquetes.end() && cod!=(*i)->paquete.obtener_codigo()){
                ++i;
            }
            if(cod==(*i)->paquete.obtener_codigo()){
                ok=true;
                ptr1->paquetes.erase(i);
                --ptr1->num_reservas;
            }
        }
    }
    void AgViajes::nuevo_cliente(const std::string& nombre, int dinero, bool& ok){
        ok=false;
        if(!nombre.empty() && buscar_cliente(nombre)==NULL && dinero>=0){
            ok=true;
            if(clientes==NULL){
                clientes = new estructura_clientes;
                clientes->cliente=Cliente(nombre, dinero);
                clientes->num_reservas=0;
                clientes->sig=NULL;
            }
            else{
            nodo_clientes ptr=clientes;
                while(ptr->sig!=NULL){
                    ptr=ptr->sig;
                }
                ptr->sig = new estructura_clientes;
                ptr=ptr->sig;
                ptr->cliente=Cliente(nombre, dinero);
                ptr->num_reservas=0;    //Por ser variable numérica de tipo simple puede estar incializada con basura
                ptr->sig=NULL;
            }
        }
    }
    void AgViajes::nuevo_paquete(const std::string& cod, int plazas, int precio, bool& ok){
        ok=false;
        if(!cod.empty() && buscar_paquete(cod)==NULL && plazas>=0 && precio>=0){
            ok=true;
            if(paquetes==NULL){
                paquetes=new estructura_paquetes;
                paquetes->paquete=Paquete(cod, plazas, precio);
                paquetes->sig=NULL;
            }
            else{
                nodo_paquetes ptr=paquetes;
                while(ptr->sig!=NULL){
                    ptr=ptr->sig;
                }
                ptr->sig=new estructura_paquetes;
                ptr=ptr->sig;
                ptr->paquete=Paquete(cod, plazas, precio);
                ptr->sig=NULL;
            }
        }
    }
    void AgViajes::eliminar_cliente(const std::string& nombre, bool& ok){
        ok=false;
        nodo_clientes ptr=clientes;
        if(ptr!=NULL){
            if(ptr->cliente.obtener_nombre()==nombre){
                ok=true;
                clientes=clientes->sig;
                delete ptr;
            }
            else{
                while(ptr->sig!=NULL && ptr->sig->cliente.obtener_nombre()!=nombre){
                    ptr=ptr->sig;
                }
                if(ptr->sig!=NULL){
                    ok=true;
                    nodo_clientes ptr2=ptr->sig;
                    ptr->sig=ptr->sig->sig;
                    delete ptr2;
                }
            }
        }
    }
    void AgViajes::nuevo_comentario(const std::string& cod, const std::string& comentario, bool& ok){
        nodo_paquetes ptr = buscar_paquete(cod);
        ok=false;
        if(ptr!=NULL){
            ok=true;
            ptr->opiniones.push_back(comentario);
        }
    }
    

    AgViajes::nodo_paquetes AgViajes::duplicar_paquetes(const nodo_paquetes &a)const{
        nodo_paquetes original, aux;
        if(a==NULL){
            original=NULL;
        }
        else{
            original = new estructura_paquetes;
            aux=original;
            aux->opiniones=a->opiniones;
            aux->paquete=a->paquete;
            nodo_paquetes ptr=a;
            while(ptr->sig!=NULL){
                ptr=ptr->sig;
                aux->sig = new estructura_paquetes;
                aux=aux->sig;
                aux->opiniones=ptr->opiniones;
                aux->paquete=ptr->paquete;
            }
            aux->sig=NULL;
        }
        return original;
    }
    AgViajes::nodo_clientes AgViajes::duplicar_clientes(const nodo_clientes &a)const{
        nodo_clientes original, aux;
        if(a==NULL){
            original=NULL;
        }
        else{
            original=new estructura_clientes;
            aux=original;
            aux->cliente=a->cliente;
            aux->num_reservas=a->num_reservas;
            aux->paquetes=buscar_paquetes_en_vector(a->paquetes);
            nodo_clientes ptr=a;
            while(ptr->sig!=NULL){
                ptr=ptr->sig;
                aux->sig = new estructura_clientes;
                aux=aux->sig;
                aux->cliente=ptr->cliente;
                aux->num_reservas=ptr->num_reservas;
                aux->paquetes=buscar_paquetes_en_vector(a->paquetes);
            }
            aux->sig=NULL;
        }
        return original;
    }

    AgViajes::Vector_Paquetes AgViajes::buscar_paquetes_en_vector(const Vector_Paquetes &a)const{
        std::vector <std::string> aux;
        for(unsigned i=0; i<a.size(); ++i){
            aux.push_back(a[i]->paquete.obtener_codigo()); //Creamos un vector de string con el nombre de los paquetes
        }   //Esto lo hago asi para poder volver a usar el siguiente metodo en la lectura de ficheros sin tener que crear un vector de Paquetes cada vez, lo cual reserva muchisima memoria
        return meter_paquetes_en_vector_string(aux);
    }


    void AgViajes::eliminar_paquetes(){
        if(paquetes!=NULL){
            nodo_paquetes aux=paquetes;
            while(aux!=NULL){
                aux=aux->sig;
                delete paquetes;
                paquetes=aux;
            }
        }
    }
    void AgViajes::eliminar_clientes(){
        if(clientes!=NULL){
            nodo_clientes p2ant=clientes, p2act=clientes->sig;
            while(p2act!=NULL){
                delete p2ant;
                p2ant=p2act;
                p2act=p2act->sig;
            }
        }
    }
    AgViajes::Vector_Paquetes AgViajes::meter_paquetes_en_vector_string(const std::vector <std::string> &a)const{
        Vector_Paquetes aux;
        for(unsigned i=0; i<a.size(); ++i){
            aux.push_back(buscar_paquete(a[i]));
       }
       return aux;
    }
    AgViajes::nodo_paquetes AgViajes::buscar_paquete(const std::string &id)const{
        nodo_paquetes ptr=paquetes;
        while(ptr!=NULL && id!=ptr->paquete.obtener_codigo()){
            ptr=ptr->sig;
        }
        return ptr;
    }
    AgViajes::nodo_clientes AgViajes::buscar_cliente(const std::string &nom)const{
        nodo_clientes ptr=clientes;
        while(ptr!=NULL && nom!=ptr->cliente.obtener_nombre()){
            ptr=ptr->sig;
        }
        return ptr;
    }
    bool AgViajes::puede_ir(const std::string &nom)const{
        nodo_clientes ptr=buscar_cliente(nom);
        int precio_total=0, dinero_cliente=0;
        if(ptr!=NULL){
            dinero_cliente=ptr->cliente.obtener_dinero();
            for(unsigned i=0; i<ptr->paquetes.size(); ++i){
                precio_total+=ptr->paquetes[i]->paquete.obtener_precio();
            }
        }
        return dinero_cliente>=precio_total;
    }
}