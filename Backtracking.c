//
// Created by Pablo Seijo on 6/12/23.
//

#include <stdio.h>
#include <limits.h>
#include "Backtracking.h"

int bact = 0; //Variable global que indica la suma de los elementos de la solucion actual

/**
 * @brief Devuelve TRUE si hay más hermanos del nodo actual que todavía no han sido generados
 * @param nivel - nivel actual
 * @param s - vector solucion
 * @param pasosMasHermanos - puntero al número de pasos de masHermanos
 * @return 1 si hay mas hermanos, 0 si no los hay
 */
int masHermanos(int nivel,int s[], int *pasosMasHermanos){
    (*pasosMasHermanos)++;
    //Comprobamos si quedan asignaciones por probar
    return s[nivel] < n - 1;
}

/**
 * @brief genera el siguiente hermano, o el primero, para el nivel actual
 * @param nivel - nivel actual
 * @param s - vector solucion
 * @param B - matriz de n*n
 * @param pasosGenerar - puntero al número de pasos de generar
 */
void generar(int nivel, int s[n], int B[n][n], int *pasosGenerar) {
    (*pasosGenerar)++; //Incrementar el número de pasos de generar
    if(nivel < n) { // Si no hemos llegado al final del arbol
        s[nivel] = s[nivel] + 1; // Generamos el siguiente hermano
        if (s[nivel] == 0) { // Es la primera tarea que pruebo
            bact += B[nivel][s[nivel]]; // Sumamos el valor de la tarea
        } else { // No es la primera tarea
            // Sumamos el valor de la tarea y restamos el valor de la tarea anterior
            bact = bact + B[nivel][s[nivel]] - B[nivel][s[nivel] - 1];
        }
    }
}

/**
 * @brief genera el siguiente hermano, o el primero, para el nivel actual
 * @param nivel - nivel actual
 * @param s - vector solucion
 * @param B - matriz de n*n
 * @param usada - vector que indica si una tarea ha sido usada
 * @param pasosGenerar - puntero al número de pasos de generar
 */
void generarUsada(int nivel, int s[], int B[n][n], int usada[], int *pasosGenerar){
    (*pasosGenerar)++; //Incrementar el número de pasos de generar
    if(nivel < n) { // Si no hemos llegado al final del arbol
        if (nivel != -1) {
            usada[s[nivel]]--; // Restamos 1 al número de veces que se ha usado la tarea
        }
        s[nivel] = s[nivel] + 1; // Generamos el siguiente hermano
        usada[s[nivel]]++; // Sumamos 1 al número de veces que se ha usado la tarea
        if (s[nivel] == 0) { // Es la primera tarea que pruebo
            bact += B[nivel][s[nivel]]; // Sumamos el valor de la tarea
        } else { // No es la primera tarea
            // Sumamos el valor de la tarea y restamos el valor de la tarea anterior
            bact = bact + B[nivel][s[nivel]] - B[nivel][s[nivel] - 1];
        }
    }
}

/**
 * @brief comprueba si a partir de (s[1],…,s[nivel]) se puede alcanzar una solución válida
 * @param nivel - nivel actual
 * @param s - vector solucion
 * @param pasosCriterio - puntero al número de pasos de criterio
 * @return 1 si es prometedor (es decir, si se puede alcanzar una solucion valida), 0 si no lo es
 */
int criterio(int nivel, int s[], int *pasosCriterio){
    int contador = 0; // Contador de pasos
    for (int i = 0; i < nivel; i++) { // Comprobamos que la tarea no se haya usado antes
        contador++; // Incrementar el contador de pasos
        if (s[nivel] == s[i]){
            *pasosCriterio += contador; //Incrementar el número de pasos de criterio
            return 0; // Si se ha usado antes, no es prometedor
        }
    }
    *pasosCriterio += contador; //Incrementar el número de pasos de criterio
    return 1; // Si no se ha usado antes, es prometedor
}

/**
 * @brief comprueba si a partir de (s[1],…,s[nivel]) se puede alcanzar una solución válida
 * @param nivel - nivel actual
 * @param s - vector solucion
 * @param usada - vector que indica si una tarea ha sido usada
 * @param pasosCriterio - puntero al número de pasos de criterio
 * @return 1 si es prometedor (es decir, si se puede alcanzar una solucion valida), 0 si no lo es
 */
int criterioUsada(int nivel, int s[], int usada[], int *pasosCriterio) {
    (*pasosCriterio)++; //Incrementar el número de pasos de criterio
    return usada[s[nivel]] == 1;
}

