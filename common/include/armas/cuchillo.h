#ifndef _CUCHILLO_H
#define _CUCHILLO_H

#include "arma.h"

class Cuchillo : public Arma {
public:
    Cuchillo();

    ~Cuchillo();

    void atacar(int distancia_a_pared, Jugador *jugador, std::map<int, Jugador *> &jugadores) override;

    bool esPistola() override;

private:
    int danio;
};

#endif
