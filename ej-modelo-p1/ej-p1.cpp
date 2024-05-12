#include <iostream>
#include <string.h>
#include "parcialm1.h"
using namespace std;

class Punto1 {
    private:
        char _codigoObra[5];
        char _direccion[30];
        int _provincia;
    public:
        void setCodigoObra(const char* codigoObra) {strcpy(_codigoObra, codigoObra);}
        void setDireccion(const char* direccion) {strcpy(_direccion, direccion);}
        void setProvincia(int provincia) {_provincia = provincia;}
        void Cargar();
        void Mostrar();
};
void Punto1::Cargar() {
    cout << "Ingrese codigo de Obra: ";
    cargarCadena(_codigoObra, 4);
    cout << "Ingrese direccion: ";
    cargarCadena(_direccion, 29);
    cout << "Ingrese numero de provincia: ";
    cin >> _provincia;
}
void Punto1::Mostrar() {
    cout << "Codigo de Obra: " << _codigoObra << endl;
    cout << "Direccion: " << _direccion << endl;
    cout << "Provincia: " << _provincia << endl;
}

void fcPunto1() {
    FILE *p;
    p = fopen("obras.dat", "rb");
    if(p==NULL) {
        cout << "FILE ERROR";
        exit(1);
    }

    FILE *q;
    q = fopen("punto1.dat", "wb");
    fclose(q);

    q = fopen("punto1.dat", "ab");
    if(q==NULL) {
        cout << "FILE ERROR";
        exit(1);
    }

    Obra ob;
    Punto1 p1;

    while(fread(&ob, sizeof(Obra), 1, p) == 1) {
        if(ob.getEstadoEjecucion() == 1) {
            p1.setCodigoObra(ob.getCodigoObra());
            p1.setDireccion(ob.getDireccion());
            p1.setProvincia(ob.getProvincia());
            fwrite(&p1, sizeof(Punto1), 1, q);
        }
    }

    fclose(q);
    fclose(p);
}

void fcPunto1B() {
    FILE *q;
    q = fopen("punto1.dat", "wb");
    fclose(q);
    q = fopen("punto1.dat", "ab");
    if(q==NULL) {
        cout << "FILE ERROR";
        exit(1);
    }
    ArchivoObras archOb("obras.dat");
    int totalReg = archOb.contarRegistros();
    Punto1 p1;
    Obra ob;
    for(int i=0;i<totalReg;i++) {
        ob = archOb.leerRegistro(i);
        if(ob.getEstadoEjecucion() == 3 && ob.getActivo()) {
            p1.setCodigoObra(ob.getCodigoObra());
            p1.setDireccion(ob.getDireccion());
            p1.setProvincia(ob.getProvincia());
            fwrite(&p1, sizeof(Punto1), 1, q);
        }
    }
    fclose(q);
}

//FUNCION PUNTO 2/////////////////////////////////////////////////////////////////////////////////////
void fcPunto2() {
    int provArr[50]{0};
    FILE *p;
    p = fopen("proveedores.dat", "rb");
    if(p==NULL) {
        cout << "FILE ERROR FCP2";
        exit(1);
    }
    Proveedor prov;
    while(fread(&prov, sizeof(Proveedor), 1, p)==1) {
        provArr[prov.getProvincia() - 1]++;
    }
    fclose(p);
    int minProv = 0;
    int nroProv;
    bool band = true;
    for(int i = 0; i < 50; i++) {
        if(provArr[i] != 0 && band) {
            minProv = provArr[i];
            nroProv = i + 1;
            band = false;
        } else if(provArr[i] != 0 && provArr[i] < minProv) {
            minProv = provArr[i];
            nroProv = i + 1;
        }
    }
    cout << "Provincia con menos proveedores es la numero: " << nroProv << endl;
}

//FUNCION PUNTO A1/////////////////////////////////////////////////////////////////////////////////////
//FUNCION PUNTO A2/////////////////////////////////////////////////////////////////////////////////////
void fcPuntoA2() {
    float provsArr[60]{0};

    ArchivoCompras archComp("compras.dat");
    int totalRegs = archComp.contarRegistros();
    Compra comp;
    for(int i=0;i<totalRegs;i++) {
        comp = archComp.leerRegistro(i);
        provsArr[comp.getNumeroproveedor() - 1] += comp.getImporte();
    }

    float maxImp = 0;
    int nroProv;

    for(int i=0;i<60;i++) {
        if(provsArr[i] > maxImp) {
            maxImp = provsArr[i];
            nroProv = i + 1;
        }
    }

    ArchivoProveedores archProv("proveedores.dat");
    int totalProvRegs = archProv.contarRegistros();
    Proveedor prov;
    for(int i=0;i<totalProvRegs;i++) {
        prov = archProv.leerRegistro(i);
        if(prov.getNumeroProveedor() == nroProv) {
            cout << "El nombre del proveedor que mayor importe haya obtenido entre todas las compras es: " << prov.getNombre() << endl;
            break;
        }
    }
}

//FUNCION PUNTO A3/////////////////////////////////////////////////////////////////////////////////////
void fcPuntoA3() {
    bool provsArr[60]{false};
    ArchivoCompras archCompras("compras.dat");
    int totalRegs = archCompras.contarRegistros();
    Compra comp;
    for(int i=0;i<totalRegs;i++) {
        comp = archCompras.leerRegistro(i);
//        cout << comp.getFechaCompra().getAnio() << endl;
        if(comp.getFechaCompra().getAnio() == 2022) {
            provsArr[comp.getNumeroproveedor() - 1] = true;
        }
    }
    for(int i=0;i<60;i++) {
        if(!provsArr[i]) {
            cout << "Nro prov sin ventas: " << i + 1 << endl;
        }
    }
}

//FUNCION PUNTO A4/////////////////////////////////////////////////////////////////////////////////////

//FUNCION PUNTO A5/////////////////////////////////////////////////////////////////////////////////////
void fcPuntoA5() {
    int provinciasArr[24]{0};
    ArchivoProveedores archProvs("proveedores.dat");
    int totalRegs = archProvs.contarRegistros();
    Proveedor prov;
    for(int i=0;i<totalRegs;i++) {
        prov = archProvs.leerRegistro(i);
        provinciasArr[prov.getProvincia() - 1]++;
    }
    cout << "Los numeros de provincias con mas de 22 proveedores son:" << endl;
    for(int i=0;i<24;i++) {
        if(provinciasArr[i] >= 22) cout << "Prov numero: " << i + 1 << endl;
    }
}

//MIS FUNCIONES/////////////////////////////////////////////////////////////////////////////////////
void agregarReg() {
//  el file ya tiene q existir porq uso append
    FILE *p;
    p = fopen("proveedores.dat", "ab");
    if(p==NULL) {
        cout << "FILE ERROR FC AGREGAR";
        exit(1);
    }
    Proveedor ob;
    ob.Cargar();
    fwrite(&ob, sizeof(Proveedor), 1, p);
    fclose(p);
}

void leerRegs() {
    FILE *p;
    p = fopen("compras.dat", "rb");
    if(p==NULL) {
        cout << "FILE ERROR FC LEER";
        exit(1);
    }
    Compra ob;
    while(fread(&ob, sizeof(Compra), 1, p)==1) {
        ob.Mostrar();
    }
    fclose(p);
}

int main() {
//    fcPunto1B();
//    agregarReg();
//    agregarReg();
//    leerRegs();
//    fcPunto2();
//    fcPuntoA2();
//    fcPuntoA3();
    fcPuntoA5();

    return 0;
}












