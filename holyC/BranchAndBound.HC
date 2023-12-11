// Created by Pablo Seijo on 28/11/23.

// HolyC no utiliza archivos de cabecera de la misma manera que C, por lo que no es necesario incluir "printf.h".
// La inclusión de "BranchAndBound.h" y "lista.h" dependerá de si estas implementaciones están disponibles en HolyC.

// HolyC utiliza 'I64' para enteros de 64 bits.

// Definición de la estructura NODO, si aún no está definida.
// Deberías definir la estructura NODO y cualquier otra estructura o tipo de datos necesarios en HolyC.

// Definición de N si no está definida previamente.
#define N 3 // Suponiendo que N es el tamaño de la matriz.

// Implementación de las funciones en HolyC.
// Las funciones de C se traducirán a HolyC con algunos ajustes.

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



F64 max(F64 a, F64 b) {
    return a > b ? a : b;
}



// Otras funciones privadas y públicas se adaptarían de manera similar.
// ...

// Nota: La implementación exacta de cada función dependerá de cómo se define y se maneja la estructura NODO en HolyC,
// así como del manejo de matrices y otros tipos de datos en el entorno específico de TempleOS.
