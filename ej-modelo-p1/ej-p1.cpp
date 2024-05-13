#include <iostream>
#include <cstring>
#include "parcialm1.h"
using namespace std;

//class ArchivoGenerico
//{
//private:
//    char _nombre[30];
//
//public:
//    ArchivoGenerico(const char *nombre = "data.dat")
//    {
//        setNombre(nombre);
//    }
//    const char *getNombre() { return _nombre; };
//	void setNombre(const char *nombre)
//	{
//		strcpy(_nombre, nombre);
//	};
//    T leerRegistro(int pos){
//        T obj;
//        // obj.setNumero(-1);
//        FILE *p;
//        p = fopen("viajes.dat", "rb");
//        if (p == nullptr)
//        {
//            cout << "ERROR DE ARCHIVO" << endl;
//            // obj.setNumero(-2);
//            return obj;
//        }
//        fseek(p, pos * sizeof obj, 0);
//        fread(&obj, sizeof obj, 1, p);
//        fclose(p);
//        return obj;
//    };
//    void grabarRegistro(T obj)
//    {
//        FILE *p;
//        p = fopen(this->getNombre(), "ab");
//        if (p == nullptr)
//        {
//            cout << "ERROR DE ARCHIVO" << endl;
//            return;
//        }
//        int cantGrabados = fwrite(&obj, sizeof obj, 1, p);
//        cout << cantGrabados << endl;
//        fclose(p);
//    };
//
//    int contarRegistros()
//    {
//        FILE *p;
//        T obj;
//
//        p = fopen(this->getNombre(), "rb");
//        if (p == nullptr)
//        {
//            cout << "ERROR DE ARCHIVO" << endl;
//            return -2;
//        }
//
//        fseek(p, 0, SEEK_END);
//        int tamArchivo = ftell(p);
//        int tamT = sizeof obj;
//
//        cout << tamArchivo << ", " << tamT << endl;
//
//        fclose(p);
//
//        return tamArchivo / tamT;
//    };
//
//    // modificarRegistro(Empresa obj, int pos){};
//    void listarRegistros()
//    {
//        T obj;
//        int cant = contarRegistros();
//
//        cout << "Listando " << cant << " registros..." << endl;
//
//        for (int i = 0; i < cant; i++)
//        {
//            obj = leerRegistro(i);
//            obj.Mostrar();
//        }
//    };
//
//    int buscarRegistro(int numRegistro)
//    {
//        T obj;
//        int cant = contarRegistros();
//
//        for (int i = 0; i < cant; i++)
//        {
//            obj = leerRegistro(i);
//
//            if (obj.getNumero() == numRegistro)
//            {
//                return i;
//            }
//        }
//        return -1;
//    };
//};

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
    ArchivoObras archObras("obras.dat");
    int totalRegsObras = archObras.contarRegistros();
    Obra objObra;
    for(int i=0;i<totalRegsObras;i++) {
        objObra = archObras.leerRegistro(i);
        Punto1 objP1;
        if(objObra.getEstadoEjecucion()==3 && objObra.getActivo()) {
            objP1.setCodigoObra(objObra.getCodigoObra());
            objP1.setDireccion(objObra.getDireccion());
            objP1.setProvincia(objObra.getProvincia());
            FILE *p;
            p=fopen("punto1.dat", "ab");
            if(p==NULL){return;}
            fwrite(&objP1,sizeof(objP1),1,p);
            fclose(p);
        }
    }
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
int cantComprasPorMaterial(int codMaterial) {
    int cantCompras = 0;
     ArchivoCompras archCompras("compras.dat");
     int totalCompras = archCompras.contarRegistros();
     Compra comp;
     for(int i=0;i<totalCompras;i++) {
         comp = archCompras.leerRegistro(i);
         if(comp.getCodigoMaterial() == codMaterial && comp.getActivo()) {
             cantCompras++;
         }
     }
    return cantCompras;
}

