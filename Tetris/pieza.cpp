#include "pieza.h"

// 0 -> O
// 1 -> I
// 2 -> T

static const int TOTAL_PIEZAS = 3;
static const int TOTAL_ROTACIONES = 4;

static const unsigned char mascaras[TOTAL_PIEZAS][TOTAL_ROTACIONES][4] = {
    // O
    {
        {0b1100, 0b1100, 0b0000, 0b0000},
        {0b1100, 0b1100, 0b0000, 0b0000},
        {0b1100, 0b1100, 0b0000, 0b0000},
        {0b1100, 0b1100, 0b0000, 0b0000}
    },

    // I
    {
        {0b1111, 0b0000, 0b0000, 0b0000},
        {0b1000, 0b1000, 0b1000, 0b1000},
        {0b1111, 0b0000, 0b0000, 0b0000},
        {0b1000, 0b1000, 0b1000, 0b1000}
    },

    // T
    {
        {0b1110, 0b0100, 0b0000, 0b0000},
        {0b0100, 0b1100, 0b0100, 0b0000},
        {0b0100, 0b1110, 0b0000, 0b0000},
        {0b1000, 0b1100, 0b1000, 0b0000}
    }
};

static const int anchos[TOTAL_PIEZAS][TOTAL_ROTACIONES] = {
    {2, 2, 2, 2},
    {4, 1, 4, 1},
    {3, 2, 3, 2}
};

static const int altos[TOTAL_PIEZAS][TOTAL_ROTACIONES] = {
    {2, 2, 2, 2},
    {1, 4, 1, 4},
    {2, 3, 2, 3}
};

Pieza::Pieza(int tipoPieza, int columnaInicial) {
    tipo = tipoPieza;
    rotacion = 0;
    fila = 0;
    columna = columnaInicial;
}

Pieza::~Pieza() {
}

int Pieza::obtenerTipo() const {
    return tipo;
}

int Pieza::obtenerRotacion() const {
    return rotacion;
}

int Pieza::obtenerFila() const {
    return fila;
}

int Pieza::obtenerColumna() const {
    return columna;
}

void Pieza::fijarFila(int nuevaFila) {
    fila = nuevaFila;
}

void Pieza::fijarColumna(int nuevaColumna) {
    columna = nuevaColumna;
}

void Pieza::moverIzquierda() {
    columna--;
}

void Pieza::moverDerecha() {
    columna++;
}

void Pieza::moverAbajo() {
    fila++;
}

void Pieza::rotarHorario() {
    rotacion = (rotacion + 1) % 4;
}

int Pieza::obtenerSiguienteRotacion() const {
    return (rotacion + 1) % 4;
}

int Pieza::obtenerAnchoActual() const {
    return anchos[tipo][rotacion];
}

int Pieza::obtenerAltoActual() const {
    return altos[tipo][rotacion];
}

unsigned char Pieza::obtenerFilaMascara(int indiceFila) const {
    if (indiceFila < 0 || indiceFila >= 4) {
        return 0;
    }

    return mascaras[tipo][rotacion][indiceFila];
}

unsigned char Pieza::obtenerFilaMascaraConRotacion(int indiceFila, int rot) const {
    if (indiceFila < 0 || indiceFila >= 4) {
        return 0;
    }

    if (rot < 0 || rot >= 4) {
        return 0;
    }

    return mascaras[tipo][rot][indiceFila];
}
