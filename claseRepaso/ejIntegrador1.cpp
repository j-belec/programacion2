#include <iostream>
#include <string.h>
using namespace std;

//CARGAR CADENA
void cargarCadena(char *pal, int tam){
    int i;
    fflush (stdin);
    for(i=0; i<tam;i++){
        pal[i]=cin.get();
        if(pal[i]=='\n')break;
    }
    pal[i]='\0';
    fflush(stdin);
}

//CLASE TARJETA
class Tarjeta {
    private:
        int _numero;
        int _dni;
        float _saldo;
        bool _estado;
    public:
        Tarjeta(int numero = 0, int dni = 0, float saldo = 0, bool estado = true);
        //setters
        void setNumero(int numero) {_numero = numero;}
        void setDni(int dni) {_dni = dni;}
        void setSaldo(float saldo) {_saldo = saldo;}
        void setEstado(bool estado) {_estado = estado;}
        //getters
        int getNumero() {return _numero;}
        int getDni() {return _dni;}
        float getSaldo() {return _saldo;}
        bool getEstado() {return _estado;}
        //cargar y mostrar
        void Cargar();
        void Mostrar();
};
Tarjeta::Tarjeta(int numero, int dni, float saldo, bool estado){
    _numero = numero;
    _dni = dni;
    _saldo = saldo;
    _estado = estado;
}
void Tarjeta::Cargar() {
    cout << "Ingrese numero: ";
    cin >> _numero;
    cout << "Ingrese dni: ";
    cin >> _dni;
    cout << "Ingrese saldo";
    cin >> _saldo;
    cout << "Ingrese estado: ";
    cin >> _estado;
}
void Tarjeta::Mostrar() {
    if(_estado) {
        cout << "Numero: " << _numero << endl;
        cout << "DNI: " << _dni << endl;
        cout << "Saldo: " << _saldo << endl;
    }
}

//CLASE VIAJES
class Viaje {
    private:
        int _nroViaje;
        int _nroTarjeta; //?????
        int _medioTransporte;
        char _fecha[30];
        float _importe;
        bool _estado;
    public:
        //setters
        void setNroViaje(int nroViaje) {_nroViaje = nroViaje;}
        void setNroTarjeta(int nroTarjeta) {_nroTarjeta = nroTarjeta;}
        void setMedioTransporte(int medioTransporte) {_medioTransporte = medioTransporte;}
        void setFecha(const char* fecha) {strcpy(_fecha, fecha);}
        void setImporte(float importe) {_importe = importe;}
        void setEstado(bool estado) {_estado = estado;}
        //getters
        int getNroViaje() {return _nroViaje;}
        int getNroTarjeta() {return _nroTarjeta;}
        int getMedioTransporte() {return _medioTransporte;}
        const char* getFecha() {return _fecha;}
        float getImporte() {return _importe;}
        bool getEstado() {return _estado};
        //cargar y mostrar
        void Cargar();
        void Mostrar();
};
void Viaje::Cargar() {
    cout << "Ingresar nro viaje: ";
    cin >> _nroViaje;
    cout << "Ingresar nro tarjeta: ";
    cin >> _nroTarjeta;
    cout << "Ingresar medio de transporte: ";
    cin >> _medioTransporte;
    cin.ignore();
    cout << "Ingresar fecha: ";
    cargarCadena(_fecha, 29);
    cout << "Ingresar importe: ";
    cin >> _importe;
    cout << "Ingresar estado: ";
    cin >> _estado;
}
void Viaje::Mostrar() {
    if(_estado) {
        cout << "Nro viaje: " << _nroViaje << endl;
        cout << "Nro tarjeta: " << _nroTarjeta << endl;
        cout << "Medio de transporte: " << _medioTransporte << endl;
        cout << "Fecha: " << _fecha << endl;
        cout << "Importe: " << _importe << endl;
    }
}
