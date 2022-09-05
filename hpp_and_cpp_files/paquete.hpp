#ifndef paquete_hpp
#define paquete_hpp
#include <iostream>

namespace umalcc{
    class Paquete{
    public:
        ~Paquete();
        Paquete();
        Paquete(const std::string& c, int pl, int pr);
        Paquete(const Paquete& o);
        Paquete& operator=(const Paquete& o);
        bool error() const;
        std::string obtener_codigo() const;
        int obtener_plazas() const;
        int obtener_precio() const;
        void modificar_plazas(int p, bool& ok);
        void modificar_precio(int p, bool& ok);
        void mostrar()const;
    private:
        std::string id;
        unsigned n_plazas;
        int precio;
    };

}
#endif