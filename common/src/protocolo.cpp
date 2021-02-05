#include "../include/protocolo.h"

Protocolo::Protocolo(Socket socket) : socket(std::move(socket)) {}

Protocolo::~Protocolo() {};


void Protocolo::enviar(std::vector<char> &informacion) {
    unsigned int size = htonl(informacion.size());
    char number_str[4];
    memcpy(number_str, &size, 4);
    socket.enviar(number_str, 4);
    std::string buffer(informacion.begin(), informacion.end());
    socket.enviar(buffer.c_str(), buffer.size());
    std::cout << "termine de enviar";
}

std::stringstream Protocolo::recibir_aux() {
    char length_str[4];
    socket.recibir(length_str, 4);

    unsigned int *buf = (unsigned int *) length_str;
    unsigned int length = ntohl(*buf);

    char buffer[TAMANIO];
    std::stringstream informacion;
    unsigned int restante = length;
    unsigned int cant_recibidos = 0;
    while (restante > TAMANIO) {
        cant_recibidos = socket.recibir(buffer, TAMANIO);
        informacion.write(buffer, cant_recibidos);
        restante = restante - cant_recibidos;
    }
    if (restante > 0) {
        cant_recibidos = socket.recibir(buffer, restante);
        informacion.write(buffer, cant_recibidos);
    }
    return informacion;
}

std::vector<char> Protocolo::recibir() {
    std::string someString = recibir_aux().str();
    std::vector<char> informacion(someString.begin(), someString.end());
    return informacion;
}

Comando* Protocolo::deserializarComando(std::vector<char> &informacion) {

    if (informacion[1] == static_cast<int>(Accion::ataque)) {

        return new Ataque((int) informacion[0]);
    } else if (informacion[1] == static_cast<int>(Accion::aperturaDePuerta)) {
        return new AperturaDePuerta((int) informacion[0]);
    } else {
        Accion accion;
        if (informacion[1] == static_cast<int>(Accion::rotarDerecha)) {
            accion = Accion::rotarDerecha;
        } else if (informacion[1] == static_cast<int>(Accion::rotarIzquierda)) {
            accion = Accion::rotarIzquierda;
        } else if (informacion[1] == static_cast<int>(Accion::moverArriba)) {
            accion = Accion::moverArriba;
        } else {
            accion = Accion::moverAbajo;
        }
        int id = (int) informacion[0];
        return new Movimiento(id, accion);
    }
}


void Protocolo::cerrar() {
    this->socket.cerrar();
}
