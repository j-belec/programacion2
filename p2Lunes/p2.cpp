#include <iostream>
#include <cstring>
#include <cstdlib>
#include "parcial2.h"
using namespace std;

class Punto1 {
private:
    int _codigoMaterial;
    int _tipo;
    float _importeTotal;
public:
    void setCodigoMaterial(int codigoMaterial) {_codigoMaterial = codigoMaterial;}
    void setTipo(int tipo) {_tipo = tipo;}
    void setImporteTotal(float importeTotal) {_importeTotal = importeTotal;}
    void Mostrar() {
        cout << "cod mat: " << _codigoMaterial << endl;
        cout << "tipo: " << _tipo << endl;
        cout << "imp: " << _importeTotal << endl;
        cout << endl;
    }
};

void fcPunto1() {
    ArchivoMateriales archMateriales("materiales.dat");
    int totalRegsMateriales = archMateriales.contarRegistros();
    Material objMaterial;

    ArchivoCompras archCompras("compras.dat");
    int totalRegsCompras = archCompras.contarRegistros();
    Compra objCompra;

    FILE *p;
    p=fopen("punto1.dat", "ab");
    if(p==NULL) {
        cout << "error";
        return;
    }

    for(int i=0;i<totalRegsMateriales;i++) {
        objMaterial = archMateriales.leerRegistro(i);
        float impTotal = 0;

        for(int i=0;i<totalRegsCompras;i++) {
            objCompra = archCompras.leerRegistro(i);
            if(objCompra.getFechaCompra().getAnio() == 2024 && objMaterial.getCodigoMaterial() == objCompra.getCodigoMaterial()) {
                impTotal += objCompra.getImporte();
            }
        }

        Punto1 objPunto1;
        objPunto1.setCodigoMaterial(objMaterial.getCodigoMaterial());
        objPunto1.setTipo(objMaterial.getTipo());
        objPunto1.setImporteTotal(impTotal);

        fwrite(&objPunto1,sizeof(Punto1),1,p);
    }
        fclose(p);
}

void fcPunto2() {
    ArchivoObras archObras("obras.dat");
    int totalRegsObras = archObras.contarRegistros();
    Obra objObra;

    int provincias[24]{0};

    for(int i=0;i<totalRegsObras;i++) {
        objObra = archObras.leerRegistro(i);
        provincias[objObra.getProvincia()-1]++;
    }

    for(int i=0;i<24;i++) {
        cout << "En la prov numero " << i + 1 << " hay " << provincias[i] << " obras" << endl;
    }
}

void fcPunto3() {
    ArchivoMateriales archMateriales("materiales.dat");
    int totalRegsMateriales = archMateriales.contarRegistros();
    Material objMaterial;

    Material *vec;
    vec = new Material[totalRegsMateriales];
    if(vec==NULL) return;

    for(int i=0;i<totalRegsMateriales;i++) {
        objMaterial = archMateriales.leerRegistro(i);
        vec[i] = objMaterial;
    }

    int tipo;
    cout << "Ingresa un tipo de material: ";
    cin >> tipo;

    for(int i=0;i<totalRegsMateriales;i++) {
        if(vec[i].getTipo() == tipo) {
            vec[i].Mostrar();
        }
    }

    delete []vec;
}

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

int main() {
//    agregarReg();
//    agregarReg();
//    agregarReg();
//    agregarReg();
//    leerRegs();
//    fcPunto1();
//    fcPunto2();
    fcPunto3();
    return 0;
}
