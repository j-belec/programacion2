#include <iostream>
#include <cstdlib>
#include <cstring>
#include "p2.h"
using namespace std;

//////////////////////////////////////////////////
//////////////PARTE 1/////////////////////////////
//////////////////////////////////////////////////
bool Jugador::operator==(Deporte &objDeporte) {
    if(idDeporte == objDeporte.getIDdeporte()) {
        return true;
    }
    return false;
}

class PuntoA {
private:
    int _idEquipo;
    char _nombre[30];
    int _categoria;
public:
    //setters
    void setIdEquipo(int idEquipo) {_idEquipo = idEquipo;}
    void setNombre(const char* nombre) {strcpy(_nombre, nombre);}
    void setCategoria(int categoria) {_categoria = categoria;}
    void Mostrar() {
        cout << _idEquipo << endl;
        cout << _nombre << endl;
        cout << _categoria << endl;
    }
};

int fcCategoriaDeporte(int idDeporte) {
    ArchivoDeportes archDeportes("deportes.dat");
    int cantTotalDeportes = archDeportes.contarRegistros();
    Deporte objDeporte;
    int idCategoria;
    for(int i=0;i<cantTotalDeportes;i++) {
        objDeporte = archDeportes.leerRegistro(i);
        if(objDeporte.getIDdeporte() == idDeporte) {
            idCategoria = objDeporte.getIDcategoria();
            return idCategoria;
        }
    }
    return -1;
}

void fcPuntoA() {
    ArchivoEquipos archEquipos("equipos.dat");
    int cantTotalEquipos = archEquipos.contarRegistros();
    Equipo objEquipo;
    for(int i=0;i<cantTotalEquipos;i++) {
        PuntoA objPuntoA;
        objEquipo = archEquipos.leerRegistro(i);

        int contadorJugadores = 0;

        ArchivoJugadores archJugadores("jugadores.dat");
        int cantTotalJugadores = archJugadores.contarRegistros();
        Jugador objJugador;

        int idCategoria;
        for(int i=0;i<cantTotalJugadores;i++) {
            objJugador = archJugadores.leerRegistro(i);

            if(objEquipo.getIDequipo() == objJugador.getIDequipo()) {
                contadorJugadores++;
                idCategoria = fcCategoriaDeporte(objJugador.getIDdeporte());
            }

        }

        if(contadorJugadores >= 2) {
            objPuntoA.setIdEquipo(objEquipo.getIDequipo());
            objPuntoA.setNombre(objEquipo.getNombre());
            objPuntoA.setCategoria(idCategoria);
            FILE *p;
            p=fopen("puntoA.dat", "ab");
            if(p==NULL) exit(1);
            fwrite(&objPuntoA,sizeof(PuntoA),1,p);
            fclose(p);
        }
    }
}

PuntoA leerRegPuntoA(int pos){
        PuntoA reg;
        FILE *p;
        p=fopen("puntoA.dat", "rb");
        if(p==NULL) exit(1);
        fseek(p, sizeof reg*pos,0);
        fread(&reg, sizeof reg,1, p);
        fclose(p);
        return reg;
}

void fcPuntoB() {
    FILE *p;
    p=fopen("puntoA.dat","rb");
    if(p==NULL) exit(1);
    fseek(p,0,2);
    int bytes = ftell(p);
    int tam = bytes / sizeof(PuntoA);

    if(tam==0) {
        cout << "No hay registros";
        return;
    }

    PuntoA *vec;
    vec = new PuntoA[tam];
    if(vec==NULL) return;
    PuntoA obj;
    for(int i=0;i<tam;i++) {
        vec[i] = leerRegPuntoA(i);
    }
    for(int i=0;i<tam;i++) {
        vec[i].Mostrar();
    }
}

//////////////////////////////////////////////////
//////////////PARTE 2/////////////////////////////
//////////////////////////////////////////////////
void fcPunto2A() {
    ArchivoDeportes archDeportes("deportes.dat");
    int totalRegsDeportes = archDeportes.contarRegistros();
    Deporte objDeporte;

    ArchivoJugadores archJugadores("jugadores.dat");
    int totalRegsJugadores = archJugadores.contarRegistros();
    Jugador objJugador;

    for(int i=0;i<totalRegsDeportes;i++) {
        objDeporte = archDeportes.leerRegistro(i);

        bool claustro1 = false;
        bool claustro2 = false;
        bool claustro3 = false;
        bool claustro4 = false;

        for(int i=0;i<totalRegsJugadores;i++) {
            objJugador = archJugadores.leerRegistro(i);
            if(objJugador.getIDdeporte() == objDeporte.getIDdeporte()) {
                if(objJugador.getClaustro() == 1) claustro1 = true;
                if(objJugador.getClaustro() == 2) claustro2 = true;
                if(objJugador.getClaustro() == 3) claustro3 = true;
                if(objJugador.getClaustro() == 4) claustro4 = true;
            }
        }

        if(claustro1 && claustro2 && claustro3 && claustro4) {
            FILE *p;
            p=fopen("punto2A.dat", "ab");
            if(p==NULL) return;
            fwrite(&objDeporte,sizeof(Deporte),1,p);
            fclose(p);
        }
    }
}

