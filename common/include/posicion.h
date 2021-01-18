#ifndef POSICION_H
#define POSICION_H

class Jugador;
class Posicion{
  public:
    Posicion(int pixelesX,int pixelesY,float anguloDeVista):
    pixelesX(pixelesX),
    pixelesY(pixelesY),
    anguloDeVista(anguloDeVista){}
    ~Posicion(){}
    int distanciaA(Posicion &posicion);
    bool intersectaConMiAngulo(Posicion &otroJugador);
    void actualizar_posicion(int pixelesx, int pixelesy);
    int pixelesEnX();
    int pixelesEnY();
    float getAnguloDeVista(){ return this->anguloDeVista;}
    bool estaCerca(int& posx, int& posy);
    void rotar(float anguloRotacion);
  private:
    int pixelesX;
    int pixelesY;
    float anguloDeVista;
};

#endif
