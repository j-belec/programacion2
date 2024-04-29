#include <iostream>
#include <cstring>

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

class Articulo{
    private:
        int codigo;
        char nombre[30];
        int stock;
        float precio;
    public:
        void setCodigo(int c){codigo=c;}
        void setNombre(const char *n){strcpy(nombre, n);}
        void setStock(int s){stock=s;}
        void setPrecio(float p){precio=p;}
        int getCodigo(){return codigo;}
        const char *getNombre(){return nombre;}
        int getStock(){return stock;}
        float getPrecio(){return precio;}
        void Cargar();
        void Mostrar();
};

void Articulo::Cargar(){
    cout<<"CODIGO: ";
    cin>>codigo;
    cout<<"NOMBRE: ";
    cargarCadena(nombre, 29);
    cout<<"STOCK: ";
    cin>>stock;
    cout<<"PRECIO: ";
    cin>>precio;
}

void Articulo::Mostrar(){
    cout<<"CODIGO: "<<codigo<<endl;
    cout<<"NOMBRE: "<<nombre<<endl;
    cout<<"STOCK: "<<stock<<endl;
    cout<<"PRECIO: "<<precio<<endl;
}

/**
MODOS DE APERTURA:
rb: read binary - abre el archivo en modo de lectura. Si no existe, no lo crea.
ab: append binary - abre el archivo en modo de escritura. Si no existe, lo crea. Siempre escribe al final.
wb: write binary - crea un archivo vacío y lo abre en modo de escritura. Si no existe, lo crea. Si ya existe,
                    lo pisa (se pierde el archivo viejo).
*/

/**
FILE: tipo de datos del que vamos a declarar un puntero para realizar la apertura del archivo.
Una vez abierto, usaremos ese puntero para referirnos al archivo.
fopen: función para abrir un archivo. Recibe el nombre del archivo y el modo de apertura.
fread: lleva la información del disco a la memoria.
fread(direccion de memoria donde voy a guardar la información,
      tamaño de un registro, cantidad de registros a leer, puntero FILE)
fwrite: lleva la información de la memoria al disco.
fwrite(direccion de memoria donde está la información que voy a guardar,
      tamaño de un registro, cantidad de registros a escribir, puntero FILE)
fclose: cierra el archivo. Recibe únicamente el puntero como parámetro.

eof: indica que se terminó el archivo
*/

void listarArticulos(){
    Articulo objArt;
    FILE *p;
    p=fopen("articulos lunes.dat", "rb");
    if(p==NULL){
        cout<<"ERROR DE ARCHIVO"<<endl;
        return;
    }
    while(fread(&objArt, sizeof (Articulo), 1, p)==1){
        objArt.Mostrar();
        cout<<endl;
    }
    fclose(p);
}

void grabarArticulo(Articulo obj){
    FILE *p;
    p = fopen("articulos lunes.dat", "ab");
    if(p == NULL) {
        cout << "ERROR DE FILE" << endl;
        return;
    }
    fwrite(&obj, sizeof(Articulo),1,p);
    fclose(p);
}

int main(){
    Articulo obj;
    obj.Cargar();

    grabarArticulo(obj);
    listarArticulos();

    return 0;
}