void fcPunto2B() {
    ArchivoEquipos archEquipo("equipos.dat");
    int totalRegsEquipos = archEquipo.contarRegistros();
    Equipo objEquipo;

    int contadorEqsNivelInicial = 0;

    for(int i=0;i<totalRegsEquipos;i++) {
        objEquipo = archEquipo.leerRegistro(i);
        if(objEquipo.getNivel() == 1) {
            contadorEqsNivelInicial++;
        }
    }

//    FILE *p;
//    p=fopen("equipos.dat", "rb");
//    if(p==NULL) return;
//    fseek(p,0,2);
//    int bytes = ftell(p);
//    int tam = bytes / sizeof(Equipo);

    int tam = contadorEqsNivelInicial;

    Equipo *vec;
    vec = new Equipo[tam];
    if(vec==NULL) return;
    int index = 0;

    for(int i=0;i<totalRegsEquipos;i++) {
        objEquipo = archEquipo.leerRegistro(i);
        if(objEquipo.getNivel() == 1) {
            vec[index] = objEquipo;
            index++;
        }
    }

    for(int i=0;i<tam;i++) {
        vec[i].Mostrar();
    }
}

//bool Jugador::operator==(int idClaustro) {
//    if(getClaustro() == idClaustro) {
//        return true;
//    }
//    return false;
//}

//////////////////////////////////////////////////
//////////////PARTE 3/////////////////////////////
//////////////////////////////////////////////////
class Parte3 {
private:
    int _dni;
    char _nombre[30];
    char _apellido[30];
    int _claustro;
    char _nombreEquipo[30];
public:
    void setDni(int dni) {_dni = dni;}
    void setNombre(const char* nombre) {strcpy(_nombre, nombre);}
    void setApellido(const char* apellido) {strcpy(_apellido, apellido);}
    void setClaustro(int claustro) {_claustro = claustro;}
    void setNombreEquipo(const char* nombreEquipo) {strcpy(_nombreEquipo, nombreEquipo);}
};

void fcPunto3A() {
    ArchivoJugadores archJugadores("jugadores.dat");
    int totalRegsJugadores = archJugadores.contarRegistros();
    Jugador objJugador;

    ArchivoDeportes archDeportes("deportes.dat");
    int totalRegsDeportes = archDeportes.contarRegistros();
    Deporte objDeporte;

    FILE *p;
    p=fopen("parte3.dat", "ab");
    if(p==NULL) return;

    for(int i=0;i<totalRegsJugadores;i++) {
        objJugador = archJugadores.leerRegistro(i);

        if(objJugador.getMatricula() > 10000 && objJugador.getFechaInscirpcion().getAnio() == 2024) {
            Parte3 objParte3;
            for(int i=0;i<totalRegsDeportes;i++) {
                objDeporte = archDeportes.leerRegistro(i);
                if(objDeporte.getIDdeporte() == objJugador.getIDdeporte()) {
                    objParte3.setNombreEquipo(objDeporte.getNombre());
                }
            }
            objParte3.setDni(objJugador.getDNI());
            objParte3.setNombre(objJugador.getNombre());
            objParte3.setApellido(objJugador.getApellido());
            objParte3.setClaustro(objJugador.getClaustro());

            fwrite(&objParte3,sizeof(Parte3),1,p);
        }
    }

    fclose(p);
}

void fcPunto3B() {
    int idEquipo;
    cout << "Ingrese un id de equipo: ";
    cin >> idEquipo;

    ArchivoJugadores archJugadores("jugadores.dat");
    int totalRegsJugadores = archJugadores.contarRegistros();
    Jugador objJugador;

    int contador = 0;

    for(int i=0;i<totalRegsJugadores;i++) {
        objJugador = archJugadores.leerRegistro(i);
        if(objJugador.getIDequipo() == idEquipo) {
            contador++;
        }
    }

    Jugador *vec;
    vec = new Jugador[contador];
    if(vec==NULL) return;
    int index = 0;

    for(int i=0;i<totalRegsJugadores;i++) {
        objJugador = archJugadores.leerRegistro(i);
        if(objJugador.getIDequipo() == idEquipo) {
            vec[index] = objJugador;
            index++;
        }
    }

    for(int i=0;i<contador;i++) {
        vec[i].Mostrar();
    }

    delete []vec;
}

bool Jugador::operator>(int anio) {
    if(getFechaInscirpcion().getAnio() > anio) {
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
    p = fopen("jugadores.dat", "rb");
    if(p==NULL) {
        cout << "FILE ERROR FC LEER";
        exit(1);
    }
    Jugador ob;
    while(fread(&ob, sizeof(Jugador), 1, p)==1) {
        ob.Mostrar();
    }
    fclose(p);
}

int main() {
//    agregarReg();
    leerRegs();

//    fcPuntoA();
//    fcPuntoB();
//    Jugador jug;
//    Deporte dep;
//    jug.Cargar();
//    dep.Cargar();
//    if(jug==dep) {
//        cout << "iguales";
//    } else {
//        cout << "dist";
//    }
//    fcPunto3B();
//    Jugador objJugador;
//    objJugador.Cargar();
//    objJugador.Mostrar();
//
//    if(objJugador>2022) {
//        cout << "asdasd";
//    } else {
//        cout << "asdasdsssssss";
//    }

    return 0;
}





