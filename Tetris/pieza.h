#ifndef PIEZA_H
#define PIEZA_H

class Pieza {
private:
    int tipo;
    int rotacion;
    int fila;
    int columna;

public:
    Pieza(int tipoPieza, int columnaInicial);
    ~Pieza();

    int obtenerTipo() const;
    int obtenerRotacion() const;
    int obtenerFila() const;
    int obtenerColumna() const;

    void fijarFila(int nuevaFila);
    void fijarColumna(int nuevaColumna);

    void moverIzquierda();
    void moverDerecha();
    void moverAbajo();

    void rotarHorario();
    int obtenerSiguienteRotacion() const;

    int obtenerAnchoActual() const;
    int obtenerAltoActual() const;

    unsigned char obtenerFilaMascara(int indiceFila) const;
    unsigned char obtenerFilaMascaraConRotacion(int indiceFila, int rot) const;
};

#endif
