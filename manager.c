#include <stdio.h>
#include <math.h>
#include "manager.h"
#include "joueur.h"
#include "IA.h"

int markov[NB_ROOM][NB_ROOM] = {
    {0, 33, 33, 33, 0, 0, 0, 0, 0, 0, 1},
    {0, 0, 12, 12, 16, 16, 16, 8, 8, 8, 4},
    {0, 12, 0, 12, 16, 16, 16, 8, 8, 8, 4},
    {0, 12, 12, 0, 16, 16, 16, 8, 8, 8, 4},
    {0, 7, 7, 7, 0, 6, 6, 17, 17, 17, 16},
    {0, 7, 7, 7, 6, 0, 6, 17, 17, 17, 16},
    {0, 7, 7, 7, 6, 6, 0, 17, 17, 17, 16},
    {0, 7, 7, 7, 10, 10, 10, 0, 15, 15, 19},
    {0, 7, 7, 7, 10, 10, 10, 15, 0, 15, 19},
    {0, 7, 7, 7, 10, 10, 10, 15, 15, 0, 19},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};

/*int markov[NB_ROOM][NB_ROOM] = {
	{0, 100},
	{100,0}
};*/

int ManagerProchaineSalle(int typeSalle) {
    int alpha = (rand() % 100) +1;
    int cumul = 0;
    int prochaineSalle = 0;

    for(int i = 0; i < NB_ROOM; i++) {
        cumul += markov[typeSalle][i];
        if(alpha <= cumul) {
            prochaineSalle = i;
            break;
        }
    }
    return prochaineSalle;
}


SDL_bool ManagerDeplacementJoueur(Joueur_t * joueur, Salle_t * salle, Direction_t direction, int * salleCourante, int * recompense) {
    int xMax, yMax, xMin, yMin;
    int xPorte =salle->destination.x + ((salle->destination.w/2)/(SIZE_TILE) * (SIZE_TILE));
    SDL_bool aChangeDeSalle = SDL_FALSE;

    if(xPorte == joueur->destination.x) {
        yMin = salle->destination.y;
        yMax = salle->destination.y + salle->destination.h - SIZE_TILE;
    }
    else {
        yMin = salle->destination.y + SIZE_TILE;
        yMax = salle->destination.y + salle->destination.h - 2*SIZE_TILE;
    }

    if((salle->destination.y + SIZE_TILE <= joueur->destination.y) && (joueur->destination.y <= salle->destination.y + salle->destination.h - 2*SIZE_TILE)) {
        xMin = salle->destination.x + SIZE_TILE;
        xMax = salle->destination.x + salle->destination.w - 2*SIZE_TILE;
    }
    else {
        xMin = xPorte;
        xMax = xPorte;
    }

    switch(direction) {
        case HAUT:
            joueur->destination.y = (joueur->destination.y - PLAYER_SPEED <= yMin)?yMin:joueur->destination.y - PLAYER_SPEED;
            joueur->nextFrame.y = (joueur->frames.h)/2;
            if(joueur->destination.y <= salle->destination.y && (salle->nbObjectifsVivants == 0)) {
                if (salleCourante != NULL){
                    *salleCourante = ManagerProchaineSalle(*salleCourante);
                }
                if(recompense != NULL)
                    *recompense += RECOMPENSE_FIN;
                aChangeDeSalle = SDL_TRUE;
            }
            break;
        case BAS:
            joueur->destination.y = (joueur->destination.y + PLAYER_SPEED >= yMax)?yMax:joueur->destination.y + PLAYER_SPEED;
            joueur->nextFrame.y = 0;
            break;
        case GAUCHE:
            joueur->destination.x = (joueur->destination.x - PLAYER_SPEED <= xMin)?xMin:joueur->destination.x - PLAYER_SPEED;
            joueur->nextFrame.y = 3*(joueur->frames.h)/4;
            break;
        case DROITE:
            joueur->destination.x = (joueur->destination.x + PLAYER_SPEED >= xMax)?xMax:joueur->destination.x + PLAYER_SPEED;
            joueur->nextFrame.y = (joueur->frames.h)/4;
            break;
        default:
            joueur->nextFrame.x = 0;
            break;
    }

    ManagerKillEnemies(joueur, salle, recompense);

    return aChangeDeSalle;
}


void ManagerDeplacementEnnemi(Entite_t * ennemi) {
    ennemi->etapeCourante = (ennemi->etapeCourante + 1) % ennemi->nbEtapes;
    ennemi->destination.x = (ennemi->etapes)[ennemi->etapeCourante].x;
    ennemi->destination.y = (ennemi->etapes)[ennemi->etapeCourante].y;
}


