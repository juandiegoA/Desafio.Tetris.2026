#include <iostream>
#include "tablero.h"
#include "pieza.h"

Tablero::Tablero(int anchoTablero, int altoTablero) {
    ancho = anchoTablero;
    alto = altoTablero;
    bytesPorFila = ancho / 8;

    celdas = new unsigned char*[alto];

    for (int i = 0; i < alto; i++) {
        celdas[i] = new unsigned char[bytesPorFila];

        for (int j = 0; j < bytesPorFila; j++) {
            celdas[i][j] = 0;
        }
    }
}

Tablero::~Tablero() {
    for (int i = 0; i < alto; i++) {
        delete[] celdas[i];
    }

    delete[] celdas;
}

int Tablero::obtenerAncho() const {
    return ancho;
}

int Tablero::obtenerAlto() const {
    return alto;
}

int Tablero::obtenerBytesPorFila() const {
    return bytesPorFila;
}

bool Tablero::estaDentro(int fila, int columna) const {
    if (fila < 0 || fila >= alto) {
        return false;
    }

    if (columna < 0 || columna >= ancho) {
        return false;
    }

    return true;
}

bool Tablero::obtenerCelda(int fila, int columna) const {
    if (!estaDentro(fila, columna)) {
        return false;
    }

    int indiceByte = columna / 8;
    int posicionBit = 7 - (columna % 8);
    unsigned char mascara = (unsigned char)(1 << posicionBit);

    return (celdas[fila][indiceByte] & mascara) != 0;
}

void Tablero::activarCelda(int fila, int columna) {
    if (!estaDentro(fila, columna)) {
        return;
    }

    int indiceByte = columna / 8;
    int posicionBit = 7 - (columna % 8);
    unsigned char mascara = (unsigned char)(1 << posicionBit);

    celdas[fila][indiceByte] = (unsigned char)(celdas[fila][indiceByte] | mascara);
}

void Tablero::limpiarCelda(int fila, int columna) {
    if (!estaDentro(fila, columna)) {
        return;
    }

    int indiceByte = columna / 8;
    int posicionBit = 7 - (columna % 8);
    unsigned char mascara = (unsigned char)(1 << posicionBit);

    celdas[fila][indiceByte] = (unsigned char)(celdas[fila][indiceByte] & (unsigned char)(~mascara));
}

bool Tablero::hayPiezaEnPosicion(const Pieza* piezaActual, int filaTablero, int columnaTablero) const {
    if (piezaActual == 0) {
        return false;
    }

    int filaLocal = filaTablero - piezaActual->obtenerFila();
    int columnaLocal = columnaTablero - piezaActual->obtenerColumna();

    if (filaLocal < 0 || filaLocal >= 4) {
        return false;
    }

    if (columnaLocal < 0 || columnaLocal >= 4) {
        return false;
    }

    unsigned char mascaraFila = piezaActual->obtenerFilaMascara(filaLocal);
    unsigned char mascaraBit = (unsigned char)(1 << (3 - columnaLocal));

    return (mascaraFila & mascaraBit) != 0;
}

void Tablero::imprimir(const Pieza* piezaActual) const {
    int i = 0;
    int j = 0;

    std::cout << std::endl;
    std::cout << "Tablero (" << alto << " x " << ancho << ")" << std::endl;
    std::cout << std::endl;

    for (i = 0; i < alto; i++) {
        for (j = 0; j < ancho; j++) {
            if (hayPiezaEnPosicion(piezaActual, i, j)) {
                std::cout << "O";
            } else if (obtenerCelda(i, j)) {
                std::cout << "#";
            } else {
                std::cout << ".";
            }
        }
        std::cout << std::endl;
    }

    std::cout << std::endl;
}
