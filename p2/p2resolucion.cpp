#include <iostream>
#include <cstdlib>
#include <cstring>
#include "p2h.h"
using namespace std;

class Punto1 {
private:
    int _id;
    char _nombre[30];
    int _categoriaDeporte;
public:
    void setId(int id) {_id = id;}
    void setNombre(const char* nombre) {strcpy(_nombre, nombre);}
    void setCategoriaDeporte(int categoriaDeporte) {_categoriaDeporte = categoriaDeporte;}
    void Mostrar() {
        cout << "id: " << _id << endl;
        cout << "nombre: " << _nombre << endl;
        cout << "cat dep: " << _categoriaDeporte << endl;
        cout << endl;
    }

};

int catDeporte(int idDep) {
    ArchivoDeportes archDeportes("deportes.dat");
    int totalRegsDeportes = archDeportes.contarRegistros();
    Deporte objDeporte;

    for(int k=0;k<totalRegsDeportes;k++) {
        objDeporte = archDeportes.leerRegistro(k);
        if(idDep == objDeporte.getIDdeporte()) {
           return objDeporte.getIDcategoria();
        }
    }
}

void fcPunto1() {
    ArchivoEquipos archEquipos("equipos.dat");
    int totalRegsEquipos = archEquipos.contarRegistros();
    Equipo objEquipo;

    ArchivoJugadores archJugadores("jugadores.dat");
    int totalRegsJugadores = archJugadores.contarRegistros();
    Jugador objJugador;

    FILE *p;
    p=fopen("punto1.dat", "ab");
    if(p==NULL) return;

    for(int i=0;i<totalRegsEquipos;i++) {
        objEquipo = archEquipos.leerRegistro(i);

        int cantJugadores = 0;
        int catDep;

        for(int j=0;j<totalRegsJugadores;j++) {
            objJugador = archJugadores.leerRegistro(j);
            if(objJugador.getIDequipo() == objEquipo.getIDequipo()) {
                cantJugadores++;
            }
            catDep = catDeporte(objJugador.getIDdeporte());
        }

        if(cantJugadores > 1) {

            Punto1 objPunto1;
            objPunto1.setCategoriaDeporte(catDep);
            objPunto1.setId(objEquipo.getIDequipo());
            objPunto1.setNombre(objEquipo.getNombre());
            fwrite(&objPunto1,sizeof(Punto1),1,p);
        }
    }
            fclose(p);

}

Punto1 leerRegPunto1(int pos) {
    FILE *p;
    p=fopen("punto1.dat", "rb");
    if(p==NULL) exit(1);
    Punto1 objPunto1;
    fseek(p,sizeof(Punto1) * pos,0);
    fread(&objPunto1,sizeof(Punto1),1,p);
    fclose(p);
    return objPunto1;
}

void fcPunto2() {
    FILE *p;
    p=fopen("punto1.dat", "rb");
    if(p==NULL) return;
    Punto1 objPunto1;
    int cont = 0;
    while(fread(&objPunto1,sizeof(Punto1),1,p)==1){
        cont++;
    }
    fclose(p);

    int tam = cont;
    Punto1 *vec;
    vec = new Punto1[tam];
    if(vec==NULL) return;

    for(int i=0;i<tam;i++) {
        vec[i] = leerRegPunto1(i);
    }

    for(int i=0;i<tam;i++) {
        vec[i].Mostrar();
    }

    delete[]vec;
}

bool Jugador::operator==(Deporte objDeporte) {
    if(getIDdeporte() == objDeporte.getIDdeporte()) {
        return true;
    }
    return false;
}

void agregarReg() {
    FILE *p;
    p = fopen("deportes.dat", "ab");
    if(p==NULL) {
        cout << "FILE ERROR FC AGREGAR";
        exit(1);
    }
    Deporte ob;
    ob.Cargar();
    fwrite(&ob, sizeof(Deporte), 1, p);
    fclose(p);
}

void leerRegs() {
    FILE *p;
    p = fopen("punto1.dat", "rb");
    if(p==NULL) {
        cout << "FILE ERROR FC LEER";
        exit(1);
    }
    Punto1 ob;
    while(fread(&ob, sizeof(Punto1), 1, p)==1) {
        ob.Mostrar();
    }
    fclose(p);
}

int main() {
//    agregarReg();
//    agregarReg();
    fcPunto2();

//    leerRegs();
    return 0;
}
