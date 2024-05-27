#include <iostream>
#include <cstring>
using namespace std;
#include "parcial1l.h"


class Punto1 {
    private:
        int _DNI;
        char _nombre[25];
        char _apellido[30];
        Fecha _fechaInsc;
    public:
        void setDni(int DNI) {_DNI = DNI;}
        void setNombre(const char* nombre) {strcpy(_nombre, nombre);}
        void setApellido(const char* apellido) {strcpy(_apellido, apellido);}
        void setFechaInsc(Fecha fechaInsc) {_fechaInsc = fechaInsc;}
        void Mostrar() {
            cout << "DNI: " << _DNI << endl;
            cout << "Nombre: " << _nombre << endl;
            cout << "Apellido: " << _apellido << endl;
            cout << endl;
        }
};

void funcionPunto1() {
    ArchivoJugadores archJugadores("jugadores.dat");
    int totalRegsJugadores = archJugadores.contarRegistros();
    Jugador objJugador;
    for(int i=0;i<totalRegsJugadores;i++) {
        objJugador = archJugadores.leerRegistro(i);
        int idEquipo = objJugador.getIdEquipo();
        if(objJugador.getEstado()) {
            ArchivoEquipos archEquipos("equipos.dat");
            int totalRegsEquipos = archEquipos.contarRegistros();
            Equipo objEquipo;
            for(int j=0;j<totalRegsEquipos;j++) {
                objEquipo = archEquipos.leerRegistro(j);
                if(objEquipo.getIdEquipo() == idEquipo && objEquipo.getNivel() == 1 && objEquipo.getEstado()) {
                    Punto1 objPunto1;
                    objPunto1.setDni(objJugador.getDNI());
                    objPunto1.setNombre(objJugador.getNombre());
                    objPunto1.setApellido(objJugador.getApellido());
                    objPunto1.setFechaInsc(objJugador.getFechaInscirpcion());
                    FILE *p;
                    p=fopen("punto1.dat", "ab");
                    if(p==NULL){return;}
                    fwrite(&objPunto1,sizeof(Punto1),1,p);
                    fclose(p);
                }
            }

        }

    }

}

//void agregarReg() {
//    FILE *p;
//    p = fopen("punto1.dat", "ab");
//    if(p==NULL) {
//        cout << "FILE ERROR FC AGREGAR";
//        exit(1);
//    }
//    Punto1 ob;
//    ob.Cargar();
//    fwrite(&ob, sizeof(Punto1), 1, p);
//    fclose(p);
//}

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
    funcionPunto1();
//    agregarReg();
    leerRegs();
    return 0;
}







