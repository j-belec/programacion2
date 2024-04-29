

int main() {
    Articulo obj;
    //obj.Cargar(); //se hace antes de crear el puntero FILE //ya cree el registro ahora lo leo

    FILE *p;
    p= fopen("artiuculos-lunes", "ab");
    if(p==NULL) {
        cout << "Error de archivo" << endl;
        return -1;
    }
    //fwrite(&obj, sizeof(Articulo), 1, p); ya lo escribi ahora lo leo
    //fclose(p);

    fread(&obj, sizeof obj, 1, p);
    obj.Mostrar();    //aca me muestra el file q ya escribi antes
    fread(&obj, sizeof obj, 1, p);
    obj.Mostrar();     //asi muestro dos registros, si es q hay dos cargados, sino va a mostrar el unico q haya dos veces

    fclose(p);

    return 0;
}


//for(int i=0; i < 3; i++) {
//    fread(&obj, sizeof(Articulo), 1, p);
//    obj.Mostar();
//    cout << endl;
//}
//fclose(p);

cout << fread(&obj, sizeof(Articulo), 1, p); //esto nos da la cantidad de registros q leyo correctamente

while(fread(&obj, sizeof(Articulo), 1, p) == 1) {
    obj.Mostrar();
    cout << endl;
}
