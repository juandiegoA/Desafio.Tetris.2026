#ifndef JUEGO_H
#define JUEGO_H

#include "tablero.h"
#include "pieza.h"

class Juego {
private:
    Tablero* tablero;
    Pieza* piezaActual;
    bool salir;
    bool gameOver;

    void pedirDimensiones(int& ancho, int& alto);
    char leerAccion() const;

    void crearNuevaPieza();
    void procesarAccion(char accion);

    void intentarMoverIzquierda();
    void intentarMoverDerecha();
    void intentarMoverAbajo();
    void intentarRotar();

public:
    Juego();
    ~Juego();

    void ejecutar();
};

#endif
