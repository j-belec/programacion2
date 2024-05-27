#include <cstring>
#include <iostream>

using namespace std;

void cargarCadena(char *pal, int tam){
    int i;
    fflush (stdin); ///limpia el buffer de entrada para que la carga se haga sin caracteres que hayan quedado sin usar
    for(i=0; i<tam;i++){
        pal[i]=cin.get();
        if(pal[i]=='\n')break;
    }
    pal[i]='\0';
    fflush(stdin); ///vuelve a limpiar el buffer para eliminar los caracteres sobrantes
}

class Empresa{
    private:
        int numero;
        char nombre[30];
        int cantidadEmpleados;
        int categoria;
        int numeroMunicipio;
        bool estado;
    public:
        Empresa(){estado=false;}
        void setNumero(int n){
            numero=n;
        }
        void setCategoria(int c){categoria=c;}
        void setEstado(bool e){estado=e;}
        int getNumero(){return numero;}
        bool getEstado(){return estado;}
        int getCategoria() {return categoria;}
        void Cargar(int num=-1){
            if(num == -1){
                cout<<"NUMERO: ";
                cin>>numero;
            }else{
                numero=num;
            }
            cout<<"NOMBRE: ";
            cargarCadena(nombre, 29);
            cout<<"CANTIDAD DE EMPLEADOS: ";
            cin>>cantidadEmpleados;
            cout<<"CATEGORIA: ";
            cin>>categoria;
            cout<<"NUMERO DE MUNICIPIO: ";
            cin>>numeroMunicipio;
            estado=true;
        }
        void Mostrar(){
            if(estado){
                cout<<"NUMERO: "<<numero<<endl;
                cout<<"NOMBRE: "<<nombre<<endl;
                cout<<"CANTIDAD DE EMPLEADOS: "<<cantidadEmpleados<<endl;
                cout<<"CATEGORIA: "<<categoria<<endl;
                cout<<"NUMERO DE MUNICIPIO: "<<numeroMunicipio<<endl;
            }
        }
};

class ArchivoEmpresas{
    private:
        char nombre[30];
    public:
        ArchivoEmpresas(const char *n="empresas.dat"){strcpy(nombre, n);}
        Empresa leerRegistro(int pos);
        void grabarRegistro(Empresa obj);
        void modificarRegistro(Empresa obj, int pos);
        void listarRegistros();
        int buscarRegistro(int num);
        int contarRegistros();
};

Empresa ArchivoEmpresas::leerRegistro(int pos){
    Empresa obj;
    obj.setNumero(-1);
    FILE *p;
    p=fopen(nombre,"rb");
    if(p==nullptr){
        cout<<"ERROR DE ARCHIVO"<<endl;
        obj.setNumero(-2);
        return obj;
    }
    fseek(p, pos * sizeof obj, 0);
    fread(&obj, sizeof obj, 1, p);
    fclose(p);
    return obj;
}

void ArchivoEmpresas::grabarRegistro(Empresa obj){
    FILE *p;
    p=fopen(nombre,"ab");
    if(p==nullptr){
        cout<<"ERROR DE ARCHIVO"<<endl;
        return;
    }
    fwrite(&obj, sizeof obj, 1, p);
    fclose(p);
}

void ArchivoEmpresas::modificarRegistro(Empresa obj, int pos){
    FILE *p;
    p=fopen(nombre,"rb+");
    if(p==nullptr){
        return;
    }
    fseek(p, pos * sizeof obj , 0);
    fwrite(&obj, sizeof obj, 1, p);
    fclose(p);
}

void ArchivoEmpresas::listarRegistros(){
    int cant = contarRegistros();
    Empresa obj;
    for(int i=0; i<cant; i++){
        obj = leerRegistro(i);
        obj.Mostrar();
        if(obj.getEstado()) cout<<endl;
    }
}

int ArchivoEmpresas::buscarRegistro(int num){
    Empresa obj;
    int cant=contarRegistros();
    for(int i=0; i<cant; i++){
        obj = leerRegistro(i);
        if(obj.getNumero()==num){
            return i;
        }
    }
    return -1;
}

int ArchivoEmpresas::contarRegistros(){
    FILE *p=fopen(nombre,"rb");
    if(p==nullptr){
        cout<<"ERROR DE ARCHIVO"<<endl;
        return -1;
    }
    fseek(p, 0, 2);
    int cant=ftell(p);
    fclose(p);
    return cant/sizeof (Empresa);
}

void altaEmpresa(){
    ArchivoEmpresas arcEmp;
    int num;
    cout<<"NUMERO DE EMPRESA: ";
    cin>>num;
    if(num<1){
        cout<<"EL NUMERO NO ES VALIDO";
        return;
    }
    if(arcEmp.buscarRegistro(num) >= 0){
        cout<<"EL NUMERO DE EMPRESA INGRESADO YA EXISTE EN EL ARCHIVO"<<endl;
        return;
    }
    Empresa obj;
    obj.Cargar(num);
    if(obj.getEstado()){
        ArchivoEmpresas arcEmp("empresas.dat");
        arcEmp.grabarRegistro(obj);
    }
}

