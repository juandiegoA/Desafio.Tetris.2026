#ifndef JUEGO_H
#define JUEGO_H

#include "tablero.h"
#include "pieza.h"

class Juego {
private:
    Tablero* tablero;
    Pieza* piezaActual;
    bool salir;

    void pedirDimensiones(int& ancho, int& alto);
    char leerAccion() const;
    bool piezaCabeEnLimites(int nuevaFila, int nuevaColumna, int nuevaRotacion) const;

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
