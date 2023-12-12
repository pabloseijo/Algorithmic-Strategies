//
// Created by Pablo Seijo on 28/11/23.
//

#include <printf.h>
#include "funcionesRamificacion.h"
#include "lista.h"

int Nodos = 1; // Número de nodos vivos

/** FUNCIONES PRIVADAS **/

/* PARA CI Y CS PRECISAS */

/**
 * @brief Función que calcula el máximo beneficio de una tarea
 * @param fila - fila de la matriz
 * @param B - matriz de beneficios
 * @param m - nodo
 * @return máximo beneficio de una tarea
 */
int argmax(int fila, int B[][N], NODO m) {
    int maxBeneficio = 0; // Máximo beneficio de una tarea
    int indiceMax = -1; // Indice de la tarea con máximo beneficio

    for (int j = 0; j < N; j++) { // Recorrer fila de la matriz
        if (!m.usadas[j]  && B[fila][j] > maxBeneficio) { // Si la tarea no está usada y el beneficio es mayor
            maxBeneficio = B[fila][j]; // Se guarda el beneficio asociado a la asignacion
            indiceMax = j;  // Se guarda el indice de la tarea con máximo beneficio
        }
    }

    return indiceMax; // Devuelve el indice de la tarea con máximo beneficio
}

/**
 * @brief Asignación voraz de tareas con mas beneficio
 * @param x - nodo
 * @param B - matriz de beneficios
 * @return beneficio acumulado
 */
int asignacionVoraz(NODO x, int B[][N]) {
    int bacum = 0;

    for (int i = x.nivel + 1; i < N; i++) { // Iterar sobre todas las personas
        int k = argmax(i, B, x);
        x.usadas[k] = 1; // Marcar la tarea como usada en el nodo
        bacum += B[i][k]; // Agregar el beneficio de la tarea asignada al beneficio acumulado
    }

    return bacum;
}



/**
 * @brief Función que calcula la suma de los máximos beneficios de las tareas no asignadas
 * @param x - nodo
 * @param B - matriz de beneficios
 * @return beneficio acumulado
 */
int maximosTareas(NODO x, int B[][N]) {
    int bacum = 0;

    for (int i = x.nivel + 1; i < N; i++) {
        int maxFila = 0;
        for (int j = 0; j < N; j++) {
            if (B[i][j] > maxFila && !x.usadas[j]) {
                maxFila = B[i][j];
            }
        }
        bacum += maxFila;
    }

    return bacum;
}

/* PARA CUANDO CS == CI */

/**
 * @brief Función que realiza la asignación voraz de tareas
 * @param x - nodo
 * @param B - matriz de beneficios
 * @return nodo hoja como solución
 */
NODO solAsignacionVoraz(NODO x, int B[][N]){
    int Bmax; // Para cada nivel, beneficio maximo en tareas no usadas
    int tmax = -1; // Para cada nivel, tarea con beneficio maximo no usada

    for (int i = x.nivel + 1; i < N; i++) { // Para cada nivel i
        //Busco en la fila i la tarea con beneficio maximo no usada
        Bmax = -1;
        for (int j = 0; j < N; j++) { // Pruebo tareas j para nivel i
            if (!x.usadas[j] && B[i][j] > Bmax) {
                Bmax = B[i][j]; // Se guarda el beneficio asociado a la asignacion
                tmax = j; // Se guarda tarea con máximo beneficio
            }
            
        }

        // Actualizo x en nivel i con tarea tmax con beneficio Bmax
        x.tupla[i] = tmax; // Guardo tarea con Bmax para cada persona i
        x.usadas[tmax] = 1; // La tarea tmax se marca como usada
        x.bact += Bmax; // Se actualiza el beneficio acumulado para el nodo
        Nodos++; // Incremento el número de nodos explorados
    }

    x.nivel = N - 1; // Para marcar el nodo como completo
    return x; // Devuelvo el nodo hoja como solucion
}


/** FUNCIONES PUBLICAS **/

/* FUNCIONES PARA CALCULAR CI, CS Y BE */

/**
 * @brief Función que calcula la cota inferior de un nodo (trivial)
 * @param x - nodo
 */
