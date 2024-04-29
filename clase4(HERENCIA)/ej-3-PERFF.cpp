#include <iostream>
#include <string.h>
using namespace std;

//CARGAR CADENA
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

//CLASE DIMENSION
class Denominacion {
private:
    char _nombreCientifico[30];
    char _nombreComun[30];
    char _nombreOriginario[30];
public:
    Denominacion(const char* nombreCientifico = "s/n", const char* nombreComun = "s/n", const char* nombreOriginario = "s/n");
    //setters
    void setNombreCientifico(const char* nombreCientifico) {strcpy(_nombreCientifico, nombreCientifico);}
    void setNombreComun(const char* nombreComun) {strcpy(_nombreComun, nombreComun);}
    void setNombreOriginario(const char* nombreOriginario) {strcpy(_nombreOriginario, nombreOriginario);}
    //getters
    const char* getNombreCientifico() {return _nombreCientifico;}
    const char* getNombreComun() {return _nombreComun;}
    const char* getNombreOriginario() {return _nombreOriginario;}
    //mostrar y cargar
    void Cargar();
    void Mostrar();
};

Denominacion::Denominacion(const char* nombreCientifico, const char* nombreComun, const char* nombreOriginario) {
    strcpy(_nombreCientifico, nombreCientifico);
    strcpy(_nombreComun, nombreComun);
    strcpy(_nombreOriginario, nombreOriginario);
}

void Denominacion::Cargar() {
    cout << "Ingrese nombre cientifico: ";
    cargarCadena(_nombreCientifico, 29);
    cout << "Ingrese nombre comun: ";
    cargarCadena(_nombreComun, 29);
    cout << "Ingrese nombre originario: ";
    cargarCadena(_nombreOriginario, 29);
}

void Denominacion::Mostrar() {
    cout << "Nombre cientifico: " << _nombreCientifico << endl;
    cout << "Nombre comun: " << _nombreComun << endl;
    cout << "Nombre originario: " << _nombreOriginario << endl;
}

//CLASE DIMENSION
class Dimension {
    private:
        float _largo;
        float _ancho;
        float _alto;
    public:
        Dimension(float largo = 0, float ancho = 0, float alto = 0);
        //setters
        void setLargo(float largo) {_largo = largo;}
        void setAncho(float ancho) {_ancho = ancho;}
        void setAlto(float alto) {_alto = alto;}
        //getter
        float getLargo() {return _largo;}
        float getAncho() {return _ancho;}
        float getAlto() {return _alto;}
        //cargar y mostrar
        void Cargar();
        void Mostrar();
};

Dimension::Dimension(float largo, float ancho, float alto) {
    _largo = largo;
    _ancho = ancho;
    _alto = alto;
}

void Dimension::Cargar() {
    cout << "Ingrese largo: ";
    cin >> _largo;
    cout << "Ingrese ancho: ";
    cin >> _ancho;
    cout << "Ingrese alto: ";
    cin >> _alto;
}

void Dimension::Mostrar() {
    cout << "Largo: " << _largo << endl;
    cout << "Ancho: " << _ancho<< endl;
    cout << "Alto: " << _alto<< endl;
}

class Animal {
private:
    Denominacion _denominacion;
    int _tiempoVidaProm;
    Dimension _dimension;
    float _peso;
public:
    Animal(Denominacion denominacion = Denominacion(), int tiempoVidaProm = 0, Dimension dimension = Dimension(), float peso = 0);
    //setters
    void setDenominacion(Denominacion denominacion) {_denominacion = denominacion;}
    void setTiempoVidaProm(int tiempoVidaProm) {_tiempoVidaProm = tiempoVidaProm;}
    void setDimension(Dimension dimension) {_dimension = dimension;}
    void setPeso(float peso) {_peso = peso;}
    //getter
    Denominacion getDenominacion() {return _denominacion;}
    int getTiempoVidaProm() {return _tiempoVidaProm;}
    Dimension getDimension() {return _dimension;}
    float getPeso() {return _peso;}
    //cargar y mostrar
    void Cargar();
    void Mostrar();
};

Animal::Animal(Denominacion denominacion, int tiempoVidaProm, Dimension dimension, float peso) {
    _denominacion = denominacion;
    _tiempoVidaProm = tiempoVidaProm;
    _dimension = dimension;
    _peso = peso;
}

void Animal::Cargar() {
    cout << "Ingrese denominacion: " << endl;
    _denominacion.Cargar();
    cout << "Ingrese tiempo vida prom: ";
    cin >> _tiempoVidaProm;
    cout << "Ingrese dimension: " << endl;
    _dimension.Cargar();
    cout << "Ingrese peso: ";
    cin >> _peso;
}

void Animal::Mostrar() {
    cout << "Denominacion: " << endl;
    _denominacion.Mostrar();
    cout << "Tiempo vida prom: " << _tiempoVidaProm << endl;
    cout << "Dimension: " << endl;
    _dimension.Mostrar();
    cout << "Peso: " << _peso << endl;
}

//CLASE PEZ
class Pez: public Animal {
    private:
        char _tipoAgua[30];
        float _profundidad;
    public:
        //setters
        void setTipoAgua(const char* tipoAgua) {strcpy(_tipoAgua, tipoAgua);}
        void setProfundidad(float profundidad) {_profundidad = profundidad;}
        //getters
        const char* getTipoAgua() {return _tipoAgua;}
        float getProfundidad() {return _profundidad;}
        //cargar y mostrar
        void Cargar();
        void Mostrar();
};

void Pez::Cargar() {
    Animal::Cargar();
    cin.ignore();
    cout << "Ingrese tipo de agua: ";
    cargarCadena(_tipoAgua, 29);
    cout << "Ingrese profundidad: ";
    cin >> _profundidad;
}

void Pez::Mostrar() {
    Animal::Mostrar();
    cout << "Tipo de agua: " << _tipoAgua << endl;
    cout << "Profundidad: " << _profundidad << endl;
}

//FUNCION MAIN
int main() {
//    Animal perro;
//    Denominacion denom;
//    denom.setNombreCientifico("Canis lupus familiaris");
//    denom.setNombreComun("Perro");
//    denom.setNombreOriginario("Perrin");
//    perro.setDenominacion(denom);
//    perro.Mostrar();
    Pez dorado;
    dorado.Cargar();
    dorado.Mostrar();

    return 0;
}
