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

    void imprimir(const Pieza* piezaActual) const;
};

#endif