void fcPuntoA1() {
    ArchivoMateriales archMat("materiales.dat");
    int totalMateriales = archMat.contarRegistros();
    Material mat;
    for(int i=0;i<totalMateriales;i++) {
        mat = archMat.leerRegistro(i);
        int codMaterial = mat.getCodigoMaterial();
        int cantCompras = cantComprasPorMaterial(codMaterial);
        cout << "El material con codigo " << codMaterial << " tiene " << cantCompras << " compras" << endl;
    }
}

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
int fcAux( int codMaterial) {
   ArchivoCompras archCompras("compras.dat");
        int totalRegsCompras = archCompras.contarRegistros();
        Compra objCompra;
        int cantCompras = 0;
        for(int i=0;i<totalRegsCompras;i++) {
            objCompra = archCompras.leerRegistro(i);
            if(objCompra.getCodigoMaterial() == codMaterial) {
                cantCompras++;
            }
        }
        return cantCompras;
}

void fcPuntoA1B() {
    ArchivoMateriales archMateriales("materiales.dat");
    int totalRegsMateriales = archMateriales.contarRegistros();
    Material objMaterial;
    for(int i=0;i<totalRegsMateriales;i++) {
        objMaterial = archMateriales.leerRegistro(i);
        int codMaterial = objMaterial.getCodigoMaterial();
        int cantCompras = fcAux(codMaterial);
        cout << "Para el material con codigo " << objMaterial.getCodigoMaterial() << " se compro " << cantCompras << " cantidad." << endl;
    }

}

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
//FUNCION PUNTO A6/////////////////////////////////////////////////////////////////////////////////////
void fcPuntoA6() {
    ArchivoCompras archComp("compras.dat");
    int totalRegs = archComp.contarRegistros();
    Compra comp;
    for(int i=0;i<totalRegs;i++) {
        comp = archComp.leerRegistro(i);
        if(comp.getFechaCompra().getAnio() == 2020) {
            comp.setActivo(false);
            FILE *p;
            p=fopen("compras.dat", "rb+");
            fseek(p, sizeof(Compra)*i, 0);
            fwrite(&comp, sizeof(Compra), 1, p);
            fclose(p);
        }
    }
}

void fcPuntoA6B() {
    FILE *p;
    p=fopen("compras.dat", "rb+");
    if(p==NULL){return;}
    Compra objCompra;
    int contador = 0;
    while(fread(&objCompra,sizeof(Compra),1,p)==1) {
        if(objCompra.getFechaCompra().getAnio()==2020) {
            objCompra.setActivo(false);
            fseek(p,sizeof(Compra)*contador,0);
            fwrite(&objCompra,sizeof(Compra),1,p);
            fseek(p, 0, SEEK_CUR);
        }
        contador++;
    }
    fclose(p);
}

//FUNCION PUNTO A7/////////////////////////////////////////////////////////////////////////////////////
void fcPuntoA7() {
    ArchivoMateriales archMateriales("materiales.dat");
    int totalRegsMateriales = archMateriales.contarRegistros();
    Material objMaterial;
    for(int i=0;i<totalRegsMateriales;i++) {
        objMaterial = archMateriales.leerRegistro(i);
        if(strcmp(objMaterial.getNombre(),"abertura") == 0) {
            float nuevoPU = objMaterial.getPU() + objMaterial.getPU() * 0.1;
            objMaterial.setPU(nuevoPU);
            FILE *p;
            p=fopen("materiales.dat", "rb+");
            fseek(p,sizeof(Material)*i,0);
            fwrite(&objMaterial,sizeof(Material),1,p);
            fclose(p);
        }
    }
}

//MIS FUNCIONES/////////////////////////////////////////////////////////////////////////////////////
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
//    fcPuntoA7();
//    leerRegs();
//    agregarReg();
//    fcPunto1();
//    fcPunto2();
//    fcPuntoA1();
    fcPuntoA1B();
//    fcPuntoA3();
//    fcPuntoA5();
//    fcPuntoA6();
    return 0;
}












