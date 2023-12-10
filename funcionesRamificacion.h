//
// Created by Pablo Seijo on 28/11/23.
//

#ifndef PRACTICA6RAMIFICACION_FUNCIONESRAMIFICACION_H
#define PRACTICA6RAMIFICACION_FUNCIONESRAMIFICACION_H

/** FUNCIONES PRINCIPALES **/

#include "lista.h"

/**
 * @brief Función que calcula la cota inferior de un nodo
 * @param B - matriz de beneficios
 * @param s - nodo solución
 */
void asignacionTrivial(int B[][N], NODO s);

/**
 * @brief Función que realiza la asignación precisa de tareas
 * @param B - matriz de beneficios
 * @param s - nodo solución
 */
void asignacionPrecisa(int B[][N], NODO s);


/* FUNCIONES PARA EL PROCESO DE RAMIFICACIÓN Y PODA */

/**
 * @brief Función que comprueba si un nodo es solución
 * @param x - nodo
 * @return 1 si es solucion y 0 en otro caso
 */
int esSolucion(NODO x);

/**
 * @brief Función que selecciona el nodo con mayor beneficio estimado y lo elimina de la lista de nodos vivos
 * @param LNV - puntero a la lista de nodos vivos
 * @return nodo con mayor beneficio estimado
 */
NODO seleccionar(TLISTA *LNV);

/**
 * @brief Función que calcula el máximo entre dos números
 * @param a - número 1
 * @param b - número 2
 * @return numero mayor
 */
float max (float a, float b);

/* FUNCIONES PARA CALCULAR CI, CS Y BE */

/**
 * @brief Función que calcula la cota inferior de un nodo (trivial)
 * @param x - nodo
 */
void CItrivial(NODO *x);

/**
 * @brief Función que calcula la cota superior de un nodo (precisa)
 * @param x - nodo
 * @param B - matriz de beneficios
 */
void CIprecisa(NODO *x, int B[][N]);

/**
 * @brief Función que calcula la cota superior de un nodo (trivial)
 * @param x - nodo
 * @param B - matriz de beneficios
 */
void CStrivial(NODO *x, int B[][N]);

/**
 * @brief Función que calcula la cota superior de un nodo (precisa)
 * @param x - nodo
 * @param B - matriz de beneficios
 */
void CSprecisa(NODO *x, int B[][N]);

/**
 * @brief Función que calcula el beneficio estimado de un nodo
 * @param x - nodo
 */
void BE(NODO *x);

#endif //PRACTICA6RAMIFICACION_FUNCIONESRAMIFICACION_H
