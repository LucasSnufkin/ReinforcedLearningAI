#include "entite.h"
#include <stdlib.h>


Entite_t * EntiteCreate(SDL_Renderer * renderer, Type_t type, Pos_t * etapes, int etapeCourante, int nbEtapes) {
    Entite_t * entite = NULL;
    SDL_Texture * spriteSheet = NULL;
    int nbFrames = 0;

    entite = (Entite_t *)malloc(sizeof(Entite_t));

    entite->type = type;
    entite->etat = VIVANT;
    switch(type) {
        case SLIME_V:
            spriteSheet = IMG_LoadTexture(renderer, "assets/ThreeBasicSlimes/GreenSlimeMove.png");
            entite->nextFrame = (SDL_Rect){0, 0, 16, 16};
            nbFrames = 8;
            break;
        case SLIME_R:
            spriteSheet = IMG_LoadTexture(renderer, "assets/ThreeBasicSlimes/RedSlimeMove.png");
            entite->nextFrame = (SDL_Rect){0, 0, 16, 16};
            nbFrames = 8;
            break;
        default:
            break;
    }

    entite->frames.x = entite->frames.y = 0;
    SDL_QueryTexture(spriteSheet, NULL, NULL, &(entite->frames.w), &(entite->frames.h));


    entite->spriteSheet = spriteSheet;
    entite->nbFrames = nbFrames;
	entite->etapes = etapes;
	entite->etapeCourante = etapeCourante;
	entite->nbEtapes = nbEtapes;

    entite->destination = (SDL_Rect){(entite->etapes)[etapeCourante].x, (entite->etapes)[etapeCourante].y, entite->nextFrame.w*ZOOM, entite->nextFrame.h*ZOOM};
    
	return entite;
}



void EntiteDestroy(Entite_t * entite) {
    SDL_DestroyTexture(entite->spriteSheet);
	free(entite->etapes);
    free(entite);
}


void EntiteFrameSuivante(Entite_t * entite) {
    entite->nextFrame.x = (entite->nextFrame.x + entite->nextFrame.w) % entite->frames.w;
}


void EntiteDisplay(SDL_Renderer * const renderer, Entite_t * const entite) {
    if(entite->etat == VIVANT) {
        SDL_RenderCopy(renderer, entite->spriteSheet, &(entite->nextFrame), &(entite->destination));
        EntiteFrameSuivante(entite);
    }
}