void ManagerDeplacementEntites(Entite_t ** entites, int nbEntites) {
	for (int i= 0; i<nbEntites; i++){
		if (entites[i]->etat == VIVANT){
			entites[i]->etapeCourante = (entites[i]->etapeCourante + 1) % entites[i]->nbEtapes;
			entites[i]->destination.x = (entites[i]->etapes)[entites[i]->etapeCourante].x;
			entites[i]->destination.y = (entites[i]->etapes)[entites[i]->etapeCourante].y;
		}
	}
}


void ManagerKillEnemies(Joueur_t * joueur, Salle_t * salle, int * recompense) {
    SDL_Rect intersect;
    for(int i = 0; i < salle->nbEntites; i++) {
        if((salle->entites)[i]->etat == VIVANT && SDL_IntersectRect(&(joueur->destination), &((salle->entites)[i]->destination), &intersect)) {
			switch ((salle->entites)[i]->type){
				case SLIME_V:
                    if(recompense != NULL) {
                        *recompense += RECOMPENSE_SLIME;
                    }
            		(salle->entites)[i]->etat = MORT;
            		salle->nbObjectifsVivants--;
					break;
				case SLIME_R:
					joueur->destination.x = salle->spawn.x;
					joueur->destination.y = salle->spawn.y;
					break;
			}
        }
    }
}


void ManagerAffichageVictoire(SDL_Renderer * renderer) {
    SDL_Texture * texture = IMG_LoadTexture(renderer, "assets/VictoryScreen/Pikatchoum.png");
    SDL_Rect dimTextures;
    SDL_Rect destination;

    SDL_QueryTexture(texture, NULL, NULL, &dimTextures.w, &dimTextures.h);

    destination.w = dimTextures.w * ZOOM;
    destination.h = dimTextures.h * ZOOM;
    destination.x = SCREEN_WIDTH - destination.w;
    destination.y = SCREEN_HEIGHT - destination.h;

    SDL_RenderCopy(renderer, texture, NULL, &destination);
    SDL_DestroyTexture(texture);
}

void ManagerGestionInputs(SDL_bool *cont, Direction_t *direction, Bouton_t * bouton, Bouton_t * hoveredButton){
    if(bouton != NULL)
        *bouton = BOUTON_AUCUN;  
    SDL_Event event;
    while (SDL_PollEvent(&event)){               
        switch(event.type){
        case SDL_KEYDOWN:
            switch(event.key.keysym.sym){
                case SDLK_ESCAPE:
                    *cont = SDL_FALSE;
                    break;
                case SDLK_UP:
                case SDLK_z:
                    *direction = HAUT;
                    break;
                case SDLK_DOWN:
                case SDLK_s:
                    *direction = BAS;
                    break;
                case SDLK_LEFT:
                case SDLK_q:
                    *direction = GAUCHE;
                    break;
                case SDLK_RIGHT:
                case SDLK_d:
                    *direction = DROITE;
                    break;
                default:
                    break;
            }
            break;
        case SDL_MOUSEMOTION:
            if(hoveredButton != NULL)
                *hoveredButton = ManagerDetecterBouton(event.motion.x, event.motion.y);
            break;
        case SDL_MOUSEBUTTONUP:
            if (bouton != NULL)
                *bouton = ManagerDetecterBouton(event.button.x, event.button.y);
            break;
        case SDL_QUIT :        
            *cont = SDL_FALSE;                 
            break;
        default:                                  
            break;
        }
    }
}


void ManagerResetSalle(Joueur_t * joueur, Salle_t * salle) {
    joueur->destination.x = salle->spawn.x;
    joueur->destination.y = salle->spawn.y;
    for(int i = 0; i < salle->nbEntites; i++) {
        (salle->entites)[i]->etat = VIVANT;
        (salle->entites)[i]->etapeCourante = 0;
        (salle->entites)[i]->destination.x 	= ((salle->entites)[i]->etapes)[0].x;
        (salle->entites)[i]->destination.y = ((salle->entites)[i]->etapes)[0].y;
    }
    salle->nbObjectifsVivants = salle->nbObjectifs;
}