void CItrivial(NODO *x){
    // Cota inferior = beneficio acumulado
    //Casteamos a float para que no haya problemas con la asinacion a x->CI
    x->CI = (float)x->bact;
}

/**
 * @brief Función que calcula la cota superior de un nodo (precisa)
 * @param x - nodo
 * @param B - matriz de beneficios
 */
void CIprecisa(NODO *x, int B[][N]){
    // Cota inferior = beneficio acumulado + suma de los máximos beneficios de las tareas no asignadas
    //Casteamos a float para que no haya problemas con la asinacion a x->CI
    x->CI = (float)x->bact + (float)asignacionVoraz(*x, B);
}

/**
 * @brief Función que calcula la cota superior de un nodo (trivial)
 * @param x - nodo
 * @param B - matriz de beneficios
 */
void CStrivial(NODO *x, int B[][N], float max){
    // Cota superior = beneficio acumulado + (número de tareas - nivel) * máximo beneficio
    //Casteamos a float para que no haya problemas con la asinacion a x->CS
    x->CS = (float)x->bact + (float)(N - 1 - x->nivel) * max;
}

/**
 * @brief Función que calcula la cota superior de un nodo (precisa)
 * @param x - nodo
 * @param B - matriz de beneficios
 */
void CSprecisa(NODO *x, int B[][N]){
    // Cota superior = beneficio acumulado + suma de los máximos beneficios de las tareas no asignadas
    // Casteamos a float para que no haya problemas con la asinacion a x->CS
    x->CS = (float)x->bact + (float)maximosTareas(*x, B);
}

/**
 * @brief Función que calcula el beneficio estimado de un nodo
 * @param x - nodo
 */
void BE(NODO *x) {
    // Beneficio estimado = (cota inferior + cota superior) / 2
    x->BE = (x->CI + x->CS) / 2;
}

/* FUNCIONES PARA EL PROCESO DE RAMIFICACIÓN Y PODA */

/**
 * @brief Función que comprueba si un nodo es solución
 * @param x - nodo
 * @return 1 si es solucion y 0 en otro caso
 */
int esSolucion(NODO x) {
    // Si el nivel es igual al número de tareas, es solución
    return x.nivel == N - 1;
}

/**
 * @brief Función que selecciona el nodo con mayor beneficio estimado y lo elimina de la lista de nodos vivos
 * @param LNV - puntero a la lista de nodos vivos
 * @return nodo con mayor beneficio estimado
 */
NODO seleccionar(TLISTA *LNV) {
    // Seleccionar el nodo con mayor beneficio estimado
    TPOSICION p = primeroLista(*LNV), auxPos = p; // Posición del primer elemento de la lista
    TIPOELEMENTO aux, max; // Nodos auxiliar y con mayor beneficio estimado
    recuperarElementoLista(*LNV, p, &max); // Nodo con mayor beneficio estimado

    //Recorremos la lista en busca del nodo con mayor beneficio estimado
    while (p != finLista(*LNV)) {
        recuperarElementoLista(*LNV, p, &aux); // Cogemos el nodo de la lista
        if (aux.BE > max.BE) {
            max = aux; // Nodo con mayor beneficio estimado
            auxPos = p; // Posición del nodo con mayor beneficio estimado
        }
        p = siguienteLista(*LNV, p); // Siguiente nodo
    }

    suprimirElementoLista(LNV,auxPos); // Eliminamos el nodo con mayor beneficio estimado de la lista

    return max;
}

/**
 * @brief Función que calcula el máximo entre dos números
 * @param a - número 1
 * @param b - número 2
 * @return numero mayor
 */
float max (float a, float b){
    if (a > b){
        return a;
    } else {
        return b;
    }
}

/**
 * @brief Función que calcula el máximo beneficio de una tarea
 * @param B - matriz de beneficios
 * @return máximo beneficio de una tarea
*/
float maxMatrix(int B[][N]){
    int max = 0; // Máximo beneficio de una tarea
    // Recorrer matriz de beneficios para encontrar el máximo
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++){
            if (B[i][j] > max) {
                max = B[i][j];
            }
        }
    }
    return max;
}

