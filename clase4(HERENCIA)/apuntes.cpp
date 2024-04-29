#include <iostream>
#include <string.h>
using namespace std;

void cargarCadena(char*pal, int tam);

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

////////////
/////class persona
////////////
class Persona {
    private:
        int _dni;
        char _nombre[30];
        char _apellido[30];
        Fecha _fechaNacimiento; //cuando uso como tipo una clase se llama composicion
        char _telefono[15];
    public:
        Persona(int d= 0, const char *n= "S/N", const char *a= "S/A", Fecha f= Fecha(), const char *t= "S/T");
        void setDni(int dni) {_dni= dni;}
        void setNombre(const char *nombre) {strcpy(_nombre, nombre);}
        void setApellido(const char *apellido) {strcpy(_apellido, apellido);}
        void setFechaNacimiento(Fecha fechaN) {_fechaNacimiento= fechaN;}
        void setDiaNacimiento(int dia) {_fechaNacimiento.setDia(dia);}
        void setTelefono(const char *tel) {strcpy(_telefono, tel);}
        int getDni() {return _dni;}
        const char *getNombre() {return _nombre;}
        const char *getApellido() {return _apellido;}
        Fecha getFechaNacimiento() {return _fechaNacimiento;}
        int getDiaNacimiento() {return _fechaNacimiento.getDia();}
        const char *getTelefono() {return _telefono;}
        void Cargar();
        void Mostrar();
};

Persona::Persona(int d, const char *n, const char *a, Fecha f, const char *t) {
    _dni = d;
    strcpy(_nombre, n);
    strcpy(_apellido, a);
    _fechaNacimiento = f;
    strcpy(_telefono, t);
}

void Persona::Cargar() {
    cout << "Dni: ";
    cin >> _dni;
    cin.ignore(); // Cuando se utiliza cin >> _dni;, se lee el número de documento, pero queda un carácter de nueva línea ('\n') en el búfer del teclado. Luego, cuando intentas ingresar el nombre con cargarCadena(_nombre, 29);, el primer carácter que lee es ese '\n', por lo que parece que salta directamente al apellido.
    cout << "Nombre: ";
    cargarCadena(_nombre, 29);
    cout << "Apellido: ";
    cargarCadena(_apellido, 29);
    cout << "Fecha Nacimiento: ";
    _fechaNacimiento.Cargar();
    cin.ignore();
    cout << "Telefono: ";
    cargarCadena(_telefono, 14);
}

void Persona::Mostrar() {
     cout << "Dni: " << _dni << endl;
    cout << "Nombre: " << _nombre << endl;
    cout << "Apellido: " << _apellido << endl;
    cout << "Fecha Nacimiento: ";
    _fechaNacimiento.Mostrar();
    cout << endl;
    cout << "Telefono: " << _telefono << endl;
}

////////////
/////class persona
////////////
class Alumno : public Persona{
    private:
        int _legajo;
    public:
        Alumno(int l= 0);
        void setLegajo(int legajo) {_legajo= legajo;}
        int getLegajo(){return _legajo;}
        //void cambiarDni(int dni) {Persona::setDni(dni)}//si la extension con Persona seria public, no podria usar setDni() para cambiar el dni porq seria privada, entonces podria usar esta para cambiarlo
        void Cargar();
        void Mostrar();
        ~Alumno() {
            cout << "Me ejecute" << endl;
        }
};

Alumno::Alumno(int l) {
    _legajo = l;
};

void Alumno::Cargar() {
    Persona::Cargar();
    cout << "Legajo: ";
    cin >> _legajo;
}

void Alumno::Mostrar() {
    Persona::Mostrar();
    cout << "Legajo: " << _legajo;
}

////////////
/////class empleado
////////////
class Empleado: public Persona {
    private:
        int _categoria;
        float _sueldo;
        Fecha _fechaIngreso;
    public:
        Empleado(int categoria = 0, float sueldo = 0, Fecha fechaIngreso = Fecha());
        void setCategoria(int categoria) {_categoria = categoria;}
        void setSueldo(float sueldo) {_sueldo = sueldo;}
        void setFechaIngreso(Fecha fechaIngreso) {_fechaIngreso = fechaIngreso;}
        int getCategoria() {return _categoria;}
        float getSueldo() {return _sueldo;}
        Fecha getFecha() {return _fechaIngreso;}
        void Cargar();
        void Mostrar();
};

Empleado::Empleado(int categoria, float sueldo, Fecha fechaIngreso) {
    _categoria = categoria;
    _sueldo = sueldo;
    _fechaIngreso = fechaIngreso;
}

void Empleado::Cargar() {
    Persona::Cargar();
    cout << "Ingrese categoria: ";
    cin >> _categoria;
    cout << "Ingrese sueldo:";
    cin >> _sueldo;
    cout << "Ingrese fecha de ingreso: ";
    _fechaIngreso.Cargar();
}

void Empleado::Mostrar() {
    Persona::Mostrar();
    cout << "Categoria: " << _categoria << endl;
    cout << "Suedo: " << _sueldo << endl;
    _fechaIngreso.Mostrar();
}

////////////
/////main
////////////
int main() {
    //Fecha aux; //le dejo los valores por default a esta insatncia
    //aux.Cargar();
    //aux.Mostrar();

    //Alumno aux2;
    //aux2.setNombre("jero");
    //aux2.Cargar();
    //aux2.Mostrar();

    Empleado emp1(2);
    emp1.Cargar();
    emp1.Mostrar();

    return 0;
}

void cargarCadena(char *pal, int tam) { //esta funcion acepta espacios
    int i;
    fflush(stdin);
    for(i = 0; i < tam; i++) {
        pal[i] = cin.get(); //cin.get() agarra de un caracter a la vez
        if(pal[i] == '\n')break;
    }
    pal[i]='\0';
    fflush(stdin);
}