void ManagerJouer(SDL_Renderer * renderer, Salle_t **salles){
    SDL_bool changementSalle;
	int salleCourante = 0;
	SDL_bool jouer_on = SDL_TRUE;
    Direction_t direction = AUCUNE;
    int deplacementIteration = 0;
    SDL_bool game_over = SDL_FALSE;
    Joueur_t * joueur = JoueurCreate(renderer, salles[0]->spawn.x, salles[0]->spawn.y);

	while (jouer_on){
        ManagerGestionInputs(&jouer_on, &direction, NULL, NULL);

        if(! game_over) {
            (deplacementIteration)++;
            (deplacementIteration) %= 4;
            if (deplacementIteration == 0){
                ManagerDeplacementEntites(salles[salleCourante]->entites, salles[salleCourante]->nbEntites);
                changementSalle = ManagerDeplacementJoueur(joueur, salles[salleCourante], direction, &salleCourante, NULL);
                if (changementSalle) {
                    ManagerResetSalle(joueur, salles[salleCourante]);
                }
                direction = AUCUNE;            
            }

            SDL_RenderClear(renderer);
            SalleDisplay(renderer, salles[salleCourante]);	
            JoueurDisplay(renderer, joueur);
            if(salleCourante == 10 && salles[salleCourante]->nbObjectifsVivants == 0){ 
                game_over = SDL_TRUE;
            }
        
        }
        else {
            SDL_RenderClear(renderer);
            SalleDisplay(renderer, salles[salleCourante]);	
            JoueurDisplay(renderer, joueur);
            ManagerAffichageVictoire(renderer);
        }

        SDL_RenderPresent(renderer);
		SDL_Delay(100);
    }

    JoueurDestroy(joueur);
}

void ManagerMenu(SDL_Renderer * renderer, Page_t * page, SDL_bool * voir_entrainement){
    TTF_Font * font = TTF_OpenFont("assets/Fonts/HWYGOTH.TTF", 72);
    SDL_Texture * textureFond = IMG_LoadTexture(renderer, "assets/Menu/Menu.png");
    SDL_Texture * textureFond2 = IMG_LoadTexture(renderer, "assets/Menu/Menu2.png");
    SDL_Surface * surface = NULL;
    surface = TTF_RenderText_Blended(font, "Super Smash Slime", (SDL_Color){0, 0, 0, 255});
    SDL_Texture * textureTitre = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    surface = TTF_RenderText_Blended(font, "  Jouer  ", (SDL_Color){0, 0, 0, 255});
    SDL_Texture * textureBoutonJouer = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    surface = TTF_RenderText_Blended(font, "Entrainer", (SDL_Color){0, 0, 0, 255});
    SDL_Texture * textureBoutonEntrainer = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    surface = TTF_RenderText_Blended(font, "Voir", (SDL_Color){0, 0, 0, 255});
    SDL_Texture * textureBoutonVoir = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    TTF_CloseFont(font);

    Bouton_t hoveredButton;
    SDL_bool menuFrame;
    int nbFrames = 0;

    SDL_bool menu_on = SDL_TRUE;
    Bouton_t bouton = BOUTON_AUCUN;
    while (menu_on){
        bouton = BOUTON_AUCUN;
        ManagerGestionInputs(&menu_on, NULL, &bouton, &hoveredButton);
        switch(bouton) {
            case BOUTON_JOUER:
                * page = JOUER;
                menu_on = SDL_FALSE;
                break;
            case BOUTON_ENTRAINER:
                *page = ENTRAINER;
                menu_on = SDL_FALSE;
                break;
            case BOUTON_VOIR:
                *voir_entrainement = ! *voir_entrainement;
                break;
            case BOUTON_AUCUN:
                break;
        }

        nbFrames++;
        nbFrames %= 50;
        if(nbFrames == 0)
            menuFrame = !menuFrame;
        if(menuFrame)
            ManagerDisplayMenu(renderer, *voir_entrainement, textureFond, textureTitre, textureBoutonJouer, textureBoutonEntrainer, textureBoutonVoir, &hoveredButton);
        else
            ManagerDisplayMenu(renderer, *voir_entrainement, textureFond2, textureTitre, textureBoutonJouer, textureBoutonEntrainer, textureBoutonVoir, &hoveredButton);
        SDL_RenderPresent(renderer);
		SDL_Delay(10);
    }
    SDL_DestroyTexture(textureBoutonVoir);
    SDL_DestroyTexture(textureBoutonEntrainer);
    SDL_DestroyTexture(textureBoutonJouer);
    SDL_DestroyTexture(textureTitre);
    SDL_DestroyTexture(textureFond2);
    SDL_DestroyTexture(textureFond);
}


