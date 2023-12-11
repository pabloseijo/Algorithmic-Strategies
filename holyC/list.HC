// Asumiendo que TIPOELEMENTO y TPOSICION están definidos apropiadamente en HolyC.

#define N 3

Struct Celda {
    TIPOELEMENTO elemento;
    Struct Celda *sig;
};

Struct L {
    TPOSICION inicio;
    U0 longitud;
    TPOSICION fin;
};

Void crearLista(TLISTA *l) {
    *l = MAlloc(sizeof(Struct L));
    (*l)->inicio = MAlloc(sizeof(Struct Celda));
    (*l)->fin = (*l)->inicio;
    (*l)->fin->sig = 0;
    (*l)->longitud = 0;
}

/* ESPECIFICO BACKTRACKING Y BRANCH AND BOUND */

Struct Nodo {
    I64 tupla[N];  // o int tupla[N]; si eso es suficiente en tu caso
    I64 nivel;     // o int nivel;
    I64 bact;      // o int bact;
    I64 usadas[N]; // o int usadas[N];
    F64 CI, BE, CS;
};
Typedef Struct Nodo NODO;

Typedef Struct Celda *TPOSICION;
Typedef Struct L *TLISTA;

/* FUNCIONES */

Void destruirLista(TLISTA *l) {
    (*l)->fin = (*l)->inicio;
    While ((*l)->fin) {
        (*l)->fin = (*l)->fin->sig;
        Free((*l)->inicio);
        (*l)->inicio = (*l)->fin;
    }
    Free(*l);
    *l = 0;
}

U0 existeLista(TLISTA l) {
    Return l != 0;
}

U0 esListaVacia(TLISTA l) {
    Return l->longitud == 0;
}

TPOSICION primeroLista(TLISTA l) {
    Return l->inicio;
}

TPOSICION siguienteLista(TLISTA l, TPOSICION p) {
    Return p->sig;
}

TPOSICION finLista(TLISTA l) {
    Return l->fin;
}

TPOSICION anteriorLista(TLISTA l, TPOSICION p) {
    TPOSICION q = l->inicio;
    While (q && q->sig != p) {
        q = q->sig;
    }
    Return q;
}

Void recuperarElementoLista(TLISTA l, TPOSICION p, TIPOELEMENTO *e) {
    *e = p->sig->elemento;
}

U0 longitudLista(TLISTA l) {
    Return l->longitud;
}

Void insertarElementoLista(TLISTA *l, TPOSICION p, TIPOELEMENTO e) {
    TPOSICION q = p->sig;
    p->sig = MAlloc(sizeof(Struct Celda));
    p->sig->elemento = e;
    p->sig->sig = q;
    If (!q) (*l)->fin = p->sig;
    (*l)->longitud++;
}

Void suprimirElementoLista(TLISTA *l, TPOSICION p) {
    TPOSICION q = p->sig;
    p->sig = q->sig;
    If (!p->sig) (*l)->fin = p;
    Free(q);
    (*l)->longitud--;
}

Void modificarElementoLista(TLISTA *l, TPOSICION p, TIPOELEMENTO e) {
    p->sig->elemento = e;
}
