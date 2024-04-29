#include <iostream>
#include <string.h>
using namespace std;

//FILENAME
const char* ARCHIVO_EMPRESAS = "empresas2.dat";

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

void limpiarArchivo(){
    FILE *p;
    p=fopen(ARCHIVO_EMPRESAS, "wb");
    if(p==NULL){
        return;
    }
    fclose(p);
}


//CLASE MUNICIPIO
class Municipio {
    private:
        int _numero;
        char _nombre[30];
        int _seccion;
        int _cantHab;
        bool _estado;
    public:
        Municipio(int numero = 0, const char* nombre = "S/N", int seccion = 0, int cantHab = 0, bool estado = true);
        //setters
        void setNumero(int numero) {_numero = numero;}
        void setNombre(const char* nombre) {strcpy(_nombre, nombre);}
        void setSeccion(int seccion) {_seccion = seccion;}
        void setCantHab(int cantHab) {_cantHab = cantHab;}
        void setEstado(bool estado) {_estado = estado;}
        //getters
        int getNumero() {return _numero;}
        const char* getNombre() {return _nombre;}
        int getSeccion() {return _seccion;}
        int getCantHab() {return _cantHab;}
        bool getEstado() {return _estado;}
        //cargar y mostrar
        void Cargar();
        void Mostrar();
};
Municipio::Municipio(int numero, const char* nombre, int seccion, int cantHab, bool estado){
    _numero = numero;
    strcpy(_nombre, nombre);
    _seccion = seccion;
    _cantHab = cantHab;
    _estado = estado;
}
void Municipio::Cargar() {
    cout << "Ingrese numero: ";
    cin >> _numero;
    cin.ignore();
    cout << "Ingrese nombre: ";
    cargarCadena(_nombre, 29);
    cout << "Ingrese seccion: ";
    cin >> _seccion;
    cout << "Ingrese cantidad habitantes: ";
    cin >> _cantHab;
    _estado = true;
}
void Municipio::Mostrar() {
    if(_estado) {
        cout << "Numero: " << _numero << endl;
        cout << "Nombre: " << _nombre << endl;
        cout << "Seccion: " << _seccion << endl;
        cout << "Cant habitantes: " << _cantHab << endl;
    }
}

//CLASE EMPRESA
class Empresa {
    private:
        int _nroEmpresa;
        char _nombre[30];
        int _cantEmpleados;
        int _categoria;
        Municipio _municipio;
        bool _estado;
    public:
        //setters
        void setNroEmpresa(int nroEmpresa) {_nroEmpresa = nroEmpresa;}
        void setNombre(const char* nombre) {strcpy(_nombre, nombre);}
        void setCantEmpleados(int cantEmpleados) {_cantEmpleados = cantEmpleados;}
        void setCategoria(int categoria) {_categoria = categoria;}
        void setMunicipio(Municipio municipio) {_municipio = municipio;}
        void setEstado(bool estado) {_estado = estado;}
        //getter
        int getNroEmpresa() {return _nroEmpresa;}
        const char* getNombre() {return _nombre;}
        int getCantEmpleados() {return _cantEmpleados;}
        int getCategoria() {return _categoria;}
        Municipio getMunicipio() {return _municipio;}
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
    cout << "Ingrese municipio: " << endl;
    _municipio.Cargar();
    _estado = true;
    cin.ignore();
}
void Empresa::Mostrar() {
    if(_estado) {
        cout << "Nro empresa: " << _nroEmpresa << endl;
        cout << "Nombre: " << _nombre << endl;
        cout << "Cantidad empleados: " << _cantEmpleados << endl;
        cout << "Categoria: " << _categoria << endl;
        cout << "Municipio: " << endl;
        cout << "Nro municipio: " << _municipio.getNumero() << endl;
        cout << "Nombre municipio: " << _municipio.getNombre() << endl;
    }
}

//FUNCION PARA AVERIGUAR POSICION
int posicion(int nroEmpresa) {
   Empresa emp;
   FILE *p;
   p = fopen(ARCHIVO_EMPRESAS, "rb");
   if(p==NULL){
        cout << "FILE ERROR";
        exit(1);
    }
    int pos = 0;
    while(fread(&emp, sizeof(Empresa), 1, p) == 1) {
        if(emp.getNroEmpresa() == nroEmpresa) {
            return pos;
        }
        pos++;
    }
    fclose(p);
    return -1;
}

//FUNCION PARA SELECCIONAR UNA EMPRESA
Empresa seleccionarEmpresa(int pos) {
    Empresa emp;
    FILE *p;
    p= fopen(ARCHIVO_EMPRESAS, "rb+");
    if(p==NULL) {
        cout << "FILE ERROR" << endl;
        exit(1);
    }
    fseek(p, sizeof(Empresa) * pos, 0);
    fread(&emp, sizeof(Empresa), 1, p);
    return emp;
}