void ManagerDisplayMenu(SDL_Renderer * renderer, SDL_bool voir_entrainement, SDL_Texture * textureFond, SDL_Texture * textureTitre, SDL_Texture * textureJouer, SDL_Texture * textureEntrainer, SDL_Texture * textureVoir, Bouton_t * hoveredButton) {
    SDL_Rect rect1 = {0};
    SDL_Rect rect2 = {0};
    
    SDL_Color couleur = {0, 0, 0, 255};

    // Affichage le fond
    SDL_RenderCopy(renderer, textureFond, NULL, NULL);
    

    // Affichage du titre
    rect1.x = SCREEN_WIDTH/4;
    rect1.w = SCREEN_WIDTH - 2*rect1.x;
    rect1.y = rect1.h = SCREEN_HEIGHT/10;
    SDL_RenderCopy(renderer, textureTitre, NULL, &rect1);
    

    // Affichage bouton Jouer
    couleur = (*hoveredButton == BOUTON_JOUER)?(SDL_Color){110, 110, 110, 255}:(SDL_Color){150, 150, 150, 255};
    rect1.y = SCREEN_HEIGHT/2 - rect1.h;
    rect1.h = SCREEN_HEIGHT/15;
    SDL_SetRenderDrawColor(renderer, couleur.r, couleur.g, couleur.b, couleur.a);
    SDL_RenderFillRect(renderer, &rect1);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderDrawRect(renderer, &rect1);

    rect2.x = rect1.x + rect1.w/3;
    rect2.w = rect1.w - 2*(rect2.x - rect1.x);
    rect2.y = rect1.y;
    rect2.h = rect1.h;
    
    SDL_RenderCopy(renderer, textureJouer, NULL, &rect2);

    //Affichage bouton Entrainer
    couleur = (*hoveredButton == BOUTON_ENTRAINER)?(SDL_Color){110, 110, 110, 255}:(SDL_Color){150, 150, 150, 255};
    rect1.y = SCREEN_HEIGHT/2 + rect1.h;
    SDL_SetRenderDrawColor(renderer, couleur.r, couleur.g, couleur.b, couleur.a);
    SDL_RenderFillRect(renderer, &rect1);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderDrawRect(renderer, &rect1);

    rect2.x = rect1.x + rect1.w/3;
    rect2.w = rect1.w - 2*(rect2.x - rect1.x);
    rect2.y = rect1.y;
    rect2.h = rect1.h;
    
    SDL_RenderCopy(renderer, textureEntrainer, NULL, &rect2);


    // Afficher bouton Voir
    couleur = (voir_entrainement)?((*hoveredButton == BOUTON_VOIR)?(SDL_Color){0, 200, 0, 255}:(SDL_Color){0, 255, 0, 255}):((*hoveredButton == BOUTON_VOIR)?(SDL_Color){200, 0, 0, 255}:(SDL_Color){255, 0, 0, 255});
    rect1.x = rect1.x + rect1.w + rect1.h;
    rect1.w = rect1.h;
    SDL_SetRenderDrawColor(renderer, couleur.r, couleur.g, couleur.b, couleur.a);
    rect1.y = SCREEN_HEIGHT/2 + rect1.h;
    SDL_RenderFillRect(renderer, &rect1);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderDrawRect(renderer, &rect1);

    couleur = (SDL_Color){0, 0, 0, 255};
    rect2.w = rect1.w;
    rect2.x = rect1.x;
    rect2.y = rect1.y + rect1.h;
    rect2.h = rect1.h/2;
    
    SDL_RenderCopy(renderer, textureVoir, NULL, &rect2);
}

Bouton_t ManagerDetecterBouton(Sint32 x, Sint32 y) {
    Bouton_t bouton = BOUTON_AUCUN;

    if((4*SCREEN_HEIGHT/10) < y && y < (7*SCREEN_HEIGHT/15)) { // y du bouton Jouer
        if((SCREEN_WIDTH/4) < x && x < (3*SCREEN_WIDTH/4))
            bouton = BOUTON_JOUER;
    }
    else if(17*SCREEN_HEIGHT/30 < y && y < 19*SCREEN_HEIGHT/30) { // y des boutons Entrainer et Voir
        if((SCREEN_WIDTH/4) < x && x < (3*SCREEN_WIDTH/4)) {
            bouton = BOUTON_ENTRAINER;
        }
        else if((3*SCREEN_WIDTH/4 + SCREEN_HEIGHT/15) < x && x < (3*SCREEN_WIDTH/4 + 2*SCREEN_HEIGHT/15)){
            bouton = BOUTON_VOIR;
        }
    }
    return bouton;
}

