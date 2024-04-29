#include <iostream>
#include <string.h>
using namespace std;

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

class Empresa {
    private:
        int _nroEmpresa;
        char _nombre[30];
        int _cantEmpleados;
        int _categoria;
        int _nroMunicipio;
        bool _estado;
    public:
        //setters
        void setNroEmpresa(int nroEmpresa) {_nroEmpresa = nroEmpresa;}
        void setNombre(const char* nombre) {strcpy(_nombre, nombre);}
        void setCantEmpleados(int cantEmpleados) {_cantEmpleados = cantEmpleados;}
        void setCategotia(int categoria) {_categoria = categoria;}
        void setNroMunicipio(int nroMunicipio) {_nroMunicipio = nroMunicipio;}
        void setEstado(bool estado) {_estado = estado;}
        //getter
        int getNroEmpresa() {return _nroEmpresa;}
        const char* getNombre() {return _nombre;}
        int getCantEmpleados() {return _cantEmpleados;}
        int getCategoria() {return _categoria;}
        int getNroMunicipio() {return _nroMunicipio;}
        int getEstado() {return _estado;}
        //cargar y mostrar
        void Cargar();
        void Mostrar();
};

void Empresa::Cargar() {
    cout << "Ingrese nro Empresa: ";
    cin >> _nroEmpresa;
    cin.ignore();
    cout << "Ingrese nombre:";
    cargarCadena(_nombre, 29);
    cout << "Ingrese cantidad empleados: ";
    cin >> _cantEmpleados;
    cout << "Ingrese categoria: ";
    cin >> _categoria;
    cout << "Ingrese nro municipio: ";
    cin >> _nroMunicipio;
    cout << "Ingrese estado: ";
    cin >> _estado;
    cin.ignore();
}

void Empresa::Mostrar() {
    cout << "Nro empresa: " << _nroEmpresa << endl;
    cout << "Nombre: " << _nombre << endl;
    cout << "Cantidad empleados: " << _cantEmpleados << endl;
    cout << "Categoria: " << _categoria << endl;
    cout << "Nro municipio: " << _nroMunicipio << endl;
    cout << "Estado: " << _estado << endl;
}

void cargarUnElemento() {
    Empresa emp;
    FILE *p;
    p = fopen("empresas.dat", "ab");
    if(p == NULL) {
        cout << "FILE ERROR";
        exit(1);
    }
    emp.Cargar();
    fwrite(&emp, sizeof(Empresa), 1, p);
    fclose(p);
}

void cargarUnVector() {
    Empresa emp[3];
    for(int i = 0; i<3; i++) {
        emp[i].Cargar();
    }
    FILE *p;
    p = fopen("empresas.dat", "ab");
    if(p == NULL) {
        cout << "FILE ERROR";
        exit(1);
    }
    fwrite(&emp, sizeof(Empresa), 3, p);
    fclose(p);
}

void mostrarUnElemento() {
    Empresa emp;
    FILE *p;
    p = fopen("empresas.dat", "rb");
    if(p == NULL) {
        cout << "FILE ERROR";
        exit(1);
    }
    fread(&emp, sizeof(Empresa), 1, p);
    emp.Mostrar();
    fclose(p);
}

void mostrarTodoElFile() {
    Empresa emp;
    FILE *p;
    p = fopen("empresas.dat", "rb");
    if(p == NULL) {
        cout << "FILE ERROR";
        exit(1);
    }
    while(fread(&emp, sizeof(Empresa), 1, p) == 1) {
        emp.Mostrar();
    }
    fclose(p);
}

void cantEmpMuni() {
    int v[150]{0};
    Empresa emp;
    FILE *p;
    p = fopen("empresas.dat", "rb");
    if(p==NULL) {
        cout << "FILE ERROR";
        exit(1);
    }
    while(fread(&emp, sizeof(Empresa), 1, p) == 1) {
        v[emp.getNroMunicipio() - 1]++;
    }

    for(int i = 0; i < 150; i++ ){
        cout << v[i] << endl;
    }
    fclose(p);
}

void empMas200() {
    Empresa emp;
    FILE *p;
    p = fopen("empresas.dat", "rb");
    if(p==NULL) {
        cout << "FILE ERROR";
        exit(1);
    }
    while(fread(&emp, sizeof(Empresa), 1, p) == 1) {
        if(emp.getCantEmpleados() > 200) {
            cout << emp.getNombre() << endl;
        }
    }
    fclose(p);
}

void catMasEmp() {
    int v[80]{0};

    Empresa emp;
    FILE *p;
    p = fopen("empresas.dat", "rb");
    if(p==NULL) {
        cout << "FILE ERROR";
        exit(1);
    }
    while(fread(&emp, sizeof(Empresa), 1, p) == 1) {
        v[emp.getCategoria() - 1] += emp.getCantEmpleados();
    }
    int cantMax = 0;
    int catMax;
    for(int i = 0; i < 80; i++) {
        if(v[i] > cantMax) {
            cantMax = v[i];
            catMax = i + 1;
        }
    }
    cout << "Cat con mas empleados: " << catMax << endl;
    fclose(p);
}

//FUNCION MAIN
int main() {
    int eleccion;

    bool num = false;
    while(!num) {
        cout << "MENU: " << endl;
        cout << "1- Cargar un solo registro" << endl;
        cout << "2- Cargar varios registros" << endl;
        cout << "3- Mostrar un solo registro" << endl;
        cout << "4- Mostrar todos los registros" << endl;
        cout << "5- Mostrar cantidad de empleados por municipio" << endl;
        cout << "6- Empresas con mas 200 empleados" << endl;
        cout << "7- Mostrar categoria con mas empleados" << endl;
        cout << "Ingrese 1, 2, 3 , 4, 5, 6 o 7: ";
        cin >> eleccion;

        if(eleccion > 0 && eleccion < 7) {
            num = true;
        }
    }

    switch(eleccion) {
    case 1:
        cargarUnElemento();
        break;
    case 2:
        cargarUnVector();
    case 3:
        mostrarUnElemento();
        break;
    case 4:
        mostrarTodoElFile();
        break;
    case 5:
        cantEmpMuni();
        break;
    case 6:
        empMas200();
        break;
    case 7:
        catMasEmp();
        break;
    }

    return 0;
}