/**
 * @brief Comprueba si la tupla (s[1],…,s[nivel]) es una solución válida para el problema
 * @param nivel - nivel actual
 * @param s - vector solucion
 * @param pasosSolucion - puntero al número de pasos de solucion
 * @param pasosCriterio - puntero al número de pasos de criterio
 * @return 1 si es solucion, 0 si no lo es
 */
int solucion(int nivel, int s[], int *pasosSolucion, int *pasosCriterio) {
    (*pasosSolucion)++; //Incrementar el número de pasos de solucion
    //Si hemos llegado al ultimo nivel y la asignacion es valida, es solucion
    return nivel == n - 1 && criterio(nivel, s, pasosCriterio);
}

/**
 * @brief Comprueba si la tupla (s[1],…,s[nivel]) es una solución válida para el problema
 * @param nivel - nivel actual
 * @param s - vector solucion
 * @param usada - vector que indica si una tarea ha sido usada
 * @param pasosSolucion - puntero al número de pasos de solucion
 * @param pasosCriterio - puntero al número de pasos de criterio
 * @return 1 si es solucion, 0 si no lo es
 */
int solucionUsada(int nivel, int s[], int usada[], int *pasosSolucion, int *pasosCriterio) {
    (*pasosSolucion)++; //Incrementar el número de pasos de solucion
    //Si hemos llegado al ultimo nivel y la asignacion es valida, es solucion
    return nivel == n - 1 && criterioUsada(nivel, s, usada, pasosCriterio);
}

/**
 * @brief retrocede un nivel del árbol de soluciones. Disminuye en 1 el valor de nivel, y posiblemente tendrá que
 *          actualizar la solución actual, quitando los elementos retrocedidos.
 * @param nivel - puntero al nivel actual
 * @param s - vector solucion
 * @param B - matriz de n*n
 * @param pasosRetroceder - puntero al número de pasos de retroceder
 */
void retroceder(int *nivel, int s[], int B[n][n], int *pasosRetroceder) {
    (*pasosRetroceder)++; //Incrementar el número de pasos de retroceder
    // Si no estamos en el nivel inicial, retrocedemos
    bact -= B[*nivel][s[*nivel]]; // Restamos el valor de la tarea
    s[*nivel] = -1; // Valor inicial
    (*nivel) = (*nivel) - 1; // Retrocedemos un nivel1º
}

/**
 * @brief retrocede un nivel del árbol de soluciones. Disminuye en 1 el valor de nivel, y posiblemente tendrá que
 * @param nivel - puntero al nivel actual
 * @param s - vector solucion
 * @param usada - vector que indica si una tarea ha sido usada
 * @param B - matriz de n*n
 * @param pasosRetroceder - puntero al número de pasos de retroceder
 */
void retrocederUsada(int *nivel, int s[], int usada[], int B[n][n], int *pasosRetroceder) {
    (*pasosRetroceder)++; //Incrementar el número de pasos de retroceder
    // Si no estamos en el nivel inicial, retrocedemos
    bact -= B[*nivel][s[*nivel]]; // Restamos el valor de la tarea
    usada[s[*nivel]]--; // Restamos 1 al número de veces que se ha usado la tarea
    s[*nivel] = -1; // Valor inicial
    (*nivel) = (*nivel) - 1; // Retrocedemos un nivel1º
}

/**
 * @brief Algoritmo de backtracking
 * @param B - matriz de n*n
 */
void backtracking(int B[n][n], int s[n]){

    /** DECLARACION DE VARIABLES **/

    int nivel = 0; // Nivel actual
    int voa = INT_MIN; // Valor óptimo actual, inicializado al mínimo posible
    int soa[n]; // Solución óptima actual
    int nodosVisitados = 1; // Número de nodos visitados
    int pasosGenerar = 0; // Número de pasos de generar
    int pasosCriterio = 0; // Número de pasos de criterio
    int pasosSolucion = 0; // Número de pasos de solucion
    int pasosRetroceder = 0; // Número de pasos de retroceder
    int pasosMasHermanos = 0; // Número de pasos de masHermanos

    /** INICIALIZACION DE VARIABLES **/

    bact = 0; // Reiniciar el valor de la solución actual

    // Inicializar soa a -1
    for(int i = 0; i < n; i++) {
        soa[i] = -1;
    }

    /** ALGORITMO **/

    while(nivel != -1){
        generar(nivel, s, B, &pasosGenerar); // Generar el siguiente hermano
        if((solucion(nivel, s, &pasosSolucion, &pasosCriterio)) && bact > voa){ // Verifica si es una solución mejor
            voa = bact; // Actualizar el valor óptimo
            // Copiar s a soa
            for(int i = 0; i < n; i++){
                soa[i] = s[i];
            }
        }
        if(criterio(nivel, s, &pasosCriterio)) { // Comprobar si es prometedor
            nodosVisitados++; // Incrementar el número de nodos visitados
            if(nivel < n - 1){ // Si no hemos llegado al final del árbol
                nivel++; // Avanzar un nivel
            }
        }

        while(!masHermanos(nivel, s, &pasosMasHermanos) && nivel >= 0){ // Mientras no haya más hermanos y no estemos en el nivel inicial
            retroceder(&nivel, s, B, &pasosRetroceder); // Retroceder un nivel
        }
    }
    // Imprimir la solución óptima
    printf("SOLUCION\n\tMejor solución encontrada: { ");
    for(int i = 0; i < n; i++){
        printf("%d ", soa[i] + 1); // Ajuste para imprimir en base-1
    }
    printf("}\n\tvalor: %d\n", voa);
    printf("\tNodos visitados: %d\n", nodosVisitados);
    printf("\tPasos criterio: %d\n", pasosCriterio);
    printf("\tPasos de generar: %d\n", pasosGenerar);
    printf("\tPasos de solucion: %d\n", pasosSolucion);
    printf("\tPasos de masHermanos: %d\n", pasosMasHermanos);
    printf("\tPasos de retroceder: %d\n", pasosRetroceder);
}

