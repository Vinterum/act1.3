#include <iostream>
#include <vector>
#include "Bitacora.h"
using namespace std;
int main() {
    int keyM_i, keyD_i, keyM_f, keyD_f;
    Bitacora prueba;
    prueba.cargaDatos("bitacora.txt");
    prueba.sort();
    
    cout << "Dame la fecha de inicio mm/dd: ";
    cin >> keyM_i;
    cin >> keyD_i;
    cout << "Dame la fecha final mm/dd: ";
    cin >> keyM_f;
    cin >> keyD_f;
    prueba.searchRange(keyM_i, keyD_i, keyM_f, keyD_f);
    return 0;
}

