#include "comandos/ataque.h"

void Ataque::ejecutar(EstadoJuego &estadoJuego) {
    estadoJuego.realizarAtaque(this->idJugador);
}