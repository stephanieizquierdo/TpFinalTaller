#ifndef _PROTOCOLO_H
#define _PROTOCOLO_H


#include "socket.h"

#include "comandos/ataque.h"
#include "comandos/movimiento.h"
#include "comandos/aperturaDePuerta.h"
#include <iostream>

#define TAMANIO 100

class Protocolo {
public:
    Protocolo(Socket socket) : socket(std::move(socket)) {}

    ~Protocolo() {};

    void enviar(std::vector<char> &informacion) {
        std::string buffer(informacion.begin(), informacion.end());
        std::string tamanio;
        tamanio.push_back(informacion.size());
        socket.enviar(tamanio.c_str(),1);
        socket.enviar(buffer.c_str(), buffer.size());
        std::cout << "termine de enviar";
    }

    std::stringstream recibir_aux() {
        char tam[1];
        char buffer[TAMANIO];
        std::stringstream informacion;
        int cant_recibidos = socket.recibir(tam, 1);
        int cant_a_recibir = tam[0];
        cant_recibidos = 0;
        while (cant_recibidos < cant_a_recibir) {
            informacion.write(buffer, cant_recibidos);
            cant_recibidos += socket.recibir(buffer, TAMANIO);
        }
        return informacion;
    }

    std::vector<char> recibir() {
        std::string someString = recibir_aux().str();
        std::vector<char> informacion(someString.begin(), someString.end());
        return informacion;
    }

    Comando *deserializarComando(std::vector<char> &informacion) {

        if (informacion[1] == static_cast<int>(Accion::ataque)) {

            return new Ataque((int)informacion[0]);
        } else if (informacion[1] == static_cast<int>(Accion::aperturaDePuerta)){
            return new AperturaDePuerta((int)informacion[0]);
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
            int id = (int)informacion[0];
            return new Movimiento(id, accion);
        }
    }

    Protocolo& operator=(Protocolo& protocolo){
      if (this == &protocolo){
        return *this;
      }
      this->socket = std::move(protocolo.socket);
      return *this;
    }

    void cerrar(){
      this->socket.cerrar();
    }


private:
    Socket socket;
};

#endif
