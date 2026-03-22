#include <iostream>
#include "juego.h"
#include "util.h"

Juego::Juego() {
    tablero = 0;
    piezaActual = 0;
    salir = false;
    gameOver = false;
    lineasEliminadasTotales = 0;
    ultimasFilasEliminadas = 0;
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

const char* Juego::obtenerNombrePiezaActual() const {
    if (piezaActual == 0) {
        return "Ninguna";
    }

    if (piezaActual->obtenerTipo() == 0) {
        return "O";
    } else if (piezaActual->obtenerTipo() == 1) {
        return "I";
    } else if (piezaActual->obtenerTipo() == 2) {
        return "T";
    } else if (piezaActual->obtenerTipo() == 3) {
        return "L";
    } else if (piezaActual->obtenerTipo() == 4) {
        return "J";
    } else if (piezaActual->obtenerTipo() == 5) {
        return "S";
    } else if (piezaActual->obtenerTipo() == 6) {
        return "Z";
    }

    return "Desconocida";
}

void Juego::mostrarEncabezado() const {
    std::cout << std::endl;
    std::cout << "Pieza actual: " << obtenerNombrePiezaActual() << std::endl;
    std::cout << "Lineas eliminadas: " << lineasEliminadasTotales << std::endl;

    if (ultimasFilasEliminadas > 0) {
        std::cout << "Ultimo movimiento: se eliminaron "
                  << ultimasFilasEliminadas
                  << " fila(s)." << std::endl;
    }
}

void Juego::crearNuevaPieza() {
    int tipo = generarNumeroAleatorio(0, 6);
    int columnaInicial = 0;
    Pieza* nuevaPieza = 0;

    nuevaPieza = new Pieza(tipo, 0);
    columnaInicial = (tablero->obtenerAncho() - nuevaPieza->obtenerAnchoActual()) / 2;
    nuevaPieza->fijarColumna(columnaInicial);
    nuevaPieza->fijarFila(0);

    if (tablero->hayColisionConPieza(*nuevaPieza,
                                     nuevaPieza->obtenerFila(),
                                     nuevaPieza->obtenerColumna(),
                                     nuevaPieza->obtenerRotacion())) {
        delete nuevaPieza;
        nuevaPieza = 0;
        gameOver = true;
        return;
    }

    if (piezaActual != 0) {
        delete piezaActual;
        piezaActual = 0;
    }

    piezaActual = nuevaPieza;
}

void Juego::intentarMoverIzquierda() {
    int nuevaColumna = piezaActual->obtenerColumna() - 1;
    ultimasFilasEliminadas = 0;

    if (!tablero->hayColisionConPieza(*piezaActual,
                                      piezaActual->obtenerFila(),
                                      nuevaColumna,
                                      piezaActual->obtenerRotacion())) {
        piezaActual->fijarColumna(nuevaColumna);
    }
}

void Juego::intentarMoverDerecha() {
    int nuevaColumna = piezaActual->obtenerColumna() + 1;
    ultimasFilasEliminadas = 0;

    if (!tablero->hayColisionConPieza(*piezaActual,
                                      piezaActual->obtenerFila(),
                                      nuevaColumna,
                                      piezaActual->obtenerRotacion())) {
        piezaActual->fijarColumna(nuevaColumna);
    }
}

void Juego::intentarMoverAbajo() {
    int nuevaFila = piezaActual->obtenerFila() + 1;
    int filasEliminadas = 0;

    ultimasFilasEliminadas = 0;

    if (!tablero->hayColisionConPieza(*piezaActual,
                                      nuevaFila,
                                      piezaActual->obtenerColumna(),
                                      piezaActual->obtenerRotacion())) {
        piezaActual->fijarFila(nuevaFila);
    } else {
        tablero->fijarPieza(*piezaActual);
        filasEliminadas = tablero->limpiarFilasCompletas();
        ultimasFilasEliminadas = filasEliminadas;
        lineasEliminadasTotales += filasEliminadas;
        crearNuevaPieza();
    }
}

void Juego::intentarRotar() {
    int nuevaRotacion = piezaActual->obtenerSiguienteRotacion();
    int columnaActual = piezaActual->obtenerColumna();
    int filaActual = piezaActual->obtenerFila();

    int desplazamientosNormales[5] = {0, -1, 1, -2, 2};
    int desplazamientosI[7] = {0, -1, 1, -2, 2, -3, 3};

    int i = 0;
    int nuevaColumna = 0;

    ultimasFilasEliminadas = 0;

    if (piezaActual->obtenerTipo() == 1) {
        for (i = 0; i < 7; i++) {
            nuevaColumna = columnaActual + desplazamientosI[i];

            if (!tablero->hayColisionConPieza(*piezaActual,
                                              filaActual,
                                              nuevaColumna,
                                              nuevaRotacion)) {
                piezaActual->fijarColumna(nuevaColumna);
                piezaActual->rotarHorario();
                return;
            }
        }
    } else {
        for (i = 0; i < 5; i++) {
            nuevaColumna = columnaActual + desplazamientosNormales[i];

            if (!tablero->hayColisionConPieza(*piezaActual,
                                              filaActual,
                                              nuevaColumna,
                                              nuevaRotacion)) {
                piezaActual->fijarColumna(nuevaColumna);
                piezaActual->rotarHorario();
                return;
            }
        }
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
        mostrarEncabezado();
        tablero->imprimir(piezaActual);
        accion = leerAccion();
        procesarAccion(accion);
    }

    if (gameOver) {
        mostrarEncabezado();
        tablero->imprimir(0);
        std::cout << "GAME OVER" << std::endl;
    } else {
        mostrarEncabezado();
        tablero->imprimir(piezaActual);
    }
}