void ManagerEntrainerIA(SDL_Renderer * renderer, Salle_t *salle, SDL_bool voir_entrainement, int nbIterationMax, int nbRunMax, int idSalle, int sdlDelay, int fakeRun){
    char nomFichier[30];
    SDL_bool IA_on = SDL_TRUE;
    int nbRun = 1;
	if (fakeRun){
		sprintf(nomFichier,"QTables/QTable_fakeRun");
	}
	else{
		sprintf(nomFichier, "QTables/QTable_Salle_%d", idSalle);
	}
    float ** qtableA = IAChargerUneQTable(nomFichier);
    float ** qtableB = IAChargerUneQTable(nomFichier);
    
    float ** qtableAdditionnee = (float**)malloc(NB_ETATS*sizeof(float**));
    for(int i = 0; i < NB_ETATS; i++) {
            qtableAdditionnee[i] = (float*)malloc(5*sizeof(float));
    }

    int TailleRun = 0;
    Iteration_t *run = (Iteration_t*)malloc(nbIterationMax* sizeof(Iteration_t));
    Joueur_t * joueur = JoueurCreate(renderer, salle->spawn.x, salle->spawn.y+SIZE_TILE);
    while (nbRun <= nbRunMax && IA_on){
        memset(run,0,nbIterationMax*sizeof(Iteration_t));

        ManagerResetSalle(joueur, salle);
        (joueur->destination.y)+=SIZE_TILE;

        if (fakeRun) fprintf(stderr, "===============RUN N° %d / %d===============\n\n", nbRun, nbRunMax);
        if (nbRun % 1000 == 0) printf("%d / %d\n", nbRun, nbRunMax);
        if (nbRun == nbRunMax) {
			printf("Appuyez sur ENTER pour voir la derniere run !\n");
            getchar();
            voir_entrainement = SDL_TRUE;
        }

        ManagerAdditionQtable(qtableAdditionnee, qtableA , qtableB);

        TailleRun = IARun(renderer, qtableAdditionnee, salle, run, ManagerNewEps(nbRun, nbRunMax), voir_entrainement, joueur, nbIterationMax, sdlDelay, fakeRun);

        IARenforcement(run, TailleRun, qtableA , qtableB);

        ManagerGestionInputs(&IA_on, NULL, NULL, NULL);

        nbRun++;
    }


    fprintf(stdout, "Fini !\n");


    ManagerAdditionQtable(qtableAdditionnee, qtableA , qtableB);

    for(int i = 0; i < NB_ETATS; i++){
        for(int j =0; j<5; j++){
            qtableAdditionnee[i][j] /= 2.0;
        }
    }


    if (!fakeRun) IASauvegarderUneQTable(qtableAdditionnee, nomFichier);

    IALibererUneQTable(qtableA);
    IALibererUneQTable(qtableB);
    IALibererUneQTable(qtableAdditionnee);
    free(run);
    JoueurDestroy(joueur);
}

float ManagerNewEps(int nbRun, int nbRunMax){
    return exp(-10*nbRun/(float)nbRunMax);
    //return fmin(1.0 , 2.0 - (2.0 * (float)nbRun)/(float)nbRunMax);
    //return 1 - exp(10*(nbRun)/(float)nbRunMax - 10);
}

void ManagerChargerParamsEntrainement(int *nbIterationMax, int *nbRunMax, int *salleEntrainement, int *sdlDelay, int *fakeRun){
    printf("\n\n\n\n\n\n\n\n");
    printf("=========================================\n");
    printf("===============NEW SESSION===============\n");
    printf("=========================================\n");
	do{
		printf("nbIterationMax :");
		scanf("%d%*c", nbIterationMax);
	} while (*nbIterationMax <= 0);
	do{
		printf("nbRunMax :");
		scanf("%d%*c", nbRunMax);
	} while (*nbRunMax <= 0);
	do{
		printf("salleEntrainement :");
		scanf("%d%*c", salleEntrainement);
	} while (*salleEntrainement < 0 || 10 < *salleEntrainement );
	do{
		printf("Delay SDL :");
		scanf("%d%*c", sdlDelay);
	} while (*sdlDelay < 0 );
	do{
		printf("FakeRun (pas sauvegarde + Default qtable +debug) :");
		scanf("%d%*c", fakeRun);
	} while (*fakeRun != 0 && *fakeRun != 1);
	
}

void ManagerAdditionQtable(float ** qtableAdditionnee, float ** qtableA ,float ** qtableB){
    for(int i = 0; i < NB_ETATS; i++){
        for(int j =0; j<5; j++){
            qtableAdditionnee[i][j]= qtableA[i][j] + qtableB[i][j];
        }
    }
}
