#include "../include/armaAnimada.h"

#define RUTAIMG "../../client/resources/images/Weapons.png"
#define SPRITES_W 64.55
#define SPRITES_H 65
#define FRAMES_X 5
#define FRAMES_Y 4
#define POSX 318
#define POSY 420
#define CONTADOR_INICIAL 10

#define ID_CUCHILLO 3
#define ID_PISTOLA 4
#define ID_AMETRALLADORA 1
#define ID_LANZACOHETES 5
#define ID_CANION_DE_CADENA 2

ArmaAnimada::ArmaAnimada(SDL_Renderer *render): contador(CONTADOR_INICIAL), atacando(false) {
    Sprite spriteCuchillo(render, RUTAIMG, 1, 0, SPRITES_H, SPRITES_W);
    Sprite spritePistola(render, RUTAIMG, 0, 1, SPRITES_H, SPRITES_W);
    Sprite spriteAmetralladora(render, RUTAIMG, 0, 2, SPRITES_H, SPRITES_W);
    Sprite spriteCanion(render, RUTAIMG, 0, 3, SPRITES_H, SPRITES_W);
    Animacion animacionCuchillo(render, RUTAIMG, FRAMES_X, SPRITES_H, SPRITES_W, 0, -1);
    Animacion animacionPistola(render, RUTAIMG, FRAMES_X, SPRITES_H, SPRITES_W, 1, -1);
    Animacion animacionAmetralladora(render, RUTAIMG, FRAMES_X, SPRITES_H, SPRITES_W, 2, -1);
    Animacion animacionCanion(render, RUTAIMG, FRAMES_X, SPRITES_H, SPRITES_W, 3, -1);
    this->sprites.insert(std::make_pair(ID_CUCHILLO, spriteCuchillo));
    this->sprites.insert(std::make_pair(ID_PISTOLA, spritePistola));
    this->sprites.insert(std::make_pair(ID_AMETRALLADORA, spriteAmetralladora));
    this->sprites.insert(std::make_pair(ID_CANION_DE_CADENA, spriteCanion));
    this->animaciones.insert(std::make_pair(ID_CUCHILLO, animacionCuchillo));
    this->animaciones.insert(std::make_pair(ID_PISTOLA, animacionPistola));
    this->animaciones.insert(std::make_pair(ID_AMETRALLADORA, animacionAmetralladora));
    this->animaciones.insert(std::make_pair(ID_CANION_DE_CADENA, animacionCanion));
    this->armaActual = ID_PISTOLA;
}

ArmaAnimada::~ArmaAnimada() {}

void ArmaAnimada::actualizar(int armaActual, bool estado) {
    this->armaActual = armaActual;
    this->atacando = estado;
}

void ArmaAnimada::renderizar() {

    //std::cerr << "arma: " << this->armaActual << "\n";
    if (this->atacando) {
        if(this->contador != 0){
            std::cerr << "entre";
            this->animaciones.find(this->armaActual)->second.renderizar(POSX, POSY, 0, NULL);
            this->contador--;
        } else {
            this->contador = CONTADOR_INICIAL;
            this->atacando = false;
        }
    } else {
        //this->sprites.find(this->armaActual)->second.reescalar(2, 2);
        this->sprites.find(this->armaActual)->second.renderizar(POSX, POSY, 0, NULL);
    }

}
