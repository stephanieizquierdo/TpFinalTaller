#ifndef WOLFSTEIN_LABEL_H
#define WOLFSTEIN_LABEL_H

#include "fonts.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

class Label {
public:
    Label(int xpos, int ypos, std::string text, TTF_Font *font, SDL_Color &color, SDL_Renderer *renderer);

    void setLabelText();

    void actualizarTexto(std::string texto);

    void draw();

    ~Label();

private:
    SDL_Rect pos;
    std::string label;
    TTF_Font *font;
    SDL_Color textColor;
    SDL_Texture *labelTexture;
    SDL_Renderer *renderer;
};


#endif //WOLFSTEIN_LABEL_H