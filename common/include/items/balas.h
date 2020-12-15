#ifndef BALAS_H
#define BALAS_H

#include "item.h"

class Balas : public Item {
public:
    Balas(Posicion &posicion): Item(posicion){}

    ~Balas();

    void obtenerBeneficio(Jugador *jugador) override;

private:
    int cant_balas;
};

#endif