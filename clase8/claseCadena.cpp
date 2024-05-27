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
            if(palabras==nullptr) exit(-1);
            strcpy(palabras, cad);
        }
        void concatenar(const char *cad) {
            tam2= strlen(cad)+1;
            concatenacion = new char[tam + tam2];
            if(concatenacion==nullptr) exit(1);

        }
        Mostrar(){
            cout<<palabras<<endl;
        }
        ~Cadena(){delete[] palabras;}
};

int main(){
    Cadena obj("Hola mundo");
    obj.setPalabras("Yo tengo un sapo que se llama pepe");
    obj.Mostrar();
    return 0;
}
