#include "../include/manejador_eventos.h"

#include "comandos/movimiento.h"
#include "comandos/ataque.h"
#include "comandos/aperturaDePuerta.h"
#include "comandos/cambioDeArma.h"
#include <config.h>

#define RUTA_SONIDO_AMBIENTE SOUNDS_DIR THEME

ManejadorEventos::ManejadorEventos(int &idJugador, BlockingQueue<Comando *> &eventos) :
        idJugador(idJugador),
        eventos(eventos),
        corriendo(true),
        sonidoAmbiente(RUTA_SONIDO_AMBIENTE) {}

ManejadorEventos::~ManejadorEventos() {}

void ManejadorEventos::run() {
    SDL_Event evento;
    while (this->corriendo) {
        //std::cerr << "sigo en manejador de enventos\n";
        while (SDL_PollEvent(&evento)) {
            detectarEventos(evento);
            std::chrono::milliseconds duration(60);
            std::this_thread::sleep_for(duration);
        }
    }
}

void ManejadorEventos::crearMovimiento(Accion direccion) {
    Comando *movimiento = new Movimiento(this->idJugador, direccion);
    this->eventos.push(movimiento);

}

void ManejadorEventos::crearAtaque() {
    Comando *ataque = new Ataque(this->idJugador);
    this->eventos.push(ataque);

}

void ManejadorEventos::crearAperturaDePuerta() {
    Comando *apertura = new AperturaDePuerta(this->idJugador);
    this->eventos.push(apertura);
}

void ManejadorEventos::crearCambioDeArma() {
    Comando *cambio = new CambioDeArma(this->idJugador);
    this->eventos.push(cambio);

}

void ManejadorEventos::detectarEventos(SDL_Event &evento) {
    switch (evento.type) {
        case SDL_QUIT:
            std::cerr << "entre en quit de manejador " << std::endl;
            this->stop();
            break;
        case SDL_KEYDOWN:
            switch (evento.key.keysym.sym) {
                // aca mandariamos la informacion o crearimos el evento;
                case SDLK_LEFT:         // x, y, vida, angulo;
                    crearMovimiento(Accion::rotarIzquierda);
                    break;
                case SDLK_RIGHT:
                    crearMovimiento(Accion::rotarDerecha);
                    break;
                case SDLK_UP:
                    crearMovimiento(Accion::moverArriba);
                    break;
                case SDLK_DOWN:
                    crearMovimiento(Accion::moverAbajo);
                    break;
                case SDLK_PERIOD:
                    crearAtaque();
                    break;
                case SDLK_g:
                    std::cerr << "comando cambio de arma" << std::endl;
                    crearCambioDeArma();
                    break;
                case SDLK_SPACE:
                    crearAperturaDePuerta();
                    //reproducir_sonido(SONIDO_DE_PUERTA, REPETICION_PUERTA);
                    break;
            }
            break;
        case SDL_KEYUP:
            if (evento.key.keysym.sym == SDLK_PERIOD) {
                // dejo de disparar;
                // sonido.stop()
            }
            break;

        default:
            break;
    }
}

void ManejadorEventos::stop() {
    this->corriendo = false;
}

bool ManejadorEventos::esta_vivo() {
    return this->corriendo;
}
