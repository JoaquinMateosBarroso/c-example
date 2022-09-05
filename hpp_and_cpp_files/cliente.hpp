#ifndef cliente_hpp
#define cliente_hpp
#include <iostream>

namespace umalcc
{
    class Cliente
    {
    public:
        ~Cliente();
        Cliente();
        Cliente(const std::string &n, int d);
        Cliente(const Cliente &o);
        Cliente &operator=(const Cliente &o);
        bool error();
        std::string obtener_nombre() const;
        int obtener_dinero() const;
        void modificar_dinero(int d, bool &ok);
        void mostrar() const;

    private:
        std::string nombre;
        int dinero;
    };
}

#endif