#include "joueur.h"
#include <stdlib.h>


Joueur_t * JoueurCreate(SDL_Renderer * renderer, int x, int y) {
    Joueur_t * joueur = NULL;
    SDL_Texture * spriteSheet = NULL;
    int nbFrames = 0;

    joueur = (Joueur_t *)malloc(sizeof(Joueur_t));

	spriteSheet = IMG_LoadTexture(renderer, "assets/Player/Character.png");
	joueur->nextFrame = (SDL_Rect){0, 32, 16, 16};
	nbFrames = 4;

    joueur->frames.x = joueur->frames.y = 0;
    SDL_QueryTexture(spriteSheet, NULL, NULL, &(joueur->frames.w), &(joueur->frames.h));


    joueur->spriteSheet = spriteSheet;
    joueur->nbFrames = nbFrames;

    joueur->destination = (SDL_Rect){x, y, joueur->nextFrame.w*ZOOM, joueur->nextFrame.h*ZOOM};
    
	return joueur;
}



void JoueurDestroy(Joueur_t * joueur) {
    SDL_DestroyTexture(joueur->spriteSheet);
    free(joueur);
}


void JoueurFrameSuivante(Joueur_t * joueur) {
    joueur->nextFrame.x = (joueur->nextFrame.x + joueur->nextFrame.w) % joueur->frames.w;
}


void JoueurDisplay(SDL_Renderer * const renderer, Joueur_t * const joueur) {
	SDL_RenderCopy(renderer, joueur->spriteSheet, &(joueur->nextFrame), &(joueur->destination));
    //JoueurFrameSuivante(joueur);
}

