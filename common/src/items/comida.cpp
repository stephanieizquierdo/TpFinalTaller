#include "items/comida.h"

#define VIDA 10
#define VIDA_MAXIMA 100

Comida::Comida(Posicion &posicion) : Item(posicion), puntos_de_vida(VIDA) {}

Comida::~Comida() {}

void Comida::obtenerBeneficio(Jugador *jugador) {
    if (jugador->puntos_de_vida() != VIDA_MAXIMA) {
        jugador->actualizar_vida(this->puntos_de_vida);
    }
}