void modificarCategoria(){
    int num;
    cout<<"INGRESE EL NUMERO DE EMPRESA A MODIFICAR: ";
    cin>>num;
    ArchivoEmpresas arcEmp;
    int pos=arcEmp.buscarRegistro(num);
    if(pos==-1){
        cout<<"NO EXISTE ESE NUMERO EN EL ARCHIVO";
        return;
    }
    Empresa obj;
    obj = arcEmp.leerRegistro(pos);
    if(obj.getEstado()==false){
        cout<<"EL REGISTRO QUE QUIERE MODIFICAR ESTA DADO DE BAJA";
        return;
    }
    int cat;
    cout<<"INGRESE LA CATEGORIA NUEVA: ";
    cin>>cat;
    obj.setCategoria(cat);
    arcEmp.modificarRegistro(obj, pos);
}

void bajaEmpresa(){
    int num;
    cout<<"INGRESE EL NUMERO DE EMPRESA A DAR DE BAJA: ";
    cin>>num;
    ArchivoEmpresas arcEmp;
    int pos=arcEmp.buscarRegistro(num);
    if(pos==-1){
        cout<<"NO EXISTE ESE NUMERO EN EL ARCHIVO";
        return;
    }
    Empresa obj;
    obj = arcEmp.leerRegistro(pos);
    if(obj.getEstado()==false){
        cout<<"EL REGISTRO YA ESTA DADO DE BAJA";
        return;
    }
    obj.setEstado(false);
    arcEmp.modificarRegistro(obj, pos);
}

void listarEmpresas(){
    ArchivoEmpresas arcEmp;
    arcEmp.listarRegistros();
}

void listarPorNumero(){
    int num;
    cout<<"INGRESE EL NUMERO DE LA EMPRESA: ";
    cin>>num;
    ArchivoEmpresas arcEmp;
    int pos=arcEmp.buscarRegistro(num);
    if(pos<0){
        cout<<"NO EXISTE UNA EMPRESA CON ESE NUMERO";
        return;
    }
    Empresa obj;
    obj = arcEmp.leerRegistro(pos);
    obj.Mostrar();
}

void menuPrincipal(){
    int opc;
    while(true){
        system("cls");
        cout<<"MENU PRINCIPAL"<<endl;
        cout<<"--------------"<<endl;
        cout<<"1 - ALTA"<<endl;
        cout<<"2 - BAJA LOGICA"<<endl;
        cout<<"3 - MODIFICAR CATEGORIA"<<endl;
        cout<<"4 - LISTAR ARCHIVO"<<endl;
        cout<<"5 - LISTAR POR NUMERO"<<endl;
        cout<<"0 - SALIR"<<endl;
        cout<<"-------------------"<<endl;
        cout<<"INGRESE UNA OPCION: ";
        cin>>opc;
        system("cls");
        switch(opc){
            case 1:
                altaEmpresa();
                break;
            case 2:
                bajaEmpresa();
                break;
            case 3:
                modificarCategoria();
                break;
            case 4:
                listarEmpresas();
                break;
            case 5:
                listarPorNumero();
                break;
            case 0:
                return;
            default:
                cout<<"OPCION INCORRECTA"<<endl;
                break;
        }
        system("pause");
    }
}

void cargarVector(int *v, int tam){
    for(int i=0; i<tam; i++){
//        cout<<"VALOR: ";
//        cin>>v[i];
        v[i]=i+1;
    }
}

void mostrarVector(int *v, int tam){
    for(int i=0; i<tam; i++){
        cout<<"VALOR: "<<v[i]<<endl;
    }
}

//funcion que pide categoria. se cargan en un vector solo las empresas de esa categoria (el tamaño del vector tiene que ser dinamico)
void fcCat() {
    int nroCat;
    cout << "Ingrese categoria: ";
    cin >> nroCat;

    ArchivoEmpresas archiEmpresas;
    int cantRegistros = archiEmpresas.contarRegistros();
    Empresa objEmpresa;

    int tam = 0;

    for(int i=0;i<cantRegistros;i++) {
        objEmpresa = archiEmpresas.leerRegistro(i);
        if(objEmpresa.getCategoria() == nroCat) {
            tam++;
        }
    }

    Empresa *v;
    v = new Empresa[tam];
    int pos = 0;
    for(int i=0;i<cantRegistros;i++) {
        objEmpresa = archiEmpresas.leerRegistro(i);
        if(objEmpresa.getCategoria() == nroCat) {
            v[pos] = objEmpresa;
            pos++;
        }
    }

    for(int i=0;i<tam;i++) {
        v[i].Mostrar();
    }

    delete v;
}

int main(){
//    int *vec;
//    int cant;
//    cout<<"INGRESE LA CANTIDAD DE ELEMENTOS DEL VECTOR: ";
//    cin>>cant;
//    vec=new int[cant];
//    if(vec==nullptr){
//        cout<<"ERROR DE ASIGNACION DE MEMORIA"<<endl;
//        return -1;
//    }
//    cargarVector(vec, cant);
//    mostrarVector(vec, cant);
//    delete[] vec;
//    menuPrincipal();
    fcCat();
    return 0;
}
