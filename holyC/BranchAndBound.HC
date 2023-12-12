// Created by Pablo Seijo on 28/11/23.

#include "list.HC"

// HolyC utiliza 'I64' para enteros de 64 bits

// Función argmax
I64 argmax(I64 fila, I64 B[][], NODO m) {
    I64 maxBeneficio = 0;
    I64 indiceMax = -1;

    for (I64 j = 0; j < N; j++) {
        if (m.usadas[j] == 0 && B[fila][j] > maxBeneficio) {
            maxBeneficio = B[fila][j];
            indiceMax = j;
        }
    }

    return indiceMax;
}


// Función asignacionVoraz
I64 asignacionVoraz(NODO x, I64 B[][]) {
    I64 bacum = 0;

    for (I64 i = x.nivel + 1; i < N; i++) {
        I64 k = argmax(i, B, x);
        if (k != -1) {
            x.usadas[k] = 1;
            bacum += B[i][k];
        }
    }

    return bacum;
}


// Función maximosTareas
I64 maximosTareas(NODO x, I64 B[][]) {
    I64 bacum = 0;

    for (I64 i = x.nivel + 1; i < N; i++) {
        I64 maxFila = 0;
        for (I64 j = 0; j < N; j++) {
            if (B[i][j] > maxFila) {
                maxFila = B[i][j];
            }
        }
        bacum += maxFila;
    }

    return bacum;
}


// Función solAsignacionVoraz
NODO solAsignacionVoraz(NODO x, I64 B[][]) {
    I64 Bmax, tmax;

    for (I64 i = x.nivel + 1; i < N; i++) {
        Bmax = -1;
        for (I64 j = 0; j < N; j++) {
            if (!x.usadas[j] && B[i][j] > Bmax) {
                Bmax = B[i][j];
                tmax = j;
            }
        }
        x.tupla[i] = tmax;
        x.usadas[tmax] = 1;
        x.bact += Bmax;
    }

    x.nivel = N - 1;
    return x;
}

Void CItrivial(NODO *x) {
    x->CI = (F64)x->bact;  // En HolyC, se puede usar 'F64' para flotantes.
}

Void CIprecisa(NODO *x, I64 B[][]) {
    x->CI = (F64)(x->bact + asignacionVoraz(*x, B));
}

Void CStrivial(NODO *x, I64 B[][]) {
    I64 max = 0;
    for (I64 i = 0; i < N; i++) {
        for (I64 j = 0; j < N; j++) {
            if (B[i][j] > max) {
                max = B[i][j];
            }
        }
    }
    x->CS = (F64)(x->bact + (N - x->nivel) * max);
}

Void CSprecisa(NODO *x, I64 B[][]) {
    x->CS = (F64)(x->bact + maximosTareas(*x, B));
}

Void BE(NODO *x) {
    x->BE = (x->CI + x->CS) / 2.0;
}

I64 esSolucion(NODO x) {
    return x.nivel == N - 1;
}

NODO seleccionar(TLISTA *LNV) {
    TPOSICION p = primeroLista(*LNV), auxPos = p;
    NODO aux, max;

    recuperarElementoLista(*LNV, p, &max);

    p = siguienteLista(*LNV, p);
    while (p) {  // En HolyC, a menudo se usa '0' o 'null' para el final de la lista en lugar de 'finLista'.
        recuperarElementoLista(*LNV, p, &aux);
        if (aux.BE > max.BE) {
            max = aux;
            auxPos = p;
        }
        p = siguienteLista(*LNV, p);
    }

    suprimirElementoLista(LNV, auxPos);

    return max;
}

F64 max(F64 a, F64 b) {
    return a > b ? a : b;
}

/** FUNCIONES PRINCIPALES **/

