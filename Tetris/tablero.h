#ifndef TABLERO_H
#define TABLERO_H

class Pieza;

class Tablero {
private:
    int ancho;
    int alto;
    int bytesPorFila;
    unsigned char** celdas;

    bool hayPiezaEnPosicion(const Pieza* piezaActual, int fila, int columna) const;

public:
    Tablero(int anchoTablero, int altoTablero);
    ~Tablero();

    int obtenerAncho() const;
    int obtenerAlto() const;
    int obtenerBytesPorFila() const;

    bool estaDentro(int fila, int columna) const;

    bool obtenerCelda(int fila, int columna) const;
    void activarCelda(int fila, int columna);
    void limpiarCelda(int fila, int columna);

    bool hayColisionConPieza(const Pieza& pieza, int nuevaFila, int nuevaColumna, int nuevaRotacion) const;
    void fijarPieza(const Pieza& pieza);

    bool filaCompleta(int fila) const;
    void eliminarFila(int fila);
    int limpiarFilasCompletas();

    void imprimir(const Pieza* piezaActual) const;
};

#endif
