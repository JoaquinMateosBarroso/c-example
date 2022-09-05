#include "cliente.hpp"
using namespace umalcc;

namespace umalcc
{

    Cliente::~Cliente() {}
    Cliente::Cliente() : nombre(), dinero(0) {}
    Cliente::Cliente(const std::string &n, int d) : nombre(n), dinero(d) {}
    Cliente::Cliente(const Cliente &o) : nombre(o.nombre), dinero(o.dinero) {}
    Cliente &Cliente::operator=(const Cliente &o)
    {
        if (this != &o)
        {
            nombre = o.nombre;
            dinero = o.dinero;
        }
        return *this;
    }
    bool Cliente::error()
    {
        return (nombre.empty() || dinero < 0);
    }
    std::string Cliente::obtener_nombre() const
    {
        return nombre;
    }
    int Cliente::obtener_dinero() const
    {
        return dinero;
    }
    void Cliente::modificar_dinero(int d, bool &ok)
    {
        if (d >= 0)
        {
            dinero = d;
            ok = true;
        }
        else
        {
            ok = false;
        }
    }
    void Cliente::mostrar() const
    {
        std::cout << nombre << ' ' << dinero;
    }
}