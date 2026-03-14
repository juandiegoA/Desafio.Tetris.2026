#include <cstdlib>
#include <ctime>
#include "juego.h"

int main() {
    std::srand((unsigned int)std::time(0));

    Juego juego;
    juego.ejecutar();

    return 0;
}
