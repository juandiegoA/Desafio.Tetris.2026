#include <iostream>
#include "juego.h"
#include "util.h"

Juego::Juego() {
    tablero = 0;
    piezaActual = 0;
    salir = false;
}

Juego::~Juego() {
    if (piezaActual != 0) {
        delete piezaActual;
        piezaActual = 0;
    }

    if (tablero != 0) {
        delete tablero;
        tablero = 0;
    }
}

void Juego::pedirDimensiones(int& ancho, int& alto) {
    do {
        std::cout << "Ingrese el ancho del tablero (minimo 8 y multiplo de 8): ";
        std::cin >> ancho;

        if (!anchoValido(ancho)) {
            std::cout << "Ancho invalido. Debe ser >= 8 y multiplo de 8." << std::endl;
        }
    } while (!anchoValido(ancho));

    do {
        std::cout << "Ingrese el alto del tablero (minimo 8): ";
        std::cin >> alto;

        if (!altoValido(alto)) {
            std::cout << "Alto invalido. Debe ser >= 8." << std::endl;
        }
    } while (!altoValido(alto));
}

char Juego::leerAccion() const {
    char accion = 0;

    do {
        std::cout << "Accion [A]Izq [D]Der [S]Bajar [W]Rotar [Q]Salir: ";
        std::cin >> accion;
        accion = convertirAMayuscula(accion);

        if (!comandoValido(accion)) {
            std::cout << "Comando invalido." << std::endl;
        }
    } while (!comandoValido(accion));

    return accion;
}

bool Juego::piezaCabeEnLimites(int nuevaFila, int nuevaColumna, int nuevaRotacion) const {
    int filaLocal = 0;
    int columnaLocal = 0;
    unsigned char mascaraFila = 0;
    unsigned char mascaraBit = 0;

    for (filaLocal = 0; filaLocal < 4; filaLocal++) {
        mascaraFila = piezaActual->obtenerFilaMascaraConRotacion(filaLocal, nuevaRotacion);

        for (columnaLocal = 0; columnaLocal < 4; columnaLocal++) {
            mascaraBit = (unsigned char)(1 << (3 - columnaLocal));

            if ((mascaraFila & mascaraBit) != 0) {
                int filaTablero = nuevaFila + filaLocal;
                int columnaTablero = nuevaColumna + columnaLocal;

                if (!tablero->estaDentro(filaTablero, columnaTablero)) {
                    return false;
                }
            }
        }
    }

    return true;
}

void Juego::intentarMoverIzquierda() {
    int nuevaColumna = piezaActual->obtenerColumna() - 1;

    if (piezaCabeEnLimites(piezaActual->obtenerFila(), nuevaColumna, piezaActual->obtenerRotacion())) {
        piezaActual->fijarColumna(nuevaColumna);
    }
}

void Juego::intentarMoverDerecha() {
    int nuevaColumna = piezaActual->obtenerColumna() + 1;

    if (piezaCabeEnLimites(piezaActual->obtenerFila(), nuevaColumna, piezaActual->obtenerRotacion())) {
        piezaActual->fijarColumna(nuevaColumna);
    }
}

void Juego::intentarMoverAbajo() {
    int nuevaFila = piezaActual->obtenerFila() + 1;

    if (piezaCabeEnLimites(nuevaFila, piezaActual->obtenerColumna(), piezaActual->obtenerRotacion())) {
        piezaActual->fijarFila(nuevaFila);
    }
}

void Juego::intentarRotar() {
    int nuevaRotacion = piezaActual->obtenerSiguienteRotacion();

    if (piezaCabeEnLimites(piezaActual->obtenerFila(), piezaActual->obtenerColumna(), nuevaRotacion)) {
        piezaActual->rotarHorario();
    }
}

void Juego::procesarAccion(char accion) {
    if (accion == 'A') {
        intentarMoverIzquierda();
    } else if (accion == 'D') {
        intentarMoverDerecha();
    } else if (accion == 'S') {
        intentarMoverAbajo();
    } else if (accion == 'W') {
        intentarRotar();
    } else if (accion == 'Q') {
        salir = true;
    }
}

void Juego::ejecutar() {
    int ancho = 0;
    int alto = 0;
    int columnaInicial = 0;
    char accion = 0;

    pedirDimensiones(ancho, alto);

    tablero = new Tablero(ancho, alto);

    // Por ahora seguimos usando la pieza O (tipo 0)
    columnaInicial = (ancho / 2) - 1;
    piezaActual = new Pieza(0, columnaInicial);

    std::cout << std::endl;
    std::cout << "Tablero creado correctamente." << std::endl;
    std::cout << "Bytes por fila: " << tablero->obtenerBytesPorFila() << std::endl;

    while (!salir) {
        tablero->imprimir(piezaActual);
        accion = leerAccion();
        procesarAccion(accion);
    }
}
