#include "agviajes.hpp"
#include <cassert>
#include <string>
using namespace std;
using namespace umalcc;

void fallo(bool ok){
    if(!ok){
        cout << "Ha habido algun fallo en la ejecucion del metodo";
    }
}
string leer_nombre_fich(){
    string a;
    cout << "Introduzca el nombre del fichero: ";
    getline(cin, a);
    return a;
}

void destructor(AgViajes &a){
    a.~AgViajes();
}
void constructor_por_defecto(AgViajes &a){
    a = AgViajes();
}
void constructor_de_copia(AgViajes &a){
    a=AgViajes(a);
}
void operador_igual(AgViajes &a){
    AgViajes b=a;
    a=b;
}
void leer_paquetes(AgViajes &a){
    string nom=leer_nombre_fich();
    bool ok=false;
    a.leer_paquetes(nom, ok);
    fallo(ok);  //Uso esto en vez de assert por si una vez me sale el fallo quiero comprobar qué ha ocurrido mirando las caracteristicas del objeto en otro metodo
}
void leer_clientes(AgViajes &a){
    string nom=leer_nombre_fich();
    bool ok=false;
    a.leer_clientes(nom, ok);
    fallo(ok);
}
void guardar_paquetes(AgViajes &a){
    string nom=leer_nombre_fich();
    bool ok=false;
    a.guardar_paquetes(nom, ok);
    fallo(ok);
}
void guardar_clientes(AgViajes &a){
    string nom=leer_nombre_fich();
    bool ok=false;
    a.guardar_clientes(nom, ok);
    fallo(ok);
}
void nueva_reserva(AgViajes &a){
    string nom, cod;
    bool ok=false;
    cout << "Introduzca el nombre del cliente: ";
    getline(cin, nom);
    cout << "Introduzca el codigo del paquete: ";
    getline(cin, cod);
    a.nueva_reserva(nom, cod, ok);
    fallo(ok);
}

void eliminar_reserva(AgViajes &a){
    string nom, cod;
    bool ok=false;
    cout << "Introduzca el nombre del cliente: ";
    getline(cin, nom);
    cout << "Introduzca el codigo del paquete: ";
    getline(cin, cod);
    a.eliminar_reserva(nom, cod, ok);
    fallo(ok);
}

void nuevo_cliente(AgViajes &a){
    string nom;
    int dinero;
    bool ok=false;
    cout << "Introduzca el nombre del cliente: ";
    getline(cin, nom);
    cout << "Introduzca el dinero del cliente: ";
    cin >> dinero;
    a.nuevo_cliente(nom, dinero, ok);
    fallo(ok);
}
void nuevo_paquete(AgViajes &a){
    string cod;
    int plazas, precio;
    bool ok=false;
    cout << "Introduzca el codigo del paquete: ";
    getline(cin, cod);
    cout << "Introduzca la cantidad de plazas del paquete: ";
    cin >> plazas;
    cout << "Introduzca el precio del paquete: ";
    cin >> precio;
    a.nuevo_paquete(cod, plazas, precio, ok);
    fallo(ok);
}
void eliminar_cliente(AgViajes &a){
    string nom;
    bool ok=false;
    cout << "Introduzca el nombre del cliente: ";
    getline(cin, nom);
    a.eliminar_cliente(nom, ok);
    fallo(ok);
}
void nuevo_comentario(AgViajes &a){
    string cod, comment;
    bool ok=false;
    cout << "Introduzca el codigo del paquete: ";
    getline(cin, cod);
    cout << "Introduzca el comentario: ";
    getline(cin, comment);    
    a.nuevo_comentario(cod, comment, ok);
    fallo(ok);
}



int main(){
    AgViajes a;
    int eleccion;
    do{
        cout << "\nElija una opcion de las siguientes:\n";
        cout << "0.- Acabar la ejecucion\n";
        cout << "1.- Destruir la agencia actual(no recomendable si se va a utilizar posteriormente)\n";
        cout << "2.- Crear una agencia vacia\n";
        cout << "3.- Crear una agencia como copia de la actual\n";
        cout << "4.- Crear una agencia y aplicarle el operador igual sobre la agencia actual\n";
        cout << "5.- Leer paquetes de fichero\n";
        cout << "6.- Leer clientes de fichero\n";
        cout << "7.- Guardar paquetes en fichero\n";
        cout << "8.- Guardar clientes en fichero\n";
        cout << "9.- Hacer una nueva reserva para un cliente existente\n";
        cout << "10.- Eliminar la reserva de un cliente\n";
        cout << "11.- Anyadir un nuevo cliente\n";
        cout << "12.- Anyadir un nuevo paquete\n";
        cout << "13.- Eliminar un cliente\n";
        cout << "14.- Anyadir un comentario a un paquete\n";



        cin >> eleccion;
        cin.ignore();
        switch (eleccion)
        {
        case 1:
            destructor(a);
            break;
        case 2:
            constructor_por_defecto(a);
            break;
        case 3:
            constructor_de_copia(a);
            break;
        case 4:
            operador_igual(a);
            break;
        case 5:
            leer_paquetes(a);
            break;
        case 6:
            leer_clientes(a);
            break;
        case 7:
            guardar_paquetes(a);
            break;
        case 8:
            guardar_clientes(a);
            break;
        case 9:
            nueva_reserva(a);
            break;   
        case 10:
            eliminar_reserva(a);
            break;
        case 11:
            nuevo_cliente(a);
            break;
        case 12:
            nuevo_paquete(a);
            break;
        case 13:
            eliminar_cliente(a);
            break;
        case 14:
            nuevo_comentario(a);
            break;
        case 15:
            string nom;
            getline(cin, nom);
            if(a.puede_ir(nom)){
                cout << "Puede ir";
            }
            else{
                cout << "No puede ir";
            }
        }

    }while(eleccion!='0');
}