#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include "config.h"
#include "salle.h"
#include "manager.h"
#include "joueur.h"
#define FREE freeMemory(window, renderer)

void freeMemory(SDL_Window * window, SDL_Renderer * renderer){
	if (renderer != NULL){
		SDL_DestroyRenderer(renderer);
		renderer = NULL;
	}
	if (window != NULL){
		SDL_DestroyWindow(window);
		window = NULL;
	}
}

int main(int argc, char **argv) {
	(void)argc;
	(void)argv;


//===================== INIT ====================

	srand(time(0));

	/* Initialisation de la SDL  + gestion de l'échec possible */
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		SDL_Log("Error : SDL initialisation - %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}

	if (TTF_Init() != 0)
	{
		SDL_Log("Erreur d'initialisation TTF : %s\n", TTF_GetError());
		SDL_Quit();
		exit(EXIT_FAILURE);
	}
	
	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;

	window = SDL_CreateWindow("Super Smash Slime", 100, 100, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
	if (window == NULL) {
		SDL_Log("Error : SDL window creation - %s\n", SDL_GetError()); // échec de la création de la fenêtre
		FREE;
		SDL_Quit();                              // On referme la SDL       
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if(renderer == NULL){
		SDL_Log("Error : SDL renderer creation - %s\n", SDL_GetError());  // échec de la création du renderer
		FREE;
    	SDL_Quit();
    }

	IMG_Init(IMG_INIT_PNG);
	Salle_t ** salles;
	SalleCharger(renderer, &salles);
	

//==================== BOUCLE ====================

	SDL_bool program_on = SDL_TRUE;

	Page_t page = MENU;
	SDL_bool voir_entrainement = SDL_FALSE;
	unsigned int beginTrain, endTrain;

	int nbIterationMax;
	int nbRunMax;
	int idSalle;
	int sdlDelay;
	int fakeRun;


	while (program_on){

        switch (page){
            case MENU:
				ManagerMenu(renderer, &page, &voir_entrainement );
				if(page==MENU) program_on = SDL_FALSE;
                break;
            case JOUER:
				ManagerJouer(renderer, salles);
				page = MENU;
                break;
            case ENTRAINER:
				ManagerChargerParamsEntrainement(&nbIterationMax, &nbRunMax, &idSalle, &sdlDelay, &fakeRun);
				beginTrain = SDL_GetTicks();
				ManagerEntrainerIA(renderer, salles[idSalle], voir_entrainement, nbIterationMax, nbRunMax, idSalle, sdlDelay, fakeRun);
				endTrain = SDL_GetTicks();
				printf("%.3fs\n", (endTrain - beginTrain)/1000.0);
				page = MENU;
                break;
        }
	}
	
//==================== FIN ====================


	/* et on referme tout ce qu'on a ouvert en ordre inverse de la création */
	SalleDestroyAll(salles);
	IMG_Quit();
	FREE;
	TTF_Quit();
	SDL_Quit();

	return 0;
}

