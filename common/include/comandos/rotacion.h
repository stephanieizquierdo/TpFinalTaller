#ifndef ROTACION_H
#define ROTACION_H

#include "comando.h"
#include "iserializable.h"

class Rotacion : public Comando, public ISerializable {

private:
    //Accion sentidoDeRotacion;
public:

    Rotacion(Accion sentidoDeRotacion) : sentidoDeRotacion(sentidoDeRotacion) {}

    std::vector<char> serializar() {
        std::vector<char> info;
        return info;
    }

    void deserializar(std::vector<char> serializado) {}

    void ejecutar(EstadoJuego &EstadoJuego) override {}

    ~Rotacion();
};

#endif