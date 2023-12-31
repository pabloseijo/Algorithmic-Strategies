#include "Backtracking.h"

int main() {

    /**
     * !!! IMPORTANTE !!!
     * Cuando se descomente el código de abajo, comentar el código de abajo de la otra matriz
     * y viceversa. Tambien hay que cambiar el tamaño de la matriz en funcionesBacktracking.h
     */

    /**
     * s[i]= 0 -> el número i-ésimo no se utiliza
     * s[1]= 1 -> el número i-ésimo sí se utiliza
     * s[i]= -1 -> valor de inicialización (número i-ésimo no estudiado)
     */

    
    int matriz[n][n] = {
            {11, 17, 8},
            {9,  7,  6},
            {13, 15, 16}
    };

    int s[] = {-1,-1,-1}; //Vector solucion con inicializacion a -1
    
        /*
    int matriz [n][n] = {
            {11,17,8,16,20,14},
            {9,7,6,12,15,18},
            {13,15,16,12,16,18},
            {21,24,28,17,26,20},
            {10,14,12,11,15,13},
            {12,20,19,13,22,17}
    };

    int s[] = {-1,-1,-1,-1,-1,-1}; //Vector solucion con inicializacion a -1
        */

    backtracking(matriz, s);
    backtrackingUsada(matriz, s);
}
