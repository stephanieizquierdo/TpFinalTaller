#include "../include/contenedorDeElementos.h"
#include <iostream>

void ContenedorDeElementos::aniadirPuerta(Puerta &puerta) {
    this->puertas.push_back(puerta);
}

std::vector<char> ContenedorDeElementos::serializar() {
    std::vector<char> informacion;
    std::vector<char> aux(4);
    aux = numberToCharArray(elementos.size());
    informacion.insert(informacion.end(), aux.begin(), aux.end());
    for (auto &elemento : elementos) {
        std::vector<char> itemSerializado = ((Item *) elemento)->serializar();
        aux = numberToCharArray(itemSerializado.size());
        informacion.insert(informacion.end(), aux.begin(), aux.end());
        informacion.insert(informacion.end(), itemSerializado.begin(),
                           itemSerializado.end());
    }
    std::vector<char> aux2(4);
    aux2 = numberToCharArray(puertas.size());
    informacion.insert(informacion.end(), aux2.begin(), aux2.end());
    for (auto &puerta: puertas){
        std::vector<char> puertaSerializada = puerta.serializar();
        aux2 = numberToCharArray(puertaSerializada.size());
        informacion.insert(informacion.end(), aux2.begin(), aux2.end());
        informacion.insert(informacion.end(), puertaSerializada.begin(),
                           puertaSerializada.end());
    }
    return informacion;
}


Item *deserializarItem(std::vector<char> &informacion) {
//    std::cerr << "informacion size" << informacion.size()<<std::endl;

    std::vector<char> sub(4);
    int idx = 0;
    sub = std::vector<char>(&informacion[idx], &informacion[idx + 4]);
    char number[4];
    memcpy(number, sub.data(), 4);
    uint32_t *buf = (uint32_t *) number;
    int idTipo = ntohl(*buf);
//    std::cerr << "id tpo" << idTipo<<std::endl;
    Posicion posicion;
    std::vector<char> posicionSerializado(informacion.begin() + 4,
                                          informacion.end());
  //  std::cerr << "posicion size" << posicionSerializado.size()<<std::endl;
    posicion.deserializar(posicionSerializado);
    return new NoItem(posicion, idTipo);
}

Puerta deserializarPuerta(std::vector<char>& informacion){
    std::vector<char> sub(4);
    int idx = 0;
    sub = std::vector<char>(&informacion[idx], &informacion[idx + 4]);
    char number[4];
    memcpy(number, sub.data(), 4);
    uint32_t *buf = (uint32_t *) number;
    int fila = ntohl(*buf); //fila
    std::cerr << "puerta fila: " << fila << "\n";
    idx +=4;
    sub = std::vector<char>(&informacion[idx], &informacion[idx + 4]);
    char number2[4];
    memcpy(number2, sub.data(), 4);
    uint32_t *buf2 = (uint32_t *) number2;
    int columna = ntohl(*buf2); // colmuna
    std::cerr << "puerta columna: " << columna << "\n";
    idx +=4;
    sub = std::vector<char>(&informacion[idx], &informacion[idx + 4]);
    char number3[4];
    memcpy(number3, sub.data(), 4);
    uint32_t *buf3 = (uint32_t *) number3;
    bool abierta = ntohl(*buf3); // puerta esta abierta;
    std::cerr << "puerta abierta: " << abierta << "\n";
    idx +=4;
    Posicion posicion;
    std::vector<char> posicionSerializado(informacion.begin() + idx,
                                          informacion.end());
    posicion.deserializar(posicionSerializado);
    std::cerr << "puerta posx: " << posicion.pixelesEnX() << "\n";
    std::cerr << "puerta posy: " << posicion.pixelesEnY() << "\n";
    Puerta puerta(false, posicion,fila, columna, abierta);
    return puerta;
}

void ContenedorDeElementos::deserializar(std::vector<char> &serializado) {
    std::vector<char> sub(4);
    int idx = 0;
    sub = std::vector<char>(&serializado[idx], &serializado[idx + 4]);
    int elementosSize = charArrayToNumber(sub);
    idx += 4;
//    std::cerr << "size elementos: " <<elementosSize <<std::endl;
    for (int i = 0; i < elementosSize; i++) {
        sub = std::vector<char>(&serializado[idx], &serializado[idx + 4]);
        idx += 4;
        std::vector<char> itemSerializado(serializado.begin() + idx,
                                          serializado.begin() + idx + charArrayToNumber(sub));
        idx += charArrayToNumber(sub);
        Item *item = deserializarItem(itemSerializado);
    //    std::cerr << "fin item: " <<i <<std::endl;
        this->elementos.push_back(item);
    }
    sub = std::vector<char>(&serializado[idx], &serializado[idx + 4]);
    int puertaSize = charArrayToNumber(sub);
    idx +=4;
    for (int i = 0; i< puertaSize; i++){
        sub = std::vector<char>(&serializado[idx], &serializado[idx +4]);
        idx +=4;
        std::vector<char> puertaSerializada(serializado.begin() + idx,
                                            serializado.begin() + charArrayToNumber(sub));
        idx += charArrayToNumber(sub);
        Puerta puerta = deserializarPuerta(puertaSerializada);
        this->puertas.push_back(puerta);
    }
}

std::vector<Item *> &ContenedorDeElementos::obtenerItems() {
    return this->elementos;
}


Puerta &ContenedorDeElementos::puertaMasCercana(Posicion &posicionJugador,
                                                double &distancia) {
    int cantPuertas = this->puertas.size();
    int posPuertaMasCercana = 0;
    distancia = this->puertas[0].distanciaA(posicionJugador);
    for (int i = 1; i < cantPuertas; i++) {
        double distanciaParcial = this->puertas[i].distanciaA(posicionJugador);
        if (distanciaParcial < distancia) {
            distancia = distanciaParcial;
            posPuertaMasCercana = i;
        }
    }
    return this->puertas[posPuertaMasCercana];
}

void ContenedorDeElementos::agregarElemento(Item *item) {
    this->elementos.push_back(item);
}

void ContenedorDeElementos::sacarElementoDePosicion(Posicion &posicion) {
    std::vector<Item *> elementosFiltrados;
    for (int i = 0; i < this->elementos.size(); i++) {
        if (this->elementos[i]->obtenerPosicion() == posicion) {
            delete this->elementos[i];
        } else {
            elementosFiltrados.push_back(this->elementos[i]);
        }
    }
    this->elementos.swap(elementosFiltrados);
}

ContenedorDeElementos::ContenedorDeElementos() :
        elementos() {}

ContenedorDeElementos::~ContenedorDeElementos() {}

Item *ContenedorDeElementos::buscarElemento(int &posx, int &posy) {
    for (int i = 0; i < this->elementos.size(); i++) {
        if (this->elementos[i]->estaCerca(posx, posy)) {
            return this->elementos[i];
        }
    }
    return nullptr;
}

bool ContenedorDeElementos::hayPuertas() {
    return (this->puertas.size() > 0);
}

Puerta &ContenedorDeElementos::obtenerPuertaEn(int &fila, int &columna) {
    int cantidadDePuertas = this->puertas.size();
    int puertaEnPos = 0;
    for (int i = 0; i < cantidadDePuertas; i++) {
        if (this->puertas[i].estaEnPosDelMapa(fila, columna)) {
            puertaEnPos = i;
        }
    }
    return this->puertas[puertaEnPos];
}
