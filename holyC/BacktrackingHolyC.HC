// HolyC no tiene una biblioteca estándar como C, por lo que algunos incluidos pueden no ser necesarios o disponibles.
// No hay necesidad de incluir <stdio.h> o <limits.h>, ya que HolyC proporciona funcionalidades integradas.

#define n 3 // Tamaño de la matriz

// Variable global para la suma de elementos de la solución actual
I64 bact = 0;

// Funciones equivalentes a las de C, adaptadas a HolyC

// HolyC utiliza "I64" para enteros de 64 bits, similar al "int" en C.

I64 masHermanos(I64 nivel, I64 s[], I64* pasosMasHermanos) {
    (*pasosMasHermanos)++;
    return s[nivel] < n - 1;
}

Void generar(I64 nivel, I64 s[], I64 B[][], I64* pasosGenerar) {
    (*pasosGenerar)++;
    if (nivel < n) {
        s[nivel] = s[nivel] + 1;
        if (s[nivel] == 0) {
            bact += B[nivel][s[nivel]];
        } else {
            bact = bact + B[nivel][s[nivel]] - B[nivel][s[nivel] - 1];
        }
    }
}

Void generarUsada(I64 nivel, I64 s[], I64 B[][], I64 usada[], I64* pasosGenerar) {
    (*pasosGenerar)++;
    if (nivel < n) {
        if (nivel != -1) {
            usada[s[nivel]]--;
        }
        s[nivel] = s[nivel] + 1;
        usada[s[nivel]]++;
        if (s[nivel] == 0) {
            bact += B[nivel][s[nivel]];
        } else {
            bact = bact + B[nivel][s[nivel]] - B[nivel][s[nivel] - 1];
        }
    }
}


I64 criterio(I64 nivel, I64 s[], I64* pasosCriterio) {
    I64 contador = 0;
    for (I64 i = 0; i < nivel; i++) {
        contador++;
        if (s[nivel] == s[i]) {
            *pasosCriterio += contador;
            return 0;
        }
    }
    *pasosCriterio += contador;
    return 1;
}


I64 criterioUsada(I64 nivel, I64 s[], I64 usada[], I64* pasosCriterio) {
    (*pasosCriterio)++;
    return usada[s[nivel]] == 1;
}


I64 solucion(I64 nivel, I64 s[], I64* pasosSolucion, I64* pasosCriterio) {
    (*pasosSolucion)++;
    return nivel == n - 1 && criterio(nivel, s, pasosCriterio);
}

I64 solucionUsada(I64 nivel, I64 s[], I64 usada[], I64* pasosSolucion, I64* pasosCriterio) {
    (*pasosSolucion)++;
    return nivel == n - 1 && criterioUsada(nivel, s, usada, pasosCriterio);
}

Void retroceder(I64* nivel, I64 s[], I64 B[][], I64* pasosRetroceder) {
    (*pasosRetroceder)++;
    if (*nivel > 0) {
        bact -= B[*nivel][s[*nivel]];
        s[*nivel] = -1;
        (*nivel)--;
    }
}

Void retrocederUsada(I64* nivel, I64 s[], I64 usada[], I64 B[][], I64* pasosRetroceder) {
    (*pasosRetroceder)++;
    if (*nivel > 0) {
        bact -= B[*nivel][s[*nivel]];
        usada[s[*nivel]]--;
        s[*nivel] = -1;
        (*nivel)--;
    }
}

Void backtracking(I64 B[][], I64 s[]) {
    I64 nivel = 0, voa = MIN_I64, nodosVisitados = 1;
    I64 pasosGenerar = 0, pasosCriterio = 0, pasosSolucion = 0, pasosRetroceder = 0, pasosMasHermanos = 0;
    I64 soa[n];

    bact = 0;
    for (I64 i = 0; i < n; i++) soa[i] = -1;

    while (nivel != -1) {
        generar(nivel, s, B, &pasosGenerar);
        if (solucion(nivel, s, &pasosSolucion, &pasosCriterio) && bact > voa) {
            voa = bact;
            for (I64 i = 0; i < n; i++) soa[i] = s[i];
        }
        if (criterio(nivel, s, &pasosCriterio)) {
            nodosVisitados++;
            if (nivel < n - 1) nivel++;
        }
        while (!masHermanos(nivel, s, &pasosMasHermanos) && nivel >= 0) {
            retroceder(&nivel, s, B, &pasosRetroceder);
        }
    }

    // Finalización de la función con la impresión de resultados
    Print("SOLUCION\n\tMejor solución encontrada: { ");
    for (I64 i = 0; i < n; i++) {
        PrintF("%d ", soa[i] + 1); // Ajuste para imprimir en base-1
    }
    Print("}\n\tvalor: %lld\n", voa); // %lld para imprimir un I64
  
}

Void backtrackingUsada(I64 B[][], I64 s[]) {
    I64 nivel = 0, nodosVisitados = 1, voaUsada = MIN_I64;
    I64 pasosGenerar = 0, pasosCriterio = 0, pasosSolucion = 0, pasosRetroceder = 0, pasosMasHermanos = 0;
    I64 soaAux[n], usada[n];

    bact = 0;
    for (I64 i = 0; i < n; i++) {
        soaAux[i] = -1;
        usada[i] = 0;
    }

    while (nivel != -1) {
        generarUsada(nivel, s, B, usada, &pasosGenerar);
        if (solucionUsada(nivel, s, usada, &pasosSolucion, &pasosCriterio) && bact > voaUsada) {
            voaUsada = bact;
            for (I64 i = 0; i < n; i++) {
                soaAux[i] = s[i];
            }
        }
        if (criterioUsada(nivel, s, usada, &pasosCriterio)) {
            nodosVisitados++;
            if (nivel < n - 1) nivel++;
        }
        while (!masHermanos(nivel, s, &pasosMasHermanos) && nivel >= 0) {
            retrocederUsada(&nivel, s, usada, B, &pasosRetroceder);
        }
    }

    // Código para imprimir la solución óptima y estadísticas
    Print("SOLUCION CON VECTOR USADA:\n\tMejor solución encontrada: { ");
    for (I64 i = 0; i < n; i++) {
        PrintF("%d ", soaAux[i] + 1); // Ajuste para imprimir en base-1
    }
    Print("}\n\tvalor: %lld\n", voaUsada); // %lld para imprimir un I64
}

