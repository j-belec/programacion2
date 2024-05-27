#include <iostream>
#include <cstring>
//#include "elpuntoh"
using namespace std;

//CARGAR CADENA ///////////////////////////////////////////////////////////////
void cargarCadena(char *pal, int tam){
    int i;
    fflush(stdin);
    for(i=0; i<tam; i++)
    {
        pal[i]=cin.get();
        if(pal[i]=='\n') break;
    }
    pal[i]='\0';
    fflush(stdin);
}

//AGREGAR REGISTRO /////////////////////////////////////////////////////////////
void agregarReg() {
    FILE *p;
    p = fopen("materiales.dat", "ab");
    if(p==NULL) {
        cout << "FILE ERROR FC AGREGAR";
        exit(1);
    }
    Material ob;
    ob.Cargar();
    fwrite(&ob, sizeof(Material), 1, p);
    fclose(p);
}

//LEER TODOS LOS REGISTROS /////////////////////////////////////////////////////
void leerRegs() {
    FILE *p;
    p = fopen("materiales.dat", "rb");
    if(p==NULL) {
        cout << "FILE ERROR FC LEER";
        exit(1);
    }
    Material ob;
    while(fread(&ob, sizeof(Material), 1, p)==1) {
        ob.Mostrar();
    }
    fclose(p);
}
