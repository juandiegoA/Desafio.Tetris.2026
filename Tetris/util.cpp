#include "util.h"

bool anchoValido(int ancho) {
    if (ancho < 8) {
        return false;
    }

    if (ancho % 8 != 0) {
        return false;
    }

    return true;
}

bool altoValido(int alto) {
    if (alto < 8) {
        return false;
    }

    return true;
}

char convertirAMayuscula(char c) {
    if (c >= 'a' && c <= 'z') {
        return (char)(c - ('a' - 'A'));
    }

    return c;
}

bool comandoValido(char comando) {
    char c = convertirAMayuscula(comando);

    return c == 'A' || c == 'D' || c == 'S' || c == 'W' || c == 'Q';
}
