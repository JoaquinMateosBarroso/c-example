#ifndef agviajes_hpp
#define agviajes_hpp
#include "cliente.hpp"
#include "paquete.hpp"
#include <vector>
#include <deque>

namespace umalcc
{
    class AgViajes
    {
    public:
        ~AgViajes();
        AgViajes();
        AgViajes(const AgViajes &o);
        AgViajes &operator=(const AgViajes &o);
        void leer_paquetes(const std::string &fich_paquetes, bool &ok);
        void leer_clientes(const std::string &fich_clientes, bool &ok);
        void guardar_paquetes(const std::string &fich_paquetes, bool &ok) const;
        void guardar_clientes(const std::string &fich_clientes, bool &ok) const;
        void nueva_reserva(const std::string &nombre, const std::string &cod, bool &ok);
        void eliminar_reserva(const std::string &nombre, const std::string &cod, bool &ok) const;
        void nuevo_cliente(const std::string &nombre, int dinero, bool &ok);
        void nuevo_paquete(const std::string &cod, int plazas, int precio, bool &ok);
        void eliminar_cliente(const std::string &nombre, bool &ok);
        void nuevo_comentario(const std::string &cod, const std::string &comentario, bool &ok);
        bool puede_ir(const std::string &id) const;

    private:
        struct estructura_paquetes;
        typedef estructura_paquetes *nodo_paquetes;
        typedef Opiniones std::deque<std::string>
        struct estructura_paquetes
        {
            umalcc::Paquete paquete;
            Opiniones opiniones;
            nodo_paquetes sig;
        };
        typedef std::vector<nodo_paquetes> Vector_Paquetes;
        struct estructura_clientes;
        typedef estructura_clientes *nodo_clientes;
        struct estructura_clientes
        {
            Cliente cliente;
            int num_reservas;
            Vector_Paquetes paquetes;
            nodo_clientes sig;
        };
        nodo_paquetes paquetes;
        nodo_clientes clientes;
        nodo_paquetes duplicar_paquetes(const nodo_paquetes &a) const;
        nodo_clientes duplicar_clientes(const nodo_clientes &a) const;
        Vector_Paquetes buscar_paquetes_en_vector(const Vector_Paquetes &a) const;
        void eliminar_paquetes();
        void eliminar_clientes();
        Vector_Paquetes meter_paquetes_en_vector_string(const std::vector<std::string> &a) const;
        nodo_paquetes buscar_paquete(const std::string &id) const;
        nodo_clientes buscar_cliente(const std::string &nom) const;
    };
}

#endif