/**
 * @brief Función que devuelve el número de veces que se ha usado cada tarea, con el añadido de usada que mejora la eficiencia
 * @param B - matriz de n*n
 * @param s - vector solucion
 */
void backtrackingUsada (int B[n][n], int s[n]){

    /** DECLARACION DE VARIABLES **/

    int nivel = 0; // Nivel actual
    int nodosVisitados = 1; // Número de nodos visitados, se inicializa a 1 porque el nodo raíz ya se ha visitado
    int pasosGenerar = 0; // Número de pasos de generar
    int pasosCriterio = 0; // Número de pasos de criterio
    int pasosSolucion = 0; // Número de pasos de solucion
    int pasosRetroceder = 0; // Número de pasos de retroceder
    int pasosMasHermanos = 0; // Número de pasos de masHermanos
    int voaUsada = INT_MIN; // Valor óptimo actual, inicializado al mínimo posible
    int soaAux[n]; // Vector auxiliar para guardar la solución óptima
    int usada[n]; // Vector que indica si una tarea ha sido usada
    //Debe haber algun problema de memoria en el programa y esto lo arregla
    int arregloMemoria[n]; // Por alguna razon esto no hace nada pero si lo saco me da SIGSEGV

    /** INICIALIZACION DE VARIABLES **/

    bact = 0; // Reiniciar el valor de la solución actual

    // Inicializar soa a -1
    for(int i = 0; i < n; i++) {
        soaAux[i] = -1;
    }

    // Inicializar usada a 0
    for(int i = 0; i < n; i++) {
        usada[i] = 0;
    }

    /** ALGORITMO **/

    while(nivel != -1){
        generarUsada(nivel, s, B, usada, &pasosGenerar); // Generar el siguiente hermano
        if(solucionUsada(nivel, s, usada, &pasosSolucion, &pasosCriterio) && bact > voaUsada){ // Verifica si es una solución mejor
            voaUsada = bact; // Actualizar el valor óptimo
            // Copiar s a soa
            for(int i = 0; i < n; i++){
                soaAux[i] = s[i];
            }
        }
        if(criterioUsada(nivel, s, usada, &pasosCriterio)) { // Comprobar si es prometedor
            nodosVisitados++; // Incrementar el número de nodos visitados
            if(nivel < n - 1){ // Si no hemos llegado al final del árbol
                nivel++; // Avanzar un nivel
            }
        }

        while(!masHermanos(nivel, s, &pasosMasHermanos) && nivel >= 0){
            retrocederUsada(&nivel, s, usada, B, &pasosRetroceder);
        }

    }
    // Imprimir la solución óptima
    printf("\nSOLUCION CON VECTOR USADA:\n\tMejor solución encontrada: { ");
    for(int i = 0; i < n; i++){
        printf("%d ", soaAux[i] + 1); // Ajuste para imprimir en base-1
    }
    printf("}\n\tvalor: %d\n", voaUsada);
    printf("\tNodos visitados: %d\n", nodosVisitados);
    printf("\tPasos criterio: %d\n", pasosCriterio);
    printf("\tPasos de generar: %d\n", pasosGenerar);
    printf("\tPasos de solucion: %d\n", pasosSolucion);
    printf("\tPasos de masHermanos: %d\n", pasosMasHermanos);
    printf("\tPasos de retroceder: %d\n", pasosRetroceder);
}

