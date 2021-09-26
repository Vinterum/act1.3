#include "Bitacora.h"
using namespace std;
int main() {
    //Ingresar fecha de inicio aqui
    int keyMes_i = 8;
    int keyDia_i = 1;
    //Ingresar fecha final aqui
    int keyMes_f = 8;
    int keyDia_f = 1;

    Bitacora vec;//Crea el vector donde se guardaran los datos
    vec.cargaDatos("bitacora.txt"); //Llena el vector
    vec.sort(); //Ordena
    vec.searchRange(keyMes_i, keyDia_i, keyMes_f, keyDia_f); //Busqueda de consulta
    vec.guardar(keyMes_i, keyDia_i, keyMes_f, keyDia_f); //Guarda consulta a .txt
    return 0;
}

