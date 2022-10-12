#ifndef JOUEUR_H
#define JOUEUR_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "config.h"



typedef struct {
    SDL_Texture   * spriteSheet;
    SDL_Rect        frames,
                    nextFrame,
                    destination;
    int             nbFrames;
} Joueur_t;


Joueur_t * JoueurCreate(SDL_Renderer * renderer, int x, int y);

void JoueurDestroy(Joueur_t * joueur);

void JoueurFrameSuivante(Joueur_t * joueur);

void JoueurDisplay(SDL_Renderer * const renderer, Joueur_t * const joueur);

#endif //JOUEUR_H