//FUNCION PARA MODIFICAR EMPRESA
void modificarEmpresa(Empresa emp, int pos) {
    FILE *p;
    p = fopen(ARCHIVO_EMPRESAS, "rb+");
    if(p==NULL) {
        cout << "FILE ERROR" << endl;
        exit(1);
    }
    fseek(p, sizeof(Empresa) * pos, 0);
    fwrite(&emp, sizeof(Empresa), 1, p);
}

//FUNCION ALTA EMPRESA
void altaEmpresa() {
    Empresa emp;
    emp.Cargar();
    int nroE = emp.getNroEmpresa();

    Empresa emp2;
    FILE *p;
    p = fopen(ARCHIVO_EMPRESAS, "rb");
    if(p==NULL){
        cout << "FILE ERROR";
        exit(1);
    }
    bool numExiste = false;
    while(fread(&emp2, sizeof(Empresa), 1, p) == 1) {
        if(emp.getNroEmpresa() == emp2.getNroEmpresa()) {
            numExiste = true;
            break;
        }
    }
    fclose(p);

    if(numExiste) {
        cout << "El numero de empresa ya existe. Cargue otro." << endl;
        altaEmpresa();
    } else {
        p = fopen(ARCHIVO_EMPRESAS, "ab");
        if(p==NULL){
          cout << "FILE ERROR";
            exit(1);
        }
        fwrite(&emp, sizeof(Empresa), 1, p);
        fclose(p);
    }
}
//FUNCION BAJA EMPRESA
void bajaEmpresa() {
    int nroEmpresa;
    cout << "Ingrese numero de empresa: ";
    cin >> nroEmpresa;

    int pos = posicion(nroEmpresa); //busco la posicion del registro
    if(pos<0){
        cout<<"NO EXISTE EL NUMERO DE EMPRESA EN EL ARCHIVO"<<endl;
        return;
    }

    Empresa emp;
    emp = seleccionarEmpresa(pos);
    emp.setEstado(false);
    modificarEmpresa(emp, pos);
    cout << "La empresa fue dadaa de baja" << endl;
}

//FUNCION PARA MODIFICAR CATEGORIA EMPRESA
void modificarCategoria() {
    int nroEmp, nroCat;
    cout << "Ingrese nro empresa: ";
    cin >> nroEmp;
    cout << "Ingrese nro de nueva categoria: ";
    cin >> nroCat;

    int pos = posicion(nroEmp);
    if(pos < 0) {
        cout << "Esa empresa no existe" << endl;
        return;
    }

    Empresa emp;
    emp = seleccionarEmpresa(pos);
    emp.setCategoria(nroCat);
    modificarEmpresa(emp, pos);
    cout << "Nro de categoria actualizado" << endl;
}

//FUNCION LISTAR EMPRESAS
void listarEmpresas() {
    Empresa emp;
    FILE *p;
    p = fopen(ARCHIVO_EMPRESAS, "rb");
    if(p==NULL) {
        cout << "FILE ERROR";
        exit(1);
    }
    while(fread(&emp, sizeof(Empresa), 1, p) == 1) {
        emp.Mostrar();
    }
    fclose(p);
}

//FUNCION MUNI MENOS 200K HABITANTES
void muniMinHab() {
    int muniHab[135]{0};

    Empresa emp;
    FILE *p;
    p = fopen(ARCHIVO_EMPRESAS, "rb");
    if(p==NULL){
        cout << "FILE ERROR" << endl;
        exit(1);
    }
    while(fread(&emp, sizeof(Empresa), 1, p) == 1) {
        muniHab[emp.getMunicipio().getNumero() - 1] += emp.getMunicipio().getCantHab();
    }
    fclose(p);
    for(int i=0;i<135;i++) {
        if(muniHab[i] < 200000 && muniHab[i] != 0) {
            cout << "Municipio nro " << i + 1 << ", tiene menos de 200.000 habitantes" << endl;
        }
    }
}

//FUNCION MAIN
int main() {
    int eleccion;

    bool num = false;
    while(!num) {
        cout << "MENU: " << endl;
        cout << "1- ALTA EMPRESA" << endl;
        cout << "2- BAJA EMPRESA" << endl;
        cout << "3- MODIFICAR CATEGORIA EMPRESA" << endl;
        cout << "4- LISTAR ELEMENTOS" << endl;
        cout << "5- CANTIDAD DE MUNICIPIOS CON MENOS DE 200.000 HABITANTES" << endl;
        cout << "0- SALIR" << endl;
        cout << "Ingrese 0, 1, 2, 3, 4 o 5: " << endl;
        cin >> eleccion;

        if(eleccion >= 0 && eleccion < 6) {
            num = true;
        }
    }

    switch(eleccion) {
    case 0:
        exit(1);
        break;
    case 1:
        altaEmpresa();
        break;
    case 2:
        bajaEmpresa();
    case 3:
        modificarCategoria();
        break;
    case 4:
        listarEmpresas();
        break;
    case 5:
        muniMinHab();
        break;

    }

    return 0;
}