/** FUNCIONES PRINCIPALES **/

/**
 * @brief Función que calcula la cota inferior de un nodo
 * @param B - matriz de beneficios
 * @param s - nodo solución
 * @param nNodos - numero de nodos
 */
void asignacionTrivial(int B[][N], NODO s) {
    /* DECLARACION DE VARIABLES */
    TLISTA LNV; // Lista de nodos vivos
    NODO raiz, x, y; // Nodo raíz, nodo seleccionado (x) y nodo hijo de x (y)
    float C; // Variable de poda
    int nNodos = 1; // Número de nodos explorados
    float maxMatriz = maxMatrix(B); // Maximo de la matriz

    /* INICIALIZACIONES */

    // Inicializar el nodo solución s
    s.bact = 0;
    for (int i = 0; i < N; i++) {
        s.tupla[i] = -1;
    }

    // Inicialización nodo raíz
    raiz.bact = 0; // No hay asignaciones. Beneficio acumulado es 0
    raiz.nivel = -1; // Primer nivel del árbol

    // Inicializar tupla de solución y tareas usadas
    for (int i = 0; i < N; i++) {
        raiz.tupla[i] = -1;
        raiz.usadas[i] = 0;
    }

    // Llamadas a funciones para cota inferior, cota superior y beneficio estimado
    CItrivial(&raiz);
    CStrivial(&raiz, B, maxMatriz);
    BE(&raiz);

    // Inicialización variable de poda
    C = raiz.CI;

    // Inicialización lista de nodos vivos
    crearLista(&LNV);

    // Guardar raíz como primer elemento de LNV
    insertarElementoLista(&LNV, primeroLista(LNV), raiz);

    /* BUCLE PRINCIPAL */
    // Bucle principal de ramificación y poda
    while (!esListaVacia(LNV)) {
        x = seleccionar(&LNV); // Selecciona x y lo elimina de la lista
        if (x.CS > C) { // Ramificamos si hay potencial
            for (int i = 0; i < N; i++) { // Generar cada hijo y de x
                y.nivel = x.nivel + 1; // Nivel del hijo y es el siguiente al de x
                for (int j = 0; j < N; j++) { // Copiar estado de x a y
                    y.tupla[j] = x.tupla[j]; // Copiar tupla
                    y.usadas[j] = x.usadas[j]; // Copiar usadas
                }
                if (!x.usadas[i]) { // Si la tarea i no está usada
                    // Copiar estado de x a y y modificar para el nuevo nivel
                    y.tupla[y.nivel] = i;
                    y.usadas[i] = 1;
                    y.bact = x.bact + B[y.nivel][i];

                    // Calcular CI, CS y BE para nodo y
                    CItrivial(&y);
                    CStrivial(&y, B, maxMatriz);
                    BE(&y);
                    
                    nNodos++; // Incrementa el número de nodos

                    // Actualizar mejor solución y variable de poda
                    if (esSolucion(y) && y.bact > s.bact) {
                        s = y; // s es la mejor solución hasta ahora
                        C = max(C, (float)y.bact);
                    } else if (!esSolucion(y) && y.CS > C) {
                        insertarElementoLista(&LNV, primeroLista(LNV), y);
                        C = max(C, y.CI);
                    }
                }
            }
        }
    }

    /* IMPRIMIR RESULTADO FINAL */
    printf("Resultado final de la asignacion TRIVIAL:\n");
    printf("\tBeneficio acumulado: %d\n", s.bact);
    printf("\tAsignaciones de tareas: { ");
    for (int i = 0; i < N; i++) {
        printf("%d ", s.tupla[i]);
    }
    printf("}\n");
    printf("\tNumero de nodos explorados: %d\n\n", nNodos);
}

/**
 * @brief Función que realiza la asignación precisa de tareas
 * @param B - matriz de beneficios
 * @param s - nodo solución
 * @param nNodos - numero de nodos
 */
