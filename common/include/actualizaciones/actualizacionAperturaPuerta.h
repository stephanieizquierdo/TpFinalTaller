#ifndef ACTUALIZACION_PUERTA_H
#define ACTUALIZACION_PUERTA_H


#include <list>
#include "iserializable.h"
#include "ranking.h"
#include "actualizacion.h"
#include "puerta.h"

class ActualizacionAperturaPuerta : public Actualizacion {
public:
    ActualizacionAperturaPuerta(Puerta& puerta);
    ActualizacionAperturaPuerta(){}
    ~ActualizacionAperturaPuerta();

    std::vector<char> serializar() override;

    void deserializar(std::vector<char> &serializado) override;

    int obtenerId() override { return static_cast<int>(Accion::aperturaDePuerta); }

private:
    Puerta puerta;
};

#endif