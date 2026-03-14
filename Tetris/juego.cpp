#include <iostream>
#include "juego.h"
#include "util.h"

Juego::Juego() {
    tablero = 0;
    piezaActual = 0;
    salir = false;
    gameOver = false;
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

void Juego::crearNuevaPieza() {
    int tipo = generarNumeroAleatorio(0, 2);
    int columnaInicial = 0;

    if (piezaActual != 0) {
        delete piezaActual;
        piezaActual = 0;
    }

    piezaActual = new Pieza(tipo, 0);
    columnaInicial = (tablero->obtenerAncho() - piezaActual->obtenerAnchoActual()) / 2;
    piezaActual->fijarColumna(columnaInicial);
    piezaActual->fijarFila(0);

    if (tablero->hayColisionConPieza(*piezaActual,
                                     piezaActual->obtenerFila(),
                                     piezaActual->obtenerColumna(),
                                     piezaActual->obtenerRotacion())) {
        gameOver = true;
    }
}

void Juego::intentarMoverIzquierda() {
    int nuevaColumna = piezaActual->obtenerColumna() - 1;

    if (!tablero->hayColisionConPieza(*piezaActual,
                                      piezaActual->obtenerFila(),
                                      nuevaColumna,
                                      piezaActual->obtenerRotacion())) {
        piezaActual->fijarColumna(nuevaColumna);
    }
}

void Juego::intentarMoverDerecha() {
    int nuevaColumna = piezaActual->obtenerColumna() + 1;

    if (!tablero->hayColisionConPieza(*piezaActual,
                                      piezaActual->obtenerFila(),
                                      nuevaColumna,
                                      piezaActual->obtenerRotacion())) {
        piezaActual->fijarColumna(nuevaColumna);
    }
}

void Juego::intentarMoverAbajo() {
    int nuevaFila = piezaActual->obtenerFila() + 1;

    if (!tablero->hayColisionConPieza(*piezaActual,
                                      nuevaFila,
                                      piezaActual->obtenerColumna(),
                                      piezaActual->obtenerRotacion())) {
        piezaActual->fijarFila(nuevaFila);
    } else {
        tablero->fijarPieza(*piezaActual);
        tablero->limpiarFilasCompletas();
        crearNuevaPieza();
    }
}

void Juego::intentarRotar() {
    int nuevaRotacion = piezaActual->obtenerSiguienteRotacion();

    if (!tablero->hayColisionConPieza(*piezaActual,
                                      piezaActual->obtenerFila(),
                                      piezaActual->obtenerColumna(),
                                      nuevaRotacion)) {
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
    char accion = 0;

    pedirDimensiones(ancho, alto);

    tablero = new Tablero(ancho, alto);
    crearNuevaPieza();

    std::cout << std::endl;
    std::cout << "Tablero creado correctamente." << std::endl;
    std::cout << "Bytes por fila: " << tablero->obtenerBytesPorFila() << std::endl;

    while (!salir && !gameOver) {
        tablero->imprimir(piezaActual);
        accion = leerAccion();
        procesarAccion(accion);
    }

    tablero->imprimir(piezaActual);

    if (gameOver) {
        std::cout << "GAME OVER" << std::endl;
    }
}