void asignacionPrecisa(int B[][N], NODO s) {

    /* DECLARACION DE VARIABLES */
    TLISTA LNV; // Lista de nodos vivos
    NODO raiz, x, y; // Nodo raíz, nodo seleccionado (x) y nodo hijo de x (y)
    float C; // Variable de poda
    

    /* INICIALIZACIONES */

    // Inicializar el nodo solución s
    s.bact = 0;
    for (int i = 0; i < N; i++) {
        s.tupla[i] = -1;
    }

    // Inicialización nodo raíz
    raiz.bact = 0; // No hay asignaciones. Beneficio acumulado es 0
    raiz.nivel = -1; // Primer nivel del árbol

    // Inicializar tupla de solución y tareas usadas
    for (int i = 0; i < N; i++) {
        raiz.tupla[i] = -1;
        raiz.usadas[i] = 0;
    }

    // Llamadas a funciones para cota inferior, cota superior y beneficio estimado
    CIprecisa(&raiz, B);
    CSprecisa(&raiz, B);
    BE(&raiz);

    // Inicialización variable de poda
    C = raiz.CI;

    // Inicialización lista de nodos vivos
    crearLista(&LNV);

    // Guardar raíz como primer elemento de LNV
    insertarElementoLista(&LNV, primeroLista(LNV), raiz);

    /* BUCLE PRINCIPAL */

    // Bucle principal de ramificación y poda
    while (!esListaVacia(LNV)) {
        x = seleccionar(&LNV); // Selecciona x y lo elimina de la lista
        
        if (x.CS > C) { // Ramificamos si hay potencial
            for (int i = 0; i < N; i++) { // Generar cada hijo y de x
                y.nivel = x.nivel + 1; // Nivel del hijo y es el siguiente al de x
                for (int j = 0; j < N; j++) { // Copiar estado de x a y
                    y.tupla[j] = x.tupla[j]; // Copiar tupla
                    y.usadas[j] = x.usadas[j]; // Copiar usadas
                }
                if (!x.usadas[i]) { // Si la tarea i no está usada
                    // Copiar estado de x a y y modificar para el nuevo nivel
                    y.tupla[y.nivel] = i;
                    y.usadas[i] = 1;
                    y.bact = x.bact + B[y.nivel][i];

                    // Calcular CI, CS y BE para nodo y
                    CIprecisa(&y, B);
                    CSprecisa(&y, B);
                    BE(&y);

                    printf("Nodo y: %d CS: %f CI: %f\n", Nodos, y.CS, y.CI);

                    Nodos++; // Incrementa el número de nodos

                    if (!esSolucion(y) && y.CS >= C && y.CS == y.CI) { // Si CS == CI, asignación voraz
                        y = solAsignacionVoraz(y, B);
                        
                        printf("\t ALGORIMTO VORAZ Nodo y: %d CS: %f CI: %f\n", Nodos, y.CS, y.CI);
                        s = y; // s es la mejor solución hasta ahora
                        C = max(C,y.CI); // Actualizo la variable de poda

                        break; // Termina la búsqueda, no analizo a los demas hermanos
                    }

                    // Actualizar mejor solución y variable de poda
                    if (esSolucion(y) && y.bact > s.bact) {
                        s = y; // s es la mejor solución hasta ahora
                        C = max(C, (float)y.bact); // Actualizo la variable de poda

                    } 

                    else if (!esSolucion(y) && y.CS > C) {
                        insertarElementoLista(&LNV, primeroLista(LNV), y);
                        C = max(C, y.CI);
                    }
                }
            }
        } else if (x.CS == C && x.CS == x.CI) { // Nodo x seleccionado es solución voraz
            y = solAsignacionVoraz(x, B);
            s = y; // s es la mejor solución hasta ahora
        }
    }

    /* IMPRIMIR RESULTADO FINAL */
    printf("Resultado final de la asignacion PRECISA:\n");
    printf("\tBeneficio acumulado: %d\n", s.bact);
    printf("\tAsignaciones de tareas: { ");
    for (int i = 0; i < N; i++) {
        printf("%d ", s.tupla[i]);
    }
    printf("}\n");
    printf("\tNumero de nodos explorados: %d\n\n", Nodos);
}