Void asignacionTrivial(I64 B[][], NODO s) {
    TLISTA LNV;
    NODO raiz, x, y;
    F64 C;
    I64 nNodos = 0;

    // Inicialización del nodo solución s
    s.bact = 0;
    For (I64 i = 0; i < N; i++) {
        s.tupla[i] = -1;
    }

    // Inicialización del nodo raíz
    raiz.bact = 0;
    raiz.nivel = -1;
    For (I64 i = 0; i < N; i++) {
        raiz.tupla[i] = -1;
        raiz.usadas[i] = 0;
    }

    // Cota inferior, cota superior y beneficio estimado
    CItrivial(&raiz);
    CStrivial(&raiz, B);
    BE(&raiz);

    // Variable de poda
    C = raiz.CI;

    // Lista de nodos vivos
    crearLista(&LNV);
    insertarElementoLista(&LNV, primeroLista(LNV), raiz);

    // Bucle principal
    While (!esListaVacia(LNV)) {
        x = seleccionar(&LNV);

        If (x.CS > C) {
            For (I64 i = 0; i < N; i++) {
                y.nivel = x.nivel + 1;
                For (I64 j = 0; j < N; j++) {
                    y.tupla[j] = x.tupla[j];
                    y.usadas[j] = x.usadas[j];
                }
                If (!x.usadas[i]) {
                    y.tupla[y.nivel] = i;
                    y.usadas[i] = 1;
                    y.bact = x.bact + B[y.nivel][i];

                    CItrivial(&y);
                    CStrivial(&y, B);
                    BE(&y);

                    nNodos++;

                    If (esSolucion(y) && y.bact > s.bact) {
                        s = y;
                        C = Max(C, y.bact);
                    } Else If (!esSolucion(y) && y.CS > C) {
                        insertarElementoLista(&LNV, primeroLista(LNV), y);
                        C = Max(C, y.CI);
                    }
                }
            }
        }
    }

    // Imprimir resultado
    Print("Resultado final de la asignacion TRIVIAL:\n");
    PrintF("\tBeneficio acumulado: %d\n", s.bact);
    Print("\tAsignaciones de tareas: { ");
    For (I64 i = 0; i < N; i++) {
        PrintF("%d ", s.tupla[i] + 1);
    }
    Print("}\n");
    PrintF("\tNumero de nodos explorados: %d\n\n", nNodos);
}

Void asignacionPrecisa(I64 B[][], NODO s) {
    TLISTA LNV;
    NODO raiz, x, y;
    F64 C;
    I64 Nodos = 0;

    // Inicialización del nodo solución s
    s.bact = 0;
    For (I64 i = 0; i < N; i++) {
        s.tupla[i] = -1;
    }

    // Inicialización del nodo raíz
    raiz.bact = 0;
    raiz.nivel = -1;
    For (I64 i = 0; i < N; i++) {
        raiz.tupla[i] = -1;
        raiz.usadas[i] = 0;
    }

    CIprecisa(&raiz, B);
    CSprecisa(&raiz, B);
    BE(&raiz);

    C = raiz.CI;

    crearLista(&LNV);
    insertarElementoLista(&LNV, primeroLista(LNV), raiz);

    While (!esListaVacia(LNV)) {
        x = seleccionar(&LNV);

        If (x.CS > C) {
            For (I64 i = 0; i < N; i++) {
                y.nivel = x.nivel + 1;
                For (I64 j = 0; j < N; j++) {
                    y.tupla[j] = x.tupla[j];
                    y.usadas[j] = x.usadas[j];
                }
                If (!x.usadas[i]) {
                    y.tupla[y.nivel] = i;
                    y.usadas[i] = 1;
                    y.bact = x.bact + B[y.nivel][i];

                    CIprecisa(&y, B);
                    CSprecisa(&y, B);
                    BE(&y);

                    nNodos++;

                    If (!esSolucion(y) && y.CS >= C && y.CS == y.CI) {
                        y = solAsignacionVoraz(y, B);
                        s = y;
                        C = max(C,y.CI);
                        Break;
                    }

                    If (esSolucion(y) && y.bact > s.bact) {
                        s = y;
                        C = Max(C, y.bact);
                    } Else If (!esSolucion(y) && y.CS > C) {
                        insertarElementoLista(&LNV, primeroLista(LNV), y);
                        C = Max(C, y.CI);
                    }
                }
            }
        } Else If (x.CS == C && x.CS == x.CI) {
            y = solAsignacionVoraz(x, B);
            s = y;
        }
    }

    // Imprimir resultado
    Print("Resultado final de la asignacion PRECISA:\n");
    PrintF("\tBeneficio acumulado: %d\n", s.bact);
    Print("\tAsignaciones de tareas: { ");
    For (I64 i = 0; i < N; i++) {
        PrintF("%d ", s.tupla[i] + 1);
    }
    Print("}\n");
    PrintF("\tNumero de nodos explorados: %d\n\n", Nodos);
}
