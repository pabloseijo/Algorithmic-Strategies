//
// Created by Pablo Seijo on 6/12/23.
//

#ifndef PRACTICA6BACKTRACKING_FUNCIONESBACKTRACKING_H
#define PRACTICA6BACKTRACKING_FUNCIONESBACKTRACKING_H

/**
 * !!! IMPORTANTE !!!
 * Camiar el tamaño de la variable gobal n cuando se cambie de tamaño de matriz
 */
#define n 3 //tamaño de la matriz

/**
 * @brief Algoritmo de backtracking
 * @param matriz - matriz de n*n
 */
void backtracking(int matriz[n][n], int s[n]);

/**
 * @brief Función que devuelve el número de veces que se ha usado cada tarea, con el añadido de usada que mejora la eficiencia
 * @param B - matriz de n*n
 * @param s - vector solucion
 */
void backtrackingUsada (int B[n][n], int s[n]);

#endif //PRACTICA6BACKTRACKING_FUNCIONESBACKTRACKING_H
