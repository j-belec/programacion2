#include <iostream>
#include <cstring>

using namespace std;

class Cadena{
    private:
        char *palabras;
        int tam;
    public:
        Cadena(const char *cad){
            tam=strlen(cad)+1;
            palabras=new char[tam];
            if(palabras==nullptr)exit(-1);
            strcpy(palabras, cad);
        }
        void setPalabras(const char *cad){
            delete[] palabras;
            tam=strlen(cad)+1;
            palabras=new char[tam];
            if(palabras==nullptr)exit(-1);
            strcpy(palabras, cad);
        }

        void concatenar(const char *cad) {
            char *cadAux = new char[tam];
            if(cadAux==nullptr)exit(-1);
            strcpy(cadAux, palabras);

            int tamCad = strlen(cad);
            int tamTotal = tam + tamCad;

//            cout << cadAux << endl;
//            cout << cad << endl;
//            cout << "tam total " << tamTotal << endl;
//            cout << "tam cad " << tamCad << endl;
//            cout << "tam aux " << tam << endl;
//            cout << palabras << endl;

            delete[]palabras;
//            cout << "desp: " << palabras << endl;

//            char *palabras;
            palabras = new char[tamTotal];
            if(palabras==nullptr){
                delete[] cadAux;
                exit(-2);
            }

            int pos1 = 0;
            int pos2 = 0;

            for(int i=0;i<tamTotal;i++) {
                if(pos1 < tam - 1) {
                    palabras[i] = cadAux[i];
                    pos1++;
                } else {
                    palabras[i] = cad[pos2];
                    pos2++;
                }
            }
        }

        const char *getPalabras(){return palabras;}
        ~Cadena(){
            delete[] palabras;
        }
};

int main(){
    Cadena cad("hola");
//    cout<<cad.getPalabras()<<endl;
    cad.concatenar(" mundo!");
    cout<<cad.getPalabras()<<endl;
    ///hola mundo!
    return 0;
}

//      void concatenar(const char *cad){
//            char *aux=new char[tam];
//            if(aux==nullptr){
//                delete[] palabras;
//                exit(-1);
//            }
//            strcpy(aux, palabras);
//            delete[] palabras;
//            int tamNuevo=tam+strlen(cad);
//            palabras = new char[tamNuevo];
//            if(palabras==nullptr){
//                delete[] aux;
//                exit(-2);
//            }
//            strcpy(palabras, aux);
//            delete[] aux;
//            int pos=0;
//            for(int i=tam-1; i<tamNuevo; i++){
//                palabras[i]=cad[pos];
//                pos++;
//            }
//        }
