#include <iostream>
#include <string.h>
using namespace std;

void cargarCadena(char *pal, int tam) {
    int i;
    fflush(stdin);
    for(i = 0; i < tam; i++) {
        pal[i] = cin.get();
        if(pal[i] == '\n')break;
    }
    pal[i]='\0';
    fflush(stdin);
}

class Direccion {
    private:
        char _calle[30];
        int _numero;
        int _codPostal;
        char _localidad[30];
    public:
        Direccion(const char* calle = "s/c", int numero = 0, int codPostal = 0, const char* localidad = "s/l");
        //setters
        void setCalle(const char* calle) {strcpy(_calle, calle);}
        void setNumero(int numero) {_numero = numero;}
        void serCodPostal(int codPostal) {_codPostal = codPostal;}
        void setLocalidad(const char* localidad) {strcpy(_localidad, localidad);}
        //getter
        const char* getCalle() {return _calle;}
        int getNumero() {return _numero;}
        int getCodPostal() {return _codPostal;}
        const char* getLocalidad() {return _localidad;}
        //cargar y mostrar
        void Cargar();
        void Mostrar();
};
Direccion::Direccion(const char* calle, int numero, int codPostal, const char* localidad) {
    strcpy(_calle, calle);
    _numero = numero;
    _codPostal = codPostal;
    strcpy(_localidad, localidad);
}
void Direccion::Cargar() {
    cout << "Ingrese calle: ";
    cargarCadena(_calle, 29);
    cout << "Ingrese numero: ";
    cin >> _numero;
    cout << "Ingrese cod postal: ";
    cin >> _codPostal;
    cin.ignore();
    cout << "Ingrese localidad: ";
    cargarCadena(_localidad, 29);
}
void Direccion::Mostrar() {
    cout << "Calle: " << _calle << endl;
    cout << "Numero: " << _numero << endl;
    cout << "Cod postal: " << _codPostal << endl;
    cout << "Localidad: " << _localidad << endl;
}

class Fecha {
    private:
        int _dia;
        int _mes;
        int _anio;
    public:
        Fecha(int dia=1, int mes=1, int anio=1900) {
            _dia = dia;
            _mes = mes;
            _anio = anio;
        }
        void setDia(int dia) {
            if(dia>0 && dia<32) {
                _dia = dia;
            }
        }
        void setMes(int mes) {
            _mes= mes;
        }
        void setAnio(int anio) {
            _anio= anio;
        }
        void Cargar() {
            cout << "Dia: ";
            cin >> _dia;
            cout << "Mes: ";
            cin >> _mes;
            cout << "Año: ";
            cin >> _anio;
        }
        void Mostrar() {
            cout << _dia << "/" << _mes << "/" << _anio;
        }
        int getDia() {return _dia;}
        int getMes() {return _mes;}
        int getAnio() {return _anio;}

};

class Inmueble {
    private:
        Direccion _direccion;
        Fecha _fechaIngreso;
        Fecha _fechaOperacion;
        int _superficie;
        int _tipoOperacion;
    public:
        //hInmueble();
        //setters
        void setDireccion(Direccion direccion) {_direccion = direccion;}
        void setFechaIngreso(Fecha fechaIngreso) {_fechaIngreso = fechaIngreso;}
        void setFechaOperacion(Fecha fechaOperacion) {_fechaOperacion = fechaOperacion;}
        void setSuperficie(int superficie) {_superficie = superficie;}
        void setTipoOperacion(int tipoOperacion) {_tipoOperacion = tipoOperacion;}
        //getters
        Direccion getDireccion() {return _direccion;}
        Fecha getFechaIngreso() {return _fechaIngreso;}
        Fecha getFechaOperacion() {return _fechaOperacion;}
        int getSuperficie() {return _superficie;}
        int getTipoOperacion() {return _tipoOperacion;}
        //cargar y mostrar
        void Cargar();
        void Mostrar();
};
void Inmueble::Cargar() {
    cout << "Ingrese direccion: " << endl;
    _direccion.Cargar();
    cout << "Ingrese fecha ingreso: " << endl;
    _fechaIngreso.Cargar();
    cout << "Ingrese fecha operacion: " << endl;
    _fechaOperacion.Cargar();
    cout << "Ingrese superficie: ";
    cin >> _superficie;
    cout << "Ingrese tipo opercaion:";
    cin >> _tipoOperacion;
}
void Inmueble::Mostrar() {
    cout << "Direccion: " << endl;
    _direccion.Mostrar();
    cout << "Fecha ingreso: " <<endl;
    _fechaIngreso.Mostrar();
    cout << "Fecha operacion: " <<endl;
    _fechaOperacion.Mostrar();
    cout << "Superficie: " << _superficie << endl;
    cout << "Tipo opercaion: " << _tipoOperacion << endl;
}

class Casa: public Inmueble {
    private:
        int _cantAmbientes;
        int _supConstruida;
    public:
        //setters
        void setCantAmbientes(int cantAmbientes) {_cantAmbientes = cantAmbientes;}
        void setSupConstruida(int supConstruida) {_supConstruida = supConstruida;}
        //getter
        int getCantAmbientes() {return _cantAmbientes;}
        int getSupConstruida() {return _supConstruida;}
        //cargar y mostrar
        void Cargar();
        void Mostrar();
};
void Casa::Cargar() {
    Inmueble::Cargar();
    cout << "Ingrese cant amb: ";
    cin >> _cantAmbientes;
    cout << "Ingrese sup construida: ";
    cin >> _supConstruida;
}
void Casa::Mostrar() {
    Inmueble::Mostrar();
    cout << "Cant amb: " << _cantAmbientes << endl;
    cout << "Ingrese sup construida: " << _supConstruida << endl;
}

int main() {
    //Direccion dir1;

    //Inmueble inm;
    //inm.Cargar();
    //inm.Mostrar();

    Casa casa1;
    casa1.Cargar();
    casa1.Mostrar();

    return 0;
}
