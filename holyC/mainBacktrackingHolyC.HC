#include "Backtracking.HC"

I64 Main() {
  
    I64 matriz[n][n] = {
        {11, 17, 8},
        {9,  7,  6},
        {13, 15, 16}
    };

    I64 s[] = {-1, -1, -1}; // Vector solución con inicialización a -1
    
    // Si tienes otra matriz y un vector s diferente para probar, comenta el bloque anterior y descomenta este.
    /*
    I64 matriz[n][n] = {
        {11, 17, 8, 16, 20, 14},
        {9, 7, 6, 12, 15, 18},
        {13, 15, 16, 12, 16, 18},
        {21, 24, 28, 17, 26, 20},
        {10, 14, 12, 11, 15, 13},
        {12, 20, 19, 13, 22, 17}
    };

    I64 s[] = {-1, -1, -1, -1, -1, -1}; // Vector solución con inicialización a -1
    */

    backtracking(matriz, s);
    backtrackingUsada(matriz, s);
}

