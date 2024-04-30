#include <iostream>
#include <string.h>
using namespace std;

//FILENAME
const char* ARCHIVO_EMPRESAS = "empresas2.dat";

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
//FUNCION LIMPIAR ARCHIVO
void limpiarArchivo(){
    FILE *p;
    p=fopen("cat15.dat", "wb");
    if(p==NULL){
        return;
    }
    fclose(p);
}

//CLASE CATEGORIAS
class Categoria {
    private:
        int _numero;
        char _nombre[30];
        bool _estado;
    public:
        Categoria(int numero = 0, const char* nombre = "S/N", bool estado = true);
        //setters
        void setNumero(int numero) {_numero = numero;}
        void setNombre(const char* nombre) {strcpy(_nombre, nombre);}
        void setEstado(bool estado) {_estado = estado;}
        //getters
        int getNumero() {return _numero;}
        const char* getNombre() {return _nombre;}
        bool getEstado() {return _estado;}
        //cargar y mostrar
        void Cargar();
        void Mostrar();
};
Categoria::Categoria(int numero, const char* nombre, bool estado) {
    _numero = numero;
    strcpy(_nombre, nombre);
    _estado = estado;
}
void Categoria::Cargar() {
    cout << "Ingrese numero: ";
    cin >> _numero;
    cin.ignore();
    cout << "Ingrese nombre: ";
    cargarCadena(_nombre, 29);
    _estado = true;
}
void Categoria::Mostrar() {
    if(_estado) {
        cout << "Numero: " << _numero << endl;
        cout << "Nombre: " << _nombre << endl;
    }
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
        Categoria _categoria;
        Municipio _municipio;
        bool _estado;
    public:
        //setters
        void setNroEmpresa(int nroEmpresa) {_nroEmpresa = nroEmpresa;}
        void setNombre(const char* nombre) {strcpy(_nombre, nombre);}
        void setCantEmpleados(int cantEmpleados) {_cantEmpleados = cantEmpleados;}
        void setCategoria(Categoria categoria) {_categoria = categoria;}
        void setMunicipio(Municipio municipio) {_municipio = municipio;}
        void setEstado(bool estado) {_estado = estado;}
        //getter
        int getNroEmpresa() {return _nroEmpresa;}
        const char* getNombre() {return _nombre;}
        int getCantEmpleados() {return _cantEmpleados;}
        Categoria getCategoria() {return _categoria;}
        Municipio getMunicipio() {return _municipio;}
        bool getEstado() {return _estado;}
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
    _categoria.Cargar();
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
        cout << "Categoria: " << _categoria.getNumero() << endl;
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
    cout << "La empresa fue dada de baja" << endl;
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

//FUNCION CAT CON MAS EMP
void catMaxEmp() {
    int cats[80]{0};
    Empresa emp;
    FILE *p;
    p = fopen(ARCHIVO_EMPRESAS, "rb");
    if(p==NULL) {
        cout << "FILE ERROR" << endl;
        exit(1);
    }
    while(fread(&emp, sizeof(Empresa), 1, p) == 1) {
        cats[emp.getCategoria().getNumero() - 1] += emp.getCantEmpleados();
    }
    fclose(p);
    int nroMaxEmp = 0;
    int catMax;
    for(int i=0;i<80;i++) {
        if(cats[i] > nroMaxEmp) {
            nroMaxEmp = cats[i];
            catMax = i;
        }
    }
    cout << "Categoria con mas empleados es la categoria numero " << catMax + 1 << endl;
}

class Cat15 {
    private:
        int _nroEmp;
        char _nombreEmp[30];
        int _nroMuni;
        bool _estado;
    public:
        Cat15(int nroEmp = 0, const char* nombreEmp = "S/N", int nroMuni = 0, bool estado = 0);
        //setters
        void setNroEmp(int nroEmp) {_nroEmp = nroEmp;}
        void setNombreEmp(const char* nombreEmp) {strcpy(_nombreEmp, nombreEmp);}
        void setNroMuni(int nroMuni) {_nroMuni = nroMuni;}
        void setEstado(bool estado) {_estado = estado;}
        //getters
        int getNroEmp() {return _nroEmp;}
        const char* getNombreEmp() {return _nombreEmp;}
        int getNroMuni() {return _nroMuni;}
        bool getEstado() {return _estado;}
        //mostrar
        void Mostrar();
};
Cat15::Cat15(int nroEmp, const char* nombreEmp, int nroMuni, bool estado) {
    _nroEmp = nroEmp;
    strcpy(_nombreEmp, nombreEmp);
    _nroMuni = nroMuni;
    _estado = estado;
}
void Cat15::Mostrar() {
    if(_estado) {
        cout << "Numero Empresa: " << _nroEmp << endl;
        cout << "Nombre Empresa: " << _nombreEmp << endl;
        cout << "Numero Municipalidad: " << _nroMuni << endl;
    }
}

//FUNCION GENERAR UN FILE NUEVO CON LA CAT 15
void fcCat15() {
    Empresa emp;
    FILE *p;
    p = fopen(ARCHIVO_EMPRESAS, "rb");
    if(p==NULL){
        cout << "FILE ERROR" << endl;
        exit(1);
    }
    while(fread(&emp, sizeof(Empresa), 1, p) == 1) {
        if(emp.getCategoria().getNumero() == 15) {
            Cat15 cat(emp.getNroEmpresa(), emp.getNombre(), emp.getMunicipio().getNumero(), emp.getEstado());
            FILE *q;
            q = fopen("cat15.dat", "ab");
            if(q==NULL){exit(1);}
            fwrite(&cat, sizeof(Cat15), 1, q);
            fclose(q);
        }
    }
    fclose(p);

}

//FUNCION LISTAR TODAS LAS EMPRESAS
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


//FUNCION LISTAR EMPRESAS CAT 15
void listarEmpresasCat15() {
    Cat15 emp;
    FILE *p;
    p = fopen("cat15.dat", "rb");
    if(p==NULL) {
        cout << "FILE ERROR";
        exit(1);
    }
    while(fread(&emp, sizeof(Cat15), 1, p) == 1) {
        emp.Mostrar();
    }
    fclose(p);
}

//FUNCION CANT EMPRESAS
void cantEmpresas() {
    FILE *p;
    p = fopen(ARCHIVO_EMPRESAS, "rb");
    if(p==NULL) {
        cout << "FILE ERROR" << endl;
        exit(1);
    }
    fseek(p, sizeof(Empresa) * 0, 2);
    cout << ftell(p) << endl;
    cout << "Cant empresas: " << ftell(p) / sizeof(Empresa) << endl;
    fclose(p);
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
        cout << "6- EMPRESAS CON CATEGORIA 15" << endl;
        cout << "7- CANTIDAD TOTAL DE EMPRESAS" << endl;
        cout << "0- SALIR" << endl;
        cout << "Ingrese 0, 1, 2, 3, 4, 5 o 6: " << endl;
        cin >> eleccion;

        if(eleccion >= 0 && eleccion < 8) {
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
    case 6:
        listarEmpresasCat15();
        break;
    case 7:
        cantEmpresas();
        break;

    }

    return 0;
}


//class ArchivoEmpresas {
//    private:
//        char nombre[30];
//    public:
//        ArchivoEmpresas(const char* nombre)
//};

