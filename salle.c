#include "salle.h"

void SalleDestroy(Salle_t * salle){
	SDL_DestroyTexture(salle->texture);
	for (int i=0; i<salle->nbEntites; i++){
		EntiteDestroy((salle->entites)[i]);
	}
	free(salle->entites);
	free(salle);
}

Salle_t* SalleCreate(SDL_Texture * texture, int id, int nbCellWidth, int nbCellHeight){
	

	Salle_t* salle = (Salle_t*)malloc(sizeof(Salle_t));
	salle->id = id;

	salle->nbCellWidth = nbCellWidth;
	salle->nbCellHeight = nbCellHeight;

	salle->texture = texture;

	SDL_Rect source = {0};
	SDL_QueryTexture(salle->texture, NULL, NULL, &source.w, &source.h);
	salle->destination.w = source.w*ZOOM;
	salle->destination.h = source.h*ZOOM;
	salle->destination.x = (SCREEN_WIDTH-salle->destination.w)/2;
	salle->destination.y = (SCREEN_HEIGHT-salle->destination.h)/2;
	
	salle->spawn.x = salle->destination.x + salle->destination.w/2 - SIZE_TILE/2;
	salle->spawn.y = salle->destination.y + salle->destination.h - SIZE_TILE;


	return salle;
}

void SalleDisplay(SDL_Renderer *renderer, Salle_t const * const salle){
	SDL_Rect source = {0};
	SDL_QueryTexture(salle->texture, NULL, NULL, &source.w, &source.h);
	SDL_RenderCopy(renderer, salle->texture, &source, &(salle->destination));

	for (int i=0 ; i<salle->nbEntites ; i++){
		if ((salle->entites)[i]->etat == VIVANT){
			EntiteDisplay(renderer, salle->entites[i]);
		}
	}
}

void SalleCharger(SDL_Renderer * renderer, Salle_t ***salles){
	*salles = (Salle_t**)malloc(NB_ROOM*sizeof(Salle_t*));
	SDL_Texture * texture;
	Entite_t ** entites;
	int nbEntites;
	Pos_t * etapes;
	int nbEtapes;
	int etapeCourante;

	//SALLE 0

	texture = IMG_LoadTexture(renderer, "assets/Salles/Salle_5x5_Grise.png");
	(*salles)[0] = SalleCreate(texture, 0, 5, 5);
	nbEntites = 0;
	
	(*salles)[0]->entites = NULL;
	(*salles)[0]->nbObjectifs= 0;
	(*salles)[0]->nbObjectifsVivants = 0;	
	(*salles)[0]->nbEntites = nbEntites;	


	//SALLE 1

	texture = IMG_LoadTexture(renderer, "assets/Salles/Salle_9x8_Rouge.png");
	(*salles)[1] = SalleCreate(texture, 1, 9, 8);
	nbEntites = 2;
	entites = (Entite_t**)malloc(nbEntites*sizeof(Entite_t*));

		//ENTITE 0
		nbEtapes = 8;
		etapes = (Pos_t*)malloc(nbEtapes*sizeof(Pos_t));
			etapes[0] = (Pos_t){(*salles)[1]->destination.x + 7*SIZE_TILE,(*salles)[1]->destination.y + 3*SIZE_TILE};
			etapes[1] = (Pos_t){(*salles)[1]->destination.x + 6*SIZE_TILE,(*salles)[1]->destination.y + 3*SIZE_TILE};
			etapes[2] = (Pos_t){(*salles)[1]->destination.x + 5*SIZE_TILE,(*salles)[1]->destination.y + 3*SIZE_TILE};
			etapes[3] = (Pos_t){(*salles)[1]->destination.x + 5*SIZE_TILE,(*salles)[1]->destination.y + 2*SIZE_TILE};
			etapes[4] = (Pos_t){(*salles)[1]->destination.x + 5*SIZE_TILE,(*salles)[1]->destination.y + 1*SIZE_TILE};
			etapes[5] = (Pos_t){(*salles)[1]->destination.x + 6*SIZE_TILE,(*salles)[1]->destination.y + 1*SIZE_TILE};
			etapes[6] = (Pos_t){(*salles)[1]->destination.x + 7*SIZE_TILE,(*salles)[1]->destination.y + 1*SIZE_TILE};
			etapes[7] = (Pos_t){(*salles)[1]->destination.x + 7*SIZE_TILE,(*salles)[1]->destination.y + 2*SIZE_TILE};
		etapeCourante = 0;
		entites[0] = EntiteCreate(renderer, SLIME_V, etapes, etapeCourante, nbEtapes);

		//ENTITE 1
		nbEtapes = 12;
		etapes = (Pos_t*)malloc(nbEtapes*sizeof(Pos_t));
			etapes[0] = (Pos_t){(*salles)[1]->destination.x + 2*SIZE_TILE,(*salles)[1]->destination.y + 4*SIZE_TILE};
			etapes[1] = (Pos_t){(*salles)[1]->destination.x + 3*SIZE_TILE,(*salles)[1]->destination.y + 4*SIZE_TILE};
			etapes[2] = (Pos_t){(*salles)[1]->destination.x + 4*SIZE_TILE,(*salles)[1]->destination.y + 4*SIZE_TILE};
			etapes[3] = (Pos_t){(*salles)[1]->destination.x + 5*SIZE_TILE,(*salles)[1]->destination.y + 4*SIZE_TILE};
			etapes[4] = (Pos_t){(*salles)[1]->destination.x + 6*SIZE_TILE,(*salles)[1]->destination.y + 4*SIZE_TILE};
			etapes[5] = (Pos_t){(*salles)[1]->destination.x + 7*SIZE_TILE,(*salles)[1]->destination.y + 4*SIZE_TILE};
			etapes[6] = (Pos_t){(*salles)[1]->destination.x + 6*SIZE_TILE,(*salles)[1]->destination.y + 4*SIZE_TILE};
			etapes[7] = (Pos_t){(*salles)[1]->destination.x + 5*SIZE_TILE,(*salles)[1]->destination.y + 4*SIZE_TILE};
			etapes[8] = (Pos_t){(*salles)[1]->destination.x + 4*SIZE_TILE,(*salles)[1]->destination.y + 4*SIZE_TILE};
			etapes[9] = (Pos_t){(*salles)[1]->destination.x + 3*SIZE_TILE,(*salles)[1]->destination.y + 4*SIZE_TILE};
			etapes[10] = (Pos_t){(*salles)[1]->destination.x + 2*SIZE_TILE,(*salles)[1]->destination.y + 4*SIZE_TILE};
			etapes[11] = (Pos_t){(*salles)[1]->destination.x + 1*SIZE_TILE,(*salles)[1]->destination.y + 4*SIZE_TILE};

		etapeCourante = 0;
		entites[1] = EntiteCreate(renderer, SLIME_R, etapes, etapeCourante, nbEtapes);


	(*salles)[1]->entites = entites;
	(*salles)[1]->nbObjectifs = 1;	
	(*salles)[1]->nbObjectifsVivants = 1;	
	(*salles)[1]->nbEntites = nbEntites;	
	//SALLE 2

	texture = IMG_LoadTexture(renderer, "assets/Salles/Salle_9x8_Bleu.png");
	(*salles)[2] = SalleCreate(texture, 2, 9, 8);
	nbEntites = 2;
	entites = (Entite_t**)malloc(nbEntites*sizeof(Entite_t*));

		//ENTITE 0
		nbEtapes = 4;
		etapes = (Pos_t*)malloc(nbEtapes*sizeof(Pos_t));
			etapes[0] = (Pos_t){(*salles)[2]->destination.x + 1*SIZE_TILE,(*salles)[2]->destination.y + 2*SIZE_TILE};
			etapes[1] = (Pos_t){(*salles)[2]->destination.x + 1*SIZE_TILE,(*salles)[2]->destination.y + 3*SIZE_TILE};
			etapes[2] = (Pos_t){(*salles)[2]->destination.x + 2*SIZE_TILE,(*salles)[2]->destination.y + 3*SIZE_TILE};
			etapes[3] = (Pos_t){(*salles)[2]->destination.x + 2*SIZE_TILE,(*salles)[2]->destination.y + 2*SIZE_TILE};
		etapeCourante = 0;
		entites[0] = EntiteCreate(renderer, SLIME_V, etapes, etapeCourante, nbEtapes);

		//ENTITE 1
		nbEtapes = 4;
		etapes = (Pos_t*)malloc(nbEtapes*sizeof(Pos_t));
			etapes[0] = (Pos_t){(*salles)[2]->destination.x + 7*SIZE_TILE,(*salles)[2]->destination.y + 3*SIZE_TILE};
			etapes[1] = (Pos_t){(*salles)[2]->destination.x + 7*SIZE_TILE,(*salles)[2]->destination.y + 2*SIZE_TILE};
			etapes[2] = (Pos_t){(*salles)[2]->destination.x + 6*SIZE_TILE,(*salles)[2]->destination.y + 2*SIZE_TILE};
			etapes[3] = (Pos_t){(*salles)[2]->destination.x + 6*SIZE_TILE,(*salles)[2]->destination.y + 3*SIZE_TILE};
		etapeCourante = 0;
		entites[1] = EntiteCreate(renderer, SLIME_V, etapes, etapeCourante, nbEtapes);


	(*salles)[2]->entites = entites;
	(*salles)[2]->nbObjectifs = 2;
	(*salles)[2]->nbObjectifsVivants = 2;	
	(*salles)[2]->nbEntites = nbEntites;


	//SALLE 3

	texture = IMG_LoadTexture(renderer, "assets/Salles/Salle_9x8_Jaune.png");
	(*salles)[3] = SalleCreate(texture, 3, 9, 8);
	nbEntites = 3;
	entites = (Entite_t**)malloc(nbEntites*sizeof(Entite_t*));

		//ENTITE 0
		nbEtapes = 6;
		etapes = (Pos_t*)malloc(nbEtapes*sizeof(Pos_t));
			etapes[0] = (Pos_t){(*salles)[3]->destination.x + 1*SIZE_TILE,(*salles)[3]->destination.y + 2*SIZE_TILE};
			etapes[1] = (Pos_t){(*salles)[3]->destination.x + 1*SIZE_TILE,(*salles)[3]->destination.y + 3*SIZE_TILE};
			etapes[2] = (Pos_t){(*salles)[3]->destination.x + 1*SIZE_TILE,(*salles)[3]->destination.y + 4*SIZE_TILE};
			etapes[3] = (Pos_t){(*salles)[3]->destination.x + 1*SIZE_TILE,(*salles)[3]->destination.y + 5*SIZE_TILE};
			etapes[4] = (Pos_t){(*salles)[3]->destination.x + 1*SIZE_TILE,(*salles)[3]->destination.y + 4*SIZE_TILE};
			etapes[5] = (Pos_t){(*salles)[3]->destination.x + 1*SIZE_TILE,(*salles)[3]->destination.y + 3*SIZE_TILE};
		etapeCourante = 0;
		entites[0] = EntiteCreate(renderer, SLIME_V, etapes, etapeCourante, nbEtapes);

		//ENTITE 1
		nbEtapes = 6;
		etapes = (Pos_t*)malloc(nbEtapes*sizeof(Pos_t));
			etapes[0] = (Pos_t){(*salles)[3]->destination.x + 7*SIZE_TILE,(*salles)[3]->destination.y + 5*SIZE_TILE};
			etapes[1] = (Pos_t){(*salles)[3]->destination.x + 7*SIZE_TILE,(*salles)[3]->destination.y + 4*SIZE_TILE};
			etapes[2] = (Pos_t){(*salles)[3]->destination.x + 7*SIZE_TILE,(*salles)[3]->destination.y + 3*SIZE_TILE};
			etapes[3] = (Pos_t){(*salles)[3]->destination.x + 7*SIZE_TILE,(*salles)[3]->destination.y + 2*SIZE_TILE};
			etapes[4] = (Pos_t){(*salles)[3]->destination.x + 7*SIZE_TILE,(*salles)[3]->destination.y + 3*SIZE_TILE};
			etapes[5] = (Pos_t){(*salles)[3]->destination.x + 7*SIZE_TILE,(*salles)[3]->destination.y + 4*SIZE_TILE};
			
		etapeCourante = 3;
		entites[1] = EntiteCreate(renderer, SLIME_V, etapes, etapeCourante, nbEtapes);
		
		//ENTITE 2
		nbEtapes = 38;
		etapes = (Pos_t*)malloc(nbEtapes*sizeof(Pos_t));
			etapes[0] = (Pos_t){(*salles)[3]->destination.x + 2*SIZE_TILE,(*salles)[3]->destination.y + 5*SIZE_TILE};
			etapes[1] = (Pos_t){(*salles)[3]->destination.x + 2*SIZE_TILE,(*salles)[3]->destination.y + 4*SIZE_TILE};
			etapes[2] = (Pos_t){(*salles)[3]->destination.x + 2*SIZE_TILE,(*salles)[3]->destination.y + 3*SIZE_TILE};
			etapes[3] = (Pos_t){(*salles)[3]->destination.x + 2*SIZE_TILE,(*salles)[3]->destination.y + 2*SIZE_TILE};
			etapes[4] = (Pos_t){(*salles)[3]->destination.x + 3*SIZE_TILE,(*salles)[3]->destination.y + 2*SIZE_TILE};
			etapes[5] = (Pos_t){(*salles)[3]->destination.x + 3*SIZE_TILE,(*salles)[3]->destination.y + 3*SIZE_TILE};
			etapes[6] = (Pos_t){(*salles)[3]->destination.x + 3*SIZE_TILE,(*salles)[3]->destination.y + 4*SIZE_TILE};
			etapes[7] = (Pos_t){(*salles)[3]->destination.x + 3*SIZE_TILE,(*salles)[3]->destination.y + 5*SIZE_TILE};
			etapes[8] = (Pos_t){(*salles)[3]->destination.x + 4*SIZE_TILE,(*salles)[3]->destination.y + 5*SIZE_TILE};
			etapes[9] = (Pos_t){(*salles)[3]->destination.x + 4*SIZE_TILE,(*salles)[3]->destination.y + 4*SIZE_TILE};
			etapes[10] = (Pos_t){(*salles)[3]->destination.x + 4*SIZE_TILE,(*salles)[3]->destination.y + 3*SIZE_TILE};
			etapes[11] = (Pos_t){(*salles)[3]->destination.x + 4*SIZE_TILE,(*salles)[3]->destination.y + 2*SIZE_TILE};
			etapes[12] = (Pos_t){(*salles)[3]->destination.x + 5*SIZE_TILE,(*salles)[3]->destination.y + 2*SIZE_TILE};
			etapes[13] = (Pos_t){(*salles)[3]->destination.x + 5*SIZE_TILE,(*salles)[3]->destination.y + 3*SIZE_TILE};
			etapes[14] = (Pos_t){(*salles)[3]->destination.x + 5*SIZE_TILE,(*salles)[3]->destination.y + 4*SIZE_TILE};
			etapes[15] = (Pos_t){(*salles)[3]->destination.x + 5*SIZE_TILE,(*salles)[3]->destination.y + 5*SIZE_TILE};
			etapes[16] = (Pos_t){(*salles)[3]->destination.x + 6*SIZE_TILE,(*salles)[3]->destination.y + 5*SIZE_TILE};
			etapes[17] = (Pos_t){(*salles)[3]->destination.x + 6*SIZE_TILE,(*salles)[3]->destination.y + 4*SIZE_TILE};
			etapes[18] = (Pos_t){(*salles)[3]->destination.x + 6*SIZE_TILE,(*salles)[3]->destination.y + 3*SIZE_TILE};
			etapes[19] = (Pos_t){(*salles)[3]->destination.x + 6*SIZE_TILE,(*salles)[3]->destination.y + 2*SIZE_TILE};
			etapes[20] = (Pos_t){(*salles)[3]->destination.x + 6*SIZE_TILE,(*salles)[3]->destination.y + 3*SIZE_TILE};
			etapes[21] = (Pos_t){(*salles)[3]->destination.x + 6*SIZE_TILE,(*salles)[3]->destination.y + 4*SIZE_TILE};
			etapes[22] = (Pos_t){(*salles)[3]->destination.x + 6*SIZE_TILE,(*salles)[3]->destination.y + 5*SIZE_TILE};
			etapes[23] = (Pos_t){(*salles)[3]->destination.x + 5*SIZE_TILE,(*salles)[3]->destination.y + 5*SIZE_TILE};
			etapes[24] = (Pos_t){(*salles)[3]->destination.x + 5*SIZE_TILE,(*salles)[3]->destination.y + 4*SIZE_TILE};
			etapes[25] = (Pos_t){(*salles)[3]->destination.x + 5*SIZE_TILE,(*salles)[3]->destination.y + 3*SIZE_TILE};
			etapes[26] = (Pos_t){(*salles)[3]->destination.x + 5*SIZE_TILE,(*salles)[3]->destination.y + 2*SIZE_TILE};
			etapes[27] = (Pos_t){(*salles)[3]->destination.x + 4*SIZE_TILE,(*salles)[3]->destination.y + 2*SIZE_TILE};
			etapes[28] = (Pos_t){(*salles)[3]->destination.x + 4*SIZE_TILE,(*salles)[3]->destination.y + 3*SIZE_TILE};
			etapes[29] = (Pos_t){(*salles)[3]->destination.x + 4*SIZE_TILE,(*salles)[3]->destination.y + 4*SIZE_TILE};
			etapes[30] = (Pos_t){(*salles)[3]->destination.x + 4*SIZE_TILE,(*salles)[3]->destination.y + 5*SIZE_TILE};
			etapes[31] = (Pos_t){(*salles)[3]->destination.x + 3*SIZE_TILE,(*salles)[3]->destination.y + 5*SIZE_TILE};
			etapes[32] = (Pos_t){(*salles)[3]->destination.x + 3*SIZE_TILE,(*salles)[3]->destination.y + 4*SIZE_TILE};
			etapes[33] = (Pos_t){(*salles)[3]->destination.x + 3*SIZE_TILE,(*salles)[3]->destination.y + 3*SIZE_TILE};
			etapes[34] = (Pos_t){(*salles)[3]->destination.x + 3*SIZE_TILE,(*salles)[3]->destination.y + 2*SIZE_TILE};
			etapes[35] = (Pos_t){(*salles)[3]->destination.x + 2*SIZE_TILE,(*salles)[3]->destination.y + 2*SIZE_TILE};
			etapes[36] = (Pos_t){(*salles)[3]->destination.x + 2*SIZE_TILE,(*salles)[3]->destination.y + 3*SIZE_TILE};
			etapes[37] = (Pos_t){(*salles)[3]->destination.x + 2*SIZE_TILE,(*salles)[3]->destination.y + 4*SIZE_TILE};
		etapeCourante = 0;		
		entites[2] = EntiteCreate(renderer, SLIME_R, etapes, etapeCourante, nbEtapes);


	(*salles)[3]->entites = entites;
	(*salles)[3]->nbObjectifs = 2;
	(*salles)[3]->nbObjectifsVivants = 2;	
	(*salles)[3]->nbEntites = nbEntites;

	//SALLE 4

	texture = IMG_LoadTexture(renderer, "assets/Salles/Salle_13x11_Rouge.png");
	(*salles)[4] = SalleCreate(texture, 4, 13, 11);
	nbEntites = 8;
	entites = (Entite_t**)malloc(nbEntites*sizeof(Entite_t*));	

		//Entite 0
		nbEtapes = 1;
		etapes = (Pos_t*)malloc(nbEtapes*sizeof(Pos_t));
			etapes[0] = (Pos_t){(*salles)[4]->destination.x + 2*SIZE_TILE,(*salles)[4]->destination.y + 3*SIZE_TILE};
		etapeCourante = 0;
		entites[0] = EntiteCreate(renderer, SLIME_V, etapes, etapeCourante, nbEtapes);

		//Entite 1
		nbEtapes = 1;
		etapes = (Pos_t*)malloc(nbEtapes*sizeof(Pos_t));
			etapes[0] = (Pos_t){(*salles)[4]->destination.x + 2*SIZE_TILE,(*salles)[4]->destination.y + 8*SIZE_TILE};
		etapeCourante = 0;
		entites[1] = EntiteCreate(renderer, SLIME_V, etapes, etapeCourante, nbEtapes);

		//Entite 2
		nbEtapes = 1;
		etapes = (Pos_t*)malloc(nbEtapes*sizeof(Pos_t));
			etapes[0] = (Pos_t){(*salles)[4]->destination.x + 10*SIZE_TILE,(*salles)[4]->destination.y + 3*SIZE_TILE};
		etapeCourante = 0;
		entites[2] = EntiteCreate(renderer, SLIME_V, etapes, etapeCourante, nbEtapes);

		//Entite 3
		nbEtapes = 1;
		etapes = (Pos_t*)malloc(nbEtapes*sizeof(Pos_t));
			etapes[0] = (Pos_t){(*salles)[4]->destination.x + 10*SIZE_TILE,(*salles)[4]->destination.y + 7*SIZE_TILE};
		etapeCourante = 0;
		entites[3] = EntiteCreate(renderer, SLIME_V, etapes, etapeCourante, nbEtapes);

		//Entite 4
		nbEtapes = 8;
		etapes = (Pos_t*)malloc(nbEtapes*sizeof(Pos_t));
			etapes[0] = (Pos_t){(*salles)[4]->destination.x + 2*SIZE_TILE,(*salles)[4]->destination.y + 2*SIZE_TILE};
			etapes[1] = (Pos_t){(*salles)[4]->destination.x + 3*SIZE_TILE,(*salles)[4]->destination.y + 2*SIZE_TILE};
			etapes[2] = (Pos_t){(*salles)[4]->destination.x + 3*SIZE_TILE,(*salles)[4]->destination.y + 3*SIZE_TILE};
			etapes[3] = (Pos_t){(*salles)[4]->destination.x + 3*SIZE_TILE,(*salles)[4]->destination.y + 4*SIZE_TILE};
			etapes[4] = (Pos_t){(*salles)[4]->destination.x + 2*SIZE_TILE,(*salles)[4]->destination.y + 4*SIZE_TILE};
			etapes[5] = (Pos_t){(*salles)[4]->destination.x + 1*SIZE_TILE,(*salles)[4]->destination.y + 4*SIZE_TILE};
			etapes[6] = (Pos_t){(*salles)[4]->destination.x + 1*SIZE_TILE,(*salles)[4]->destination.y + 3*SIZE_TILE};
			etapes[7] = (Pos_t){(*salles)[4]->destination.x + 1*SIZE_TILE,(*salles)[4]->destination.y + 2*SIZE_TILE};
		etapeCourante = 0;
		entites[4] = EntiteCreate(renderer, SLIME_R, etapes, etapeCourante, nbEtapes);
		
		//Entite 5
		nbEtapes = 8;
		etapes = (Pos_t*)malloc(nbEtapes*sizeof(Pos_t));

			etapes[0] = (Pos_t){(*salles)[4]->destination.x + 2*SIZE_TILE,(*salles)[4]->destination.y + 4*SIZE_TILE};
			etapes[1] = (Pos_t){(*salles)[4]->destination.x + 1*SIZE_TILE,(*salles)[4]->destination.y + 4*SIZE_TILE};
			etapes[2] = (Pos_t){(*salles)[4]->destination.x + 1*SIZE_TILE,(*salles)[4]->destination.y + 3*SIZE_TILE};
			etapes[3] = (Pos_t){(*salles)[4]->destination.x + 1*SIZE_TILE,(*salles)[4]->destination.y + 2*SIZE_TILE};
			etapes[4] = (Pos_t){(*salles)[4]->destination.x + 2*SIZE_TILE,(*salles)[4]->destination.y + 2*SIZE_TILE};
			etapes[5] = (Pos_t){(*salles)[4]->destination.x + 3*SIZE_TILE,(*salles)[4]->destination.y + 2*SIZE_TILE};
			etapes[6] = (Pos_t){(*salles)[4]->destination.x + 3*SIZE_TILE,(*salles)[4]->destination.y + 3*SIZE_TILE};
			etapes[7] = (Pos_t){(*salles)[4]->destination.x + 3*SIZE_TILE,(*salles)[4]->destination.y + 4*SIZE_TILE};
		etapeCourante = 0;
		entites[5] = EntiteCreate(renderer, SLIME_R, etapes, etapeCourante, nbEtapes);
		
		//Entite 6
		nbEtapes = 8;
		etapes = (Pos_t*)malloc(nbEtapes*sizeof(Pos_t));
			etapes[0] = (Pos_t){(*salles)[4]->destination.x + 10*SIZE_TILE,(*salles)[4]->destination.y + 6*SIZE_TILE};
			etapes[1] = (Pos_t){(*salles)[4]->destination.x + 11*SIZE_TILE,(*salles)[4]->destination.y + 6*SIZE_TILE};
			etapes[2] = (Pos_t){(*salles)[4]->destination.x + 11*SIZE_TILE,(*salles)[4]->destination.y + 7*SIZE_TILE};
			etapes[3] = (Pos_t){(*salles)[4]->destination.x + 11*SIZE_TILE,(*salles)[4]->destination.y + 8*SIZE_TILE};
			etapes[4] = (Pos_t){(*salles)[4]->destination.x + 10*SIZE_TILE,(*salles)[4]->destination.y + 8*SIZE_TILE};
			etapes[5] = (Pos_t){(*salles)[4]->destination.x + 9*SIZE_TILE,(*salles)[4]->destination.y + 8*SIZE_TILE};
			etapes[6] = (Pos_t){(*salles)[4]->destination.x + 9*SIZE_TILE,(*salles)[4]->destination.y + 7*SIZE_TILE};
			etapes[7] = (Pos_t){(*salles)[4]->destination.x + 9*SIZE_TILE,(*salles)[4]->destination.y + 6*SIZE_TILE};
		etapeCourante = 0;
		entites[6] = EntiteCreate(renderer, SLIME_R, etapes, etapeCourante, nbEtapes);

		//Entite 7
		nbEtapes = 8;
		etapes = (Pos_t*)malloc(nbEtapes*sizeof(Pos_t));
			etapes[0] = (Pos_t){(*salles)[4]->destination.x + 10*SIZE_TILE,(*salles)[4]->destination.y + 8*SIZE_TILE};
			etapes[1] = (Pos_t){(*salles)[4]->destination.x + 9*SIZE_TILE,(*salles)[4]->destination.y + 8*SIZE_TILE};
			etapes[2] = (Pos_t){(*salles)[4]->destination.x + 9*SIZE_TILE,(*salles)[4]->destination.y + 7*SIZE_TILE};
			etapes[3] = (Pos_t){(*salles)[4]->destination.x + 9*SIZE_TILE,(*salles)[4]->destination.y + 6*SIZE_TILE};
			etapes[4] = (Pos_t){(*salles)[4]->destination.x + 10*SIZE_TILE,(*salles)[4]->destination.y + 6*SIZE_TILE};
			etapes[5] = (Pos_t){(*salles)[4]->destination.x + 11*SIZE_TILE,(*salles)[4]->destination.y + 6*SIZE_TILE};
			etapes[6] = (Pos_t){(*salles)[4]->destination.x + 11*SIZE_TILE,(*salles)[4]->destination.y + 7*SIZE_TILE};
			etapes[7] = (Pos_t){(*salles)[4]->destination.x + 11*SIZE_TILE,(*salles)[4]->destination.y + 8*SIZE_TILE};
		etapeCourante = 0;
		entites[7] = EntiteCreate(renderer, SLIME_R, etapes, etapeCourante, nbEtapes);


	(*salles)[4]->entites = entites;
	(*salles)[4]->nbObjectifs = 4;
	(*salles)[4]->nbObjectifsVivants = 4;	
	(*salles)[4]->nbEntites = nbEntites;

	//Salle 5
	texture = IMG_LoadTexture(renderer, "assets/Salles/Salle_13x11_Bleu.png");
	(*salles)[5] = SalleCreate(texture, 5, 13, 11);
	nbEntites = 4;
	entites = (Entite_t**)malloc(nbEntites*sizeof(Entite_t*));
	
		//Entite 0
		nbEtapes = 20;
		etapes = (Pos_t*)malloc(nbEtapes*sizeof(Pos_t));
			etapes[0] = (Pos_t){(*salles)[5]->destination.x + 1*SIZE_TILE,(*salles)[5]->destination.y + 2*SIZE_TILE};
			etapes[1] = (Pos_t){(*salles)[5]->destination.x + 2*SIZE_TILE,(*salles)[5]->destination.y + 2*SIZE_TILE};
			etapes[2] = (Pos_t){(*salles)[5]->destination.x + 3*SIZE_TILE,(*salles)[5]->destination.y + 2*SIZE_TILE};
			etapes[3] = (Pos_t){(*salles)[5]->destination.x + 4*SIZE_TILE,(*salles)[5]->destination.y + 2*SIZE_TILE};
			etapes[4] = (Pos_t){(*salles)[5]->destination.x + 5*SIZE_TILE,(*salles)[5]->destination.y + 2*SIZE_TILE};
			etapes[5] = (Pos_t){(*salles)[5]->destination.x + 6*SIZE_TILE,(*salles)[5]->destination.y + 2*SIZE_TILE};
			etapes[6] = (Pos_t){(*salles)[5]->destination.x + 7*SIZE_TILE,(*salles)[5]->destination.y + 2*SIZE_TILE};
			etapes[7] = (Pos_t){(*salles)[5]->destination.x + 8*SIZE_TILE,(*salles)[5]->destination.y + 2*SIZE_TILE};
			etapes[8] = (Pos_t){(*salles)[5]->destination.x + 9*SIZE_TILE,(*salles)[5]->destination.y + 2*SIZE_TILE};
			etapes[9] = (Pos_t){(*salles)[5]->destination.x + 10*SIZE_TILE,(*salles)[5]->destination.y + 2*SIZE_TILE};
			etapes[10] = (Pos_t){(*salles)[5]->destination.x + 11*SIZE_TILE,(*salles)[5]->destination.y + 2*SIZE_TILE};
			etapes[11] = (Pos_t){(*salles)[5]->destination.x + 10*SIZE_TILE,(*salles)[5]->destination.y + 2*SIZE_TILE};
			etapes[12] = (Pos_t){(*salles)[5]->destination.x + 9*SIZE_TILE,(*salles)[5]->destination.y + 2*SIZE_TILE};
			etapes[13] = (Pos_t){(*salles)[5]->destination.x + 8*SIZE_TILE,(*salles)[5]->destination.y + 2*SIZE_TILE};
			etapes[14] = (Pos_t){(*salles)[5]->destination.x + 7*SIZE_TILE,(*salles)[5]->destination.y + 2*SIZE_TILE};
			etapes[15] = (Pos_t){(*salles)[5]->destination.x + 6*SIZE_TILE,(*salles)[5]->destination.y + 2*SIZE_TILE};
			etapes[16] = (Pos_t){(*salles)[5]->destination.x + 5*SIZE_TILE,(*salles)[5]->destination.y + 2*SIZE_TILE};
			etapes[17] = (Pos_t){(*salles)[5]->destination.x + 4*SIZE_TILE,(*salles)[5]->destination.y + 2*SIZE_TILE};
			etapes[18] = (Pos_t){(*salles)[5]->destination.x + 3*SIZE_TILE,(*salles)[5]->destination.y + 2*SIZE_TILE};
			etapes[19] = (Pos_t){(*salles)[5]->destination.x + 2*SIZE_TILE,(*salles)[5]->destination.y + 2*SIZE_TILE};

		etapeCourante = 0;
		entites[0] = EntiteCreate(renderer, SLIME_V, etapes, etapeCourante, nbEtapes);

		//Entite 1
		nbEtapes = 4;
		etapes = (Pos_t*)malloc(nbEtapes*sizeof(Pos_t));
			etapes[0] = (Pos_t){(*salles)[5]->destination.x + 6*SIZE_TILE,(*salles)[5]->destination.y + 5*SIZE_TILE};
			etapes[1] = (Pos_t){(*salles)[5]->destination.x + 6*SIZE_TILE,(*salles)[5]->destination.y + 4*SIZE_TILE};
			etapes[2] = (Pos_t){(*salles)[5]->destination.x + 6*SIZE_TILE,(*salles)[5]->destination.y + 3*SIZE_TILE};
			etapes[3] = (Pos_t){(*salles)[5]->destination.x + 6*SIZE_TILE,(*salles)[5]->destination.y + 4*SIZE_TILE};

		etapeCourante = 0;
		entites[1] = EntiteCreate(renderer, SLIME_V, etapes, etapeCourante, nbEtapes);

		//Entite 2
		nbEtapes = 20;
		etapes = (Pos_t*)malloc(nbEtapes*sizeof(Pos_t));
			etapes[0] = (Pos_t){(*salles)[5]->destination.x + 8*SIZE_TILE,(*salles)[5]->destination.y + 4*SIZE_TILE};
			etapes[1] = (Pos_t){(*salles)[5]->destination.x + 8*SIZE_TILE,(*salles)[5]->destination.y + 5*SIZE_TILE};
			etapes[2] = (Pos_t){(*salles)[5]->destination.x + 7*SIZE_TILE,(*salles)[5]->destination.y + 5*SIZE_TILE};
			etapes[3] = (Pos_t){(*salles)[5]->destination.x + 7*SIZE_TILE,(*salles)[5]->destination.y + 6*SIZE_TILE};
			etapes[4] = (Pos_t){(*salles)[5]->destination.x + 6*SIZE_TILE,(*salles)[5]->destination.y + 6*SIZE_TILE};
			etapes[5] = (Pos_t){(*salles)[5]->destination.x + 5*SIZE_TILE,(*salles)[5]->destination.y + 6*SIZE_TILE};
			etapes[6] = (Pos_t){(*salles)[5]->destination.x + 5*SIZE_TILE,(*salles)[5]->destination.y + 5*SIZE_TILE};
			etapes[7] = (Pos_t){(*salles)[5]->destination.x + 4*SIZE_TILE,(*salles)[5]->destination.y + 5*SIZE_TILE};
			etapes[8] = (Pos_t){(*salles)[5]->destination.x + 4*SIZE_TILE,(*salles)[5]->destination.y + 4*SIZE_TILE};
			etapes[9] = (Pos_t){(*salles)[5]->destination.x + 3*SIZE_TILE,(*salles)[5]->destination.y + 4*SIZE_TILE};
			etapes[10] = (Pos_t){(*salles)[5]->destination.x + 4*SIZE_TILE,(*salles)[5]->destination.y + 4*SIZE_TILE};
			etapes[11] = (Pos_t){(*salles)[5]->destination.x + 4*SIZE_TILE,(*salles)[5]->destination.y + 5*SIZE_TILE};
			etapes[12] = (Pos_t){(*salles)[5]->destination.x + 5*SIZE_TILE,(*salles)[5]->destination.y + 5*SIZE_TILE};
			etapes[13] = (Pos_t){(*salles)[5]->destination.x + 5*SIZE_TILE,(*salles)[5]->destination.y + 6*SIZE_TILE};
			etapes[14] = (Pos_t){(*salles)[5]->destination.x + 6*SIZE_TILE,(*salles)[5]->destination.y + 6*SIZE_TILE};
			etapes[15] = (Pos_t){(*salles)[5]->destination.x + 7*SIZE_TILE,(*salles)[5]->destination.y + 6*SIZE_TILE};
			etapes[16] = (Pos_t){(*salles)[5]->destination.x + 7*SIZE_TILE,(*salles)[5]->destination.y + 5*SIZE_TILE};
			etapes[17] = (Pos_t){(*salles)[5]->destination.x + 8*SIZE_TILE,(*salles)[5]->destination.y + 5*SIZE_TILE};
			etapes[18] = (Pos_t){(*salles)[5]->destination.x + 8*SIZE_TILE,(*salles)[5]->destination.y + 4*SIZE_TILE};
			etapes[19] = (Pos_t){(*salles)[5]->destination.x + 9*SIZE_TILE,(*salles)[5]->destination.y + 4*SIZE_TILE};
		etapeCourante = 0;
		entites[2] = EntiteCreate(renderer, SLIME_R, etapes, etapeCourante, nbEtapes);

		//Entite 3
		nbEtapes = 20;
		etapes = (Pos_t*)malloc(nbEtapes*sizeof(Pos_t));
			etapes[0] = (Pos_t){(*salles)[5]->destination.x + 4*SIZE_TILE,(*salles)[5]->destination.y + 7*SIZE_TILE};
			etapes[1] = (Pos_t){(*salles)[5]->destination.x + 5*SIZE_TILE,(*salles)[5]->destination.y + 7*SIZE_TILE};
			etapes[2] = (Pos_t){(*salles)[5]->destination.x + 5*SIZE_TILE,(*salles)[5]->destination.y + 8*SIZE_TILE};
			etapes[3] = (Pos_t){(*salles)[5]->destination.x + 6*SIZE_TILE,(*salles)[5]->destination.y + 8*SIZE_TILE};
			etapes[4] = (Pos_t){(*salles)[5]->destination.x + 7*SIZE_TILE,(*salles)[5]->destination.y + 8*SIZE_TILE};
			etapes[5] = (Pos_t){(*salles)[5]->destination.x + 7*SIZE_TILE,(*salles)[5]->destination.y + 7*SIZE_TILE};
			etapes[6] = (Pos_t){(*salles)[5]->destination.x + 8*SIZE_TILE,(*salles)[5]->destination.y + 7*SIZE_TILE};
			etapes[7] = (Pos_t){(*salles)[5]->destination.x + 8*SIZE_TILE,(*salles)[5]->destination.y + 6*SIZE_TILE};
			etapes[8] = (Pos_t){(*salles)[5]->destination.x + 9*SIZE_TILE,(*salles)[5]->destination.y + 6*SIZE_TILE};
			etapes[9] = (Pos_t){(*salles)[5]->destination.x + 8*SIZE_TILE,(*salles)[5]->destination.y + 6*SIZE_TILE};
			etapes[10] = (Pos_t){(*salles)[5]->destination.x + 8*SIZE_TILE,(*salles)[5]->destination.y + 7*SIZE_TILE};
			etapes[11] = (Pos_t){(*salles)[5]->destination.x + 7*SIZE_TILE,(*salles)[5]->destination.y + 7*SIZE_TILE};
			etapes[12] = (Pos_t){(*salles)[5]->destination.x + 7*SIZE_TILE,(*salles)[5]->destination.y + 8*SIZE_TILE};
			etapes[13] = (Pos_t){(*salles)[5]->destination.x + 6*SIZE_TILE,(*salles)[5]->destination.y + 8*SIZE_TILE};
			etapes[14] = (Pos_t){(*salles)[5]->destination.x + 5*SIZE_TILE,(*salles)[5]->destination.y + 8*SIZE_TILE};
			etapes[15] = (Pos_t){(*salles)[5]->destination.x + 5*SIZE_TILE,(*salles)[5]->destination.y + 7*SIZE_TILE};
			etapes[16] = (Pos_t){(*salles)[5]->destination.x + 4*SIZE_TILE,(*salles)[5]->destination.y + 7*SIZE_TILE};
			etapes[17] = (Pos_t){(*salles)[5]->destination.x + 4*SIZE_TILE,(*salles)[5]->destination.y + 6*SIZE_TILE};
			etapes[18] = (Pos_t){(*salles)[5]->destination.x + 3*SIZE_TILE,(*salles)[5]->destination.y + 6*SIZE_TILE};
			etapes[19] = (Pos_t){(*salles)[5]->destination.x + 4*SIZE_TILE,(*salles)[5]->destination.y + 6*SIZE_TILE};
		etapeCourante = 0;
		entites[3] = EntiteCreate(renderer, SLIME_R, etapes, etapeCourante, nbEtapes);



	(*salles)[5]->entites = entites;
	(*salles)[5]->nbObjectifs = 2;
	(*salles)[5]->nbObjectifsVivants = 2;	
	(*salles)[5]->nbEntites = nbEntites;


	//Salle 6
	texture = IMG_LoadTexture(renderer, "assets/Salles/Salle_13x11_Jaune.png");
	(*salles)[6] = SalleCreate(texture, 6, 13, 11);
	nbEntites = 14;
	entites = (Entite_t**)malloc(nbEntites*sizeof(Entite_t*));

		//Entite 0
		nbEtapes = 26;
		etapes = (Pos_t*)malloc(nbEtapes*sizeof(Pos_t));
			etapes[0] = (Pos_t){(*salles)[6]->destination.x + 9*SIZE_TILE,(*salles)[6]->destination.y + 2*SIZE_TILE};
			etapes[1] = (Pos_t){(*salles)[6]->destination.x + 9*SIZE_TILE,(*salles)[6]->destination.y + 3*SIZE_TILE};
			etapes[2] = (Pos_t){(*salles)[6]->destination.x + 8*SIZE_TILE,(*salles)[6]->destination.y + 3*SIZE_TILE};
			etapes[3] = (Pos_t){(*salles)[6]->destination.x + 8*SIZE_TILE,(*salles)[6]->destination.y + 4*SIZE_TILE};
			etapes[4] = (Pos_t){(*salles)[6]->destination.x + 7*SIZE_TILE,(*salles)[6]->destination.y + 4*SIZE_TILE};
			etapes[5] = (Pos_t){(*salles)[6]->destination.x + 7*SIZE_TILE,(*salles)[6]->destination.y + 5*SIZE_TILE};
			etapes[6] = (Pos_t){(*salles)[6]->destination.x + 6*SIZE_TILE,(*salles)[6]->destination.y + 5*SIZE_TILE};
			etapes[7] = (Pos_t){(*salles)[6]->destination.x + 6*SIZE_TILE,(*salles)[6]->destination.y + 6*SIZE_TILE};
			etapes[8] = (Pos_t){(*salles)[6]->destination.x + 5*SIZE_TILE,(*salles)[6]->destination.y + 6*SIZE_TILE};
			etapes[9] = (Pos_t){(*salles)[6]->destination.x + 5*SIZE_TILE,(*salles)[6]->destination.y + 7*SIZE_TILE};
			etapes[10] = (Pos_t){(*salles)[6]->destination.x + 4*SIZE_TILE,(*salles)[6]->destination.y + 7*SIZE_TILE};
			etapes[11] = (Pos_t){(*salles)[6]->destination.x + 4*SIZE_TILE,(*salles)[6]->destination.y + 8*SIZE_TILE};
			etapes[12] = (Pos_t){(*salles)[6]->destination.x + 3*SIZE_TILE,(*salles)[6]->destination.y + 8*SIZE_TILE};
			etapes[13] = (Pos_t){(*salles)[6]->destination.x + 2*SIZE_TILE,(*salles)[6]->destination.y + 8*SIZE_TILE};
			etapes[14] = (Pos_t){(*salles)[6]->destination.x + 2*SIZE_TILE,(*salles)[6]->destination.y + 7*SIZE_TILE};
			etapes[15] = (Pos_t){(*salles)[6]->destination.x + 3*SIZE_TILE,(*salles)[6]->destination.y + 7*SIZE_TILE};
			etapes[16] = (Pos_t){(*salles)[6]->destination.x + 3*SIZE_TILE,(*salles)[6]->destination.y + 6*SIZE_TILE};
			etapes[17] = (Pos_t){(*salles)[6]->destination.x + 4*SIZE_TILE,(*salles)[6]->destination.y + 6*SIZE_TILE};
			etapes[18] = (Pos_t){(*salles)[6]->destination.x + 4*SIZE_TILE,(*salles)[6]->destination.y + 5*SIZE_TILE};
			etapes[19] = (Pos_t){(*salles)[6]->destination.x + 5*SIZE_TILE,(*salles)[6]->destination.y + 5*SIZE_TILE};
			etapes[20] = (Pos_t){(*salles)[6]->destination.x + 5*SIZE_TILE,(*salles)[6]->destination.y + 4*SIZE_TILE};
			etapes[21] = (Pos_t){(*salles)[6]->destination.x + 6*SIZE_TILE,(*salles)[6]->destination.y + 4*SIZE_TILE};
			etapes[22] = (Pos_t){(*salles)[6]->destination.x + 6*SIZE_TILE,(*salles)[6]->destination.y + 3*SIZE_TILE};
			etapes[23] = (Pos_t){(*salles)[6]->destination.x + 7*SIZE_TILE,(*salles)[6]->destination.y + 3*SIZE_TILE};
			etapes[24] = (Pos_t){(*salles)[6]->destination.x + 7*SIZE_TILE,(*salles)[6]->destination.y + 2*SIZE_TILE};
			etapes[25] = (Pos_t){(*salles)[6]->destination.x + 8*SIZE_TILE,(*salles)[6]->destination.y + 2*SIZE_TILE};
		etapeCourante = 0;
		entites[0] = EntiteCreate(renderer, SLIME_R, etapes, etapeCourante, nbEtapes);

		//Entite 1
		nbEtapes = 26;
		etapes = (Pos_t*)malloc(nbEtapes*sizeof(Pos_t));
			etapes[0] = (Pos_t){(*salles)[6]->destination.x + 8*SIZE_TILE,(*salles)[6]->destination.y + 3*SIZE_TILE};
			etapes[1] = (Pos_t){(*salles)[6]->destination.x + 8*SIZE_TILE,(*salles)[6]->destination.y + 4*SIZE_TILE};
			etapes[2] = (Pos_t){(*salles)[6]->destination.x + 7*SIZE_TILE,(*salles)[6]->destination.y + 4*SIZE_TILE};
			etapes[3] = (Pos_t){(*salles)[6]->destination.x + 7*SIZE_TILE,(*salles)[6]->destination.y + 5*SIZE_TILE};
			etapes[4] = (Pos_t){(*salles)[6]->destination.x + 6*SIZE_TILE,(*salles)[6]->destination.y + 5*SIZE_TILE};
			etapes[5] = (Pos_t){(*salles)[6]->destination.x + 6*SIZE_TILE,(*salles)[6]->destination.y + 6*SIZE_TILE};
			etapes[6] = (Pos_t){(*salles)[6]->destination.x + 5*SIZE_TILE,(*salles)[6]->destination.y + 6*SIZE_TILE};
			etapes[7] = (Pos_t){(*salles)[6]->destination.x + 5*SIZE_TILE,(*salles)[6]->destination.y + 7*SIZE_TILE};
			etapes[8] = (Pos_t){(*salles)[6]->destination.x + 4*SIZE_TILE,(*salles)[6]->destination.y + 7*SIZE_TILE};
			etapes[9] = (Pos_t){(*salles)[6]->destination.x + 4*SIZE_TILE,(*salles)[6]->destination.y + 8*SIZE_TILE};
			etapes[10] = (Pos_t){(*salles)[6]->destination.x + 3*SIZE_TILE,(*salles)[6]->destination.y + 8*SIZE_TILE};
			etapes[11] = (Pos_t){(*salles)[6]->destination.x + 2*SIZE_TILE,(*salles)[6]->destination.y + 8*SIZE_TILE};
			etapes[12] = (Pos_t){(*salles)[6]->destination.x + 2*SIZE_TILE,(*salles)[6]->destination.y + 7*SIZE_TILE};
			etapes[13] = (Pos_t){(*salles)[6]->destination.x + 3*SIZE_TILE,(*salles)[6]->destination.y + 7*SIZE_TILE};
			etapes[14] = (Pos_t){(*salles)[6]->destination.x + 3*SIZE_TILE,(*salles)[6]->destination.y + 6*SIZE_TILE};
			etapes[15] = (Pos_t){(*salles)[6]->destination.x + 4*SIZE_TILE,(*salles)[6]->destination.y + 6*SIZE_TILE};
			etapes[16] = (Pos_t){(*salles)[6]->destination.x + 4*SIZE_TILE,(*salles)[6]->destination.y + 5*SIZE_TILE};
			etapes[17] = (Pos_t){(*salles)[6]->destination.x + 5*SIZE_TILE,(*salles)[6]->destination.y + 5*SIZE_TILE};
			etapes[18] = (Pos_t){(*salles)[6]->destination.x + 5*SIZE_TILE,(*salles)[6]->destination.y + 4*SIZE_TILE};
			etapes[19] = (Pos_t){(*salles)[6]->destination.x + 6*SIZE_TILE,(*salles)[6]->destination.y + 4*SIZE_TILE};
			etapes[20] = (Pos_t){(*salles)[6]->destination.x + 6*SIZE_TILE,(*salles)[6]->destination.y + 3*SIZE_TILE};
			etapes[21] = (Pos_t){(*salles)[6]->destination.x + 7*SIZE_TILE,(*salles)[6]->destination.y + 3*SIZE_TILE};
			etapes[22] = (Pos_t){(*salles)[6]->destination.x + 7*SIZE_TILE,(*salles)[6]->destination.y + 2*SIZE_TILE};
			etapes[23] = (Pos_t){(*salles)[6]->destination.x + 8*SIZE_TILE,(*salles)[6]->destination.y + 2*SIZE_TILE};
			etapes[24] = (Pos_t){(*salles)[6]->destination.x + 9*SIZE_TILE,(*salles)[6]->destination.y + 2*SIZE_TILE};
			etapes[25] = (Pos_t){(*salles)[6]->destination.x + 9*SIZE_TILE,(*salles)[6]->destination.y + 3*SIZE_TILE};
		etapeCourante = 0;
		entites[1] = EntiteCreate(renderer, SLIME_R, etapes, etapeCourante, nbEtapes);

		//Entite 2
		nbEtapes = 26;
		etapes = (Pos_t*)malloc(nbEtapes*sizeof(Pos_t));
			etapes[0] = (Pos_t){(*salles)[6]->destination.x + 7*SIZE_TILE,(*salles)[6]->destination.y + 4*SIZE_TILE};
			etapes[1] = (Pos_t){(*salles)[6]->destination.x + 7*SIZE_TILE,(*salles)[6]->destination.y + 5*SIZE_TILE};
			etapes[2] = (Pos_t){(*salles)[6]->destination.x + 6*SIZE_TILE,(*salles)[6]->destination.y + 5*SIZE_TILE};
			etapes[3] = (Pos_t){(*salles)[6]->destination.x + 6*SIZE_TILE,(*salles)[6]->destination.y + 6*SIZE_TILE};
			etapes[4] = (Pos_t){(*salles)[6]->destination.x + 5*SIZE_TILE,(*salles)[6]->destination.y + 6*SIZE_TILE};
			etapes[5] = (Pos_t){(*salles)[6]->destination.x + 5*SIZE_TILE,(*salles)[6]->destination.y + 7*SIZE_TILE};
			etapes[6] = (Pos_t){(*salles)[6]->destination.x + 4*SIZE_TILE,(*salles)[6]->destination.y + 7*SIZE_TILE};
			etapes[7] = (Pos_t){(*salles)[6]->destination.x + 4*SIZE_TILE,(*salles)[6]->destination.y + 8*SIZE_TILE};
			etapes[8] = (Pos_t){(*salles)[6]->destination.x + 3*SIZE_TILE,(*salles)[6]->destination.y + 8*SIZE_TILE};
			etapes[9] = (Pos_t){(*salles)[6]->destination.x + 2*SIZE_TILE,(*salles)[6]->destination.y + 8*SIZE_TILE};
			etapes[10] = (Pos_t){(*salles)[6]->destination.x + 2*SIZE_TILE,(*salles)[6]->destination.y + 7*SIZE_TILE};
			etapes[11] = (Pos_t){(*salles)[6]->destination.x + 3*SIZE_TILE,(*salles)[6]->destination.y + 7*SIZE_TILE};
			etapes[12] = (Pos_t){(*salles)[6]->destination.x + 3*SIZE_TILE,(*salles)[6]->destination.y + 6*SIZE_TILE};
			etapes[13] = (Pos_t){(*salles)[6]->destination.x + 4*SIZE_TILE,(*salles)[6]->destination.y + 6*SIZE_TILE};
			etapes[14] = (Pos_t){(*salles)[6]->destination.x + 4*SIZE_TILE,(*salles)[6]->destination.y + 5*SIZE_TILE};
			etapes[15] = (Pos_t){(*salles)[6]->destination.x + 5*SIZE_TILE,(*salles)[6]->destination.y + 5*SIZE_TILE};
			etapes[16] = (Pos_t){(*salles)[6]->destination.x + 5*SIZE_TILE,(*salles)[6]->destination.y + 4*SIZE_TILE};
			etapes[17] = (Pos_t){(*salles)[6]->destination.x + 6*SIZE_TILE,(*salles)[6]->destination.y + 4*SIZE_TILE};
			etapes[18] = (Pos_t){(*salles)[6]->destination.x + 6*SIZE_TILE,(*salles)[6]->destination.y + 3*SIZE_TILE};
			etapes[19] = (Pos_t){(*salles)[6]->destination.x + 7*SIZE_TILE,(*salles)[6]->destination.y + 3*SIZE_TILE};
			etapes[20] = (Pos_t){(*salles)[6]->destination.x + 7*SIZE_TILE,(*salles)[6]->destination.y + 2*SIZE_TILE};
			etapes[21] = (Pos_t){(*salles)[6]->destination.x + 8*SIZE_TILE,(*salles)[6]->destination.y + 2*SIZE_TILE};
			etapes[22] = (Pos_t){(*salles)[6]->destination.x + 9*SIZE_TILE,(*salles)[6]->destination.y + 2*SIZE_TILE};
			etapes[23] = (Pos_t){(*salles)[6]->destination.x + 9*SIZE_TILE,(*salles)[6]->destination.y + 3*SIZE_TILE};
			etapes[24] = (Pos_t){(*salles)[6]->destination.x + 8*SIZE_TILE,(*salles)[6]->destination.y + 3*SIZE_TILE};
			etapes[25] = (Pos_t){(*salles)[6]->destination.x + 8*SIZE_TILE,(*salles)[6]->destination.y + 4*SIZE_TILE};
		etapeCourante = 0;
		entites[2] = EntiteCreate(renderer, SLIME_R, etapes, etapeCourante, nbEtapes);

		//Entite 3
		nbEtapes = 26;
		etapes = (Pos_t*)malloc(nbEtapes*sizeof(Pos_t));
			etapes[0] = (Pos_t){(*salles)[6]->destination.x + 6*SIZE_TILE,(*salles)[6]->destination.y + 5*SIZE_TILE};
			etapes[1] = (Pos_t){(*salles)[6]->destination.x + 6*SIZE_TILE,(*salles)[6]->destination.y + 6*SIZE_TILE};
			etapes[2] = (Pos_t){(*salles)[6]->destination.x + 5*SIZE_TILE,(*salles)[6]->destination.y + 6*SIZE_TILE};
			etapes[3] = (Pos_t){(*salles)[6]->destination.x + 5*SIZE_TILE,(*salles)[6]->destination.y + 7*SIZE_TILE};
			etapes[4] = (Pos_t){(*salles)[6]->destination.x + 4*SIZE_TILE,(*salles)[6]->destination.y + 7*SIZE_TILE};
			etapes[5] = (Pos_t){(*salles)[6]->destination.x + 4*SIZE_TILE,(*salles)[6]->destination.y + 8*SIZE_TILE};
			etapes[6] = (Pos_t){(*salles)[6]->destination.x + 3*SIZE_TILE,(*salles)[6]->destination.y + 8*SIZE_TILE};
			etapes[7] = (Pos_t){(*salles)[6]->destination.x + 2*SIZE_TILE,(*salles)[6]->destination.y + 8*SIZE_TILE};
			etapes[8] = (Pos_t){(*salles)[6]->destination.x + 2*SIZE_TILE,(*salles)[6]->destination.y + 7*SIZE_TILE};
			etapes[9] = (Pos_t){(*salles)[6]->destination.x + 3*SIZE_TILE,(*salles)[6]->destination.y + 7*SIZE_TILE};
			etapes[10] = (Pos_t){(*salles)[6]->destination.x + 3*SIZE_TILE,(*salles)[6]->destination.y + 6*SIZE_TILE};
			etapes[11] = (Pos_t){(*salles)[6]->destination.x + 4*SIZE_TILE,(*salles)[6]->destination.y + 6*SIZE_TILE};
			etapes[12] = (Pos_t){(*salles)[6]->destination.x + 4*SIZE_TILE,(*salles)[6]->destination.y + 5*SIZE_TILE};
			etapes[13] = (Pos_t){(*salles)[6]->destination.x + 5*SIZE_TILE,(*salles)[6]->destination.y + 5*SIZE_TILE};
			etapes[14] = (Pos_t){(*salles)[6]->destination.x + 5*SIZE_TILE,(*salles)[6]->destination.y + 4*SIZE_TILE};
			etapes[15] = (Pos_t){(*salles)[6]->destination.x + 6*SIZE_TILE,(*salles)[6]->destination.y + 4*SIZE_TILE};
			etapes[16] = (Pos_t){(*salles)[6]->destination.x + 6*SIZE_TILE,(*salles)[6]->destination.y + 3*SIZE_TILE};
			etapes[17] = (Pos_t){(*salles)[6]->destination.x + 7*SIZE_TILE,(*salles)[6]->destination.y + 3*SIZE_TILE};
			etapes[18] = (Pos_t){(*salles)[6]->destination.x + 7*SIZE_TILE,(*salles)[6]->destination.y + 2*SIZE_TILE};
			etapes[19] = (Pos_t){(*salles)[6]->destination.x + 8*SIZE_TILE,(*salles)[6]->destination.y + 2*SIZE_TILE};
			etapes[20] = (Pos_t){(*salles)[6]->destination.x + 9*SIZE_TILE,(*salles)[6]->destination.y + 2*SIZE_TILE};
			etapes[21] = (Pos_t){(*salles)[6]->destination.x + 9*SIZE_TILE,(*salles)[6]->destination.y + 3*SIZE_TILE};
			etapes[22] = (Pos_t){(*salles)[6]->destination.x + 8*SIZE_TILE,(*salles)[6]->destination.y + 3*SIZE_TILE};
			etapes[23] = (Pos_t){(*salles)[6]->destination.x + 8*SIZE_TILE,(*salles)[6]->destination.y + 4*SIZE_TILE};
			etapes[24] = (Pos_t){(*salles)[6]->destination.x + 7*SIZE_TILE,(*salles)[6]->destination.y + 4*SIZE_TILE};
			etapes[25] = (Pos_t){(*salles)[6]->destination.x + 7*SIZE_TILE,(*salles)[6]->destination.y + 5*SIZE_TILE};
		etapeCourante = 0;
		entites[3] = EntiteCreate(renderer, SLIME_V, etapes, etapeCourante, nbEtapes);

		//Entite 4
		nbEtapes = 26;
		etapes = (Pos_t*)malloc(nbEtapes*sizeof(Pos_t));
			etapes[0] = (Pos_t){(*salles)[6]->destination.x + 5*SIZE_TILE,(*salles)[6]->destination.y + 6*SIZE_TILE};
			etapes[1] = (Pos_t){(*salles)[6]->destination.x + 5*SIZE_TILE,(*salles)[6]->destination.y + 7*SIZE_TILE};
			etapes[2] = (Pos_t){(*salles)[6]->destination.x + 4*SIZE_TILE,(*salles)[6]->destination.y + 7*SIZE_TILE};
			etapes[3] = (Pos_t){(*salles)[6]->destination.x + 4*SIZE_TILE,(*salles)[6]->destination.y + 8*SIZE_TILE};
			etapes[4] = (Pos_t){(*salles)[6]->destination.x + 3*SIZE_TILE,(*salles)[6]->destination.y + 8*SIZE_TILE};
			etapes[5] = (Pos_t){(*salles)[6]->destination.x + 2*SIZE_TILE,(*salles)[6]->destination.y + 8*SIZE_TILE};
			etapes[6] = (Pos_t){(*salles)[6]->destination.x + 2*SIZE_TILE,(*salles)[6]->destination.y + 7*SIZE_TILE};
			etapes[7] = (Pos_t){(*salles)[6]->destination.x + 3*SIZE_TILE,(*salles)[6]->destination.y + 7*SIZE_TILE};
			etapes[8] = (Pos_t){(*salles)[6]->destination.x + 3*SIZE_TILE,(*salles)[6]->destination.y + 6*SIZE_TILE};
			etapes[9] = (Pos_t){(*salles)[6]->destination.x + 4*SIZE_TILE,(*salles)[6]->destination.y + 6*SIZE_TILE};
			etapes[10] = (Pos_t){(*salles)[6]->destination.x + 4*SIZE_TILE,(*salles)[6]->destination.y + 5*SIZE_TILE};
			etapes[11] = (Pos_t){(*salles)[6]->destination.x + 5*SIZE_TILE,(*salles)[6]->destination.y + 5*SIZE_TILE};
			etapes[12] = (Pos_t){(*salles)[6]->destination.x + 5*SIZE_TILE,(*salles)[6]->destination.y + 4*SIZE_TILE};
			etapes[13] = (Pos_t){(*salles)[6]->destination.x + 6*SIZE_TILE,(*salles)[6]->destination.y + 4*SIZE_TILE};
			etapes[14] = (Pos_t){(*salles)[6]->destination.x + 6*SIZE_TILE,(*salles)[6]->destination.y + 3*SIZE_TILE};
			etapes[15] = (Pos_t){(*salles)[6]->destination.x + 7*SIZE_TILE,(*salles)[6]->destination.y + 3*SIZE_TILE};
			etapes[16] = (Pos_t){(*salles)[6]->destination.x + 7*SIZE_TILE,(*salles)[6]->destination.y + 2*SIZE_TILE};
			etapes[17] = (Pos_t){(*salles)[6]->destination.x + 8*SIZE_TILE,(*salles)[6]->destination.y + 2*SIZE_TILE};
			etapes[18] = (Pos_t){(*salles)[6]->destination.x + 9*SIZE_TILE,(*salles)[6]->destination.y + 2*SIZE_TILE};
			etapes[19] = (Pos_t){(*salles)[6]->destination.x + 9*SIZE_TILE,(*salles)[6]->destination.y + 3*SIZE_TILE};
			etapes[20] = (Pos_t){(*salles)[6]->destination.x + 8*SIZE_TILE,(*salles)[6]->destination.y + 3*SIZE_TILE};
			etapes[21] = (Pos_t){(*salles)[6]->destination.x + 8*SIZE_TILE,(*salles)[6]->destination.y + 4*SIZE_TILE};
			etapes[22] = (Pos_t){(*salles)[6]->destination.x + 7*SIZE_TILE,(*salles)[6]->destination.y + 4*SIZE_TILE};
			etapes[23] = (Pos_t){(*salles)[6]->destination.x + 7*SIZE_TILE,(*salles)[6]->destination.y + 5*SIZE_TILE};
			etapes[24] = (Pos_t){(*salles)[6]->destination.x + 6*SIZE_TILE,(*salles)[6]->destination.y + 5*SIZE_TILE};
			etapes[25] = (Pos_t){(*salles)[6]->destination.x + 6*SIZE_TILE,(*salles)[6]->destination.y + 6*SIZE_TILE};
		etapeCourante = 0;
		entites[4] = EntiteCreate(renderer, SLIME_V, etapes, etapeCourante, nbEtapes);

		//Entite 5
		nbEtapes = 26;
		etapes = (Pos_t*)malloc(nbEtapes*sizeof(Pos_t));
			etapes[0] = (Pos_t){(*salles)[6]->destination.x + 4*SIZE_TILE,(*salles)[6]->destination.y + 7*SIZE_TILE};
			etapes[1] = (Pos_t){(*salles)[6]->destination.x + 4*SIZE_TILE,(*salles)[6]->destination.y + 8*SIZE_TILE};
			etapes[2] = (Pos_t){(*salles)[6]->destination.x + 3*SIZE_TILE,(*salles)[6]->destination.y + 8*SIZE_TILE};
			etapes[3] = (Pos_t){(*salles)[6]->destination.x + 2*SIZE_TILE,(*salles)[6]->destination.y + 8*SIZE_TILE};
			etapes[4] = (Pos_t){(*salles)[6]->destination.x + 2*SIZE_TILE,(*salles)[6]->destination.y + 7*SIZE_TILE};
			etapes[5] = (Pos_t){(*salles)[6]->destination.x + 3*SIZE_TILE,(*salles)[6]->destination.y + 7*SIZE_TILE};
			etapes[6] = (Pos_t){(*salles)[6]->destination.x + 3*SIZE_TILE,(*salles)[6]->destination.y + 6*SIZE_TILE};
			etapes[7] = (Pos_t){(*salles)[6]->destination.x + 4*SIZE_TILE,(*salles)[6]->destination.y + 6*SIZE_TILE};
			etapes[8] = (Pos_t){(*salles)[6]->destination.x + 4*SIZE_TILE,(*salles)[6]->destination.y + 5*SIZE_TILE};
			etapes[9] = (Pos_t){(*salles)[6]->destination.x + 5*SIZE_TILE,(*salles)[6]->destination.y + 5*SIZE_TILE};
			etapes[10] = (Pos_t){(*salles)[6]->destination.x + 5*SIZE_TILE,(*salles)[6]->destination.y + 4*SIZE_TILE};
			etapes[11] = (Pos_t){(*salles)[6]->destination.x + 6*SIZE_TILE,(*salles)[6]->destination.y + 4*SIZE_TILE};
			etapes[12] = (Pos_t){(*salles)[6]->destination.x + 6*SIZE_TILE,(*salles)[6]->destination.y + 3*SIZE_TILE};
			etapes[13] = (Pos_t){(*salles)[6]->destination.x + 7*SIZE_TILE,(*salles)[6]->destination.y + 3*SIZE_TILE};
			etapes[14] = (Pos_t){(*salles)[6]->destination.x + 7*SIZE_TILE,(*salles)[6]->destination.y + 2*SIZE_TILE};
			etapes[15] = (Pos_t){(*salles)[6]->destination.x + 8*SIZE_TILE,(*salles)[6]->destination.y + 2*SIZE_TILE};
			etapes[16] = (Pos_t){(*salles)[6]->destination.x + 9*SIZE_TILE,(*salles)[6]->destination.y + 2*SIZE_TILE};
			etapes[17] = (Pos_t){(*salles)[6]->destination.x + 9*SIZE_TILE,(*salles)[6]->destination.y + 3*SIZE_TILE};
			etapes[18] = (Pos_t){(*salles)[6]->destination.x + 8*SIZE_TILE,(*salles)[6]->destination.y + 3*SIZE_TILE};
			etapes[19] = (Pos_t){(*salles)[6]->destination.x + 8*SIZE_TILE,(*salles)[6]->destination.y + 4*SIZE_TILE};
			etapes[20] = (Pos_t){(*salles)[6]->destination.x + 7*SIZE_TILE,(*salles)[6]->destination.y + 4*SIZE_TILE};
			etapes[21] = (Pos_t){(*salles)[6]->destination.x + 7*SIZE_TILE,(*salles)[6]->destination.y + 5*SIZE_TILE};
			etapes[22] = (Pos_t){(*salles)[6]->destination.x + 6*SIZE_TILE,(*salles)[6]->destination.y + 5*SIZE_TILE};
			etapes[23] = (Pos_t){(*salles)[6]->destination.x + 6*SIZE_TILE,(*salles)[6]->destination.y + 6*SIZE_TILE};
			etapes[24] = (Pos_t){(*salles)[6]->destination.x + 5*SIZE_TILE,(*salles)[6]->destination.y + 6*SIZE_TILE};
			etapes[25] = (Pos_t){(*salles)[6]->destination.x + 5*SIZE_TILE,(*salles)[6]->destination.y + 7*SIZE_TILE};
		etapeCourante = 0;
		entites[5] = EntiteCreate(renderer, SLIME_R, etapes, etapeCourante, nbEtapes);

		//Entite 6
		nbEtapes = 26;
		etapes = (Pos_t*)malloc(nbEtapes*sizeof(Pos_t));
			etapes[0] = (Pos_t){(*salles)[6]->destination.x + 3*SIZE_TILE,(*salles)[6]->destination.y + 8*SIZE_TILE};
			etapes[1] = (Pos_t){(*salles)[6]->destination.x + 2*SIZE_TILE,(*salles)[6]->destination.y + 8*SIZE_TILE};
			etapes[2] = (Pos_t){(*salles)[6]->destination.x + 2*SIZE_TILE,(*salles)[6]->destination.y + 7*SIZE_TILE};
			etapes[3] = (Pos_t){(*salles)[6]->destination.x + 3*SIZE_TILE,(*salles)[6]->destination.y + 7*SIZE_TILE};
			etapes[4] = (Pos_t){(*salles)[6]->destination.x + 3*SIZE_TILE,(*salles)[6]->destination.y + 6*SIZE_TILE};
			etapes[5] = (Pos_t){(*salles)[6]->destination.x + 4*SIZE_TILE,(*salles)[6]->destination.y + 6*SIZE_TILE};
			etapes[6] = (Pos_t){(*salles)[6]->destination.x + 4*SIZE_TILE,(*salles)[6]->destination.y + 5*SIZE_TILE};
			etapes[7] = (Pos_t){(*salles)[6]->destination.x + 5*SIZE_TILE,(*salles)[6]->destination.y + 5*SIZE_TILE};
			etapes[8] = (Pos_t){(*salles)[6]->destination.x + 5*SIZE_TILE,(*salles)[6]->destination.y + 4*SIZE_TILE};
			etapes[9] = (Pos_t){(*salles)[6]->destination.x + 6*SIZE_TILE,(*salles)[6]->destination.y + 4*SIZE_TILE};
			etapes[10] = (Pos_t){(*salles)[6]->destination.x + 6*SIZE_TILE,(*salles)[6]->destination.y + 3*SIZE_TILE};
			etapes[11] = (Pos_t){(*salles)[6]->destination.x + 7*SIZE_TILE,(*salles)[6]->destination.y + 3*SIZE_TILE};
			etapes[12] = (Pos_t){(*salles)[6]->destination.x + 7*SIZE_TILE,(*salles)[6]->destination.y + 2*SIZE_TILE};
			etapes[13] = (Pos_t){(*salles)[6]->destination.x + 8*SIZE_TILE,(*salles)[6]->destination.y + 2*SIZE_TILE};
			etapes[14] = (Pos_t){(*salles)[6]->destination.x + 9*SIZE_TILE,(*salles)[6]->destination.y + 2*SIZE_TILE};
			etapes[15] = (Pos_t){(*salles)[6]->destination.x + 9*SIZE_TILE,(*salles)[6]->destination.y + 3*SIZE_TILE};
			etapes[16] = (Pos_t){(*salles)[6]->destination.x + 8*SIZE_TILE,(*salles)[6]->destination.y + 3*SIZE_TILE};
			etapes[17] = (Pos_t){(*salles)[6]->destination.x + 8*SIZE_TILE,(*salles)[6]->destination.y + 4*SIZE_TILE};
			etapes[18] = (Pos_t){(*salles)[6]->destination.x + 7*SIZE_TILE,(*salles)[6]->destination.y + 4*SIZE_TILE};
			etapes[19] = (Pos_t){(*salles)[6]->destination.x + 7*SIZE_TILE,(*salles)[6]->destination.y + 5*SIZE_TILE};
			etapes[20] = (Pos_t){(*salles)[6]->destination.x + 6*SIZE_TILE,(*salles)[6]->destination.y + 5*SIZE_TILE};
			etapes[21] = (Pos_t){(*salles)[6]->destination.x + 6*SIZE_TILE,(*salles)[6]->destination.y + 6*SIZE_TILE};
			etapes[22] = (Pos_t){(*salles)[6]->destination.x + 5*SIZE_TILE,(*salles)[6]->destination.y + 6*SIZE_TILE};
			etapes[23] = (Pos_t){(*salles)[6]->destination.x + 5*SIZE_TILE,(*salles)[6]->destination.y + 7*SIZE_TILE};
			etapes[24] = (Pos_t){(*salles)[6]->destination.x + 4*SIZE_TILE,(*salles)[6]->destination.y + 7*SIZE_TILE};
			etapes[25] = (Pos_t){(*salles)[6]->destination.x + 4*SIZE_TILE,(*salles)[6]->destination.y + 8*SIZE_TILE};
		etapeCourante = 0;
		entites[6] = EntiteCreate(renderer, SLIME_R, etapes, etapeCourante, nbEtapes);

		//Entite 7
		nbEtapes = 26;
		etapes = (Pos_t*)malloc(nbEtapes*sizeof(Pos_t));
			etapes[0] = (Pos_t){(*salles)[6]->destination.x + 2*SIZE_TILE,(*salles)[6]->destination.y + 8*SIZE_TILE};
			etapes[1] = (Pos_t){(*salles)[6]->destination.x + 2*SIZE_TILE,(*salles)[6]->destination.y + 7*SIZE_TILE};
			etapes[2] = (Pos_t){(*salles)[6]->destination.x + 3*SIZE_TILE,(*salles)[6]->destination.y + 7*SIZE_TILE};
			etapes[3] = (Pos_t){(*salles)[6]->destination.x + 3*SIZE_TILE,(*salles)[6]->destination.y + 6*SIZE_TILE};
			etapes[4] = (Pos_t){(*salles)[6]->destination.x + 4*SIZE_TILE,(*salles)[6]->destination.y + 6*SIZE_TILE};
			etapes[5] = (Pos_t){(*salles)[6]->destination.x + 4*SIZE_TILE,(*salles)[6]->destination.y + 5*SIZE_TILE};
			etapes[6] = (Pos_t){(*salles)[6]->destination.x + 5*SIZE_TILE,(*salles)[6]->destination.y + 5*SIZE_TILE};
			etapes[7] = (Pos_t){(*salles)[6]->destination.x + 5*SIZE_TILE,(*salles)[6]->destination.y + 4*SIZE_TILE};
			etapes[8] = (Pos_t){(*salles)[6]->destination.x + 6*SIZE_TILE,(*salles)[6]->destination.y + 4*SIZE_TILE};
			etapes[9] = (Pos_t){(*salles)[6]->destination.x + 6*SIZE_TILE,(*salles)[6]->destination.y + 3*SIZE_TILE};
			etapes[10] = (Pos_t){(*salles)[6]->destination.x + 7*SIZE_TILE,(*salles)[6]->destination.y + 3*SIZE_TILE};
			etapes[11] = (Pos_t){(*salles)[6]->destination.x + 7*SIZE_TILE,(*salles)[6]->destination.y + 2*SIZE_TILE};
			etapes[12] = (Pos_t){(*salles)[6]->destination.x + 8*SIZE_TILE,(*salles)[6]->destination.y + 2*SIZE_TILE};
			etapes[13] = (Pos_t){(*salles)[6]->destination.x + 9*SIZE_TILE,(*salles)[6]->destination.y + 2*SIZE_TILE};
			etapes[14] = (Pos_t){(*salles)[6]->destination.x + 9*SIZE_TILE,(*salles)[6]->destination.y + 3*SIZE_TILE};
			etapes[15] = (Pos_t){(*salles)[6]->destination.x + 8*SIZE_TILE,(*salles)[6]->destination.y + 3*SIZE_TILE};
			etapes[16] = (Pos_t){(*salles)[6]->destination.x + 8*SIZE_TILE,(*salles)[6]->destination.y + 4*SIZE_TILE};
			etapes[17] = (Pos_t){(*salles)[6]->destination.x + 7*SIZE_TILE,(*salles)[6]->destination.y + 4*SIZE_TILE};
			etapes[18] = (Pos_t){(*salles)[6]->destination.x + 7*SIZE_TILE,(*salles)[6]->destination.y + 5*SIZE_TILE};
			etapes[19] = (Pos_t){(*salles)[6]->destination.x + 6*SIZE_TILE,(*salles)[6]->destination.y + 5*SIZE_TILE};
			etapes[20] = (Pos_t){(*salles)[6]->destination.x + 6*SIZE_TILE,(*salles)[6]->destination.y + 6*SIZE_TILE};
			etapes[21] = (Pos_t){(*salles)[6]->destination.x + 5*SIZE_TILE,(*salles)[6]->destination.y + 6*SIZE_TILE};
			etapes[22] = (Pos_t){(*salles)[6]->destination.x + 5*SIZE_TILE,(*salles)[6]->destination.y + 7*SIZE_TILE};
			etapes[23] = (Pos_t){(*salles)[6]->destination.x + 4*SIZE_TILE,(*salles)[6]->destination.y + 7*SIZE_TILE};
			etapes[24] = (Pos_t){(*salles)[6]->destination.x + 4*SIZE_TILE,(*salles)[6]->destination.y + 8*SIZE_TILE};
			etapes[25] = (Pos_t){(*salles)[6]->destination.x + 3*SIZE_TILE,(*salles)[6]->destination.y + 8*SIZE_TILE};
		etapeCourante = 0;
		entites[7] = EntiteCreate(renderer, SLIME_R, etapes, etapeCourante, nbEtapes);

		//Entite 8
		nbEtapes = 26;
		etapes = (Pos_t*)malloc(nbEtapes*sizeof(Pos_t));
			etapes[0] = (Pos_t){(*salles)[6]->destination.x + 3*SIZE_TILE,(*salles)[6]->destination.y + 7*SIZE_TILE};
			etapes[1] = (Pos_t){(*salles)[6]->destination.x + 3*SIZE_TILE,(*salles)[6]->destination.y + 6*SIZE_TILE};
			etapes[2] = (Pos_t){(*salles)[6]->destination.x + 4*SIZE_TILE,(*salles)[6]->destination.y + 6*SIZE_TILE};
			etapes[3] = (Pos_t){(*salles)[6]->destination.x + 4*SIZE_TILE,(*salles)[6]->destination.y + 5*SIZE_TILE};
			etapes[4] = (Pos_t){(*salles)[6]->destination.x + 5*SIZE_TILE,(*salles)[6]->destination.y + 5*SIZE_TILE};
			etapes[5] = (Pos_t){(*salles)[6]->destination.x + 5*SIZE_TILE,(*salles)[6]->destination.y + 4*SIZE_TILE};
			etapes[6] = (Pos_t){(*salles)[6]->destination.x + 6*SIZE_TILE,(*salles)[6]->destination.y + 4*SIZE_TILE};
			etapes[7] = (Pos_t){(*salles)[6]->destination.x + 6*SIZE_TILE,(*salles)[6]->destination.y + 3*SIZE_TILE};
			etapes[8] = (Pos_t){(*salles)[6]->destination.x + 7*SIZE_TILE,(*salles)[6]->destination.y + 3*SIZE_TILE};
			etapes[9] = (Pos_t){(*salles)[6]->destination.x + 7*SIZE_TILE,(*salles)[6]->destination.y + 2*SIZE_TILE};
			etapes[10] = (Pos_t){(*salles)[6]->destination.x + 8*SIZE_TILE,(*salles)[6]->destination.y + 2*SIZE_TILE};
			etapes[11] = (Pos_t){(*salles)[6]->destination.x + 9*SIZE_TILE,(*salles)[6]->destination.y + 2*SIZE_TILE};
			etapes[12] = (Pos_t){(*salles)[6]->destination.x + 9*SIZE_TILE,(*salles)[6]->destination.y + 3*SIZE_TILE};
			etapes[13] = (Pos_t){(*salles)[6]->destination.x + 8*SIZE_TILE,(*salles)[6]->destination.y + 3*SIZE_TILE};
			etapes[14] = (Pos_t){(*salles)[6]->destination.x + 8*SIZE_TILE,(*salles)[6]->destination.y + 4*SIZE_TILE};
			etapes[15] = (Pos_t){(*salles)[6]->destination.x + 7*SIZE_TILE,(*salles)[6]->destination.y + 4*SIZE_TILE};
			etapes[16] = (Pos_t){(*salles)[6]->destination.x + 7*SIZE_TILE,(*salles)[6]->destination.y + 5*SIZE_TILE};
			etapes[17] = (Pos_t){(*salles)[6]->destination.x + 6*SIZE_TILE,(*salles)[6]->destination.y + 5*SIZE_TILE};
			etapes[18] = (Pos_t){(*salles)[6]->destination.x + 6*SIZE_TILE,(*salles)[6]->destination.y + 6*SIZE_TILE};
			etapes[19] = (Pos_t){(*salles)[6]->destination.x + 5*SIZE_TILE,(*salles)[6]->destination.y + 6*SIZE_TILE};
			etapes[20] = (Pos_t){(*salles)[6]->destination.x + 5*SIZE_TILE,(*salles)[6]->destination.y + 7*SIZE_TILE};
			etapes[21] = (Pos_t){(*salles)[6]->destination.x + 4*SIZE_TILE,(*salles)[6]->destination.y + 7*SIZE_TILE};
			etapes[22] = (Pos_t){(*salles)[6]->destination.x + 4*SIZE_TILE,(*salles)[6]->destination.y + 8*SIZE_TILE};
			etapes[23] = (Pos_t){(*salles)[6]->destination.x + 3*SIZE_TILE,(*salles)[6]->destination.y + 8*SIZE_TILE};
			etapes[24] = (Pos_t){(*salles)[6]->destination.x + 2*SIZE_TILE,(*salles)[6]->destination.y + 8*SIZE_TILE};
			etapes[25] = (Pos_t){(*salles)[6]->destination.x + 2*SIZE_TILE,(*salles)[6]->destination.y + 7*SIZE_TILE};
		etapeCourante = 0;
		entites[8] = EntiteCreate(renderer, SLIME_R, etapes, etapeCourante, nbEtapes);
		
		//Entite 9
		nbEtapes = 26;
		etapes = (Pos_t*)malloc(nbEtapes*sizeof(Pos_t));
			etapes[0] = (Pos_t){(*salles)[6]->destination.x + 4*SIZE_TILE,(*salles)[6]->destination.y + 6*SIZE_TILE};
			etapes[1] = (Pos_t){(*salles)[6]->destination.x + 4*SIZE_TILE,(*salles)[6]->destination.y + 5*SIZE_TILE};
			etapes[2] = (Pos_t){(*salles)[6]->destination.x + 5*SIZE_TILE,(*salles)[6]->destination.y + 5*SIZE_TILE};
			etapes[3] = (Pos_t){(*salles)[6]->destination.x + 5*SIZE_TILE,(*salles)[6]->destination.y + 4*SIZE_TILE};
			etapes[4] = (Pos_t){(*salles)[6]->destination.x + 6*SIZE_TILE,(*salles)[6]->destination.y + 4*SIZE_TILE};
			etapes[5] = (Pos_t){(*salles)[6]->destination.x + 6*SIZE_TILE,(*salles)[6]->destination.y + 3*SIZE_TILE};
			etapes[6] = (Pos_t){(*salles)[6]->destination.x + 7*SIZE_TILE,(*salles)[6]->destination.y + 3*SIZE_TILE};
			etapes[7] = (Pos_t){(*salles)[6]->destination.x + 7*SIZE_TILE,(*salles)[6]->destination.y + 2*SIZE_TILE};
			etapes[8] = (Pos_t){(*salles)[6]->destination.x + 8*SIZE_TILE,(*salles)[6]->destination.y + 2*SIZE_TILE};
			etapes[9] = (Pos_t){(*salles)[6]->destination.x + 9*SIZE_TILE,(*salles)[6]->destination.y + 2*SIZE_TILE};
			etapes[10] = (Pos_t){(*salles)[6]->destination.x + 9*SIZE_TILE,(*salles)[6]->destination.y + 3*SIZE_TILE};
			etapes[11] = (Pos_t){(*salles)[6]->destination.x + 8*SIZE_TILE,(*salles)[6]->destination.y + 3*SIZE_TILE};
			etapes[12] = (Pos_t){(*salles)[6]->destination.x + 8*SIZE_TILE,(*salles)[6]->destination.y + 4*SIZE_TILE};
			etapes[13] = (Pos_t){(*salles)[6]->destination.x + 7*SIZE_TILE,(*salles)[6]->destination.y + 4*SIZE_TILE};
			etapes[14] = (Pos_t){(*salles)[6]->destination.x + 7*SIZE_TILE,(*salles)[6]->destination.y + 5*SIZE_TILE};
			etapes[15] = (Pos_t){(*salles)[6]->destination.x + 6*SIZE_TILE,(*salles)[6]->destination.y + 5*SIZE_TILE};
			etapes[16] = (Pos_t){(*salles)[6]->destination.x + 6*SIZE_TILE,(*salles)[6]->destination.y + 6*SIZE_TILE};
			etapes[17] = (Pos_t){(*salles)[6]->destination.x + 5*SIZE_TILE,(*salles)[6]->destination.y + 6*SIZE_TILE};
			etapes[18] = (Pos_t){(*salles)[6]->destination.x + 5*SIZE_TILE,(*salles)[6]->destination.y + 7*SIZE_TILE};
			etapes[19] = (Pos_t){(*salles)[6]->destination.x + 4*SIZE_TILE,(*salles)[6]->destination.y + 7*SIZE_TILE};
			etapes[20] = (Pos_t){(*salles)[6]->destination.x + 4*SIZE_TILE,(*salles)[6]->destination.y + 8*SIZE_TILE};
			etapes[21] = (Pos_t){(*salles)[6]->destination.x + 3*SIZE_TILE,(*salles)[6]->destination.y + 8*SIZE_TILE};
			etapes[22] = (Pos_t){(*salles)[6]->destination.x + 2*SIZE_TILE,(*salles)[6]->destination.y + 8*SIZE_TILE};
			etapes[23] = (Pos_t){(*salles)[6]->destination.x + 2*SIZE_TILE,(*salles)[6]->destination.y + 7*SIZE_TILE};
			etapes[24] = (Pos_t){(*salles)[6]->destination.x + 3*SIZE_TILE,(*salles)[6]->destination.y + 7*SIZE_TILE};
			etapes[25] = (Pos_t){(*salles)[6]->destination.x + 3*SIZE_TILE,(*salles)[6]->destination.y + 6*SIZE_TILE};
		etapeCourante = 0;
		entites[9] = EntiteCreate(renderer, SLIME_R, etapes, etapeCourante, nbEtapes);

		//Entite 10
		nbEtapes = 26;
		etapes = (Pos_t*)malloc(nbEtapes*sizeof(Pos_t));
			etapes[0] = (Pos_t){(*salles)[6]->destination.x + 5*SIZE_TILE,(*salles)[6]->destination.y + 5*SIZE_TILE};
			etapes[1] = (Pos_t){(*salles)[6]->destination.x + 5*SIZE_TILE,(*salles)[6]->destination.y + 4*SIZE_TILE};
			etapes[2] = (Pos_t){(*salles)[6]->destination.x + 6*SIZE_TILE,(*salles)[6]->destination.y + 4*SIZE_TILE};
			etapes[3] = (Pos_t){(*salles)[6]->destination.x + 6*SIZE_TILE,(*salles)[6]->destination.y + 3*SIZE_TILE};
			etapes[4] = (Pos_t){(*salles)[6]->destination.x + 7*SIZE_TILE,(*salles)[6]->destination.y + 3*SIZE_TILE};
			etapes[5] = (Pos_t){(*salles)[6]->destination.x + 7*SIZE_TILE,(*salles)[6]->destination.y + 2*SIZE_TILE};
			etapes[6] = (Pos_t){(*salles)[6]->destination.x + 8*SIZE_TILE,(*salles)[6]->destination.y + 2*SIZE_TILE};
			etapes[7] = (Pos_t){(*salles)[6]->destination.x + 9*SIZE_TILE,(*salles)[6]->destination.y + 2*SIZE_TILE};
			etapes[8] = (Pos_t){(*salles)[6]->destination.x + 9*SIZE_TILE,(*salles)[6]->destination.y + 3*SIZE_TILE};
			etapes[9] = (Pos_t){(*salles)[6]->destination.x + 8*SIZE_TILE,(*salles)[6]->destination.y + 3*SIZE_TILE};
			etapes[10] = (Pos_t){(*salles)[6]->destination.x + 8*SIZE_TILE,(*salles)[6]->destination.y + 4*SIZE_TILE};
			etapes[11] = (Pos_t){(*salles)[6]->destination.x + 7*SIZE_TILE,(*salles)[6]->destination.y + 4*SIZE_TILE};
			etapes[12] = (Pos_t){(*salles)[6]->destination.x + 7*SIZE_TILE,(*salles)[6]->destination.y + 5*SIZE_TILE};
			etapes[13] = (Pos_t){(*salles)[6]->destination.x + 6*SIZE_TILE,(*salles)[6]->destination.y + 5*SIZE_TILE};
			etapes[14] = (Pos_t){(*salles)[6]->destination.x + 6*SIZE_TILE,(*salles)[6]->destination.y + 6*SIZE_TILE};
			etapes[15] = (Pos_t){(*salles)[6]->destination.x + 5*SIZE_TILE,(*salles)[6]->destination.y + 6*SIZE_TILE};
			etapes[16] = (Pos_t){(*salles)[6]->destination.x + 5*SIZE_TILE,(*salles)[6]->destination.y + 7*SIZE_TILE};
			etapes[17] = (Pos_t){(*salles)[6]->destination.x + 4*SIZE_TILE,(*salles)[6]->destination.y + 7*SIZE_TILE};
			etapes[18] = (Pos_t){(*salles)[6]->destination.x + 4*SIZE_TILE,(*salles)[6]->destination.y + 8*SIZE_TILE};
			etapes[19] = (Pos_t){(*salles)[6]->destination.x + 3*SIZE_TILE,(*salles)[6]->destination.y + 8*SIZE_TILE};
			etapes[20] = (Pos_t){(*salles)[6]->destination.x + 2*SIZE_TILE,(*salles)[6]->destination.y + 8*SIZE_TILE};
			etapes[21] = (Pos_t){(*salles)[6]->destination.x + 2*SIZE_TILE,(*salles)[6]->destination.y + 7*SIZE_TILE};
			etapes[22] = (Pos_t){(*salles)[6]->destination.x + 3*SIZE_TILE,(*salles)[6]->destination.y + 7*SIZE_TILE};
			etapes[23] = (Pos_t){(*salles)[6]->destination.x + 3*SIZE_TILE,(*salles)[6]->destination.y + 6*SIZE_TILE};
			etapes[24] = (Pos_t){(*salles)[6]->destination.x + 4*SIZE_TILE,(*salles)[6]->destination.y + 6*SIZE_TILE};
			etapes[25] = (Pos_t){(*salles)[6]->destination.x + 4*SIZE_TILE,(*salles)[6]->destination.y + 5*SIZE_TILE};
		etapeCourante = 0;
		entites[10] = EntiteCreate(renderer, SLIME_V, etapes, etapeCourante, nbEtapes);

		//Entite 11
		nbEtapes = 26;
		etapes = (Pos_t*)malloc(nbEtapes*sizeof(Pos_t));
			etapes[0] = (Pos_t){(*salles)[6]->destination.x + 6*SIZE_TILE,(*salles)[6]->destination.y + 4*SIZE_TILE};
			etapes[1] = (Pos_t){(*salles)[6]->destination.x + 6*SIZE_TILE,(*salles)[6]->destination.y + 3*SIZE_TILE};
			etapes[2] = (Pos_t){(*salles)[6]->destination.x + 7*SIZE_TILE,(*salles)[6]->destination.y + 3*SIZE_TILE};
			etapes[3] = (Pos_t){(*salles)[6]->destination.x + 7*SIZE_TILE,(*salles)[6]->destination.y + 2*SIZE_TILE};
			etapes[4] = (Pos_t){(*salles)[6]->destination.x + 8*SIZE_TILE,(*salles)[6]->destination.y + 2*SIZE_TILE};
			etapes[5] = (Pos_t){(*salles)[6]->destination.x + 9*SIZE_TILE,(*salles)[6]->destination.y + 2*SIZE_TILE};
			etapes[6] = (Pos_t){(*salles)[6]->destination.x + 9*SIZE_TILE,(*salles)[6]->destination.y + 3*SIZE_TILE};
			etapes[7] = (Pos_t){(*salles)[6]->destination.x + 8*SIZE_TILE,(*salles)[6]->destination.y + 3*SIZE_TILE};
			etapes[8] = (Pos_t){(*salles)[6]->destination.x + 8*SIZE_TILE,(*salles)[6]->destination.y + 4*SIZE_TILE};
			etapes[9] = (Pos_t){(*salles)[6]->destination.x + 7*SIZE_TILE,(*salles)[6]->destination.y + 4*SIZE_TILE};
			etapes[10] = (Pos_t){(*salles)[6]->destination.x + 7*SIZE_TILE,(*salles)[6]->destination.y + 5*SIZE_TILE};
			etapes[11] = (Pos_t){(*salles)[6]->destination.x + 6*SIZE_TILE,(*salles)[6]->destination.y + 5*SIZE_TILE};
			etapes[12] = (Pos_t){(*salles)[6]->destination.x + 6*SIZE_TILE,(*salles)[6]->destination.y + 6*SIZE_TILE};
			etapes[13] = (Pos_t){(*salles)[6]->destination.x + 5*SIZE_TILE,(*salles)[6]->destination.y + 6*SIZE_TILE};
			etapes[14] = (Pos_t){(*salles)[6]->destination.x + 5*SIZE_TILE,(*salles)[6]->destination.y + 7*SIZE_TILE};
			etapes[15] = (Pos_t){(*salles)[6]->destination.x + 4*SIZE_TILE,(*salles)[6]->destination.y + 7*SIZE_TILE};
			etapes[16] = (Pos_t){(*salles)[6]->destination.x + 4*SIZE_TILE,(*salles)[6]->destination.y + 8*SIZE_TILE};
			etapes[17] = (Pos_t){(*salles)[6]->destination.x + 3*SIZE_TILE,(*salles)[6]->destination.y + 8*SIZE_TILE};
			etapes[18] = (Pos_t){(*salles)[6]->destination.x + 2*SIZE_TILE,(*salles)[6]->destination.y + 8*SIZE_TILE};
			etapes[19] = (Pos_t){(*salles)[6]->destination.x + 2*SIZE_TILE,(*salles)[6]->destination.y + 7*SIZE_TILE};
			etapes[20] = (Pos_t){(*salles)[6]->destination.x + 3*SIZE_TILE,(*salles)[6]->destination.y + 7*SIZE_TILE};
			etapes[21] = (Pos_t){(*salles)[6]->destination.x + 3*SIZE_TILE,(*salles)[6]->destination.y + 6*SIZE_TILE};
			etapes[22] = (Pos_t){(*salles)[6]->destination.x + 4*SIZE_TILE,(*salles)[6]->destination.y + 6*SIZE_TILE};
			etapes[23] = (Pos_t){(*salles)[6]->destination.x + 4*SIZE_TILE,(*salles)[6]->destination.y + 5*SIZE_TILE};
			etapes[24] = (Pos_t){(*salles)[6]->destination.x + 5*SIZE_TILE,(*salles)[6]->destination.y + 5*SIZE_TILE};
			etapes[25] = (Pos_t){(*salles)[6]->destination.x + 5*SIZE_TILE,(*salles)[6]->destination.y + 4*SIZE_TILE};
		etapeCourante = 0;
		entites[11] = EntiteCreate(renderer, SLIME_R, etapes, etapeCourante, nbEtapes);

		//Entite 12
		nbEtapes = 26;
		etapes = (Pos_t*)malloc(nbEtapes*sizeof(Pos_t));
			etapes[0] = (Pos_t){(*salles)[6]->destination.x + 7*SIZE_TILE,(*salles)[6]->destination.y + 3*SIZE_TILE};
			etapes[1] = (Pos_t){(*salles)[6]->destination.x + 7*SIZE_TILE,(*salles)[6]->destination.y + 2*SIZE_TILE};
			etapes[2] = (Pos_t){(*salles)[6]->destination.x + 8*SIZE_TILE,(*salles)[6]->destination.y + 2*SIZE_TILE};
			etapes[3] = (Pos_t){(*salles)[6]->destination.x + 9*SIZE_TILE,(*salles)[6]->destination.y + 2*SIZE_TILE};
			etapes[4] = (Pos_t){(*salles)[6]->destination.x + 9*SIZE_TILE,(*salles)[6]->destination.y + 3*SIZE_TILE};
			etapes[5] = (Pos_t){(*salles)[6]->destination.x + 8*SIZE_TILE,(*salles)[6]->destination.y + 3*SIZE_TILE};
			etapes[6] = (Pos_t){(*salles)[6]->destination.x + 8*SIZE_TILE,(*salles)[6]->destination.y + 4*SIZE_TILE};
			etapes[7] = (Pos_t){(*salles)[6]->destination.x + 7*SIZE_TILE,(*salles)[6]->destination.y + 4*SIZE_TILE};
			etapes[8] = (Pos_t){(*salles)[6]->destination.x + 7*SIZE_TILE,(*salles)[6]->destination.y + 5*SIZE_TILE};
			etapes[9] = (Pos_t){(*salles)[6]->destination.x + 6*SIZE_TILE,(*salles)[6]->destination.y + 5*SIZE_TILE};
			etapes[10] = (Pos_t){(*salles)[6]->destination.x + 6*SIZE_TILE,(*salles)[6]->destination.y + 6*SIZE_TILE};
			etapes[11] = (Pos_t){(*salles)[6]->destination.x + 5*SIZE_TILE,(*salles)[6]->destination.y + 6*SIZE_TILE};
			etapes[12] = (Pos_t){(*salles)[6]->destination.x + 5*SIZE_TILE,(*salles)[6]->destination.y + 7*SIZE_TILE};
			etapes[13] = (Pos_t){(*salles)[6]->destination.x + 4*SIZE_TILE,(*salles)[6]->destination.y + 7*SIZE_TILE};
			etapes[14] = (Pos_t){(*salles)[6]->destination.x + 4*SIZE_TILE,(*salles)[6]->destination.y + 8*SIZE_TILE};
			etapes[15] = (Pos_t){(*salles)[6]->destination.x + 3*SIZE_TILE,(*salles)[6]->destination.y + 8*SIZE_TILE};
			etapes[16] = (Pos_t){(*salles)[6]->destination.x + 2*SIZE_TILE,(*salles)[6]->destination.y + 8*SIZE_TILE};
			etapes[17] = (Pos_t){(*salles)[6]->destination.x + 2*SIZE_TILE,(*salles)[6]->destination.y + 7*SIZE_TILE};
			etapes[18] = (Pos_t){(*salles)[6]->destination.x + 3*SIZE_TILE,(*salles)[6]->destination.y + 7*SIZE_TILE};
			etapes[19] = (Pos_t){(*salles)[6]->destination.x + 3*SIZE_TILE,(*salles)[6]->destination.y + 6*SIZE_TILE};
			etapes[20] = (Pos_t){(*salles)[6]->destination.x + 4*SIZE_TILE,(*salles)[6]->destination.y + 6*SIZE_TILE};
			etapes[21] = (Pos_t){(*salles)[6]->destination.x + 4*SIZE_TILE,(*salles)[6]->destination.y + 5*SIZE_TILE};
			etapes[22] = (Pos_t){(*salles)[6]->destination.x + 5*SIZE_TILE,(*salles)[6]->destination.y + 5*SIZE_TILE};
			etapes[23] = (Pos_t){(*salles)[6]->destination.x + 5*SIZE_TILE,(*salles)[6]->destination.y + 4*SIZE_TILE};
			etapes[24] = (Pos_t){(*salles)[6]->destination.x + 6*SIZE_TILE,(*salles)[6]->destination.y + 4*SIZE_TILE};
			etapes[25] = (Pos_t){(*salles)[6]->destination.x + 6*SIZE_TILE,(*salles)[6]->destination.y + 3*SIZE_TILE};
		etapeCourante = 0;
		entites[12] = EntiteCreate(renderer, SLIME_R, etapes, etapeCourante, nbEtapes);

		//Entite 13
		nbEtapes = 26;
		etapes = (Pos_t*)malloc(nbEtapes*sizeof(Pos_t));
			etapes[0] = (Pos_t){(*salles)[6]->destination.x + 8*SIZE_TILE,(*salles)[6]->destination.y + 2*SIZE_TILE};
			etapes[1] = (Pos_t){(*salles)[6]->destination.x + 9*SIZE_TILE,(*salles)[6]->destination.y + 2*SIZE_TILE};
			etapes[2] = (Pos_t){(*salles)[6]->destination.x + 9*SIZE_TILE,(*salles)[6]->destination.y + 3*SIZE_TILE};
			etapes[3] = (Pos_t){(*salles)[6]->destination.x + 8*SIZE_TILE,(*salles)[6]->destination.y + 3*SIZE_TILE};
			etapes[4] = (Pos_t){(*salles)[6]->destination.x + 8*SIZE_TILE,(*salles)[6]->destination.y + 4*SIZE_TILE};
			etapes[5] = (Pos_t){(*salles)[6]->destination.x + 7*SIZE_TILE,(*salles)[6]->destination.y + 4*SIZE_TILE};
			etapes[6] = (Pos_t){(*salles)[6]->destination.x + 7*SIZE_TILE,(*salles)[6]->destination.y + 5*SIZE_TILE};
			etapes[7] = (Pos_t){(*salles)[6]->destination.x + 6*SIZE_TILE,(*salles)[6]->destination.y + 5*SIZE_TILE};
			etapes[8] = (Pos_t){(*salles)[6]->destination.x + 6*SIZE_TILE,(*salles)[6]->destination.y + 6*SIZE_TILE};
			etapes[9] = (Pos_t){(*salles)[6]->destination.x + 5*SIZE_TILE,(*salles)[6]->destination.y + 6*SIZE_TILE};
			etapes[10] = (Pos_t){(*salles)[6]->destination.x + 5*SIZE_TILE,(*salles)[6]->destination.y + 7*SIZE_TILE};
			etapes[11] = (Pos_t){(*salles)[6]->destination.x + 4*SIZE_TILE,(*salles)[6]->destination.y + 7*SIZE_TILE};
			etapes[12] = (Pos_t){(*salles)[6]->destination.x + 4*SIZE_TILE,(*salles)[6]->destination.y + 8*SIZE_TILE};
			etapes[13] = (Pos_t){(*salles)[6]->destination.x + 3*SIZE_TILE,(*salles)[6]->destination.y + 8*SIZE_TILE};
			etapes[14] = (Pos_t){(*salles)[6]->destination.x + 2*SIZE_TILE,(*salles)[6]->destination.y + 8*SIZE_TILE};
			etapes[15] = (Pos_t){(*salles)[6]->destination.x + 2*SIZE_TILE,(*salles)[6]->destination.y + 7*SIZE_TILE};
			etapes[16] = (Pos_t){(*salles)[6]->destination.x + 3*SIZE_TILE,(*salles)[6]->destination.y + 7*SIZE_TILE};
			etapes[17] = (Pos_t){(*salles)[6]->destination.x + 3*SIZE_TILE,(*salles)[6]->destination.y + 6*SIZE_TILE};
			etapes[18] = (Pos_t){(*salles)[6]->destination.x + 4*SIZE_TILE,(*salles)[6]->destination.y + 6*SIZE_TILE};
			etapes[19] = (Pos_t){(*salles)[6]->destination.x + 4*SIZE_TILE,(*salles)[6]->destination.y + 5*SIZE_TILE};
			etapes[20] = (Pos_t){(*salles)[6]->destination.x + 5*SIZE_TILE,(*salles)[6]->destination.y + 5*SIZE_TILE};
			etapes[21] = (Pos_t){(*salles)[6]->destination.x + 5*SIZE_TILE,(*salles)[6]->destination.y + 4*SIZE_TILE};
			etapes[22] = (Pos_t){(*salles)[6]->destination.x + 6*SIZE_TILE,(*salles)[6]->destination.y + 4*SIZE_TILE};
			etapes[23] = (Pos_t){(*salles)[6]->destination.x + 6*SIZE_TILE,(*salles)[6]->destination.y + 3*SIZE_TILE};
			etapes[24] = (Pos_t){(*salles)[6]->destination.x + 7*SIZE_TILE,(*salles)[6]->destination.y + 3*SIZE_TILE};
			etapes[25] = (Pos_t){(*salles)[6]->destination.x + 7*SIZE_TILE,(*salles)[6]->destination.y + 2*SIZE_TILE};
		etapeCourante = 0;
		entites[13] = EntiteCreate(renderer, SLIME_R, etapes, etapeCourante, nbEtapes);


	(*salles)[6]->entites = entites;
	(*salles)[6]->nbObjectifs = 3;	
	(*salles)[6]->nbObjectifsVivants = 3;	
	(*salles)[6]->nbEntites = nbEntites;

	//Salle 7
	texture = IMG_LoadTexture(renderer, "assets/Salles/Salle_17x14_Rouge.png");
	(*salles)[7] = SalleCreate(texture, 7, 17, 14);
	nbEntites = 17;
	entites = (Entite_t**)malloc(nbEntites*sizeof(Entite_t*));
	
		//Entite 0
		nbEtapes = 1;
		etapes = (Pos_t*)malloc(nbEtapes*sizeof(Pos_t));
			etapes[0] = (Pos_t){(*salles)[7]->destination.x + 2*SIZE_TILE,(*salles)[7]->destination.y + 2*SIZE_TILE};
		etapeCourante = 0;
		entites[0] = EntiteCreate(renderer, SLIME_V, etapes, etapeCourante, nbEtapes);

		//Entite 1
		nbEtapes = 1;
		etapes = (Pos_t*)malloc(nbEtapes*sizeof(Pos_t));
			etapes[0] = (Pos_t){(*salles)[7]->destination.x + 2*SIZE_TILE,(*salles)[7]->destination.y + 8*SIZE_TILE};
		etapeCourante = 0;
		entites[1] = EntiteCreate(renderer, SLIME_V, etapes, etapeCourante, nbEtapes);

		//Entite 2
		nbEtapes = 1;
		etapes = (Pos_t*)malloc(nbEtapes*sizeof(Pos_t));
			etapes[0] = (Pos_t){(*salles)[7]->destination.x + 3*SIZE_TILE,(*salles)[7]->destination.y + 6*SIZE_TILE};
		etapeCourante = 0;
		entites[2] = EntiteCreate(renderer, SLIME_R, etapes, etapeCourante, nbEtapes);

		//Entite 3
		nbEtapes = 1;
		etapes = (Pos_t*)malloc(nbEtapes*sizeof(Pos_t));
			etapes[0] = (Pos_t){(*salles)[7]->destination.x + 3*SIZE_TILE,(*salles)[7]->destination.y + 11*SIZE_TILE};
		etapeCourante = 0;
		entites[3] = EntiteCreate(renderer, SLIME_V, etapes, etapeCourante, nbEtapes);

		//Entite 4
		nbEtapes = 1;
		etapes = (Pos_t*)malloc(nbEtapes*sizeof(Pos_t));
			etapes[0] = (Pos_t){(*salles)[7]->destination.x + 4*SIZE_TILE,(*salles)[7]->destination.y + 4*SIZE_TILE};
		etapeCourante = 0;
		entites[4] = EntiteCreate(renderer, SLIME_V, etapes, etapeCourante, nbEtapes);

		//Entite 5
		nbEtapes = 1;
		etapes = (Pos_t*)malloc(nbEtapes*sizeof(Pos_t));
			etapes[0] = (Pos_t){(*salles)[7]->destination.x + 4*SIZE_TILE,(*salles)[7]->destination.y + 7*SIZE_TILE};
		etapeCourante = 0;
		entites[5] = EntiteCreate(renderer, SLIME_V, etapes, etapeCourante, nbEtapes);

		//Entite 6
		nbEtapes = 1;
		etapes = (Pos_t*)malloc(nbEtapes*sizeof(Pos_t));
			etapes[0] = (Pos_t){(*salles)[7]->destination.x + 6*SIZE_TILE,(*salles)[7]->destination.y + 5*SIZE_TILE};
		etapeCourante = 0;
		entites[6] = EntiteCreate(renderer, SLIME_V, etapes, etapeCourante, nbEtapes);

		//Entite 7
		nbEtapes = 1;
		etapes = (Pos_t*)malloc(nbEtapes*sizeof(Pos_t));
			etapes[0] = (Pos_t){(*salles)[7]->destination.x + 6*SIZE_TILE,(*salles)[7]->destination.y + 9*SIZE_TILE};
		etapeCourante = 0;
		entites[7] = EntiteCreate(renderer, SLIME_V, etapes, etapeCourante, nbEtapes);

		//Entite 8
		nbEtapes = 1;
		etapes = (Pos_t*)malloc(nbEtapes*sizeof(Pos_t));
			etapes[0] = (Pos_t){(*salles)[7]->destination.x + 8*SIZE_TILE,(*salles)[7]->destination.y + 3*SIZE_TILE};
		etapeCourante = 0;
		entites[8] = EntiteCreate(renderer, SLIME_V, etapes, etapeCourante, nbEtapes);

		//Entite 9
		nbEtapes = 1;
		etapes = (Pos_t*)malloc(nbEtapes*sizeof(Pos_t));
			etapes[0] = (Pos_t){(*salles)[7]->destination.x + 9*SIZE_TILE,(*salles)[7]->destination.y + 6*SIZE_TILE};
		etapeCourante = 0;
		entites[9] = EntiteCreate(renderer, SLIME_V, etapes, etapeCourante, nbEtapes);

		//Entite 10
		nbEtapes = 1;
		etapes = (Pos_t*)malloc(nbEtapes*sizeof(Pos_t));
			etapes[0] = (Pos_t){(*salles)[7]->destination.x + 11*SIZE_TILE,(*salles)[7]->destination.y + 4*SIZE_TILE};
		etapeCourante = 0;
		entites[10] = EntiteCreate(renderer, SLIME_V, etapes, etapeCourante, nbEtapes);

		//Entite 11
		nbEtapes = 1;
		etapes = (Pos_t*)malloc(nbEtapes*sizeof(Pos_t));
			etapes[0] = (Pos_t){(*salles)[7]->destination.x + 11*SIZE_TILE,(*salles)[7]->destination.y + 7*SIZE_TILE};
		etapeCourante = 0;
		entites[11] = EntiteCreate(renderer, SLIME_V, etapes, etapeCourante, nbEtapes);

		//Entite 12
		nbEtapes = 1;
		etapes = (Pos_t*)malloc(nbEtapes*sizeof(Pos_t));
			etapes[0] = (Pos_t){(*salles)[7]->destination.x + 13*SIZE_TILE,(*salles)[7]->destination.y + 2*SIZE_TILE};
		etapeCourante = 0;
		entites[12] = EntiteCreate(renderer, SLIME_V, etapes, etapeCourante, nbEtapes);

		//Entite 13
		nbEtapes = 1;
		etapes = (Pos_t*)malloc(nbEtapes*sizeof(Pos_t));
			etapes[0] = (Pos_t){(*salles)[7]->destination.x + 13*SIZE_TILE,(*salles)[7]->destination.y + 7*SIZE_TILE};
		etapeCourante = 0;
		entites[13] = EntiteCreate(renderer, SLIME_R, etapes, etapeCourante, nbEtapes);

		//Entite 14
		nbEtapes = 1;
		etapes = (Pos_t*)malloc(nbEtapes*sizeof(Pos_t));
			etapes[0] = (Pos_t){(*salles)[7]->destination.x + 13*SIZE_TILE,(*salles)[7]->destination.y + 10*SIZE_TILE};
		etapeCourante = 0;
		entites[14] = EntiteCreate(renderer, SLIME_V, etapes, etapeCourante, nbEtapes);

		//Entite 15
		nbEtapes = 1;
		etapes = (Pos_t*)malloc(nbEtapes*sizeof(Pos_t));
			etapes[0] = (Pos_t){(*salles)[7]->destination.x + 14*SIZE_TILE,(*salles)[7]->destination.y + 7*SIZE_TILE};
		etapeCourante = 0;
		entites[15] = EntiteCreate(renderer, SLIME_V, etapes, etapeCourante, nbEtapes);

		//Entite 16
		nbEtapes = 1;
		etapes = (Pos_t*)malloc(nbEtapes*sizeof(Pos_t));
			etapes[0] = (Pos_t){(*salles)[7]->destination.x + 15*SIZE_TILE,(*salles)[7]->destination.y + 12*SIZE_TILE};
		etapeCourante = 0;
		entites[16] = EntiteCreate(renderer, SLIME_V, etapes, etapeCourante, nbEtapes);

	(*salles)[7]->entites = entites;
	(*salles)[7]->nbObjectifs = 15;	
	(*salles)[7]->nbObjectifsVivants = 15;	
	(*salles)[7]->nbEntites = nbEntites;

	//Salle 8
	texture = IMG_LoadTexture(renderer, "assets/Salles/Salle_17x14_Bleu.png");
	(*salles)[8] = SalleCreate(texture, 8, 17, 14);
	nbEntites = 14;
	entites = (Entite_t**)malloc(nbEntites*sizeof(Entite_t*));

		//Entite 0
		nbEtapes = 1;
		etapes = (Pos_t*)malloc(nbEtapes*sizeof(Pos_t));
			etapes[0] = (Pos_t){(*salles)[8]->destination.x + 2*SIZE_TILE,(*salles)[8]->destination.y + 2*SIZE_TILE};
		etapeCourante = 0;
		entites[0]= EntiteCreate(renderer, SLIME_V, etapes, etapeCourante, nbEtapes);

		//Entite 1
		nbEtapes = 1;
		etapes = (Pos_t*)malloc(nbEtapes*sizeof(Pos_t));
			etapes[0] = (Pos_t){(*salles)[8]->destination.x + 14*SIZE_TILE,(*salles)[8]->destination.y + 2*SIZE_TILE};
		etapeCourante = 0;
		entites[1]= EntiteCreate(renderer, SLIME_V, etapes, etapeCourante, nbEtapes);

		//Entite 2
		nbEtapes = 1;
		etapes = (Pos_t*)malloc(nbEtapes*sizeof(Pos_t));
			etapes[0] = (Pos_t){(*salles)[8]->destination.x + 2*SIZE_TILE,(*salles)[8]->destination.y + 11*SIZE_TILE};
		etapeCourante = 0;
		entites[2]= EntiteCreate(renderer, SLIME_V, etapes, etapeCourante, nbEtapes);

		//Entite 3
		nbEtapes = 1;
		etapes = (Pos_t*)malloc(nbEtapes*sizeof(Pos_t));
			etapes[0] = (Pos_t){(*salles)[8]->destination.x + 14*SIZE_TILE,(*salles)[8]->destination.y + 11*SIZE_TILE};
		etapeCourante = 0;
		entites[3]= EntiteCreate(renderer, SLIME_V, etapes, etapeCourante, nbEtapes);

		//Entite 4
		nbEtapes = 14;
		etapes = (Pos_t*)malloc(nbEtapes*sizeof(Pos_t));
			etapes[0] = (Pos_t){(*salles)[8]->destination.x + 5*SIZE_TILE,(*salles)[8]->destination.y + 3*SIZE_TILE};
			etapes[1] = (Pos_t){(*salles)[8]->destination.x + 6*SIZE_TILE,(*salles)[8]->destination.y + 3*SIZE_TILE};
			etapes[2] = (Pos_t){(*salles)[8]->destination.x + 7*SIZE_TILE,(*salles)[8]->destination.y + 3*SIZE_TILE};
			etapes[3] = (Pos_t){(*salles)[8]->destination.x + 8*SIZE_TILE,(*salles)[8]->destination.y + 3*SIZE_TILE};
			etapes[4] = (Pos_t){(*salles)[8]->destination.x + 7*SIZE_TILE,(*salles)[8]->destination.y + 3*SIZE_TILE};
			etapes[5] = (Pos_t){(*salles)[8]->destination.x + 6*SIZE_TILE,(*salles)[8]->destination.y + 3*SIZE_TILE};
			etapes[6] = (Pos_t){(*salles)[8]->destination.x + 5*SIZE_TILE,(*salles)[8]->destination.y + 3*SIZE_TILE};
			etapes[7] = (Pos_t){(*salles)[8]->destination.x + 4*SIZE_TILE,(*salles)[8]->destination.y + 3*SIZE_TILE};
			etapes[8] = (Pos_t){(*salles)[8]->destination.x + 3*SIZE_TILE,(*salles)[8]->destination.y + 3*SIZE_TILE};
			etapes[9] = (Pos_t){(*salles)[8]->destination.x + 2*SIZE_TILE,(*salles)[8]->destination.y + 3*SIZE_TILE};
			etapes[10] = (Pos_t){(*salles)[8]->destination.x + 1*SIZE_TILE,(*salles)[8]->destination.y + 3*SIZE_TILE};
			etapes[11] = (Pos_t){(*salles)[8]->destination.x + 2*SIZE_TILE,(*salles)[8]->destination.y + 3*SIZE_TILE};
			etapes[12] = (Pos_t){(*salles)[8]->destination.x + 3*SIZE_TILE,(*salles)[8]->destination.y + 3*SIZE_TILE};
			etapes[13] = (Pos_t){(*salles)[8]->destination.x + 4*SIZE_TILE,(*salles)[8]->destination.y + 3*SIZE_TILE};
		etapeCourante = 0;
		entites[4]= EntiteCreate(renderer, SLIME_R, etapes, etapeCourante, nbEtapes);

		//Entite 5
		nbEtapes = 12;
		etapes = (Pos_t*)malloc(nbEtapes*sizeof(Pos_t));
			etapes[0] = (Pos_t){(*salles)[8]->destination.x + 9*SIZE_TILE,(*salles)[8]->destination.y + 3*SIZE_TILE};
			etapes[1] = (Pos_t){(*salles)[8]->destination.x + 10*SIZE_TILE,(*salles)[8]->destination.y + 3*SIZE_TILE};
			etapes[2] = (Pos_t){(*salles)[8]->destination.x + 11*SIZE_TILE,(*salles)[8]->destination.y + 3*SIZE_TILE};
			etapes[3] = (Pos_t){(*salles)[8]->destination.x + 12*SIZE_TILE,(*salles)[8]->destination.y + 3*SIZE_TILE};
			etapes[4] = (Pos_t){(*salles)[8]->destination.x + 13*SIZE_TILE,(*salles)[8]->destination.y + 3*SIZE_TILE};
			etapes[5] = (Pos_t){(*salles)[8]->destination.x + 14*SIZE_TILE,(*salles)[8]->destination.y + 3*SIZE_TILE};
			etapes[6] = (Pos_t){(*salles)[8]->destination.x + 15*SIZE_TILE,(*salles)[8]->destination.y + 3*SIZE_TILE};
			etapes[7] = (Pos_t){(*salles)[8]->destination.x + 14*SIZE_TILE,(*salles)[8]->destination.y + 3*SIZE_TILE};
			etapes[8] = (Pos_t){(*salles)[8]->destination.x + 13*SIZE_TILE,(*salles)[8]->destination.y + 3*SIZE_TILE};
			etapes[9] = (Pos_t){(*salles)[8]->destination.x + 12*SIZE_TILE,(*salles)[8]->destination.y + 3*SIZE_TILE};
			etapes[10] = (Pos_t){(*salles)[8]->destination.x + 11*SIZE_TILE,(*salles)[8]->destination.y + 3*SIZE_TILE};
			etapes[11] = (Pos_t){(*salles)[8]->destination.x + 10*SIZE_TILE,(*salles)[8]->destination.y + 3*SIZE_TILE};
		etapeCourante = 0;
		entites[5]= EntiteCreate(renderer, SLIME_R, etapes, etapeCourante, nbEtapes);

		//Entite 6
		nbEtapes = 12;
		etapes = (Pos_t*)malloc(nbEtapes*sizeof(Pos_t));
			etapes[0] = (Pos_t){(*salles)[8]->destination.x + 4*SIZE_TILE,(*salles)[8]->destination.y + 4*SIZE_TILE};
			etapes[1] = (Pos_t){(*salles)[8]->destination.x + 3*SIZE_TILE,(*salles)[8]->destination.y + 4*SIZE_TILE};
			etapes[2] = (Pos_t){(*salles)[8]->destination.x + 2*SIZE_TILE,(*salles)[8]->destination.y + 4*SIZE_TILE};
			etapes[3] = (Pos_t){(*salles)[8]->destination.x + 1*SIZE_TILE,(*salles)[8]->destination.y + 4*SIZE_TILE};
			etapes[4] = (Pos_t){(*salles)[8]->destination.x + 2*SIZE_TILE,(*salles)[8]->destination.y + 4*SIZE_TILE};
			etapes[5] = (Pos_t){(*salles)[8]->destination.x + 3*SIZE_TILE,(*salles)[8]->destination.y + 4*SIZE_TILE};
			etapes[6] = (Pos_t){(*salles)[8]->destination.x + 4*SIZE_TILE,(*salles)[8]->destination.y + 4*SIZE_TILE};
			etapes[7] = (Pos_t){(*salles)[8]->destination.x + 5*SIZE_TILE,(*salles)[8]->destination.y + 4*SIZE_TILE};
			etapes[8] = (Pos_t){(*salles)[8]->destination.x + 6*SIZE_TILE,(*salles)[8]->destination.y + 4*SIZE_TILE};
			etapes[9] = (Pos_t){(*salles)[8]->destination.x + 7*SIZE_TILE,(*salles)[8]->destination.y + 4*SIZE_TILE};
			etapes[10] = (Pos_t){(*salles)[8]->destination.x + 6*SIZE_TILE,(*salles)[8]->destination.y + 4*SIZE_TILE};
			etapes[11] = (Pos_t){(*salles)[8]->destination.x + 5*SIZE_TILE,(*salles)[8]->destination.y + 4*SIZE_TILE};
		etapeCourante = 0;
		entites[6]= EntiteCreate(renderer, SLIME_R, etapes, etapeCourante, nbEtapes);

		//Entite 7
		nbEtapes = 14;
		etapes = (Pos_t*)malloc(nbEtapes*sizeof(Pos_t));
			etapes[0] = (Pos_t){(*salles)[8]->destination.x + 14*SIZE_TILE,(*salles)[8]->destination.y + 4*SIZE_TILE};
			etapes[1] = (Pos_t){(*salles)[8]->destination.x + 13*SIZE_TILE,(*salles)[8]->destination.y + 4*SIZE_TILE};
			etapes[2] = (Pos_t){(*salles)[8]->destination.x + 12*SIZE_TILE,(*salles)[8]->destination.y + 4*SIZE_TILE};
			etapes[3] = (Pos_t){(*salles)[8]->destination.x + 11*SIZE_TILE,(*salles)[8]->destination.y + 4*SIZE_TILE};
			etapes[4] = (Pos_t){(*salles)[8]->destination.x + 10*SIZE_TILE,(*salles)[8]->destination.y + 4*SIZE_TILE};
			etapes[5] = (Pos_t){(*salles)[8]->destination.x + 9*SIZE_TILE,(*salles)[8]->destination.y + 4*SIZE_TILE};
			etapes[6] = (Pos_t){(*salles)[8]->destination.x + 8*SIZE_TILE,(*salles)[8]->destination.y + 4*SIZE_TILE};
			etapes[7] = (Pos_t){(*salles)[8]->destination.x + 9*SIZE_TILE,(*salles)[8]->destination.y + 4*SIZE_TILE};
			etapes[8] = (Pos_t){(*salles)[8]->destination.x + 10*SIZE_TILE,(*salles)[8]->destination.y + 4*SIZE_TILE};
			etapes[9] = (Pos_t){(*salles)[8]->destination.x + 11*SIZE_TILE,(*salles)[8]->destination.y + 4*SIZE_TILE};
			etapes[10] = (Pos_t){(*salles)[8]->destination.x + 12*SIZE_TILE,(*salles)[8]->destination.y + 4*SIZE_TILE};
			etapes[11] = (Pos_t){(*salles)[8]->destination.x + 13*SIZE_TILE,(*salles)[8]->destination.y + 4*SIZE_TILE};
			etapes[12] = (Pos_t){(*salles)[8]->destination.x + 14*SIZE_TILE,(*salles)[8]->destination.y + 4*SIZE_TILE};
			etapes[13] = (Pos_t){(*salles)[8]->destination.x + 15*SIZE_TILE,(*salles)[8]->destination.y + 4*SIZE_TILE};
		etapeCourante = 0;
		entites[7]= EntiteCreate(renderer, SLIME_R, etapes, etapeCourante, nbEtapes);

		//Entite 8
		nbEtapes = 14;
		etapes = (Pos_t*)malloc(nbEtapes*sizeof(Pos_t));
			etapes[0] = (Pos_t){(*salles)[8]->destination.x + 6*SIZE_TILE,(*salles)[8]->destination.y + 5*SIZE_TILE};
			etapes[1] = (Pos_t){(*salles)[8]->destination.x + 7*SIZE_TILE,(*salles)[8]->destination.y + 5*SIZE_TILE};
			etapes[2] = (Pos_t){(*salles)[8]->destination.x + 8*SIZE_TILE,(*salles)[8]->destination.y + 5*SIZE_TILE};
			etapes[3] = (Pos_t){(*salles)[8]->destination.x + 7*SIZE_TILE,(*salles)[8]->destination.y + 5*SIZE_TILE};
			etapes[4] = (Pos_t){(*salles)[8]->destination.x + 6*SIZE_TILE,(*salles)[8]->destination.y + 5*SIZE_TILE};
			etapes[5] = (Pos_t){(*salles)[8]->destination.x + 5*SIZE_TILE,(*salles)[8]->destination.y + 5*SIZE_TILE};
			etapes[6] = (Pos_t){(*salles)[8]->destination.x + 4*SIZE_TILE,(*salles)[8]->destination.y + 5*SIZE_TILE};
			etapes[7] = (Pos_t){(*salles)[8]->destination.x + 3*SIZE_TILE,(*salles)[8]->destination.y + 5*SIZE_TILE};
			etapes[8] = (Pos_t){(*salles)[8]->destination.x + 2*SIZE_TILE,(*salles)[8]->destination.y + 5*SIZE_TILE};
			etapes[9] = (Pos_t){(*salles)[8]->destination.x + 1*SIZE_TILE,(*salles)[8]->destination.y + 5*SIZE_TILE};
			etapes[10] = (Pos_t){(*salles)[8]->destination.x + 2*SIZE_TILE,(*salles)[8]->destination.y + 5*SIZE_TILE};
			etapes[11] = (Pos_t){(*salles)[8]->destination.x + 3*SIZE_TILE,(*salles)[8]->destination.y + 5*SIZE_TILE};
			etapes[12] = (Pos_t){(*salles)[8]->destination.x + 4*SIZE_TILE,(*salles)[8]->destination.y + 5*SIZE_TILE};
			etapes[13] = (Pos_t){(*salles)[8]->destination.x + 5*SIZE_TILE,(*salles)[8]->destination.y + 5*SIZE_TILE};
		etapeCourante = 0;
		entites[8]= EntiteCreate(renderer, SLIME_R, etapes, etapeCourante, nbEtapes);

		//Entite 9
		nbEtapes = 12;
		etapes = (Pos_t*)malloc(nbEtapes*sizeof(Pos_t));
			etapes[0] = (Pos_t){(*salles)[8]->destination.x + 11*SIZE_TILE,(*salles)[8]->destination.y + 5*SIZE_TILE};
			etapes[1] = (Pos_t){(*salles)[8]->destination.x + 12*SIZE_TILE,(*salles)[8]->destination.y + 5*SIZE_TILE};
			etapes[2] = (Pos_t){(*salles)[8]->destination.x + 13*SIZE_TILE,(*salles)[8]->destination.y + 5*SIZE_TILE};
			etapes[3] = (Pos_t){(*salles)[8]->destination.x + 14*SIZE_TILE,(*salles)[8]->destination.y + 5*SIZE_TILE};
			etapes[4] = (Pos_t){(*salles)[8]->destination.x + 15*SIZE_TILE,(*salles)[8]->destination.y + 5*SIZE_TILE};
			etapes[5] = (Pos_t){(*salles)[8]->destination.x + 14*SIZE_TILE,(*salles)[8]->destination.y + 5*SIZE_TILE};
			etapes[6] = (Pos_t){(*salles)[8]->destination.x + 13*SIZE_TILE,(*salles)[8]->destination.y + 5*SIZE_TILE};
			etapes[7] = (Pos_t){(*salles)[8]->destination.x + 12*SIZE_TILE,(*salles)[8]->destination.y + 5*SIZE_TILE};
			etapes[8] = (Pos_t){(*salles)[8]->destination.x + 11*SIZE_TILE,(*salles)[8]->destination.y + 5*SIZE_TILE};
			etapes[9] = (Pos_t){(*salles)[8]->destination.x + 10*SIZE_TILE,(*salles)[8]->destination.y + 5*SIZE_TILE};
			etapes[10] = (Pos_t){(*salles)[8]->destination.x + 9*SIZE_TILE,(*salles)[8]->destination.y + 5*SIZE_TILE};
			etapes[11] = (Pos_t){(*salles)[8]->destination.x + 10*SIZE_TILE,(*salles)[8]->destination.y + 5*SIZE_TILE};
		etapeCourante = 0;
		entites[9]= EntiteCreate(renderer, SLIME_R, etapes, etapeCourante, nbEtapes);

		//Entite 10
		nbEtapes = 12;
		etapes = (Pos_t*)malloc(nbEtapes*sizeof(Pos_t));
			etapes[0] = (Pos_t){(*salles)[8]->destination.x + 3*SIZE_TILE,(*salles)[8]->destination.y + 6*SIZE_TILE};
			etapes[1] = (Pos_t){(*salles)[8]->destination.x + 2*SIZE_TILE,(*salles)[8]->destination.y + 6*SIZE_TILE};
			etapes[2] = (Pos_t){(*salles)[8]->destination.x + 1*SIZE_TILE,(*salles)[8]->destination.y + 6*SIZE_TILE};
			etapes[3] = (Pos_t){(*salles)[8]->destination.x + 2*SIZE_TILE,(*salles)[8]->destination.y + 6*SIZE_TILE};
			etapes[4] = (Pos_t){(*salles)[8]->destination.x + 3*SIZE_TILE,(*salles)[8]->destination.y + 6*SIZE_TILE};
			etapes[5] = (Pos_t){(*salles)[8]->destination.x + 4*SIZE_TILE,(*salles)[8]->destination.y + 6*SIZE_TILE};
			etapes[6] = (Pos_t){(*salles)[8]->destination.x + 5*SIZE_TILE,(*salles)[8]->destination.y + 6*SIZE_TILE};
			etapes[7] = (Pos_t){(*salles)[8]->destination.x + 6*SIZE_TILE,(*salles)[8]->destination.y + 6*SIZE_TILE};
			etapes[8] = (Pos_t){(*salles)[8]->destination.x + 7*SIZE_TILE,(*salles)[8]->destination.y + 6*SIZE_TILE};
			etapes[9] = (Pos_t){(*salles)[8]->destination.x + 6*SIZE_TILE,(*salles)[8]->destination.y + 6*SIZE_TILE};
			etapes[10] = (Pos_t){(*salles)[8]->destination.x + 5*SIZE_TILE,(*salles)[8]->destination.y + 6*SIZE_TILE};
			etapes[11] = (Pos_t){(*salles)[8]->destination.x + 4*SIZE_TILE,(*salles)[8]->destination.y + 6*SIZE_TILE};
		etapeCourante = 0;
		entites[10]= EntiteCreate(renderer, SLIME_R, etapes, etapeCourante, nbEtapes);

		//Entite 11
		nbEtapes = 14;
		etapes = (Pos_t*)malloc(nbEtapes*sizeof(Pos_t));
			etapes[0] = (Pos_t){(*salles)[8]->destination.x + 13*SIZE_TILE,(*salles)[8]->destination.y + 6*SIZE_TILE};
			etapes[1] = (Pos_t){(*salles)[8]->destination.x + 12*SIZE_TILE,(*salles)[8]->destination.y + 6*SIZE_TILE};
			etapes[2] = (Pos_t){(*salles)[8]->destination.x + 11*SIZE_TILE,(*salles)[8]->destination.y + 6*SIZE_TILE};
			etapes[3] = (Pos_t){(*salles)[8]->destination.x + 10*SIZE_TILE,(*salles)[8]->destination.y + 6*SIZE_TILE};
			etapes[4] = (Pos_t){(*salles)[8]->destination.x + 9*SIZE_TILE,(*salles)[8]->destination.y + 6*SIZE_TILE};
			etapes[5] = (Pos_t){(*salles)[8]->destination.x + 8*SIZE_TILE,(*salles)[8]->destination.y + 6*SIZE_TILE};
			etapes[6] = (Pos_t){(*salles)[8]->destination.x + 9*SIZE_TILE,(*salles)[8]->destination.y + 6*SIZE_TILE};
			etapes[7] = (Pos_t){(*salles)[8]->destination.x + 10*SIZE_TILE,(*salles)[8]->destination.y + 6*SIZE_TILE};
			etapes[8] = (Pos_t){(*salles)[8]->destination.x + 11*SIZE_TILE,(*salles)[8]->destination.y + 6*SIZE_TILE};
			etapes[9] = (Pos_t){(*salles)[8]->destination.x + 12*SIZE_TILE,(*salles)[8]->destination.y + 6*SIZE_TILE};
			etapes[10] = (Pos_t){(*salles)[8]->destination.x + 13*SIZE_TILE,(*salles)[8]->destination.y + 6*SIZE_TILE};
			etapes[11] = (Pos_t){(*salles)[8]->destination.x + 14*SIZE_TILE,(*salles)[8]->destination.y + 6*SIZE_TILE};
			etapes[12] = (Pos_t){(*salles)[8]->destination.x + 15*SIZE_TILE,(*salles)[8]->destination.y + 6*SIZE_TILE};
			etapes[13] = (Pos_t){(*salles)[8]->destination.x + 14*SIZE_TILE,(*salles)[8]->destination.y + 6*SIZE_TILE};
		etapeCourante = 0;
		entites[11]= EntiteCreate(renderer, SLIME_R, etapes, etapeCourante, nbEtapes);

		//Entite 12
		nbEtapes = 14;
		etapes = (Pos_t*)malloc(nbEtapes*sizeof(Pos_t));
			etapes[0] = (Pos_t){(*salles)[8]->destination.x + 2*SIZE_TILE,(*salles)[8]->destination.y + 7*SIZE_TILE};
			etapes[1] = (Pos_t){(*salles)[8]->destination.x + 1*SIZE_TILE,(*salles)[8]->destination.y + 7*SIZE_TILE};
			etapes[2] = (Pos_t){(*salles)[8]->destination.x + 2*SIZE_TILE,(*salles)[8]->destination.y + 7*SIZE_TILE};
			etapes[3] = (Pos_t){(*salles)[8]->destination.x + 3*SIZE_TILE,(*salles)[8]->destination.y + 7*SIZE_TILE};
			etapes[4] = (Pos_t){(*salles)[8]->destination.x + 4*SIZE_TILE,(*salles)[8]->destination.y + 7*SIZE_TILE};
			etapes[5] = (Pos_t){(*salles)[8]->destination.x + 5*SIZE_TILE,(*salles)[8]->destination.y + 7*SIZE_TILE};
			etapes[6] = (Pos_t){(*salles)[8]->destination.x + 6*SIZE_TILE,(*salles)[8]->destination.y + 7*SIZE_TILE};
			etapes[7] = (Pos_t){(*salles)[8]->destination.x + 7*SIZE_TILE,(*salles)[8]->destination.y + 7*SIZE_TILE};
			etapes[8] = (Pos_t){(*salles)[8]->destination.x + 8*SIZE_TILE,(*salles)[8]->destination.y + 7*SIZE_TILE};
			etapes[9] = (Pos_t){(*salles)[8]->destination.x + 9*SIZE_TILE,(*salles)[8]->destination.y + 7*SIZE_TILE};
			etapes[10] = (Pos_t){(*salles)[8]->destination.x + 8*SIZE_TILE,(*salles)[8]->destination.y + 7*SIZE_TILE};
			etapes[11] = (Pos_t){(*salles)[8]->destination.x + 7*SIZE_TILE,(*salles)[8]->destination.y + 7*SIZE_TILE};
			etapes[12] = (Pos_t){(*salles)[8]->destination.x + 6*SIZE_TILE,(*salles)[8]->destination.y + 7*SIZE_TILE};
			etapes[13] = (Pos_t){(*salles)[8]->destination.x + 5*SIZE_TILE,(*salles)[8]->destination.y + 7*SIZE_TILE};
		etapeCourante = 0;
		entites[12]= EntiteCreate(renderer, SLIME_R, etapes, etapeCourante, nbEtapes);

		//Entite 13
		nbEtapes = 12;
		etapes = (Pos_t*)malloc(nbEtapes*sizeof(Pos_t));
			etapes[0] = (Pos_t){(*salles)[8]->destination.x + 10*SIZE_TILE,(*salles)[8]->destination.y + 7*SIZE_TILE};
			etapes[1] = (Pos_t){(*salles)[8]->destination.x + 9*SIZE_TILE,(*salles)[8]->destination.y + 7*SIZE_TILE};
			etapes[2] = (Pos_t){(*salles)[8]->destination.x + 10*SIZE_TILE,(*salles)[8]->destination.y + 7*SIZE_TILE};
			etapes[3] = (Pos_t){(*salles)[8]->destination.x + 11*SIZE_TILE,(*salles)[8]->destination.y + 7*SIZE_TILE};
			etapes[4] = (Pos_t){(*salles)[8]->destination.x + 12*SIZE_TILE,(*salles)[8]->destination.y + 7*SIZE_TILE};
			etapes[5] = (Pos_t){(*salles)[8]->destination.x + 13*SIZE_TILE,(*salles)[8]->destination.y + 7*SIZE_TILE};
			etapes[6] = (Pos_t){(*salles)[8]->destination.x + 14*SIZE_TILE,(*salles)[8]->destination.y + 7*SIZE_TILE};
			etapes[7] = (Pos_t){(*salles)[8]->destination.x + 15*SIZE_TILE,(*salles)[8]->destination.y + 7*SIZE_TILE};
			etapes[8] = (Pos_t){(*salles)[8]->destination.x + 14*SIZE_TILE,(*salles)[8]->destination.y + 7*SIZE_TILE};
			etapes[9] = (Pos_t){(*salles)[8]->destination.x + 13*SIZE_TILE,(*salles)[8]->destination.y + 7*SIZE_TILE};
			etapes[10] = (Pos_t){(*salles)[8]->destination.x + 12*SIZE_TILE,(*salles)[8]->destination.y + 7*SIZE_TILE};
			etapes[11] = (Pos_t){(*salles)[8]->destination.x + 11*SIZE_TILE,(*salles)[8]->destination.y + 7*SIZE_TILE};
		etapeCourante = 0;
		entites[13]= EntiteCreate(renderer, SLIME_R, etapes, etapeCourante, nbEtapes);

	(*salles)[8]->entites = entites;
	(*salles)[8]->nbObjectifs = 4;	
	(*salles)[8]->nbObjectifsVivants = 4;	
	(*salles)[8]->nbEntites = nbEntites;

	//Salle 9
	texture = IMG_LoadTexture(renderer, "assets/Salles/Salle_17x14_Jaune.png");
	(*salles)[9] = SalleCreate(texture, 9, 17, 14);
	nbEntites = 29;
	entites = (Entite_t**)malloc(nbEntites*sizeof(Entite_t*));

		//Entite 0
		nbEtapes = 16;
		etapes = (Pos_t*)malloc(nbEtapes*sizeof(Pos_t));
			etapes[0] = (Pos_t){(*salles)[9]->destination.x + 6*SIZE_TILE,(*salles)[9]->destination.y + 3*SIZE_TILE};
			etapes[1] = (Pos_t){(*salles)[9]->destination.x + 7*SIZE_TILE,(*salles)[9]->destination.y + 3*SIZE_TILE};
			etapes[2] = (Pos_t){(*salles)[9]->destination.x + 8*SIZE_TILE,(*salles)[9]->destination.y + 3*SIZE_TILE};
			etapes[3] = (Pos_t){(*salles)[9]->destination.x + 9*SIZE_TILE,(*salles)[9]->destination.y + 3*SIZE_TILE};
			etapes[4] = (Pos_t){(*salles)[9]->destination.x + 10*SIZE_TILE,(*salles)[9]->destination.y + 3*SIZE_TILE};
			etapes[5] = (Pos_t){(*salles)[9]->destination.x + 10*SIZE_TILE,(*salles)[9]->destination.y + 4*SIZE_TILE};
			etapes[6] = (Pos_t){(*salles)[9]->destination.x + 10*SIZE_TILE,(*salles)[9]->destination.y + 5*SIZE_TILE};
			etapes[7] = (Pos_t){(*salles)[9]->destination.x + 10*SIZE_TILE,(*salles)[9]->destination.y + 6*SIZE_TILE};
			etapes[8] = (Pos_t){(*salles)[9]->destination.x + 10*SIZE_TILE,(*salles)[9]->destination.y + 7*SIZE_TILE};
			etapes[9] = (Pos_t){(*salles)[9]->destination.x + 9*SIZE_TILE,(*salles)[9]->destination.y + 7*SIZE_TILE};
			etapes[10] = (Pos_t){(*salles)[9]->destination.x + 8*SIZE_TILE,(*salles)[9]->destination.y + 7*SIZE_TILE};
			etapes[11] = (Pos_t){(*salles)[9]->destination.x + 7*SIZE_TILE,(*salles)[9]->destination.y + 7*SIZE_TILE};
			etapes[12] = (Pos_t){(*salles)[9]->destination.x + 6*SIZE_TILE,(*salles)[9]->destination.y + 7*SIZE_TILE};
			etapes[13] = (Pos_t){(*salles)[9]->destination.x + 6*SIZE_TILE,(*salles)[9]->destination.y + 6*SIZE_TILE};
			etapes[14] = (Pos_t){(*salles)[9]->destination.x + 6*SIZE_TILE,(*salles)[9]->destination.y + 5*SIZE_TILE};
			etapes[15] = (Pos_t){(*salles)[9]->destination.x + 6*SIZE_TILE,(*salles)[9]->destination.y + 4*SIZE_TILE};
		etapeCourante = 0;
		entites[0]= EntiteCreate(renderer, SLIME_V, etapes, etapeCourante, nbEtapes);

		//Entite 1
		nbEtapes = 1;
		etapes = (Pos_t*)malloc(nbEtapes*sizeof(Pos_t));
			etapes[0] = (Pos_t){(*salles)[9]->destination.x + 8*SIZE_TILE,(*salles)[9]->destination.y + 5*SIZE_TILE};
		etapeCourante = 0;
		entites[1]= EntiteCreate(renderer, SLIME_V, etapes, etapeCourante, nbEtapes);

		//Entite 2
		nbEtapes = 16;
		etapes = (Pos_t*)malloc(nbEtapes*sizeof(Pos_t));
			etapes[0] = (Pos_t){(*salles)[9]->destination.x + 8*SIZE_TILE,(*salles)[9]->destination.y + 6*SIZE_TILE};
			etapes[1] = (Pos_t){(*salles)[9]->destination.x + 7*SIZE_TILE,(*salles)[9]->destination.y + 6*SIZE_TILE};
			etapes[2] = (Pos_t){(*salles)[9]->destination.x + 7*SIZE_TILE,(*salles)[9]->destination.y + 6*SIZE_TILE};
			etapes[3] = (Pos_t){(*salles)[9]->destination.x + 7*SIZE_TILE,(*salles)[9]->destination.y + 6*SIZE_TILE};
			etapes[4] = (Pos_t){(*salles)[9]->destination.x + 7*SIZE_TILE,(*salles)[9]->destination.y + 5*SIZE_TILE};
			etapes[5] = (Pos_t){(*salles)[9]->destination.x + 7*SIZE_TILE,(*salles)[9]->destination.y + 4*SIZE_TILE};
			etapes[6] = (Pos_t){(*salles)[9]->destination.x + 7*SIZE_TILE,(*salles)[9]->destination.y + 4*SIZE_TILE};
			etapes[7] = (Pos_t){(*salles)[9]->destination.x + 7*SIZE_TILE,(*salles)[9]->destination.y + 4*SIZE_TILE};
			etapes[8] = (Pos_t){(*salles)[9]->destination.x + 8*SIZE_TILE,(*salles)[9]->destination.y + 4*SIZE_TILE};
			etapes[9] = (Pos_t){(*salles)[9]->destination.x + 9*SIZE_TILE,(*salles)[9]->destination.y + 4*SIZE_TILE};
			etapes[10] = (Pos_t){(*salles)[9]->destination.x + 9*SIZE_TILE,(*salles)[9]->destination.y + 4*SIZE_TILE};
			etapes[11] = (Pos_t){(*salles)[9]->destination.x + 9*SIZE_TILE,(*salles)[9]->destination.y + 4*SIZE_TILE};
			etapes[12] = (Pos_t){(*salles)[9]->destination.x + 9*SIZE_TILE,(*salles)[9]->destination.y + 5*SIZE_TILE};
			etapes[13] = (Pos_t){(*salles)[9]->destination.x + 9*SIZE_TILE,(*salles)[9]->destination.y + 6*SIZE_TILE};
			etapes[14] = (Pos_t){(*salles)[9]->destination.x + 9*SIZE_TILE,(*salles)[9]->destination.y + 6*SIZE_TILE};
			etapes[15] = (Pos_t){(*salles)[9]->destination.x + 9*SIZE_TILE,(*salles)[9]->destination.y + 6*SIZE_TILE};
		etapeCourante = 0;
		entites[2]= EntiteCreate(renderer, SLIME_R, etapes, etapeCourante, nbEtapes);

		//Entite 3
		nbEtapes = 16;
		etapes = (Pos_t*)malloc(nbEtapes*sizeof(Pos_t));
			etapes[0] = (Pos_t){(*salles)[9]->destination.x + 7*SIZE_TILE,(*salles)[9]->destination.y + 5*SIZE_TILE};
			etapes[1] = (Pos_t){(*salles)[9]->destination.x + 7*SIZE_TILE,(*salles)[9]->destination.y + 4*SIZE_TILE};
			etapes[2] = (Pos_t){(*salles)[9]->destination.x + 7*SIZE_TILE,(*salles)[9]->destination.y + 4*SIZE_TILE};
			etapes[3] = (Pos_t){(*salles)[9]->destination.x + 7*SIZE_TILE,(*salles)[9]->destination.y + 4*SIZE_TILE};
			etapes[4] = (Pos_t){(*salles)[9]->destination.x + 8*SIZE_TILE,(*salles)[9]->destination.y + 4*SIZE_TILE};
			etapes[5] = (Pos_t){(*salles)[9]->destination.x + 9*SIZE_TILE,(*salles)[9]->destination.y + 4*SIZE_TILE};
			etapes[6] = (Pos_t){(*salles)[9]->destination.x + 9*SIZE_TILE,(*salles)[9]->destination.y + 4*SIZE_TILE};
			etapes[7] = (Pos_t){(*salles)[9]->destination.x + 9*SIZE_TILE,(*salles)[9]->destination.y + 4*SIZE_TILE};
			etapes[8] = (Pos_t){(*salles)[9]->destination.x + 9*SIZE_TILE,(*salles)[9]->destination.y + 5*SIZE_TILE};
			etapes[9] = (Pos_t){(*salles)[9]->destination.x + 9*SIZE_TILE,(*salles)[9]->destination.y + 6*SIZE_TILE};
			etapes[10] = (Pos_t){(*salles)[9]->destination.x + 9*SIZE_TILE,(*salles)[9]->destination.y + 6*SIZE_TILE};
			etapes[11] = (Pos_t){(*salles)[9]->destination.x + 9*SIZE_TILE,(*salles)[9]->destination.y + 6*SIZE_TILE};
			etapes[12] = (Pos_t){(*salles)[9]->destination.x + 8*SIZE_TILE,(*salles)[9]->destination.y + 6*SIZE_TILE};
			etapes[13] = (Pos_t){(*salles)[9]->destination.x + 7*SIZE_TILE,(*salles)[9]->destination.y + 6*SIZE_TILE};
			etapes[14] = (Pos_t){(*salles)[9]->destination.x + 7*SIZE_TILE,(*salles)[9]->destination.y + 6*SIZE_TILE};
			etapes[15] = (Pos_t){(*salles)[9]->destination.x + 7*SIZE_TILE,(*salles)[9]->destination.y + 6*SIZE_TILE};
		etapeCourante = 0;
		entites[3]= EntiteCreate(renderer, SLIME_R, etapes, etapeCourante, nbEtapes);

		//Entite 4
		nbEtapes = 16;
		etapes = (Pos_t*)malloc(nbEtapes*sizeof(Pos_t));
			etapes[0] = (Pos_t){(*salles)[9]->destination.x + 8*SIZE_TILE,(*salles)[9]->destination.y + 4*SIZE_TILE};
			etapes[1] = (Pos_t){(*salles)[9]->destination.x + 9*SIZE_TILE,(*salles)[9]->destination.y + 4*SIZE_TILE};
			etapes[2] = (Pos_t){(*salles)[9]->destination.x + 9*SIZE_TILE,(*salles)[9]->destination.y + 4*SIZE_TILE};
			etapes[3] = (Pos_t){(*salles)[9]->destination.x + 9*SIZE_TILE,(*salles)[9]->destination.y + 4*SIZE_TILE};
			etapes[4] = (Pos_t){(*salles)[9]->destination.x + 9*SIZE_TILE,(*salles)[9]->destination.y + 5*SIZE_TILE};
			etapes[5] = (Pos_t){(*salles)[9]->destination.x + 9*SIZE_TILE,(*salles)[9]->destination.y + 6*SIZE_TILE};
			etapes[6] = (Pos_t){(*salles)[9]->destination.x + 9*SIZE_TILE,(*salles)[9]->destination.y + 6*SIZE_TILE};
			etapes[7] = (Pos_t){(*salles)[9]->destination.x + 9*SIZE_TILE,(*salles)[9]->destination.y + 6*SIZE_TILE};
			etapes[8] = (Pos_t){(*salles)[9]->destination.x + 8*SIZE_TILE,(*salles)[9]->destination.y + 6*SIZE_TILE};
			etapes[9] = (Pos_t){(*salles)[9]->destination.x + 7*SIZE_TILE,(*salles)[9]->destination.y + 6*SIZE_TILE};
			etapes[10] = (Pos_t){(*salles)[9]->destination.x + 7*SIZE_TILE,(*salles)[9]->destination.y + 6*SIZE_TILE};
			etapes[11] = (Pos_t){(*salles)[9]->destination.x + 7*SIZE_TILE,(*salles)[9]->destination.y + 6*SIZE_TILE};
			etapes[12] = (Pos_t){(*salles)[9]->destination.x + 7*SIZE_TILE,(*salles)[9]->destination.y + 5*SIZE_TILE};
			etapes[13] = (Pos_t){(*salles)[9]->destination.x + 7*SIZE_TILE,(*salles)[9]->destination.y + 4*SIZE_TILE};
			etapes[14] = (Pos_t){(*salles)[9]->destination.x + 7*SIZE_TILE,(*salles)[9]->destination.y + 4*SIZE_TILE};
			etapes[15] = (Pos_t){(*salles)[9]->destination.x + 7*SIZE_TILE,(*salles)[9]->destination.y + 4*SIZE_TILE};
		etapeCourante = 0;
		entites[4]= EntiteCreate(renderer, SLIME_R, etapes, etapeCourante, nbEtapes);

		//Entite 5
		nbEtapes = 16;
		etapes = (Pos_t*)malloc(nbEtapes*sizeof(Pos_t));
			etapes[0] = (Pos_t){(*salles)[9]->destination.x + 9*SIZE_TILE,(*salles)[9]->destination.y + 5*SIZE_TILE};
			etapes[1] = (Pos_t){(*salles)[9]->destination.x + 9*SIZE_TILE,(*salles)[9]->destination.y + 6*SIZE_TILE};
			etapes[2] = (Pos_t){(*salles)[9]->destination.x + 9*SIZE_TILE,(*salles)[9]->destination.y + 6*SIZE_TILE};
			etapes[3] = (Pos_t){(*salles)[9]->destination.x + 9*SIZE_TILE,(*salles)[9]->destination.y + 6*SIZE_TILE};
			etapes[4] = (Pos_t){(*salles)[9]->destination.x + 8*SIZE_TILE,(*salles)[9]->destination.y + 6*SIZE_TILE};
			etapes[5] = (Pos_t){(*salles)[9]->destination.x + 7*SIZE_TILE,(*salles)[9]->destination.y + 6*SIZE_TILE};
			etapes[6] = (Pos_t){(*salles)[9]->destination.x + 7*SIZE_TILE,(*salles)[9]->destination.y + 6*SIZE_TILE};
			etapes[7] = (Pos_t){(*salles)[9]->destination.x + 7*SIZE_TILE,(*salles)[9]->destination.y + 6*SIZE_TILE};
			etapes[8] = (Pos_t){(*salles)[9]->destination.x + 7*SIZE_TILE,(*salles)[9]->destination.y + 5*SIZE_TILE};
			etapes[9] = (Pos_t){(*salles)[9]->destination.x + 7*SIZE_TILE,(*salles)[9]->destination.y + 4*SIZE_TILE};
			etapes[10] = (Pos_t){(*salles)[9]->destination.x + 7*SIZE_TILE,(*salles)[9]->destination.y + 4*SIZE_TILE};
			etapes[11] = (Pos_t){(*salles)[9]->destination.x + 7*SIZE_TILE,(*salles)[9]->destination.y + 4*SIZE_TILE};
			etapes[12] = (Pos_t){(*salles)[9]->destination.x + 8*SIZE_TILE,(*salles)[9]->destination.y + 4*SIZE_TILE};
			etapes[13] = (Pos_t){(*salles)[9]->destination.x + 9*SIZE_TILE,(*salles)[9]->destination.y + 4*SIZE_TILE};
			etapes[14] = (Pos_t){(*salles)[9]->destination.x + 9*SIZE_TILE,(*salles)[9]->destination.y + 4*SIZE_TILE};
			etapes[15] = (Pos_t){(*salles)[9]->destination.x + 9*SIZE_TILE,(*salles)[9]->destination.y + 4*SIZE_TILE};
		etapeCourante = 0;
		entites[5]= EntiteCreate(renderer, SLIME_R, etapes, etapeCourante, nbEtapes);

		//Entite 6
		nbEtapes = 24;
		etapes = (Pos_t*)malloc(nbEtapes*sizeof(Pos_t));
			etapes[0] = (Pos_t){(*salles)[9]->destination.x + 7*SIZE_TILE,(*salles)[9]->destination.y + 8*SIZE_TILE};
			etapes[1] = (Pos_t){(*salles)[9]->destination.x + 6*SIZE_TILE,(*salles)[9]->destination.y + 8*SIZE_TILE};
			etapes[2] = (Pos_t){(*salles)[9]->destination.x + 5*SIZE_TILE,(*salles)[9]->destination.y + 8*SIZE_TILE};
			etapes[3] = (Pos_t){(*salles)[9]->destination.x + 5*SIZE_TILE,(*salles)[9]->destination.y + 7*SIZE_TILE};
			etapes[4] = (Pos_t){(*salles)[9]->destination.x + 5*SIZE_TILE,(*salles)[9]->destination.y + 6*SIZE_TILE};
			etapes[5] = (Pos_t){(*salles)[9]->destination.x + 5*SIZE_TILE,(*salles)[9]->destination.y + 5*SIZE_TILE};
			etapes[6] = (Pos_t){(*salles)[9]->destination.x + 5*SIZE_TILE,(*salles)[9]->destination.y + 4*SIZE_TILE};
			etapes[7] = (Pos_t){(*salles)[9]->destination.x + 5*SIZE_TILE,(*salles)[9]->destination.y + 3*SIZE_TILE};
			etapes[8] = (Pos_t){(*salles)[9]->destination.x + 5*SIZE_TILE,(*salles)[9]->destination.y + 2*SIZE_TILE};
			etapes[9] = (Pos_t){(*salles)[9]->destination.x + 6*SIZE_TILE,(*salles)[9]->destination.y + 2*SIZE_TILE};
			etapes[10] = (Pos_t){(*salles)[9]->destination.x + 7*SIZE_TILE,(*salles)[9]->destination.y + 2*SIZE_TILE};
			etapes[11] = (Pos_t){(*salles)[9]->destination.x + 8*SIZE_TILE,(*salles)[9]->destination.y + 2*SIZE_TILE};
			etapes[12] = (Pos_t){(*salles)[9]->destination.x + 9*SIZE_TILE,(*salles)[9]->destination.y + 2*SIZE_TILE};
			etapes[13] = (Pos_t){(*salles)[9]->destination.x + 10*SIZE_TILE,(*salles)[9]->destination.y + 2*SIZE_TILE};
			etapes[14] = (Pos_t){(*salles)[9]->destination.x + 11*SIZE_TILE,(*salles)[9]->destination.y + 2*SIZE_TILE};
			etapes[15] = (Pos_t){(*salles)[9]->destination.x + 11*SIZE_TILE,(*salles)[9]->destination.y + 3*SIZE_TILE};
			etapes[16] = (Pos_t){(*salles)[9]->destination.x + 11*SIZE_TILE,(*salles)[9]->destination.y + 4*SIZE_TILE};
			etapes[17] = (Pos_t){(*salles)[9]->destination.x + 11*SIZE_TILE,(*salles)[9]->destination.y + 5*SIZE_TILE};
			etapes[18] = (Pos_t){(*salles)[9]->destination.x + 11*SIZE_TILE,(*salles)[9]->destination.y + 6*SIZE_TILE};
			etapes[19] = (Pos_t){(*salles)[9]->destination.x + 11*SIZE_TILE,(*salles)[9]->destination.y + 7*SIZE_TILE};
			etapes[20] = (Pos_t){(*salles)[9]->destination.x + 11*SIZE_TILE,(*salles)[9]->destination.y + 8*SIZE_TILE};
			etapes[21] = (Pos_t){(*salles)[9]->destination.x + 10*SIZE_TILE,(*salles)[9]->destination.y + 8*SIZE_TILE};
			etapes[22] = (Pos_t){(*salles)[9]->destination.x + 9*SIZE_TILE,(*salles)[9]->destination.y + 8*SIZE_TILE};
			etapes[23] = (Pos_t){(*salles)[9]->destination.x + 8*SIZE_TILE,(*salles)[9]->destination.y + 8*SIZE_TILE};
		etapeCourante = 0;
		entites[6]= EntiteCreate(renderer, SLIME_R, etapes, etapeCourante, nbEtapes);

		//Entite 7
		nbEtapes = 24;
		etapes = (Pos_t*)malloc(nbEtapes*sizeof(Pos_t));
			etapes[0] = (Pos_t){(*salles)[9]->destination.x + 6*SIZE_TILE,(*salles)[9]->destination.y + 8*SIZE_TILE};
			etapes[1] = (Pos_t){(*salles)[9]->destination.x + 5*SIZE_TILE,(*salles)[9]->destination.y + 8*SIZE_TILE};
			etapes[2] = (Pos_t){(*salles)[9]->destination.x + 5*SIZE_TILE,(*salles)[9]->destination.y + 7*SIZE_TILE};
			etapes[3] = (Pos_t){(*salles)[9]->destination.x + 5*SIZE_TILE,(*salles)[9]->destination.y + 6*SIZE_TILE};
			etapes[4] = (Pos_t){(*salles)[9]->destination.x + 5*SIZE_TILE,(*salles)[9]->destination.y + 5*SIZE_TILE};
			etapes[5] = (Pos_t){(*salles)[9]->destination.x + 5*SIZE_TILE,(*salles)[9]->destination.y + 4*SIZE_TILE};
			etapes[6] = (Pos_t){(*salles)[9]->destination.x + 5*SIZE_TILE,(*salles)[9]->destination.y + 3*SIZE_TILE};
			etapes[7] = (Pos_t){(*salles)[9]->destination.x + 5*SIZE_TILE,(*salles)[9]->destination.y + 2*SIZE_TILE};
			etapes[8] = (Pos_t){(*salles)[9]->destination.x + 6*SIZE_TILE,(*salles)[9]->destination.y + 2*SIZE_TILE};
			etapes[9] = (Pos_t){(*salles)[9]->destination.x + 7*SIZE_TILE,(*salles)[9]->destination.y + 2*SIZE_TILE};
			etapes[10] = (Pos_t){(*salles)[9]->destination.x + 8*SIZE_TILE,(*salles)[9]->destination.y + 2*SIZE_TILE};
			etapes[11] = (Pos_t){(*salles)[9]->destination.x + 9*SIZE_TILE,(*salles)[9]->destination.y + 2*SIZE_TILE};
			etapes[12] = (Pos_t){(*salles)[9]->destination.x + 10*SIZE_TILE,(*salles)[9]->destination.y + 2*SIZE_TILE};
			etapes[13] = (Pos_t){(*salles)[9]->destination.x + 11*SIZE_TILE,(*salles)[9]->destination.y + 2*SIZE_TILE};
			etapes[14] = (Pos_t){(*salles)[9]->destination.x + 11*SIZE_TILE,(*salles)[9]->destination.y + 3*SIZE_TILE};
			etapes[15] = (Pos_t){(*salles)[9]->destination.x + 11*SIZE_TILE,(*salles)[9]->destination.y + 4*SIZE_TILE};
			etapes[16] = (Pos_t){(*salles)[9]->destination.x + 11*SIZE_TILE,(*salles)[9]->destination.y + 5*SIZE_TILE};
			etapes[17] = (Pos_t){(*salles)[9]->destination.x + 11*SIZE_TILE,(*salles)[9]->destination.y + 6*SIZE_TILE};
			etapes[18] = (Pos_t){(*salles)[9]->destination.x + 11*SIZE_TILE,(*salles)[9]->destination.y + 7*SIZE_TILE};
			etapes[19] = (Pos_t){(*salles)[9]->destination.x + 11*SIZE_TILE,(*salles)[9]->destination.y + 8*SIZE_TILE};
			etapes[20] = (Pos_t){(*salles)[9]->destination.x + 10*SIZE_TILE,(*salles)[9]->destination.y + 8*SIZE_TILE};
			etapes[21] = (Pos_t){(*salles)[9]->destination.x + 9*SIZE_TILE,(*salles)[9]->destination.y + 8*SIZE_TILE};
			etapes[22] = (Pos_t){(*salles)[9]->destination.x + 8*SIZE_TILE,(*salles)[9]->destination.y + 8*SIZE_TILE};
			etapes[23] = (Pos_t){(*salles)[9]->destination.x + 7*SIZE_TILE,(*salles)[9]->destination.y + 8*SIZE_TILE};
		etapeCourante = 0;
		entites[7]= EntiteCreate(renderer, SLIME_R, etapes, etapeCourante, nbEtapes);

		//Entite 8
		nbEtapes = 24;
		etapes = (Pos_t*)malloc(nbEtapes*sizeof(Pos_t));
			etapes[0] = (Pos_t){(*salles)[9]->destination.x + 5*SIZE_TILE,(*salles)[9]->destination.y + 8*SIZE_TILE};
			etapes[1] = (Pos_t){(*salles)[9]->destination.x + 5*SIZE_TILE,(*salles)[9]->destination.y + 7*SIZE_TILE};
			etapes[2] = (Pos_t){(*salles)[9]->destination.x + 5*SIZE_TILE,(*salles)[9]->destination.y + 6*SIZE_TILE};
			etapes[3] = (Pos_t){(*salles)[9]->destination.x + 5*SIZE_TILE,(*salles)[9]->destination.y + 5*SIZE_TILE};
			etapes[4] = (Pos_t){(*salles)[9]->destination.x + 5*SIZE_TILE,(*salles)[9]->destination.y + 4*SIZE_TILE};
			etapes[5] = (Pos_t){(*salles)[9]->destination.x + 5*SIZE_TILE,(*salles)[9]->destination.y + 3*SIZE_TILE};
			etapes[6] = (Pos_t){(*salles)[9]->destination.x + 5*SIZE_TILE,(*salles)[9]->destination.y + 2*SIZE_TILE};
			etapes[7] = (Pos_t){(*salles)[9]->destination.x + 6*SIZE_TILE,(*salles)[9]->destination.y + 2*SIZE_TILE};
			etapes[8] = (Pos_t){(*salles)[9]->destination.x + 7*SIZE_TILE,(*salles)[9]->destination.y + 2*SIZE_TILE};
			etapes[9] = (Pos_t){(*salles)[9]->destination.x + 8*SIZE_TILE,(*salles)[9]->destination.y + 2*SIZE_TILE};
			etapes[10] = (Pos_t){(*salles)[9]->destination.x + 9*SIZE_TILE,(*salles)[9]->destination.y + 2*SIZE_TILE};
			etapes[11] = (Pos_t){(*salles)[9]->destination.x + 10*SIZE_TILE,(*salles)[9]->destination.y + 2*SIZE_TILE};
			etapes[12] = (Pos_t){(*salles)[9]->destination.x + 11*SIZE_TILE,(*salles)[9]->destination.y + 2*SIZE_TILE};
			etapes[13] = (Pos_t){(*salles)[9]->destination.x + 11*SIZE_TILE,(*salles)[9]->destination.y + 3*SIZE_TILE};
			etapes[14] = (Pos_t){(*salles)[9]->destination.x + 11*SIZE_TILE,(*salles)[9]->destination.y + 4*SIZE_TILE};
			etapes[15] = (Pos_t){(*salles)[9]->destination.x + 11*SIZE_TILE,(*salles)[9]->destination.y + 5*SIZE_TILE};
			etapes[16] = (Pos_t){(*salles)[9]->destination.x + 11*SIZE_TILE,(*salles)[9]->destination.y + 6*SIZE_TILE};
			etapes[17] = (Pos_t){(*salles)[9]->destination.x + 11*SIZE_TILE,(*salles)[9]->destination.y + 7*SIZE_TILE};
			etapes[18] = (Pos_t){(*salles)[9]->destination.x + 11*SIZE_TILE,(*salles)[9]->destination.y + 8*SIZE_TILE};
			etapes[19] = (Pos_t){(*salles)[9]->destination.x + 10*SIZE_TILE,(*salles)[9]->destination.y + 8*SIZE_TILE};
			etapes[20] = (Pos_t){(*salles)[9]->destination.x + 9*SIZE_TILE,(*salles)[9]->destination.y + 8*SIZE_TILE};
			etapes[21] = (Pos_t){(*salles)[9]->destination.x + 8*SIZE_TILE,(*salles)[9]->destination.y + 8*SIZE_TILE};
			etapes[22] = (Pos_t){(*salles)[9]->destination.x + 7*SIZE_TILE,(*salles)[9]->destination.y + 8*SIZE_TILE};
			etapes[23] = (Pos_t){(*salles)[9]->destination.x + 6*SIZE_TILE,(*salles)[9]->destination.y + 8*SIZE_TILE};
		etapeCourante = 0;
		entites[8]= EntiteCreate(renderer, SLIME_R, etapes, etapeCourante, nbEtapes);

		//Entite 9
		nbEtapes = 24;
		etapes = (Pos_t*)malloc(nbEtapes*sizeof(Pos_t));
			etapes[0] = (Pos_t){(*salles)[9]->destination.x + 5*SIZE_TILE,(*salles)[9]->destination.y + 7*SIZE_TILE};
			etapes[1] = (Pos_t){(*salles)[9]->destination.x + 5*SIZE_TILE,(*salles)[9]->destination.y + 6*SIZE_TILE};
			etapes[2] = (Pos_t){(*salles)[9]->destination.x + 5*SIZE_TILE,(*salles)[9]->destination.y + 5*SIZE_TILE};
			etapes[3] = (Pos_t){(*salles)[9]->destination.x + 5*SIZE_TILE,(*salles)[9]->destination.y + 4*SIZE_TILE};
			etapes[4] = (Pos_t){(*salles)[9]->destination.x + 5*SIZE_TILE,(*salles)[9]->destination.y + 3*SIZE_TILE};
			etapes[5] = (Pos_t){(*salles)[9]->destination.x + 5*SIZE_TILE,(*salles)[9]->destination.y + 2*SIZE_TILE};
			etapes[6] = (Pos_t){(*salles)[9]->destination.x + 6*SIZE_TILE,(*salles)[9]->destination.y + 2*SIZE_TILE};
			etapes[7] = (Pos_t){(*salles)[9]->destination.x + 7*SIZE_TILE,(*salles)[9]->destination.y + 2*SIZE_TILE};
			etapes[8] = (Pos_t){(*salles)[9]->destination.x + 8*SIZE_TILE,(*salles)[9]->destination.y + 2*SIZE_TILE};
			etapes[9] = (Pos_t){(*salles)[9]->destination.x + 9*SIZE_TILE,(*salles)[9]->destination.y + 2*SIZE_TILE};
			etapes[10] = (Pos_t){(*salles)[9]->destination.x + 10*SIZE_TILE,(*salles)[9]->destination.y + 2*SIZE_TILE};
			etapes[11] = (Pos_t){(*salles)[9]->destination.x + 11*SIZE_TILE,(*salles)[9]->destination.y + 2*SIZE_TILE};
			etapes[12] = (Pos_t){(*salles)[9]->destination.x + 11*SIZE_TILE,(*salles)[9]->destination.y + 3*SIZE_TILE};
			etapes[13] = (Pos_t){(*salles)[9]->destination.x + 11*SIZE_TILE,(*salles)[9]->destination.y + 4*SIZE_TILE};
			etapes[14] = (Pos_t){(*salles)[9]->destination.x + 11*SIZE_TILE,(*salles)[9]->destination.y + 5*SIZE_TILE};
			etapes[15] = (Pos_t){(*salles)[9]->destination.x + 11*SIZE_TILE,(*salles)[9]->destination.y + 6*SIZE_TILE};
			etapes[16] = (Pos_t){(*salles)[9]->destination.x + 11*SIZE_TILE,(*salles)[9]->destination.y + 7*SIZE_TILE};
			etapes[17] = (Pos_t){(*salles)[9]->destination.x + 11*SIZE_TILE,(*salles)[9]->destination.y + 8*SIZE_TILE};
			etapes[18] = (Pos_t){(*salles)[9]->destination.x + 10*SIZE_TILE,(*salles)[9]->destination.y + 8*SIZE_TILE};
			etapes[19] = (Pos_t){(*salles)[9]->destination.x + 9*SIZE_TILE,(*salles)[9]->destination.y + 8*SIZE_TILE};
			etapes[20] = (Pos_t){(*salles)[9]->destination.x + 8*SIZE_TILE,(*salles)[9]->destination.y + 8*SIZE_TILE};
			etapes[21] = (Pos_t){(*salles)[9]->destination.x + 7*SIZE_TILE,(*salles)[9]->destination.y + 8*SIZE_TILE};
			etapes[22] = (Pos_t){(*salles)[9]->destination.x + 6*SIZE_TILE,(*salles)[9]->destination.y + 8*SIZE_TILE};
			etapes[23] = (Pos_t){(*salles)[9]->destination.x + 5*SIZE_TILE,(*salles)[9]->destination.y + 8*SIZE_TILE};
		etapeCourante = 0;
		entites[9]= EntiteCreate(renderer, SLIME_R, etapes, etapeCourante, nbEtapes);

		//Entite 10
		nbEtapes = 24;
		etapes = (Pos_t*)malloc(nbEtapes*sizeof(Pos_t));
			etapes[0] = (Pos_t){(*salles)[9]->destination.x + 5*SIZE_TILE,(*salles)[9]->destination.y + 6*SIZE_TILE};
			etapes[1] = (Pos_t){(*salles)[9]->destination.x + 5*SIZE_TILE,(*salles)[9]->destination.y + 5*SIZE_TILE};
			etapes[2] = (Pos_t){(*salles)[9]->destination.x + 5*SIZE_TILE,(*salles)[9]->destination.y + 4*SIZE_TILE};
			etapes[3] = (Pos_t){(*salles)[9]->destination.x + 5*SIZE_TILE,(*salles)[9]->destination.y + 3*SIZE_TILE};
			etapes[4] = (Pos_t){(*salles)[9]->destination.x + 5*SIZE_TILE,(*salles)[9]->destination.y + 2*SIZE_TILE};
			etapes[5] = (Pos_t){(*salles)[9]->destination.x + 6*SIZE_TILE,(*salles)[9]->destination.y + 2*SIZE_TILE};
			etapes[6] = (Pos_t){(*salles)[9]->destination.x + 7*SIZE_TILE,(*salles)[9]->destination.y + 2*SIZE_TILE};
			etapes[7] = (Pos_t){(*salles)[9]->destination.x + 8*SIZE_TILE,(*salles)[9]->destination.y + 2*SIZE_TILE};
			etapes[8] = (Pos_t){(*salles)[9]->destination.x + 9*SIZE_TILE,(*salles)[9]->destination.y + 2*SIZE_TILE};
			etapes[9] = (Pos_t){(*salles)[9]->destination.x + 10*SIZE_TILE,(*salles)[9]->destination.y + 2*SIZE_TILE};
			etapes[10] = (Pos_t){(*salles)[9]->destination.x + 11*SIZE_TILE,(*salles)[9]->destination.y + 2*SIZE_TILE};
			etapes[11] = (Pos_t){(*salles)[9]->destination.x + 11*SIZE_TILE,(*salles)[9]->destination.y + 3*SIZE_TILE};
			etapes[12] = (Pos_t){(*salles)[9]->destination.x + 11*SIZE_TILE,(*salles)[9]->destination.y + 4*SIZE_TILE};
			etapes[13] = (Pos_t){(*salles)[9]->destination.x + 11*SIZE_TILE,(*salles)[9]->destination.y + 5*SIZE_TILE};
			etapes[14] = (Pos_t){(*salles)[9]->destination.x + 11*SIZE_TILE,(*salles)[9]->destination.y + 6*SIZE_TILE};
			etapes[15] = (Pos_t){(*salles)[9]->destination.x + 11*SIZE_TILE,(*salles)[9]->destination.y + 7*SIZE_TILE};
			etapes[16] = (Pos_t){(*salles)[9]->destination.x + 11*SIZE_TILE,(*salles)[9]->destination.y + 8*SIZE_TILE};
			etapes[17] = (Pos_t){(*salles)[9]->destination.x + 10*SIZE_TILE,(*salles)[9]->destination.y + 8*SIZE_TILE};
			etapes[18] = (Pos_t){(*salles)[9]->destination.x + 9*SIZE_TILE,(*salles)[9]->destination.y + 8*SIZE_TILE};
			etapes[19] = (Pos_t){(*salles)[9]->destination.x + 8*SIZE_TILE,(*salles)[9]->destination.y + 8*SIZE_TILE};
			etapes[20] = (Pos_t){(*salles)[9]->destination.x + 7*SIZE_TILE,(*salles)[9]->destination.y + 8*SIZE_TILE};
			etapes[21] = (Pos_t){(*salles)[9]->destination.x + 6*SIZE_TILE,(*salles)[9]->destination.y + 8*SIZE_TILE};
			etapes[22] = (Pos_t){(*salles)[9]->destination.x + 5*SIZE_TILE,(*salles)[9]->destination.y + 8*SIZE_TILE};
			etapes[23] = (Pos_t){(*salles)[9]->destination.x + 5*SIZE_TILE,(*salles)[9]->destination.y + 7*SIZE_TILE};
		etapeCourante = 0;
		entites[10]= EntiteCreate(renderer, SLIME_R, etapes, etapeCourante, nbEtapes);

		//Entite 11
		nbEtapes = 24;
		etapes = (Pos_t*)malloc(nbEtapes*sizeof(Pos_t));
			etapes[0] = (Pos_t){(*salles)[9]->destination.x + 5*SIZE_TILE,(*salles)[9]->destination.y + 5*SIZE_TILE};
			etapes[1] = (Pos_t){(*salles)[9]->destination.x + 5*SIZE_TILE,(*salles)[9]->destination.y + 4*SIZE_TILE};
			etapes[2] = (Pos_t){(*salles)[9]->destination.x + 5*SIZE_TILE,(*salles)[9]->destination.y + 3*SIZE_TILE};
			etapes[3] = (Pos_t){(*salles)[9]->destination.x + 5*SIZE_TILE,(*salles)[9]->destination.y + 2*SIZE_TILE};
			etapes[4] = (Pos_t){(*salles)[9]->destination.x + 6*SIZE_TILE,(*salles)[9]->destination.y + 2*SIZE_TILE};
			etapes[5] = (Pos_t){(*salles)[9]->destination.x + 7*SIZE_TILE,(*salles)[9]->destination.y + 2*SIZE_TILE};
			etapes[6] = (Pos_t){(*salles)[9]->destination.x + 8*SIZE_TILE,(*salles)[9]->destination.y + 2*SIZE_TILE};
			etapes[7] = (Pos_t){(*salles)[9]->destination.x + 9*SIZE_TILE,(*salles)[9]->destination.y + 2*SIZE_TILE};
			etapes[8] = (Pos_t){(*salles)[9]->destination.x + 10*SIZE_TILE,(*salles)[9]->destination.y + 2*SIZE_TILE};
			etapes[9] = (Pos_t){(*salles)[9]->destination.x + 11*SIZE_TILE,(*salles)[9]->destination.y + 2*SIZE_TILE};
			etapes[10] = (Pos_t){(*salles)[9]->destination.x + 11*SIZE_TILE,(*salles)[9]->destination.y + 3*SIZE_TILE};
			etapes[11] = (Pos_t){(*salles)[9]->destination.x + 11*SIZE_TILE,(*salles)[9]->destination.y + 4*SIZE_TILE};
			etapes[12] = (Pos_t){(*salles)[9]->destination.x + 11*SIZE_TILE,(*salles)[9]->destination.y + 5*SIZE_TILE};
			etapes[13] = (Pos_t){(*salles)[9]->destination.x + 11*SIZE_TILE,(*salles)[9]->destination.y + 6*SIZE_TILE};
			etapes[14] = (Pos_t){(*salles)[9]->destination.x + 11*SIZE_TILE,(*salles)[9]->destination.y + 7*SIZE_TILE};
			etapes[15] = (Pos_t){(*salles)[9]->destination.x + 11*SIZE_TILE,(*salles)[9]->destination.y + 8*SIZE_TILE};
			etapes[16] = (Pos_t){(*salles)[9]->destination.x + 10*SIZE_TILE,(*salles)[9]->destination.y + 8*SIZE_TILE};
			etapes[17] = (Pos_t){(*salles)[9]->destination.x + 9*SIZE_TILE,(*salles)[9]->destination.y + 8*SIZE_TILE};
			etapes[18] = (Pos_t){(*salles)[9]->destination.x + 8*SIZE_TILE,(*salles)[9]->destination.y + 8*SIZE_TILE};
			etapes[19] = (Pos_t){(*salles)[9]->destination.x + 7*SIZE_TILE,(*salles)[9]->destination.y + 8*SIZE_TILE};
			etapes[20] = (Pos_t){(*salles)[9]->destination.x + 6*SIZE_TILE,(*salles)[9]->destination.y + 8*SIZE_TILE};
			etapes[21] = (Pos_t){(*salles)[9]->destination.x + 5*SIZE_TILE,(*salles)[9]->destination.y + 8*SIZE_TILE};
			etapes[22] = (Pos_t){(*salles)[9]->destination.x + 5*SIZE_TILE,(*salles)[9]->destination.y + 7*SIZE_TILE};
			etapes[23] = (Pos_t){(*salles)[9]->destination.x + 5*SIZE_TILE,(*salles)[9]->destination.y + 6*SIZE_TILE};
		etapeCourante = 0;
		entites[11]= EntiteCreate(renderer, SLIME_R, etapes, etapeCourante, nbEtapes);

		//Entite 12
		nbEtapes = 24;
		etapes = (Pos_t*)malloc(nbEtapes*sizeof(Pos_t));
			etapes[0] = (Pos_t){(*salles)[9]->destination.x + 5*SIZE_TILE,(*salles)[9]->destination.y + 4*SIZE_TILE};
			etapes[1] = (Pos_t){(*salles)[9]->destination.x + 5*SIZE_TILE,(*salles)[9]->destination.y + 3*SIZE_TILE};
			etapes[2] = (Pos_t){(*salles)[9]->destination.x + 5*SIZE_TILE,(*salles)[9]->destination.y + 2*SIZE_TILE};
			etapes[3] = (Pos_t){(*salles)[9]->destination.x + 6*SIZE_TILE,(*salles)[9]->destination.y + 2*SIZE_TILE};
			etapes[4] = (Pos_t){(*salles)[9]->destination.x + 7*SIZE_TILE,(*salles)[9]->destination.y + 2*SIZE_TILE};
			etapes[5] = (Pos_t){(*salles)[9]->destination.x + 8*SIZE_TILE,(*salles)[9]->destination.y + 2*SIZE_TILE};
			etapes[6] = (Pos_t){(*salles)[9]->destination.x + 9*SIZE_TILE,(*salles)[9]->destination.y + 2*SIZE_TILE};
			etapes[7] = (Pos_t){(*salles)[9]->destination.x + 10*SIZE_TILE,(*salles)[9]->destination.y + 2*SIZE_TILE};
			etapes[8] = (Pos_t){(*salles)[9]->destination.x + 11*SIZE_TILE,(*salles)[9]->destination.y + 2*SIZE_TILE};
			etapes[9] = (Pos_t){(*salles)[9]->destination.x + 11*SIZE_TILE,(*salles)[9]->destination.y + 3*SIZE_TILE};
			etapes[10] = (Pos_t){(*salles)[9]->destination.x + 11*SIZE_TILE,(*salles)[9]->destination.y + 4*SIZE_TILE};
			etapes[11] = (Pos_t){(*salles)[9]->destination.x + 11*SIZE_TILE,(*salles)[9]->destination.y + 5*SIZE_TILE};
			etapes[12] = (Pos_t){(*salles)[9]->destination.x + 11*SIZE_TILE,(*salles)[9]->destination.y + 6*SIZE_TILE};
			etapes[13] = (Pos_t){(*salles)[9]->destination.x + 11*SIZE_TILE,(*salles)[9]->destination.y + 7*SIZE_TILE};
			etapes[14] = (Pos_t){(*salles)[9]->destination.x + 11*SIZE_TILE,(*salles)[9]->destination.y + 8*SIZE_TILE};
			etapes[15] = (Pos_t){(*salles)[9]->destination.x + 10*SIZE_TILE,(*salles)[9]->destination.y + 8*SIZE_TILE};
			etapes[16] = (Pos_t){(*salles)[9]->destination.x + 9*SIZE_TILE,(*salles)[9]->destination.y + 8*SIZE_TILE};
			etapes[17] = (Pos_t){(*salles)[9]->destination.x + 8*SIZE_TILE,(*salles)[9]->destination.y + 8*SIZE_TILE};
			etapes[18] = (Pos_t){(*salles)[9]->destination.x + 7*SIZE_TILE,(*salles)[9]->destination.y + 8*SIZE_TILE};
			etapes[19] = (Pos_t){(*salles)[9]->destination.x + 6*SIZE_TILE,(*salles)[9]->destination.y + 8*SIZE_TILE};
			etapes[20] = (Pos_t){(*salles)[9]->destination.x + 5*SIZE_TILE,(*salles)[9]->destination.y + 8*SIZE_TILE};
			etapes[21] = (Pos_t){(*salles)[9]->destination.x + 5*SIZE_TILE,(*salles)[9]->destination.y + 7*SIZE_TILE};
			etapes[22] = (Pos_t){(*salles)[9]->destination.x + 5*SIZE_TILE,(*salles)[9]->destination.y + 6*SIZE_TILE};
			etapes[23] = (Pos_t){(*salles)[9]->destination.x + 5*SIZE_TILE,(*salles)[9]->destination.y + 5*SIZE_TILE};
		etapeCourante = 0;
		entites[12]= EntiteCreate(renderer, SLIME_R, etapes, etapeCourante, nbEtapes);

		//Entite 13
		nbEtapes = 24;
		etapes = (Pos_t*)malloc(nbEtapes*sizeof(Pos_t));
			etapes[0] = (Pos_t){(*salles)[9]->destination.x + 5*SIZE_TILE,(*salles)[9]->destination.y + 3*SIZE_TILE};
			etapes[1] = (Pos_t){(*salles)[9]->destination.x + 5*SIZE_TILE,(*salles)[9]->destination.y + 2*SIZE_TILE};
			etapes[2] = (Pos_t){(*salles)[9]->destination.x + 6*SIZE_TILE,(*salles)[9]->destination.y + 2*SIZE_TILE};
			etapes[3] = (Pos_t){(*salles)[9]->destination.x + 7*SIZE_TILE,(*salles)[9]->destination.y + 2*SIZE_TILE};
			etapes[4] = (Pos_t){(*salles)[9]->destination.x + 8*SIZE_TILE,(*salles)[9]->destination.y + 2*SIZE_TILE};
			etapes[5] = (Pos_t){(*salles)[9]->destination.x + 9*SIZE_TILE,(*salles)[9]->destination.y + 2*SIZE_TILE};
			etapes[6] = (Pos_t){(*salles)[9]->destination.x + 10*SIZE_TILE,(*salles)[9]->destination.y + 2*SIZE_TILE};
			etapes[7] = (Pos_t){(*salles)[9]->destination.x + 11*SIZE_TILE,(*salles)[9]->destination.y + 2*SIZE_TILE};
			etapes[8] = (Pos_t){(*salles)[9]->destination.x + 11*SIZE_TILE,(*salles)[9]->destination.y + 3*SIZE_TILE};
			etapes[9] = (Pos_t){(*salles)[9]->destination.x + 11*SIZE_TILE,(*salles)[9]->destination.y + 4*SIZE_TILE};
			etapes[10] = (Pos_t){(*salles)[9]->destination.x + 11*SIZE_TILE,(*salles)[9]->destination.y + 5*SIZE_TILE};
			etapes[11] = (Pos_t){(*salles)[9]->destination.x + 11*SIZE_TILE,(*salles)[9]->destination.y + 6*SIZE_TILE};
			etapes[12] = (Pos_t){(*salles)[9]->destination.x + 11*SIZE_TILE,(*salles)[9]->destination.y + 7*SIZE_TILE};
			etapes[13] = (Pos_t){(*salles)[9]->destination.x + 11*SIZE_TILE,(*salles)[9]->destination.y + 8*SIZE_TILE};
			etapes[14] = (Pos_t){(*salles)[9]->destination.x + 10*SIZE_TILE,(*salles)[9]->destination.y + 8*SIZE_TILE};
			etapes[15] = (Pos_t){(*salles)[9]->destination.x + 9*SIZE_TILE,(*salles)[9]->destination.y + 8*SIZE_TILE};
			etapes[16] = (Pos_t){(*salles)[9]->destination.x + 8*SIZE_TILE,(*salles)[9]->destination.y + 8*SIZE_TILE};
			etapes[17] = (Pos_t){(*salles)[9]->destination.x + 7*SIZE_TILE,(*salles)[9]->destination.y + 8*SIZE_TILE};
			etapes[18] = (Pos_t){(*salles)[9]->destination.x + 6*SIZE_TILE,(*salles)[9]->destination.y + 8*SIZE_TILE};
			etapes[19] = (Pos_t){(*salles)[9]->destination.x + 5*SIZE_TILE,(*salles)[9]->destination.y + 8*SIZE_TILE};
			etapes[20] = (Pos_t){(*salles)[9]->destination.x + 5*SIZE_TILE,(*salles)[9]->destination.y + 7*SIZE_TILE};
			etapes[21] = (Pos_t){(*salles)[9]->destination.x + 5*SIZE_TILE,(*salles)[9]->destination.y + 6*SIZE_TILE};
			etapes[22] = (Pos_t){(*salles)[9]->destination.x + 5*SIZE_TILE,(*salles)[9]->destination.y + 5*SIZE_TILE};
			etapes[23] = (Pos_t){(*salles)[9]->destination.x + 5*SIZE_TILE,(*salles)[9]->destination.y + 4*SIZE_TILE};
		etapeCourante = 0;
		entites[13]= EntiteCreate(renderer, SLIME_R, etapes, etapeCourante, nbEtapes);

		//Entite 14
		nbEtapes = 24;
		etapes = (Pos_t*)malloc(nbEtapes*sizeof(Pos_t));
			etapes[0] = (Pos_t){(*salles)[9]->destination.x + 5*SIZE_TILE,(*salles)[9]->destination.y + 2*SIZE_TILE};
			etapes[1] = (Pos_t){(*salles)[9]->destination.x + 6*SIZE_TILE,(*salles)[9]->destination.y + 2*SIZE_TILE};
			etapes[2] = (Pos_t){(*salles)[9]->destination.x + 7*SIZE_TILE,(*salles)[9]->destination.y + 2*SIZE_TILE};
			etapes[3] = (Pos_t){(*salles)[9]->destination.x + 8*SIZE_TILE,(*salles)[9]->destination.y + 2*SIZE_TILE};
			etapes[4] = (Pos_t){(*salles)[9]->destination.x + 9*SIZE_TILE,(*salles)[9]->destination.y + 2*SIZE_TILE};
			etapes[5] = (Pos_t){(*salles)[9]->destination.x + 10*SIZE_TILE,(*salles)[9]->destination.y + 2*SIZE_TILE};
			etapes[6] = (Pos_t){(*salles)[9]->destination.x + 11*SIZE_TILE,(*salles)[9]->destination.y + 2*SIZE_TILE};
			etapes[7] = (Pos_t){(*salles)[9]->destination.x + 11*SIZE_TILE,(*salles)[9]->destination.y + 3*SIZE_TILE};
			etapes[8] = (Pos_t){(*salles)[9]->destination.x + 11*SIZE_TILE,(*salles)[9]->destination.y + 4*SIZE_TILE};
			etapes[9] = (Pos_t){(*salles)[9]->destination.x + 11*SIZE_TILE,(*salles)[9]->destination.y + 5*SIZE_TILE};
			etapes[10] = (Pos_t){(*salles)[9]->destination.x + 11*SIZE_TILE,(*salles)[9]->destination.y + 6*SIZE_TILE};
			etapes[11] = (Pos_t){(*salles)[9]->destination.x + 11*SIZE_TILE,(*salles)[9]->destination.y + 7*SIZE_TILE};
			etapes[12] = (Pos_t){(*salles)[9]->destination.x + 11*SIZE_TILE,(*salles)[9]->destination.y + 8*SIZE_TILE};
			etapes[13] = (Pos_t){(*salles)[9]->destination.x + 10*SIZE_TILE,(*salles)[9]->destination.y + 8*SIZE_TILE};
			etapes[14] = (Pos_t){(*salles)[9]->destination.x + 9*SIZE_TILE,(*salles)[9]->destination.y + 8*SIZE_TILE};
			etapes[15] = (Pos_t){(*salles)[9]->destination.x + 8*SIZE_TILE,(*salles)[9]->destination.y + 8*SIZE_TILE};
			etapes[16] = (Pos_t){(*salles)[9]->destination.x + 7*SIZE_TILE,(*salles)[9]->destination.y + 8*SIZE_TILE};
			etapes[17] = (Pos_t){(*salles)[9]->destination.x + 6*SIZE_TILE,(*salles)[9]->destination.y + 8*SIZE_TILE};
			etapes[18] = (Pos_t){(*salles)[9]->destination.x + 5*SIZE_TILE,(*salles)[9]->destination.y + 8*SIZE_TILE};
			etapes[19] = (Pos_t){(*salles)[9]->destination.x + 5*SIZE_TILE,(*salles)[9]->destination.y + 7*SIZE_TILE};
			etapes[20] = (Pos_t){(*salles)[9]->destination.x + 5*SIZE_TILE,(*salles)[9]->destination.y + 6*SIZE_TILE};
			etapes[21] = (Pos_t){(*salles)[9]->destination.x + 5*SIZE_TILE,(*salles)[9]->destination.y + 5*SIZE_TILE};
			etapes[22] = (Pos_t){(*salles)[9]->destination.x + 5*SIZE_TILE,(*salles)[9]->destination.y + 4*SIZE_TILE};
			etapes[23] = (Pos_t){(*salles)[9]->destination.x + 5*SIZE_TILE,(*salles)[9]->destination.y + 3*SIZE_TILE};
		etapeCourante = 0;
		entites[14]= EntiteCreate(renderer, SLIME_R, etapes, etapeCourante, nbEtapes);

		//Entite 15
		nbEtapes = 24;
		etapes = (Pos_t*)malloc(nbEtapes*sizeof(Pos_t));
			etapes[0] = (Pos_t){(*salles)[9]->destination.x + 6*SIZE_TILE,(*salles)[9]->destination.y + 2*SIZE_TILE};
			etapes[1] = (Pos_t){(*salles)[9]->destination.x + 7*SIZE_TILE,(*salles)[9]->destination.y + 2*SIZE_TILE};
			etapes[2] = (Pos_t){(*salles)[9]->destination.x + 8*SIZE_TILE,(*salles)[9]->destination.y + 2*SIZE_TILE};
			etapes[3] = (Pos_t){(*salles)[9]->destination.x + 9*SIZE_TILE,(*salles)[9]->destination.y + 2*SIZE_TILE};
			etapes[4] = (Pos_t){(*salles)[9]->destination.x + 10*SIZE_TILE,(*salles)[9]->destination.y + 2*SIZE_TILE};
			etapes[5] = (Pos_t){(*salles)[9]->destination.x + 11*SIZE_TILE,(*salles)[9]->destination.y + 2*SIZE_TILE};
			etapes[6] = (Pos_t){(*salles)[9]->destination.x + 11*SIZE_TILE,(*salles)[9]->destination.y + 3*SIZE_TILE};
			etapes[7] = (Pos_t){(*salles)[9]->destination.x + 11*SIZE_TILE,(*salles)[9]->destination.y + 4*SIZE_TILE};
			etapes[8] = (Pos_t){(*salles)[9]->destination.x + 11*SIZE_TILE,(*salles)[9]->destination.y + 5*SIZE_TILE};
			etapes[9] = (Pos_t){(*salles)[9]->destination.x + 11*SIZE_TILE,(*salles)[9]->destination.y + 6*SIZE_TILE};
			etapes[10] = (Pos_t){(*salles)[9]->destination.x + 11*SIZE_TILE,(*salles)[9]->destination.y + 7*SIZE_TILE};
			etapes[11] = (Pos_t){(*salles)[9]->destination.x + 11*SIZE_TILE,(*salles)[9]->destination.y + 8*SIZE_TILE};
			etapes[12] = (Pos_t){(*salles)[9]->destination.x + 10*SIZE_TILE,(*salles)[9]->destination.y + 8*SIZE_TILE};
			etapes[13] = (Pos_t){(*salles)[9]->destination.x + 9*SIZE_TILE,(*salles)[9]->destination.y + 8*SIZE_TILE};
			etapes[14] = (Pos_t){(*salles)[9]->destination.x + 8*SIZE_TILE,(*salles)[9]->destination.y + 8*SIZE_TILE};
			etapes[15] = (Pos_t){(*salles)[9]->destination.x + 7*SIZE_TILE,(*salles)[9]->destination.y + 8*SIZE_TILE};
			etapes[16] = (Pos_t){(*salles)[9]->destination.x + 6*SIZE_TILE,(*salles)[9]->destination.y + 8*SIZE_TILE};
			etapes[17] = (Pos_t){(*salles)[9]->destination.x + 5*SIZE_TILE,(*salles)[9]->destination.y + 8*SIZE_TILE};
			etapes[18] = (Pos_t){(*salles)[9]->destination.x + 5*SIZE_TILE,(*salles)[9]->destination.y + 7*SIZE_TILE};
			etapes[19] = (Pos_t){(*salles)[9]->destination.x + 5*SIZE_TILE,(*salles)[9]->destination.y + 6*SIZE_TILE};
			etapes[20] = (Pos_t){(*salles)[9]->destination.x + 5*SIZE_TILE,(*salles)[9]->destination.y + 5*SIZE_TILE};
			etapes[21] = (Pos_t){(*salles)[9]->destination.x + 5*SIZE_TILE,(*salles)[9]->destination.y + 4*SIZE_TILE};
			etapes[22] = (Pos_t){(*salles)[9]->destination.x + 5*SIZE_TILE,(*salles)[9]->destination.y + 3*SIZE_TILE};
			etapes[23] = (Pos_t){(*salles)[9]->destination.x + 5*SIZE_TILE,(*salles)[9]->destination.y + 2*SIZE_TILE};
		etapeCourante = 0;
		entites[15]= EntiteCreate(renderer, SLIME_R, etapes, etapeCourante, nbEtapes);

		//Entite 16
		nbEtapes = 24;
		etapes = (Pos_t*)malloc(nbEtapes*sizeof(Pos_t));
			etapes[0] = (Pos_t){(*salles)[9]->destination.x + 7*SIZE_TILE,(*salles)[9]->destination.y + 2*SIZE_TILE};
			etapes[1] = (Pos_t){(*salles)[9]->destination.x + 8*SIZE_TILE,(*salles)[9]->destination.y + 2*SIZE_TILE};
			etapes[2] = (Pos_t){(*salles)[9]->destination.x + 9*SIZE_TILE,(*salles)[9]->destination.y + 2*SIZE_TILE};
			etapes[3] = (Pos_t){(*salles)[9]->destination.x + 10*SIZE_TILE,(*salles)[9]->destination.y + 2*SIZE_TILE};
			etapes[4] = (Pos_t){(*salles)[9]->destination.x + 11*SIZE_TILE,(*salles)[9]->destination.y + 2*SIZE_TILE};
			etapes[5] = (Pos_t){(*salles)[9]->destination.x + 11*SIZE_TILE,(*salles)[9]->destination.y + 3*SIZE_TILE};
			etapes[6] = (Pos_t){(*salles)[9]->destination.x + 11*SIZE_TILE,(*salles)[9]->destination.y + 4*SIZE_TILE};
			etapes[7] = (Pos_t){(*salles)[9]->destination.x + 11*SIZE_TILE,(*salles)[9]->destination.y + 5*SIZE_TILE};
			etapes[8] = (Pos_t){(*salles)[9]->destination.x + 11*SIZE_TILE,(*salles)[9]->destination.y + 6*SIZE_TILE};
			etapes[9] = (Pos_t){(*salles)[9]->destination.x + 11*SIZE_TILE,(*salles)[9]->destination.y + 7*SIZE_TILE};
			etapes[10] = (Pos_t){(*salles)[9]->destination.x + 11*SIZE_TILE,(*salles)[9]->destination.y + 8*SIZE_TILE};
			etapes[11] = (Pos_t){(*salles)[9]->destination.x + 10*SIZE_TILE,(*salles)[9]->destination.y + 8*SIZE_TILE};
			etapes[12] = (Pos_t){(*salles)[9]->destination.x + 9*SIZE_TILE,(*salles)[9]->destination.y + 8*SIZE_TILE};
			etapes[13] = (Pos_t){(*salles)[9]->destination.x + 8*SIZE_TILE,(*salles)[9]->destination.y + 8*SIZE_TILE};
			etapes[14] = (Pos_t){(*salles)[9]->destination.x + 7*SIZE_TILE,(*salles)[9]->destination.y + 8*SIZE_TILE};
			etapes[15] = (Pos_t){(*salles)[9]->destination.x + 6*SIZE_TILE,(*salles)[9]->destination.y + 8*SIZE_TILE};
			etapes[16] = (Pos_t){(*salles)[9]->destination.x + 5*SIZE_TILE,(*salles)[9]->destination.y + 8*SIZE_TILE};
			etapes[17] = (Pos_t){(*salles)[9]->destination.x + 5*SIZE_TILE,(*salles)[9]->destination.y + 7*SIZE_TILE};
			etapes[18] = (Pos_t){(*salles)[9]->destination.x + 5*SIZE_TILE,(*salles)[9]->destination.y + 6*SIZE_TILE};
			etapes[19] = (Pos_t){(*salles)[9]->destination.x + 5*SIZE_TILE,(*salles)[9]->destination.y + 5*SIZE_TILE};
			etapes[20] = (Pos_t){(*salles)[9]->destination.x + 5*SIZE_TILE,(*salles)[9]->destination.y + 4*SIZE_TILE};
			etapes[21] = (Pos_t){(*salles)[9]->destination.x + 5*SIZE_TILE,(*salles)[9]->destination.y + 3*SIZE_TILE};
			etapes[22] = (Pos_t){(*salles)[9]->destination.x + 5*SIZE_TILE,(*salles)[9]->destination.y + 2*SIZE_TILE};
			etapes[23] = (Pos_t){(*salles)[9]->destination.x + 6*SIZE_TILE,(*salles)[9]->destination.y + 2*SIZE_TILE};
		etapeCourante = 0;
		entites[16]= EntiteCreate(renderer, SLIME_R, etapes, etapeCourante, nbEtapes);

		//Entite 17
		nbEtapes = 24;
		etapes = (Pos_t*)malloc(nbEtapes*sizeof(Pos_t));
			etapes[0] = (Pos_t){(*salles)[9]->destination.x + 8*SIZE_TILE,(*salles)[9]->destination.y + 2*SIZE_TILE};
			etapes[1] = (Pos_t){(*salles)[9]->destination.x + 9*SIZE_TILE,(*salles)[9]->destination.y + 2*SIZE_TILE};
			etapes[2] = (Pos_t){(*salles)[9]->destination.x + 10*SIZE_TILE,(*salles)[9]->destination.y + 2*SIZE_TILE};
			etapes[3] = (Pos_t){(*salles)[9]->destination.x + 11*SIZE_TILE,(*salles)[9]->destination.y + 2*SIZE_TILE};
			etapes[4] = (Pos_t){(*salles)[9]->destination.x + 11*SIZE_TILE,(*salles)[9]->destination.y + 3*SIZE_TILE};
			etapes[5] = (Pos_t){(*salles)[9]->destination.x + 11*SIZE_TILE,(*salles)[9]->destination.y + 4*SIZE_TILE};
			etapes[6] = (Pos_t){(*salles)[9]->destination.x + 11*SIZE_TILE,(*salles)[9]->destination.y + 5*SIZE_TILE};
			etapes[7] = (Pos_t){(*salles)[9]->destination.x + 11*SIZE_TILE,(*salles)[9]->destination.y + 6*SIZE_TILE};
			etapes[8] = (Pos_t){(*salles)[9]->destination.x + 11*SIZE_TILE,(*salles)[9]->destination.y + 7*SIZE_TILE};
			etapes[9] = (Pos_t){(*salles)[9]->destination.x + 11*SIZE_TILE,(*salles)[9]->destination.y + 8*SIZE_TILE};
			etapes[10] = (Pos_t){(*salles)[9]->destination.x + 10*SIZE_TILE,(*salles)[9]->destination.y + 8*SIZE_TILE};
			etapes[11] = (Pos_t){(*salles)[9]->destination.x + 9*SIZE_TILE,(*salles)[9]->destination.y + 8*SIZE_TILE};
			etapes[12] = (Pos_t){(*salles)[9]->destination.x + 8*SIZE_TILE,(*salles)[9]->destination.y + 8*SIZE_TILE};
			etapes[13] = (Pos_t){(*salles)[9]->destination.x + 7*SIZE_TILE,(*salles)[9]->destination.y + 8*SIZE_TILE};
			etapes[14] = (Pos_t){(*salles)[9]->destination.x + 6*SIZE_TILE,(*salles)[9]->destination.y + 8*SIZE_TILE};
			etapes[15] = (Pos_t){(*salles)[9]->destination.x + 5*SIZE_TILE,(*salles)[9]->destination.y + 8*SIZE_TILE};
			etapes[16] = (Pos_t){(*salles)[9]->destination.x + 5*SIZE_TILE,(*salles)[9]->destination.y + 7*SIZE_TILE};
			etapes[17] = (Pos_t){(*salles)[9]->destination.x + 5*SIZE_TILE,(*salles)[9]->destination.y + 6*SIZE_TILE};
			etapes[18] = (Pos_t){(*salles)[9]->destination.x + 5*SIZE_TILE,(*salles)[9]->destination.y + 5*SIZE_TILE};
			etapes[19] = (Pos_t){(*salles)[9]->destination.x + 5*SIZE_TILE,(*salles)[9]->destination.y + 4*SIZE_TILE};
			etapes[20] = (Pos_t){(*salles)[9]->destination.x + 5*SIZE_TILE,(*salles)[9]->destination.y + 3*SIZE_TILE};
			etapes[21] = (Pos_t){(*salles)[9]->destination.x + 5*SIZE_TILE,(*salles)[9]->destination.y + 2*SIZE_TILE};
			etapes[22] = (Pos_t){(*salles)[9]->destination.x + 6*SIZE_TILE,(*salles)[9]->destination.y + 2*SIZE_TILE};
			etapes[23] = (Pos_t){(*salles)[9]->destination.x + 7*SIZE_TILE,(*salles)[9]->destination.y + 2*SIZE_TILE};
		etapeCourante = 0;
		entites[17]= EntiteCreate(renderer, SLIME_R, etapes, etapeCourante, nbEtapes);

		//Entite 18
		nbEtapes = 24;
		etapes = (Pos_t*)malloc(nbEtapes*sizeof(Pos_t));
			etapes[0] = (Pos_t){(*salles)[9]->destination.x + 9*SIZE_TILE,(*salles)[9]->destination.y + 2*SIZE_TILE};
			etapes[1] = (Pos_t){(*salles)[9]->destination.x + 10*SIZE_TILE,(*salles)[9]->destination.y + 2*SIZE_TILE};
			etapes[2] = (Pos_t){(*salles)[9]->destination.x + 11*SIZE_TILE,(*salles)[9]->destination.y + 2*SIZE_TILE};
			etapes[3] = (Pos_t){(*salles)[9]->destination.x + 11*SIZE_TILE,(*salles)[9]->destination.y + 3*SIZE_TILE};
			etapes[4] = (Pos_t){(*salles)[9]->destination.x + 11*SIZE_TILE,(*salles)[9]->destination.y + 4*SIZE_TILE};
			etapes[5] = (Pos_t){(*salles)[9]->destination.x + 11*SIZE_TILE,(*salles)[9]->destination.y + 5*SIZE_TILE};
			etapes[6] = (Pos_t){(*salles)[9]->destination.x + 11*SIZE_TILE,(*salles)[9]->destination.y + 6*SIZE_TILE};
			etapes[7] = (Pos_t){(*salles)[9]->destination.x + 11*SIZE_TILE,(*salles)[9]->destination.y + 7*SIZE_TILE};
			etapes[8] = (Pos_t){(*salles)[9]->destination.x + 11*SIZE_TILE,(*salles)[9]->destination.y + 8*SIZE_TILE};
			etapes[9] = (Pos_t){(*salles)[9]->destination.x + 10*SIZE_TILE,(*salles)[9]->destination.y + 8*SIZE_TILE};
			etapes[10] = (Pos_t){(*salles)[9]->destination.x + 9*SIZE_TILE,(*salles)[9]->destination.y + 8*SIZE_TILE};
			etapes[11] = (Pos_t){(*salles)[9]->destination.x + 8*SIZE_TILE,(*salles)[9]->destination.y + 8*SIZE_TILE};
			etapes[12] = (Pos_t){(*salles)[9]->destination.x + 7*SIZE_TILE,(*salles)[9]->destination.y + 8*SIZE_TILE};
			etapes[13] = (Pos_t){(*salles)[9]->destination.x + 6*SIZE_TILE,(*salles)[9]->destination.y + 8*SIZE_TILE};
			etapes[14] = (Pos_t){(*salles)[9]->destination.x + 5*SIZE_TILE,(*salles)[9]->destination.y + 8*SIZE_TILE};
			etapes[15] = (Pos_t){(*salles)[9]->destination.x + 5*SIZE_TILE,(*salles)[9]->destination.y + 7*SIZE_TILE};
			etapes[16] = (Pos_t){(*salles)[9]->destination.x + 5*SIZE_TILE,(*salles)[9]->destination.y + 6*SIZE_TILE};
			etapes[17] = (Pos_t){(*salles)[9]->destination.x + 5*SIZE_TILE,(*salles)[9]->destination.y + 5*SIZE_TILE};
			etapes[18] = (Pos_t){(*salles)[9]->destination.x + 5*SIZE_TILE,(*salles)[9]->destination.y + 4*SIZE_TILE};
			etapes[19] = (Pos_t){(*salles)[9]->destination.x + 5*SIZE_TILE,(*salles)[9]->destination.y + 3*SIZE_TILE};
			etapes[20] = (Pos_t){(*salles)[9]->destination.x + 5*SIZE_TILE,(*salles)[9]->destination.y + 2*SIZE_TILE};
			etapes[21] = (Pos_t){(*salles)[9]->destination.x + 6*SIZE_TILE,(*salles)[9]->destination.y + 2*SIZE_TILE};
			etapes[22] = (Pos_t){(*salles)[9]->destination.x + 7*SIZE_TILE,(*salles)[9]->destination.y + 2*SIZE_TILE};
			etapes[23] = (Pos_t){(*salles)[9]->destination.x + 8*SIZE_TILE,(*salles)[9]->destination.y + 2*SIZE_TILE};
		etapeCourante = 0;
		entites[18]= EntiteCreate(renderer, SLIME_R, etapes, etapeCourante, nbEtapes);

		//Entite 19
		nbEtapes = 24;
		etapes = (Pos_t*)malloc(nbEtapes*sizeof(Pos_t));
			etapes[0] = (Pos_t){(*salles)[9]->destination.x + 10*SIZE_TILE,(*salles)[9]->destination.y + 2*SIZE_TILE};
			etapes[1] = (Pos_t){(*salles)[9]->destination.x + 11*SIZE_TILE,(*salles)[9]->destination.y + 2*SIZE_TILE};
			etapes[2] = (Pos_t){(*salles)[9]->destination.x + 11*SIZE_TILE,(*salles)[9]->destination.y + 3*SIZE_TILE};
			etapes[3] = (Pos_t){(*salles)[9]->destination.x + 11*SIZE_TILE,(*salles)[9]->destination.y + 4*SIZE_TILE};
			etapes[4] = (Pos_t){(*salles)[9]->destination.x + 11*SIZE_TILE,(*salles)[9]->destination.y + 5*SIZE_TILE};
			etapes[5] = (Pos_t){(*salles)[9]->destination.x + 11*SIZE_TILE,(*salles)[9]->destination.y + 6*SIZE_TILE};
			etapes[6] = (Pos_t){(*salles)[9]->destination.x + 11*SIZE_TILE,(*salles)[9]->destination.y + 7*SIZE_TILE};
			etapes[7] = (Pos_t){(*salles)[9]->destination.x + 11*SIZE_TILE,(*salles)[9]->destination.y + 8*SIZE_TILE};
			etapes[8] = (Pos_t){(*salles)[9]->destination.x + 10*SIZE_TILE,(*salles)[9]->destination.y + 8*SIZE_TILE};
			etapes[9] = (Pos_t){(*salles)[9]->destination.x + 9*SIZE_TILE,(*salles)[9]->destination.y + 8*SIZE_TILE};
			etapes[10] = (Pos_t){(*salles)[9]->destination.x + 8*SIZE_TILE,(*salles)[9]->destination.y + 8*SIZE_TILE};
			etapes[11] = (Pos_t){(*salles)[9]->destination.x + 7*SIZE_TILE,(*salles)[9]->destination.y + 8*SIZE_TILE};
			etapes[12] = (Pos_t){(*salles)[9]->destination.x + 6*SIZE_TILE,(*salles)[9]->destination.y + 8*SIZE_TILE};
			etapes[13] = (Pos_t){(*salles)[9]->destination.x + 5*SIZE_TILE,(*salles)[9]->destination.y + 8*SIZE_TILE};
			etapes[14] = (Pos_t){(*salles)[9]->destination.x + 5*SIZE_TILE,(*salles)[9]->destination.y + 7*SIZE_TILE};
			etapes[15] = (Pos_t){(*salles)[9]->destination.x + 5*SIZE_TILE,(*salles)[9]->destination.y + 6*SIZE_TILE};
			etapes[16] = (Pos_t){(*salles)[9]->destination.x + 5*SIZE_TILE,(*salles)[9]->destination.y + 5*SIZE_TILE};
			etapes[17] = (Pos_t){(*salles)[9]->destination.x + 5*SIZE_TILE,(*salles)[9]->destination.y + 4*SIZE_TILE};
			etapes[18] = (Pos_t){(*salles)[9]->destination.x + 5*SIZE_TILE,(*salles)[9]->destination.y + 3*SIZE_TILE};
			etapes[19] = (Pos_t){(*salles)[9]->destination.x + 5*SIZE_TILE,(*salles)[9]->destination.y + 2*SIZE_TILE};
			etapes[20] = (Pos_t){(*salles)[9]->destination.x + 6*SIZE_TILE,(*salles)[9]->destination.y + 2*SIZE_TILE};
			etapes[21] = (Pos_t){(*salles)[9]->destination.x + 7*SIZE_TILE,(*salles)[9]->destination.y + 2*SIZE_TILE};
			etapes[22] = (Pos_t){(*salles)[9]->destination.x + 8*SIZE_TILE,(*salles)[9]->destination.y + 2*SIZE_TILE};
			etapes[23] = (Pos_t){(*salles)[9]->destination.x + 9*SIZE_TILE,(*salles)[9]->destination.y + 2*SIZE_TILE};
		etapeCourante = 0;
		entites[19]= EntiteCreate(renderer, SLIME_R, etapes, etapeCourante, nbEtapes);

		//Entite 20
		nbEtapes = 24;
		etapes = (Pos_t*)malloc(nbEtapes*sizeof(Pos_t));
			etapes[0] = (Pos_t){(*salles)[9]->destination.x + 11*SIZE_TILE,(*salles)[9]->destination.y + 2*SIZE_TILE};
			etapes[1] = (Pos_t){(*salles)[9]->destination.x + 11*SIZE_TILE,(*salles)[9]->destination.y + 3*SIZE_TILE};
			etapes[2] = (Pos_t){(*salles)[9]->destination.x + 11*SIZE_TILE,(*salles)[9]->destination.y + 4*SIZE_TILE};
			etapes[3] = (Pos_t){(*salles)[9]->destination.x + 11*SIZE_TILE,(*salles)[9]->destination.y + 5*SIZE_TILE};
			etapes[4] = (Pos_t){(*salles)[9]->destination.x + 11*SIZE_TILE,(*salles)[9]->destination.y + 6*SIZE_TILE};
			etapes[5] = (Pos_t){(*salles)[9]->destination.x + 11*SIZE_TILE,(*salles)[9]->destination.y + 7*SIZE_TILE};
			etapes[6] = (Pos_t){(*salles)[9]->destination.x + 11*SIZE_TILE,(*salles)[9]->destination.y + 8*SIZE_TILE};
			etapes[7] = (Pos_t){(*salles)[9]->destination.x + 10*SIZE_TILE,(*salles)[9]->destination.y + 8*SIZE_TILE};
			etapes[8] = (Pos_t){(*salles)[9]->destination.x + 9*SIZE_TILE,(*salles)[9]->destination.y + 8*SIZE_TILE};
			etapes[9] = (Pos_t){(*salles)[9]->destination.x + 8*SIZE_TILE,(*salles)[9]->destination.y + 8*SIZE_TILE};
			etapes[10] = (Pos_t){(*salles)[9]->destination.x + 7*SIZE_TILE,(*salles)[9]->destination.y + 8*SIZE_TILE};
			etapes[11] = (Pos_t){(*salles)[9]->destination.x + 6*SIZE_TILE,(*salles)[9]->destination.y + 8*SIZE_TILE};
			etapes[12] = (Pos_t){(*salles)[9]->destination.x + 5*SIZE_TILE,(*salles)[9]->destination.y + 8*SIZE_TILE};
			etapes[13] = (Pos_t){(*salles)[9]->destination.x + 5*SIZE_TILE,(*salles)[9]->destination.y + 7*SIZE_TILE};
			etapes[14] = (Pos_t){(*salles)[9]->destination.x + 5*SIZE_TILE,(*salles)[9]->destination.y + 6*SIZE_TILE};
			etapes[15] = (Pos_t){(*salles)[9]->destination.x + 5*SIZE_TILE,(*salles)[9]->destination.y + 5*SIZE_TILE};
			etapes[16] = (Pos_t){(*salles)[9]->destination.x + 5*SIZE_TILE,(*salles)[9]->destination.y + 4*SIZE_TILE};
			etapes[17] = (Pos_t){(*salles)[9]->destination.x + 5*SIZE_TILE,(*salles)[9]->destination.y + 3*SIZE_TILE};
			etapes[18] = (Pos_t){(*salles)[9]->destination.x + 5*SIZE_TILE,(*salles)[9]->destination.y + 2*SIZE_TILE};
			etapes[19] = (Pos_t){(*salles)[9]->destination.x + 6*SIZE_TILE,(*salles)[9]->destination.y + 2*SIZE_TILE};
			etapes[20] = (Pos_t){(*salles)[9]->destination.x + 7*SIZE_TILE,(*salles)[9]->destination.y + 2*SIZE_TILE};
			etapes[21] = (Pos_t){(*salles)[9]->destination.x + 8*SIZE_TILE,(*salles)[9]->destination.y + 2*SIZE_TILE};
			etapes[22] = (Pos_t){(*salles)[9]->destination.x + 9*SIZE_TILE,(*salles)[9]->destination.y + 2*SIZE_TILE};
			etapes[23] = (Pos_t){(*salles)[9]->destination.x + 10*SIZE_TILE,(*salles)[9]->destination.y + 2*SIZE_TILE};
		etapeCourante = 0;
		entites[20]= EntiteCreate(renderer, SLIME_R, etapes, etapeCourante, nbEtapes);

		//Entite 21
		nbEtapes = 24;
		etapes = (Pos_t*)malloc(nbEtapes*sizeof(Pos_t));
			etapes[0] = (Pos_t){(*salles)[9]->destination.x + 11*SIZE_TILE,(*salles)[9]->destination.y + 3*SIZE_TILE};
			etapes[1] = (Pos_t){(*salles)[9]->destination.x + 11*SIZE_TILE,(*salles)[9]->destination.y + 4*SIZE_TILE};
			etapes[2] = (Pos_t){(*salles)[9]->destination.x + 11*SIZE_TILE,(*salles)[9]->destination.y + 5*SIZE_TILE};
			etapes[3] = (Pos_t){(*salles)[9]->destination.x + 11*SIZE_TILE,(*salles)[9]->destination.y + 6*SIZE_TILE};
			etapes[4] = (Pos_t){(*salles)[9]->destination.x + 11*SIZE_TILE,(*salles)[9]->destination.y + 7*SIZE_TILE};
			etapes[5] = (Pos_t){(*salles)[9]->destination.x + 11*SIZE_TILE,(*salles)[9]->destination.y + 8*SIZE_TILE};
			etapes[6] = (Pos_t){(*salles)[9]->destination.x + 10*SIZE_TILE,(*salles)[9]->destination.y + 8*SIZE_TILE};
			etapes[7] = (Pos_t){(*salles)[9]->destination.x + 9*SIZE_TILE,(*salles)[9]->destination.y + 8*SIZE_TILE};
			etapes[8] = (Pos_t){(*salles)[9]->destination.x + 8*SIZE_TILE,(*salles)[9]->destination.y + 8*SIZE_TILE};
			etapes[9] = (Pos_t){(*salles)[9]->destination.x + 7*SIZE_TILE,(*salles)[9]->destination.y + 8*SIZE_TILE};
			etapes[10] = (Pos_t){(*salles)[9]->destination.x + 6*SIZE_TILE,(*salles)[9]->destination.y + 8*SIZE_TILE};
			etapes[11] = (Pos_t){(*salles)[9]->destination.x + 5*SIZE_TILE,(*salles)[9]->destination.y + 8*SIZE_TILE};
			etapes[12] = (Pos_t){(*salles)[9]->destination.x + 5*SIZE_TILE,(*salles)[9]->destination.y + 7*SIZE_TILE};
			etapes[13] = (Pos_t){(*salles)[9]->destination.x + 5*SIZE_TILE,(*salles)[9]->destination.y + 6*SIZE_TILE};
			etapes[14] = (Pos_t){(*salles)[9]->destination.x + 5*SIZE_TILE,(*salles)[9]->destination.y + 5*SIZE_TILE};
			etapes[15] = (Pos_t){(*salles)[9]->destination.x + 5*SIZE_TILE,(*salles)[9]->destination.y + 4*SIZE_TILE};
			etapes[16] = (Pos_t){(*salles)[9]->destination.x + 5*SIZE_TILE,(*salles)[9]->destination.y + 3*SIZE_TILE};
			etapes[17] = (Pos_t){(*salles)[9]->destination.x + 5*SIZE_TILE,(*salles)[9]->destination.y + 2*SIZE_TILE};
			etapes[18] = (Pos_t){(*salles)[9]->destination.x + 6*SIZE_TILE,(*salles)[9]->destination.y + 2*SIZE_TILE};
			etapes[19] = (Pos_t){(*salles)[9]->destination.x + 7*SIZE_TILE,(*salles)[9]->destination.y + 2*SIZE_TILE};
			etapes[20] = (Pos_t){(*salles)[9]->destination.x + 8*SIZE_TILE,(*salles)[9]->destination.y + 2*SIZE_TILE};
			etapes[21] = (Pos_t){(*salles)[9]->destination.x + 9*SIZE_TILE,(*salles)[9]->destination.y + 2*SIZE_TILE};
			etapes[22] = (Pos_t){(*salles)[9]->destination.x + 10*SIZE_TILE,(*salles)[9]->destination.y + 2*SIZE_TILE};
			etapes[23] = (Pos_t){(*salles)[9]->destination.x + 11*SIZE_TILE,(*salles)[9]->destination.y + 2*SIZE_TILE};
		etapeCourante = 0;
		entites[21]= EntiteCreate(renderer, SLIME_R, etapes, etapeCourante, nbEtapes);

		//Entite 22
		nbEtapes = 24;
		etapes = (Pos_t*)malloc(nbEtapes*sizeof(Pos_t));
			etapes[0] = (Pos_t){(*salles)[9]->destination.x + 11*SIZE_TILE,(*salles)[9]->destination.y + 4*SIZE_TILE};
			etapes[1] = (Pos_t){(*salles)[9]->destination.x + 11*SIZE_TILE,(*salles)[9]->destination.y + 5*SIZE_TILE};
			etapes[2] = (Pos_t){(*salles)[9]->destination.x + 11*SIZE_TILE,(*salles)[9]->destination.y + 6*SIZE_TILE};
			etapes[3] = (Pos_t){(*salles)[9]->destination.x + 11*SIZE_TILE,(*salles)[9]->destination.y + 7*SIZE_TILE};
			etapes[4] = (Pos_t){(*salles)[9]->destination.x + 11*SIZE_TILE,(*salles)[9]->destination.y + 8*SIZE_TILE};
			etapes[5] = (Pos_t){(*salles)[9]->destination.x + 10*SIZE_TILE,(*salles)[9]->destination.y + 8*SIZE_TILE};
			etapes[6] = (Pos_t){(*salles)[9]->destination.x + 9*SIZE_TILE,(*salles)[9]->destination.y + 8*SIZE_TILE};
			etapes[7] = (Pos_t){(*salles)[9]->destination.x + 8*SIZE_TILE,(*salles)[9]->destination.y + 8*SIZE_TILE};
			etapes[8] = (Pos_t){(*salles)[9]->destination.x + 7*SIZE_TILE,(*salles)[9]->destination.y + 8*SIZE_TILE};
			etapes[9] = (Pos_t){(*salles)[9]->destination.x + 6*SIZE_TILE,(*salles)[9]->destination.y + 8*SIZE_TILE};
			etapes[10] = (Pos_t){(*salles)[9]->destination.x + 5*SIZE_TILE,(*salles)[9]->destination.y + 8*SIZE_TILE};
			etapes[11] = (Pos_t){(*salles)[9]->destination.x + 5*SIZE_TILE,(*salles)[9]->destination.y + 7*SIZE_TILE};
			etapes[12] = (Pos_t){(*salles)[9]->destination.x + 5*SIZE_TILE,(*salles)[9]->destination.y + 6*SIZE_TILE};
			etapes[13] = (Pos_t){(*salles)[9]->destination.x + 5*SIZE_TILE,(*salles)[9]->destination.y + 5*SIZE_TILE};
			etapes[14] = (Pos_t){(*salles)[9]->destination.x + 5*SIZE_TILE,(*salles)[9]->destination.y + 4*SIZE_TILE};
			etapes[15] = (Pos_t){(*salles)[9]->destination.x + 5*SIZE_TILE,(*salles)[9]->destination.y + 3*SIZE_TILE};
			etapes[16] = (Pos_t){(*salles)[9]->destination.x + 5*SIZE_TILE,(*salles)[9]->destination.y + 2*SIZE_TILE};
			etapes[17] = (Pos_t){(*salles)[9]->destination.x + 6*SIZE_TILE,(*salles)[9]->destination.y + 2*SIZE_TILE};
			etapes[18] = (Pos_t){(*salles)[9]->destination.x + 7*SIZE_TILE,(*salles)[9]->destination.y + 2*SIZE_TILE};
			etapes[19] = (Pos_t){(*salles)[9]->destination.x + 8*SIZE_TILE,(*salles)[9]->destination.y + 2*SIZE_TILE};
			etapes[20] = (Pos_t){(*salles)[9]->destination.x + 9*SIZE_TILE,(*salles)[9]->destination.y + 2*SIZE_TILE};
			etapes[21] = (Pos_t){(*salles)[9]->destination.x + 10*SIZE_TILE,(*salles)[9]->destination.y + 2*SIZE_TILE};
			etapes[22] = (Pos_t){(*salles)[9]->destination.x + 11*SIZE_TILE,(*salles)[9]->destination.y + 2*SIZE_TILE};
			etapes[23] = (Pos_t){(*salles)[9]->destination.x + 11*SIZE_TILE,(*salles)[9]->destination.y + 3*SIZE_TILE};
		etapeCourante = 0;
		entites[22]= EntiteCreate(renderer, SLIME_R, etapes, etapeCourante, nbEtapes);

		//Entite 23
		nbEtapes = 24;
		etapes = (Pos_t*)malloc(nbEtapes*sizeof(Pos_t));
			etapes[0] = (Pos_t){(*salles)[9]->destination.x + 11*SIZE_TILE,(*salles)[9]->destination.y + 5*SIZE_TILE};
			etapes[1] = (Pos_t){(*salles)[9]->destination.x + 11*SIZE_TILE,(*salles)[9]->destination.y + 6*SIZE_TILE};
			etapes[2] = (Pos_t){(*salles)[9]->destination.x + 11*SIZE_TILE,(*salles)[9]->destination.y + 7*SIZE_TILE};
			etapes[3] = (Pos_t){(*salles)[9]->destination.x + 11*SIZE_TILE,(*salles)[9]->destination.y + 8*SIZE_TILE};
			etapes[4] = (Pos_t){(*salles)[9]->destination.x + 10*SIZE_TILE,(*salles)[9]->destination.y + 8*SIZE_TILE};
			etapes[5] = (Pos_t){(*salles)[9]->destination.x + 9*SIZE_TILE,(*salles)[9]->destination.y + 8*SIZE_TILE};
			etapes[6] = (Pos_t){(*salles)[9]->destination.x + 8*SIZE_TILE,(*salles)[9]->destination.y + 8*SIZE_TILE};
			etapes[7] = (Pos_t){(*salles)[9]->destination.x + 7*SIZE_TILE,(*salles)[9]->destination.y + 8*SIZE_TILE};
			etapes[8] = (Pos_t){(*salles)[9]->destination.x + 6*SIZE_TILE,(*salles)[9]->destination.y + 8*SIZE_TILE};
			etapes[9] = (Pos_t){(*salles)[9]->destination.x + 5*SIZE_TILE,(*salles)[9]->destination.y + 8*SIZE_TILE};
			etapes[10] = (Pos_t){(*salles)[9]->destination.x + 5*SIZE_TILE,(*salles)[9]->destination.y + 7*SIZE_TILE};
			etapes[11] = (Pos_t){(*salles)[9]->destination.x + 5*SIZE_TILE,(*salles)[9]->destination.y + 6*SIZE_TILE};
			etapes[12] = (Pos_t){(*salles)[9]->destination.x + 5*SIZE_TILE,(*salles)[9]->destination.y + 5*SIZE_TILE};
			etapes[13] = (Pos_t){(*salles)[9]->destination.x + 5*SIZE_TILE,(*salles)[9]->destination.y + 4*SIZE_TILE};
			etapes[14] = (Pos_t){(*salles)[9]->destination.x + 5*SIZE_TILE,(*salles)[9]->destination.y + 3*SIZE_TILE};
			etapes[15] = (Pos_t){(*salles)[9]->destination.x + 5*SIZE_TILE,(*salles)[9]->destination.y + 2*SIZE_TILE};
			etapes[16] = (Pos_t){(*salles)[9]->destination.x + 6*SIZE_TILE,(*salles)[9]->destination.y + 2*SIZE_TILE};
			etapes[17] = (Pos_t){(*salles)[9]->destination.x + 7*SIZE_TILE,(*salles)[9]->destination.y + 2*SIZE_TILE};
			etapes[18] = (Pos_t){(*salles)[9]->destination.x + 8*SIZE_TILE,(*salles)[9]->destination.y + 2*SIZE_TILE};
			etapes[19] = (Pos_t){(*salles)[9]->destination.x + 9*SIZE_TILE,(*salles)[9]->destination.y + 2*SIZE_TILE};
			etapes[20] = (Pos_t){(*salles)[9]->destination.x + 10*SIZE_TILE,(*salles)[9]->destination.y + 2*SIZE_TILE};
			etapes[21] = (Pos_t){(*salles)[9]->destination.x + 11*SIZE_TILE,(*salles)[9]->destination.y + 2*SIZE_TILE};
			etapes[22] = (Pos_t){(*salles)[9]->destination.x + 11*SIZE_TILE,(*salles)[9]->destination.y + 3*SIZE_TILE};
			etapes[23] = (Pos_t){(*salles)[9]->destination.x + 11*SIZE_TILE,(*salles)[9]->destination.y + 4*SIZE_TILE};
		etapeCourante = 0;
		entites[23]= EntiteCreate(renderer, SLIME_R, etapes, etapeCourante, nbEtapes);

		//Entite 24
		nbEtapes = 24;
		etapes = (Pos_t*)malloc(nbEtapes*sizeof(Pos_t));
			etapes[0] = (Pos_t){(*salles)[9]->destination.x + 11*SIZE_TILE,(*salles)[9]->destination.y + 6*SIZE_TILE};
			etapes[1] = (Pos_t){(*salles)[9]->destination.x + 11*SIZE_TILE,(*salles)[9]->destination.y + 7*SIZE_TILE};
			etapes[2] = (Pos_t){(*salles)[9]->destination.x + 11*SIZE_TILE,(*salles)[9]->destination.y + 8*SIZE_TILE};
			etapes[3] = (Pos_t){(*salles)[9]->destination.x + 10*SIZE_TILE,(*salles)[9]->destination.y + 8*SIZE_TILE};
			etapes[4] = (Pos_t){(*salles)[9]->destination.x + 9*SIZE_TILE,(*salles)[9]->destination.y + 8*SIZE_TILE};
			etapes[5] = (Pos_t){(*salles)[9]->destination.x + 8*SIZE_TILE,(*salles)[9]->destination.y + 8*SIZE_TILE};
			etapes[6] = (Pos_t){(*salles)[9]->destination.x + 7*SIZE_TILE,(*salles)[9]->destination.y + 8*SIZE_TILE};
			etapes[7] = (Pos_t){(*salles)[9]->destination.x + 6*SIZE_TILE,(*salles)[9]->destination.y + 8*SIZE_TILE};
			etapes[8] = (Pos_t){(*salles)[9]->destination.x + 5*SIZE_TILE,(*salles)[9]->destination.y + 8*SIZE_TILE};
			etapes[9] = (Pos_t){(*salles)[9]->destination.x + 5*SIZE_TILE,(*salles)[9]->destination.y + 7*SIZE_TILE};
			etapes[10] = (Pos_t){(*salles)[9]->destination.x + 5*SIZE_TILE,(*salles)[9]->destination.y + 6*SIZE_TILE};
			etapes[11] = (Pos_t){(*salles)[9]->destination.x + 5*SIZE_TILE,(*salles)[9]->destination.y + 5*SIZE_TILE};
			etapes[12] = (Pos_t){(*salles)[9]->destination.x + 5*SIZE_TILE,(*salles)[9]->destination.y + 4*SIZE_TILE};
			etapes[13] = (Pos_t){(*salles)[9]->destination.x + 5*SIZE_TILE,(*salles)[9]->destination.y + 3*SIZE_TILE};
			etapes[14] = (Pos_t){(*salles)[9]->destination.x + 5*SIZE_TILE,(*salles)[9]->destination.y + 2*SIZE_TILE};
			etapes[15] = (Pos_t){(*salles)[9]->destination.x + 6*SIZE_TILE,(*salles)[9]->destination.y + 2*SIZE_TILE};
			etapes[16] = (Pos_t){(*salles)[9]->destination.x + 7*SIZE_TILE,(*salles)[9]->destination.y + 2*SIZE_TILE};
			etapes[17] = (Pos_t){(*salles)[9]->destination.x + 8*SIZE_TILE,(*salles)[9]->destination.y + 2*SIZE_TILE};
			etapes[18] = (Pos_t){(*salles)[9]->destination.x + 9*SIZE_TILE,(*salles)[9]->destination.y + 2*SIZE_TILE};
			etapes[19] = (Pos_t){(*salles)[9]->destination.x + 10*SIZE_TILE,(*salles)[9]->destination.y + 2*SIZE_TILE};
			etapes[20] = (Pos_t){(*salles)[9]->destination.x + 11*SIZE_TILE,(*salles)[9]->destination.y + 2*SIZE_TILE};
			etapes[21] = (Pos_t){(*salles)[9]->destination.x + 11*SIZE_TILE,(*salles)[9]->destination.y + 3*SIZE_TILE};
			etapes[22] = (Pos_t){(*salles)[9]->destination.x + 11*SIZE_TILE,(*salles)[9]->destination.y + 4*SIZE_TILE};
			etapes[23] = (Pos_t){(*salles)[9]->destination.x + 11*SIZE_TILE,(*salles)[9]->destination.y + 5*SIZE_TILE};
		etapeCourante = 0;
		entites[24]= EntiteCreate(renderer, SLIME_R, etapes, etapeCourante, nbEtapes);

		//Entite 25
		nbEtapes = 24;
		etapes = (Pos_t*)malloc(nbEtapes*sizeof(Pos_t));
			etapes[0] = (Pos_t){(*salles)[9]->destination.x + 11*SIZE_TILE,(*salles)[9]->destination.y + 7*SIZE_TILE};
			etapes[1] = (Pos_t){(*salles)[9]->destination.x + 11*SIZE_TILE,(*salles)[9]->destination.y + 8*SIZE_TILE};
			etapes[2] = (Pos_t){(*salles)[9]->destination.x + 10*SIZE_TILE,(*salles)[9]->destination.y + 8*SIZE_TILE};
			etapes[3] = (Pos_t){(*salles)[9]->destination.x + 9*SIZE_TILE,(*salles)[9]->destination.y + 8*SIZE_TILE};
			etapes[4] = (Pos_t){(*salles)[9]->destination.x + 8*SIZE_TILE,(*salles)[9]->destination.y + 8*SIZE_TILE};
			etapes[5] = (Pos_t){(*salles)[9]->destination.x + 7*SIZE_TILE,(*salles)[9]->destination.y + 8*SIZE_TILE};
			etapes[6] = (Pos_t){(*salles)[9]->destination.x + 6*SIZE_TILE,(*salles)[9]->destination.y + 8*SIZE_TILE};
			etapes[7] = (Pos_t){(*salles)[9]->destination.x + 5*SIZE_TILE,(*salles)[9]->destination.y + 8*SIZE_TILE};
			etapes[8] = (Pos_t){(*salles)[9]->destination.x + 5*SIZE_TILE,(*salles)[9]->destination.y + 7*SIZE_TILE};
			etapes[9] = (Pos_t){(*salles)[9]->destination.x + 5*SIZE_TILE,(*salles)[9]->destination.y + 6*SIZE_TILE};
			etapes[10] = (Pos_t){(*salles)[9]->destination.x + 5*SIZE_TILE,(*salles)[9]->destination.y + 5*SIZE_TILE};
			etapes[11] = (Pos_t){(*salles)[9]->destination.x + 5*SIZE_TILE,(*salles)[9]->destination.y + 4*SIZE_TILE};
			etapes[12] = (Pos_t){(*salles)[9]->destination.x + 5*SIZE_TILE,(*salles)[9]->destination.y + 3*SIZE_TILE};
			etapes[13] = (Pos_t){(*salles)[9]->destination.x + 5*SIZE_TILE,(*salles)[9]->destination.y + 2*SIZE_TILE};
			etapes[14] = (Pos_t){(*salles)[9]->destination.x + 6*SIZE_TILE,(*salles)[9]->destination.y + 2*SIZE_TILE};
			etapes[15] = (Pos_t){(*salles)[9]->destination.x + 7*SIZE_TILE,(*salles)[9]->destination.y + 2*SIZE_TILE};
			etapes[16] = (Pos_t){(*salles)[9]->destination.x + 8*SIZE_TILE,(*salles)[9]->destination.y + 2*SIZE_TILE};
			etapes[17] = (Pos_t){(*salles)[9]->destination.x + 9*SIZE_TILE,(*salles)[9]->destination.y + 2*SIZE_TILE};
			etapes[18] = (Pos_t){(*salles)[9]->destination.x + 10*SIZE_TILE,(*salles)[9]->destination.y + 2*SIZE_TILE};
			etapes[19] = (Pos_t){(*salles)[9]->destination.x + 11*SIZE_TILE,(*salles)[9]->destination.y + 2*SIZE_TILE};
			etapes[20] = (Pos_t){(*salles)[9]->destination.x + 11*SIZE_TILE,(*salles)[9]->destination.y + 3*SIZE_TILE};
			etapes[21] = (Pos_t){(*salles)[9]->destination.x + 11*SIZE_TILE,(*salles)[9]->destination.y + 4*SIZE_TILE};
			etapes[22] = (Pos_t){(*salles)[9]->destination.x + 11*SIZE_TILE,(*salles)[9]->destination.y + 5*SIZE_TILE};
			etapes[23] = (Pos_t){(*salles)[9]->destination.x + 11*SIZE_TILE,(*salles)[9]->destination.y + 6*SIZE_TILE};
		etapeCourante = 0;
		entites[25]= EntiteCreate(renderer, SLIME_R, etapes, etapeCourante, nbEtapes);

		//Entite 26
		nbEtapes = 24;
		etapes = (Pos_t*)malloc(nbEtapes*sizeof(Pos_t));
			etapes[0] = (Pos_t){(*salles)[9]->destination.x + 11*SIZE_TILE,(*salles)[9]->destination.y + 8*SIZE_TILE};
			etapes[1] = (Pos_t){(*salles)[9]->destination.x + 10*SIZE_TILE,(*salles)[9]->destination.y + 8*SIZE_TILE};
			etapes[2] = (Pos_t){(*salles)[9]->destination.x + 9*SIZE_TILE,(*salles)[9]->destination.y + 8*SIZE_TILE};
			etapes[3] = (Pos_t){(*salles)[9]->destination.x + 8*SIZE_TILE,(*salles)[9]->destination.y + 8*SIZE_TILE};
			etapes[4] = (Pos_t){(*salles)[9]->destination.x + 7*SIZE_TILE,(*salles)[9]->destination.y + 8*SIZE_TILE};
			etapes[5] = (Pos_t){(*salles)[9]->destination.x + 6*SIZE_TILE,(*salles)[9]->destination.y + 8*SIZE_TILE};
			etapes[6] = (Pos_t){(*salles)[9]->destination.x + 5*SIZE_TILE,(*salles)[9]->destination.y + 8*SIZE_TILE};
			etapes[7] = (Pos_t){(*salles)[9]->destination.x + 5*SIZE_TILE,(*salles)[9]->destination.y + 7*SIZE_TILE};
			etapes[8] = (Pos_t){(*salles)[9]->destination.x + 5*SIZE_TILE,(*salles)[9]->destination.y + 6*SIZE_TILE};
			etapes[9] = (Pos_t){(*salles)[9]->destination.x + 5*SIZE_TILE,(*salles)[9]->destination.y + 5*SIZE_TILE};
			etapes[10] = (Pos_t){(*salles)[9]->destination.x + 5*SIZE_TILE,(*salles)[9]->destination.y + 4*SIZE_TILE};
			etapes[11] = (Pos_t){(*salles)[9]->destination.x + 5*SIZE_TILE,(*salles)[9]->destination.y + 3*SIZE_TILE};
			etapes[12] = (Pos_t){(*salles)[9]->destination.x + 5*SIZE_TILE,(*salles)[9]->destination.y + 2*SIZE_TILE};
			etapes[13] = (Pos_t){(*salles)[9]->destination.x + 6*SIZE_TILE,(*salles)[9]->destination.y + 2*SIZE_TILE};
			etapes[14] = (Pos_t){(*salles)[9]->destination.x + 7*SIZE_TILE,(*salles)[9]->destination.y + 2*SIZE_TILE};
			etapes[15] = (Pos_t){(*salles)[9]->destination.x + 8*SIZE_TILE,(*salles)[9]->destination.y + 2*SIZE_TILE};
			etapes[16] = (Pos_t){(*salles)[9]->destination.x + 9*SIZE_TILE,(*salles)[9]->destination.y + 2*SIZE_TILE};
			etapes[17] = (Pos_t){(*salles)[9]->destination.x + 10*SIZE_TILE,(*salles)[9]->destination.y + 2*SIZE_TILE};
			etapes[18] = (Pos_t){(*salles)[9]->destination.x + 11*SIZE_TILE,(*salles)[9]->destination.y + 2*SIZE_TILE};
			etapes[19] = (Pos_t){(*salles)[9]->destination.x + 11*SIZE_TILE,(*salles)[9]->destination.y + 3*SIZE_TILE};
			etapes[20] = (Pos_t){(*salles)[9]->destination.x + 11*SIZE_TILE,(*salles)[9]->destination.y + 4*SIZE_TILE};
			etapes[21] = (Pos_t){(*salles)[9]->destination.x + 11*SIZE_TILE,(*salles)[9]->destination.y + 5*SIZE_TILE};
			etapes[22] = (Pos_t){(*salles)[9]->destination.x + 11*SIZE_TILE,(*salles)[9]->destination.y + 6*SIZE_TILE};
			etapes[23] = (Pos_t){(*salles)[9]->destination.x + 11*SIZE_TILE,(*salles)[9]->destination.y + 7*SIZE_TILE};
		etapeCourante = 0;
		entites[26]= EntiteCreate(renderer, SLIME_R, etapes, etapeCourante, nbEtapes);

		//Entite 27
		nbEtapes = 24;
		etapes = (Pos_t*)malloc(nbEtapes*sizeof(Pos_t));
			etapes[0] = (Pos_t){(*salles)[9]->destination.x + 10*SIZE_TILE,(*salles)[9]->destination.y + 8*SIZE_TILE};
			etapes[1]= (Pos_t){(*salles)[9]->destination.x + 9*SIZE_TILE,(*salles)[9]->destination.y + 8*SIZE_TILE};
			etapes[2] = (Pos_t){(*salles)[9]->destination.x + 8*SIZE_TILE,(*salles)[9]->destination.y + 8*SIZE_TILE};
			etapes[3] = (Pos_t){(*salles)[9]->destination.x + 7*SIZE_TILE,(*salles)[9]->destination.y + 8*SIZE_TILE};
			etapes[4] = (Pos_t){(*salles)[9]->destination.x + 6*SIZE_TILE,(*salles)[9]->destination.y + 8*SIZE_TILE};
			etapes[5] = (Pos_t){(*salles)[9]->destination.x + 5*SIZE_TILE,(*salles)[9]->destination.y + 8*SIZE_TILE};
			etapes[6] = (Pos_t){(*salles)[9]->destination.x + 5*SIZE_TILE,(*salles)[9]->destination.y + 7*SIZE_TILE};
			etapes[7] = (Pos_t){(*salles)[9]->destination.x + 5*SIZE_TILE,(*salles)[9]->destination.y + 6*SIZE_TILE};
			etapes[8] = (Pos_t){(*salles)[9]->destination.x + 5*SIZE_TILE,(*salles)[9]->destination.y + 5*SIZE_TILE};
			etapes[9] = (Pos_t){(*salles)[9]->destination.x + 5*SIZE_TILE,(*salles)[9]->destination.y + 4*SIZE_TILE};
			etapes[10] = (Pos_t){(*salles)[9]->destination.x + 5*SIZE_TILE,(*salles)[9]->destination.y + 3*SIZE_TILE};
			etapes[11] = (Pos_t){(*salles)[9]->destination.x + 5*SIZE_TILE,(*salles)[9]->destination.y + 2*SIZE_TILE};
			etapes[12] = (Pos_t){(*salles)[9]->destination.x + 6*SIZE_TILE,(*salles)[9]->destination.y + 2*SIZE_TILE};
			etapes[13] = (Pos_t){(*salles)[9]->destination.x + 7*SIZE_TILE,(*salles)[9]->destination.y + 2*SIZE_TILE};
			etapes[14] = (Pos_t){(*salles)[9]->destination.x + 8*SIZE_TILE,(*salles)[9]->destination.y + 2*SIZE_TILE};
			etapes[15] = (Pos_t){(*salles)[9]->destination.x + 9*SIZE_TILE,(*salles)[9]->destination.y + 2*SIZE_TILE};
			etapes[16] = (Pos_t){(*salles)[9]->destination.x + 10*SIZE_TILE,(*salles)[9]->destination.y + 2*SIZE_TILE};
			etapes[17] = (Pos_t){(*salles)[9]->destination.x + 11*SIZE_TILE,(*salles)[9]->destination.y + 2*SIZE_TILE};
			etapes[18] = (Pos_t){(*salles)[9]->destination.x + 11*SIZE_TILE,(*salles)[9]->destination.y + 3*SIZE_TILE};
			etapes[19] = (Pos_t){(*salles)[9]->destination.x + 11*SIZE_TILE,(*salles)[9]->destination.y + 4*SIZE_TILE};
			etapes[20] = (Pos_t){(*salles)[9]->destination.x + 11*SIZE_TILE,(*salles)[9]->destination.y + 5*SIZE_TILE};
			etapes[21] = (Pos_t){(*salles)[9]->destination.x + 11*SIZE_TILE,(*salles)[9]->destination.y + 6*SIZE_TILE};
			etapes[22] = (Pos_t){(*salles)[9]->destination.x + 11*SIZE_TILE,(*salles)[9]->destination.y + 7*SIZE_TILE};
			etapes[23] = (Pos_t){(*salles)[9]->destination.x + 11*SIZE_TILE,(*salles)[9]->destination.y + 8*SIZE_TILE};
		etapeCourante = 0;
		entites[27]= EntiteCreate(renderer, SLIME_R, etapes, etapeCourante, nbEtapes);

		//Entite 28
		nbEtapes = 24;
		etapes = (Pos_t*)malloc(nbEtapes*sizeof(Pos_t));
			etapes[0] = (Pos_t){(*salles)[9]->destination.x + 9*SIZE_TILE,(*salles)[9]->destination.y + 8*SIZE_TILE};
			etapes[1] = (Pos_t){(*salles)[9]->destination.x + 8*SIZE_TILE,(*salles)[9]->destination.y + 8*SIZE_TILE};
			etapes[2] = (Pos_t){(*salles)[9]->destination.x + 7*SIZE_TILE,(*salles)[9]->destination.y + 8*SIZE_TILE};
			etapes[3] = (Pos_t){(*salles)[9]->destination.x + 6*SIZE_TILE,(*salles)[9]->destination.y + 8*SIZE_TILE};
			etapes[4] = (Pos_t){(*salles)[9]->destination.x + 5*SIZE_TILE,(*salles)[9]->destination.y + 8*SIZE_TILE};
			etapes[5] = (Pos_t){(*salles)[9]->destination.x + 5*SIZE_TILE,(*salles)[9]->destination.y + 7*SIZE_TILE};
			etapes[6] = (Pos_t){(*salles)[9]->destination.x + 5*SIZE_TILE,(*salles)[9]->destination.y + 6*SIZE_TILE};
			etapes[7] = (Pos_t){(*salles)[9]->destination.x + 5*SIZE_TILE,(*salles)[9]->destination.y + 5*SIZE_TILE};
			etapes[8] = (Pos_t){(*salles)[9]->destination.x + 5*SIZE_TILE,(*salles)[9]->destination.y + 4*SIZE_TILE};
			etapes[9] = (Pos_t){(*salles)[9]->destination.x + 5*SIZE_TILE,(*salles)[9]->destination.y + 3*SIZE_TILE};
			etapes[10] = (Pos_t){(*salles)[9]->destination.x + 5*SIZE_TILE,(*salles)[9]->destination.y + 2*SIZE_TILE};
			etapes[11] = (Pos_t){(*salles)[9]->destination.x + 6*SIZE_TILE,(*salles)[9]->destination.y + 2*SIZE_TILE};
			etapes[12] = (Pos_t){(*salles)[9]->destination.x + 7*SIZE_TILE,(*salles)[9]->destination.y + 2*SIZE_TILE};
			etapes[13] = (Pos_t){(*salles)[9]->destination.x + 8*SIZE_TILE,(*salles)[9]->destination.y + 2*SIZE_TILE};
			etapes[14] = (Pos_t){(*salles)[9]->destination.x + 9*SIZE_TILE,(*salles)[9]->destination.y + 2*SIZE_TILE};
			etapes[15] = (Pos_t){(*salles)[9]->destination.x + 10*SIZE_TILE,(*salles)[9]->destination.y + 2*SIZE_TILE};
			etapes[16] = (Pos_t){(*salles)[9]->destination.x + 11*SIZE_TILE,(*salles)[9]->destination.y + 2*SIZE_TILE};
			etapes[17] = (Pos_t){(*salles)[9]->destination.x + 11*SIZE_TILE,(*salles)[9]->destination.y + 3*SIZE_TILE};
			etapes[18] = (Pos_t){(*salles)[9]->destination.x + 11*SIZE_TILE,(*salles)[9]->destination.y + 4*SIZE_TILE};
			etapes[19] = (Pos_t){(*salles)[9]->destination.x + 11*SIZE_TILE,(*salles)[9]->destination.y + 5*SIZE_TILE};
			etapes[20] = (Pos_t){(*salles)[9]->destination.x + 11*SIZE_TILE,(*salles)[9]->destination.y + 6*SIZE_TILE};
			etapes[21] = (Pos_t){(*salles)[9]->destination.x + 11*SIZE_TILE,(*salles)[9]->destination.y + 7*SIZE_TILE};
			etapes[22] = (Pos_t){(*salles)[9]->destination.x + 11*SIZE_TILE,(*salles)[9]->destination.y + 8*SIZE_TILE};
			etapes[23] = (Pos_t){(*salles)[9]->destination.x + 10*SIZE_TILE,(*salles)[9]->destination.y + 8*SIZE_TILE};
		etapeCourante = 0;
		entites[28]= EntiteCreate(renderer, SLIME_R, etapes, etapeCourante, nbEtapes);


	(*salles)[9]->entites = entites;
	(*salles)[9]->nbObjectifs = 2;	
	(*salles)[9]->nbObjectifsVivants = 2;	
	(*salles)[9]->nbEntites = nbEntites;








	//SALLE 10

	texture = IMG_LoadTexture(renderer, "assets/Salles/Salle_21x17_Rose.png");
	(*salles)[10] = SalleCreate(texture, 1, 9, 8);
	nbEntites = 40;
	entites = (Entite_t**)malloc(nbEntites*sizeof(Entite_t*));

		//ENTITE 0
		nbEtapes = 8;
		etapes = (Pos_t*)malloc(nbEtapes*sizeof(Pos_t));
			etapes[0] = (Pos_t){(*salles)[10]->destination.x + 1*SIZE_TILE,(*salles)[10]->destination.y + 1*SIZE_TILE};
			etapes[1] = (Pos_t){(*salles)[10]->destination.x + 1*SIZE_TILE,(*salles)[10]->destination.y + 2*SIZE_TILE};
			etapes[2] = (Pos_t){(*salles)[10]->destination.x + 1*SIZE_TILE,(*salles)[10]->destination.y + 3*SIZE_TILE};
			etapes[3] = (Pos_t){(*salles)[10]->destination.x + 2*SIZE_TILE,(*salles)[10]->destination.y + 3*SIZE_TILE};
			etapes[4] = (Pos_t){(*salles)[10]->destination.x + 3*SIZE_TILE,(*salles)[10]->destination.y + 3*SIZE_TILE};
			etapes[5] = (Pos_t){(*salles)[10]->destination.x + 3*SIZE_TILE,(*salles)[10]->destination.y + 2*SIZE_TILE};
			etapes[6] = (Pos_t){(*salles)[10]->destination.x + 3*SIZE_TILE,(*salles)[10]->destination.y + 1*SIZE_TILE};
			etapes[7] = (Pos_t){(*salles)[10]->destination.x + 2*SIZE_TILE,(*salles)[10]->destination.y + 1*SIZE_TILE};
		etapeCourante = 0;
		entites[0] = EntiteCreate(renderer, SLIME_R, etapes, etapeCourante, nbEtapes);
		
		//ENTITE 1
		nbEtapes = 8;
		etapes = (Pos_t*)malloc(nbEtapes*sizeof(Pos_t));
			etapes[0] = (Pos_t){(*salles)[10]->destination.x + 3*SIZE_TILE,(*salles)[10]->destination.y + 3*SIZE_TILE};
			etapes[1] = (Pos_t){(*salles)[10]->destination.x + 3*SIZE_TILE,(*salles)[10]->destination.y + 2*SIZE_TILE};
			etapes[2] = (Pos_t){(*salles)[10]->destination.x + 3*SIZE_TILE,(*salles)[10]->destination.y + 1*SIZE_TILE};
			etapes[3] = (Pos_t){(*salles)[10]->destination.x + 2*SIZE_TILE,(*salles)[10]->destination.y + 1*SIZE_TILE};
			etapes[4] = (Pos_t){(*salles)[10]->destination.x + 1*SIZE_TILE,(*salles)[10]->destination.y + 1*SIZE_TILE};
			etapes[5] = (Pos_t){(*salles)[10]->destination.x + 1*SIZE_TILE,(*salles)[10]->destination.y + 2*SIZE_TILE};
			etapes[6] = (Pos_t){(*salles)[10]->destination.x + 1*SIZE_TILE,(*salles)[10]->destination.y + 3*SIZE_TILE};
			etapes[7] = (Pos_t){(*salles)[10]->destination.x + 2*SIZE_TILE,(*salles)[10]->destination.y + 3*SIZE_TILE};
		etapeCourante = 0;
		entites[1] = EntiteCreate(renderer, SLIME_R, etapes, etapeCourante, nbEtapes);

		//ENTITE 2
		nbEtapes = 1;
		etapes = (Pos_t*)malloc(nbEtapes*sizeof(Pos_t));
			etapes[0] = (Pos_t){(*salles)[10]->destination.x + 2*SIZE_TILE,(*salles)[10]->destination.y + 2*SIZE_TILE};

		etapeCourante = 0;
		entites[2] = EntiteCreate(renderer, SLIME_V, etapes, etapeCourante, nbEtapes);
		
		//ENTITE 3
		nbEtapes = 7;
		etapes = (Pos_t*)malloc(nbEtapes*sizeof(Pos_t));
			etapes[0] = (Pos_t){(*salles)[10]->destination.x + 4*SIZE_TILE,(*salles)[10]->destination.y + 1*SIZE_TILE};
			etapes[1] = (Pos_t){(*salles)[10]->destination.x + 4*SIZE_TILE,(*salles)[10]->destination.y + 2*SIZE_TILE};
			etapes[2] = (Pos_t){(*salles)[10]->destination.x + 4*SIZE_TILE,(*salles)[10]->destination.y + 3*SIZE_TILE};
			etapes[3] = (Pos_t){(*salles)[10]->destination.x + 4*SIZE_TILE,(*salles)[10]->destination.y + 4*SIZE_TILE};
			etapes[4] = (Pos_t){(*salles)[10]->destination.x + 3*SIZE_TILE,(*salles)[10]->destination.y + 4*SIZE_TILE};
			etapes[5] = (Pos_t){(*salles)[10]->destination.x + 2*SIZE_TILE,(*salles)[10]->destination.y + 4*SIZE_TILE};
			etapes[6] = (Pos_t){(*salles)[10]->destination.x + 1*SIZE_TILE,(*salles)[10]->destination.y + 4*SIZE_TILE};

		etapeCourante = 0;
		entites[3] = EntiteCreate(renderer, SLIME_R, etapes, etapeCourante, nbEtapes);

        //ENTITE 4
		nbEtapes = 20;
		etapes = (Pos_t*)malloc(nbEtapes*sizeof(Pos_t));
			etapes[0] = (Pos_t){(*salles)[10]->destination.x + 6*SIZE_TILE,(*salles)[10]->destination.y + 1*SIZE_TILE};
            etapes[1] = (Pos_t){(*salles)[10]->destination.x + 6*SIZE_TILE,(*salles)[10]->destination.y + 2*SIZE_TILE};
            etapes[2] = (Pos_t){(*salles)[10]->destination.x + 6*SIZE_TILE,(*salles)[10]->destination.y + 3*SIZE_TILE};
            etapes[3] = (Pos_t){(*salles)[10]->destination.x + 6*SIZE_TILE,(*salles)[10]->destination.y + 4*SIZE_TILE};
            etapes[4] = (Pos_t){(*salles)[10]->destination.x + 6*SIZE_TILE,(*salles)[10]->destination.y + 5*SIZE_TILE};
            etapes[5] = (Pos_t){(*salles)[10]->destination.x + 6*SIZE_TILE,(*salles)[10]->destination.y + 6*SIZE_TILE};
            etapes[6] = (Pos_t){(*salles)[10]->destination.x + 5*SIZE_TILE,(*salles)[10]->destination.y + 6*SIZE_TILE};
            etapes[7] = (Pos_t){(*salles)[10]->destination.x + 4*SIZE_TILE,(*salles)[10]->destination.y + 6*SIZE_TILE};
            etapes[8] = (Pos_t){(*salles)[10]->destination.x + 3*SIZE_TILE,(*salles)[10]->destination.y + 6*SIZE_TILE};
            etapes[9] = (Pos_t){(*salles)[10]->destination.x + 2*SIZE_TILE,(*salles)[10]->destination.y + 6*SIZE_TILE};
            etapes[10] = (Pos_t){(*salles)[10]->destination.x + 1*SIZE_TILE,(*salles)[10]->destination.y + 6*SIZE_TILE};
            etapes[11] = (Pos_t){(*salles)[10]->destination.x + 1*SIZE_TILE,(*salles)[10]->destination.y + 5*SIZE_TILE};
            etapes[12] = (Pos_t){(*salles)[10]->destination.x + 2*SIZE_TILE,(*salles)[10]->destination.y + 5*SIZE_TILE};
            etapes[13] = (Pos_t){(*salles)[10]->destination.x + 3*SIZE_TILE,(*salles)[10]->destination.y + 5*SIZE_TILE};
            etapes[14] = (Pos_t){(*salles)[10]->destination.x + 4*SIZE_TILE,(*salles)[10]->destination.y + 5*SIZE_TILE};
            etapes[15] = (Pos_t){(*salles)[10]->destination.x + 5*SIZE_TILE,(*salles)[10]->destination.y + 5*SIZE_TILE};
            etapes[16] = (Pos_t){(*salles)[10]->destination.x + 5*SIZE_TILE,(*salles)[10]->destination.y + 4*SIZE_TILE};
            etapes[17] = (Pos_t){(*salles)[10]->destination.x + 5*SIZE_TILE,(*salles)[10]->destination.y + 3*SIZE_TILE};
            etapes[18] = (Pos_t){(*salles)[10]->destination.x + 5*SIZE_TILE,(*salles)[10]->destination.y + 2*SIZE_TILE};
            etapes[19] = (Pos_t){(*salles)[10]->destination.x + 5*SIZE_TILE,(*salles)[10]->destination.y + 1*SIZE_TILE};


		etapeCourante = 0;
		entites[4] = EntiteCreate(renderer, SLIME_R, etapes, etapeCourante, nbEtapes);

        //ENTITE 5
		nbEtapes = 20;
		etapes = (Pos_t*)malloc(nbEtapes*sizeof(Pos_t));
            etapes[0] = (Pos_t){(*salles)[10]->destination.x + 6*SIZE_TILE,(*salles)[10]->destination.y + 6*SIZE_TILE};
            etapes[1] = (Pos_t){(*salles)[10]->destination.x + 5*SIZE_TILE,(*salles)[10]->destination.y + 6*SIZE_TILE};
            etapes[2] = (Pos_t){(*salles)[10]->destination.x + 4*SIZE_TILE,(*salles)[10]->destination.y + 6*SIZE_TILE};
            etapes[3] = (Pos_t){(*salles)[10]->destination.x + 3*SIZE_TILE,(*salles)[10]->destination.y + 6*SIZE_TILE};
            etapes[4] = (Pos_t){(*salles)[10]->destination.x + 2*SIZE_TILE,(*salles)[10]->destination.y + 6*SIZE_TILE};
            etapes[5] = (Pos_t){(*salles)[10]->destination.x + 1*SIZE_TILE,(*salles)[10]->destination.y + 6*SIZE_TILE};
            etapes[6] = (Pos_t){(*salles)[10]->destination.x + 1*SIZE_TILE,(*salles)[10]->destination.y + 5*SIZE_TILE};
            etapes[7] = (Pos_t){(*salles)[10]->destination.x + 2*SIZE_TILE,(*salles)[10]->destination.y + 5*SIZE_TILE};
            etapes[8] = (Pos_t){(*salles)[10]->destination.x + 3*SIZE_TILE,(*salles)[10]->destination.y + 5*SIZE_TILE};
            etapes[9] = (Pos_t){(*salles)[10]->destination.x + 4*SIZE_TILE,(*salles)[10]->destination.y + 5*SIZE_TILE};
            etapes[10] = (Pos_t){(*salles)[10]->destination.x + 5*SIZE_TILE,(*salles)[10]->destination.y + 5*SIZE_TILE};
            etapes[11] = (Pos_t){(*salles)[10]->destination.x + 5*SIZE_TILE,(*salles)[10]->destination.y + 4*SIZE_TILE};
            etapes[12] = (Pos_t){(*salles)[10]->destination.x + 5*SIZE_TILE,(*salles)[10]->destination.y + 3*SIZE_TILE};
            etapes[13] = (Pos_t){(*salles)[10]->destination.x + 5*SIZE_TILE,(*salles)[10]->destination.y + 2*SIZE_TILE};
            etapes[14] = (Pos_t){(*salles)[10]->destination.x + 5*SIZE_TILE,(*salles)[10]->destination.y + 1*SIZE_TILE};
			etapes[15] = (Pos_t){(*salles)[10]->destination.x + 6*SIZE_TILE,(*salles)[10]->destination.y + 1*SIZE_TILE};
            etapes[16] = (Pos_t){(*salles)[10]->destination.x + 6*SIZE_TILE,(*salles)[10]->destination.y + 2*SIZE_TILE};
            etapes[17] = (Pos_t){(*salles)[10]->destination.x + 6*SIZE_TILE,(*salles)[10]->destination.y + 3*SIZE_TILE};
            etapes[18] = (Pos_t){(*salles)[10]->destination.x + 6*SIZE_TILE,(*salles)[10]->destination.y + 4*SIZE_TILE};
            etapes[19] = (Pos_t){(*salles)[10]->destination.x + 6*SIZE_TILE,(*salles)[10]->destination.y + 5*SIZE_TILE};


		etapeCourante = 0;
		entites[5] = EntiteCreate(renderer, SLIME_R, etapes, etapeCourante, nbEtapes);

        //ENTITE 6
		nbEtapes = 20;
		etapes = (Pos_t*)malloc(nbEtapes*sizeof(Pos_t));
            etapes[0] = (Pos_t){(*salles)[10]->destination.x + 1*SIZE_TILE,(*salles)[10]->destination.y + 5*SIZE_TILE};
            etapes[1] = (Pos_t){(*salles)[10]->destination.x + 2*SIZE_TILE,(*salles)[10]->destination.y + 5*SIZE_TILE};
            etapes[2] = (Pos_t){(*salles)[10]->destination.x + 3*SIZE_TILE,(*salles)[10]->destination.y + 5*SIZE_TILE};
            etapes[3] = (Pos_t){(*salles)[10]->destination.x + 4*SIZE_TILE,(*salles)[10]->destination.y + 5*SIZE_TILE};
            etapes[4] = (Pos_t){(*salles)[10]->destination.x + 5*SIZE_TILE,(*salles)[10]->destination.y + 5*SIZE_TILE};
            etapes[5] = (Pos_t){(*salles)[10]->destination.x + 5*SIZE_TILE,(*salles)[10]->destination.y + 4*SIZE_TILE};
            etapes[6] = (Pos_t){(*salles)[10]->destination.x + 5*SIZE_TILE,(*salles)[10]->destination.y + 3*SIZE_TILE};
            etapes[7] = (Pos_t){(*salles)[10]->destination.x + 5*SIZE_TILE,(*salles)[10]->destination.y + 2*SIZE_TILE};
            etapes[8] = (Pos_t){(*salles)[10]->destination.x + 5*SIZE_TILE,(*salles)[10]->destination.y + 1*SIZE_TILE};
			etapes[9] = (Pos_t){(*salles)[10]->destination.x + 6*SIZE_TILE,(*salles)[10]->destination.y + 1*SIZE_TILE};
            etapes[10] = (Pos_t){(*salles)[10]->destination.x + 6*SIZE_TILE,(*salles)[10]->destination.y + 2*SIZE_TILE};
            etapes[11] = (Pos_t){(*salles)[10]->destination.x + 6*SIZE_TILE,(*salles)[10]->destination.y + 3*SIZE_TILE};
            etapes[12] = (Pos_t){(*salles)[10]->destination.x + 6*SIZE_TILE,(*salles)[10]->destination.y + 4*SIZE_TILE};
            etapes[13] = (Pos_t){(*salles)[10]->destination.x + 6*SIZE_TILE,(*salles)[10]->destination.y + 5*SIZE_TILE};
            etapes[14] = (Pos_t){(*salles)[10]->destination.x + 6*SIZE_TILE,(*salles)[10]->destination.y + 6*SIZE_TILE};
            etapes[15] = (Pos_t){(*salles)[10]->destination.x + 5*SIZE_TILE,(*salles)[10]->destination.y + 6*SIZE_TILE};
            etapes[16] = (Pos_t){(*salles)[10]->destination.x + 4*SIZE_TILE,(*salles)[10]->destination.y + 6*SIZE_TILE};
            etapes[17] = (Pos_t){(*salles)[10]->destination.x + 3*SIZE_TILE,(*salles)[10]->destination.y + 6*SIZE_TILE};
            etapes[18] = (Pos_t){(*salles)[10]->destination.x + 2*SIZE_TILE,(*salles)[10]->destination.y + 6*SIZE_TILE};
            etapes[19] = (Pos_t){(*salles)[10]->destination.x + 1*SIZE_TILE,(*salles)[10]->destination.y + 6*SIZE_TILE};


		etapeCourante = 0;
		entites[6] = EntiteCreate(renderer, SLIME_R, etapes, etapeCourante, nbEtapes);

        //ENTITE 7
		nbEtapes = 20;
		etapes = (Pos_t*)malloc(nbEtapes*sizeof(Pos_t));
            etapes[0] = (Pos_t){(*salles)[10]->destination.x + 5*SIZE_TILE,(*salles)[10]->destination.y + 5*SIZE_TILE};
            etapes[1] = (Pos_t){(*salles)[10]->destination.x + 5*SIZE_TILE,(*salles)[10]->destination.y + 4*SIZE_TILE};
            etapes[2] = (Pos_t){(*salles)[10]->destination.x + 5*SIZE_TILE,(*salles)[10]->destination.y + 3*SIZE_TILE};
            etapes[3] = (Pos_t){(*salles)[10]->destination.x + 5*SIZE_TILE,(*salles)[10]->destination.y + 2*SIZE_TILE};
            etapes[4] = (Pos_t){(*salles)[10]->destination.x + 5*SIZE_TILE,(*salles)[10]->destination.y + 1*SIZE_TILE};
			etapes[5] = (Pos_t){(*salles)[10]->destination.x + 6*SIZE_TILE,(*salles)[10]->destination.y + 1*SIZE_TILE};
            etapes[6] = (Pos_t){(*salles)[10]->destination.x + 6*SIZE_TILE,(*salles)[10]->destination.y + 2*SIZE_TILE};
            etapes[7] = (Pos_t){(*salles)[10]->destination.x + 6*SIZE_TILE,(*salles)[10]->destination.y + 3*SIZE_TILE};
            etapes[8] = (Pos_t){(*salles)[10]->destination.x + 6*SIZE_TILE,(*salles)[10]->destination.y + 4*SIZE_TILE};
            etapes[9] = (Pos_t){(*salles)[10]->destination.x + 6*SIZE_TILE,(*salles)[10]->destination.y + 5*SIZE_TILE};
            etapes[10] = (Pos_t){(*salles)[10]->destination.x + 6*SIZE_TILE,(*salles)[10]->destination.y + 6*SIZE_TILE};
            etapes[11] = (Pos_t){(*salles)[10]->destination.x + 5*SIZE_TILE,(*salles)[10]->destination.y + 6*SIZE_TILE};
            etapes[12] = (Pos_t){(*salles)[10]->destination.x + 4*SIZE_TILE,(*salles)[10]->destination.y + 6*SIZE_TILE};
            etapes[13] = (Pos_t){(*salles)[10]->destination.x + 3*SIZE_TILE,(*salles)[10]->destination.y + 6*SIZE_TILE};
            etapes[14] = (Pos_t){(*salles)[10]->destination.x + 2*SIZE_TILE,(*salles)[10]->destination.y + 6*SIZE_TILE};
            etapes[15] = (Pos_t){(*salles)[10]->destination.x + 1*SIZE_TILE,(*salles)[10]->destination.y + 6*SIZE_TILE};
            etapes[16] = (Pos_t){(*salles)[10]->destination.x + 1*SIZE_TILE,(*salles)[10]->destination.y + 5*SIZE_TILE};
            etapes[17] = (Pos_t){(*salles)[10]->destination.x + 2*SIZE_TILE,(*salles)[10]->destination.y + 5*SIZE_TILE};
            etapes[18] = (Pos_t){(*salles)[10]->destination.x + 3*SIZE_TILE,(*salles)[10]->destination.y + 5*SIZE_TILE};
            etapes[19] = (Pos_t){(*salles)[10]->destination.x + 4*SIZE_TILE,(*salles)[10]->destination.y + 5*SIZE_TILE};


		etapeCourante = 0;
		entites[7] = EntiteCreate(renderer, SLIME_R, etapes, etapeCourante, nbEtapes);

        //ENTITE 8
		nbEtapes = 12;
		etapes = (Pos_t*)malloc(nbEtapes*sizeof(Pos_t));
            etapes[0] = (Pos_t){(*salles)[10]->destination.x + 8*SIZE_TILE,(*salles)[10]->destination.y + 3*SIZE_TILE};
            etapes[1] = (Pos_t){(*salles)[10]->destination.x + 8*SIZE_TILE,(*salles)[10]->destination.y + 2*SIZE_TILE};
            etapes[2] = (Pos_t){(*salles)[10]->destination.x + 8*SIZE_TILE,(*salles)[10]->destination.y + 1*SIZE_TILE};
            etapes[3] = (Pos_t){(*salles)[10]->destination.x + 9*SIZE_TILE,(*salles)[10]->destination.y + 1*SIZE_TILE};
            etapes[4] = (Pos_t){(*salles)[10]->destination.x + 10*SIZE_TILE,(*salles)[10]->destination.y + 1*SIZE_TILE};
            etapes[5] = (Pos_t){(*salles)[10]->destination.x + 11*SIZE_TILE,(*salles)[10]->destination.y + 1*SIZE_TILE};
            etapes[6] = (Pos_t){(*salles)[10]->destination.x + 12*SIZE_TILE,(*salles)[10]->destination.y + 1*SIZE_TILE};
            etapes[7] = (Pos_t){(*salles)[10]->destination.x + 12*SIZE_TILE,(*salles)[10]->destination.y + 2*SIZE_TILE};
            etapes[8] = (Pos_t){(*salles)[10]->destination.x + 12*SIZE_TILE,(*salles)[10]->destination.y + 3*SIZE_TILE};
            etapes[9] = (Pos_t){(*salles)[10]->destination.x + 11*SIZE_TILE,(*salles)[10]->destination.y + 3*SIZE_TILE};
            etapes[10] = (Pos_t){(*salles)[10]->destination.x + 10*SIZE_TILE,(*salles)[10]->destination.y + 3*SIZE_TILE};
            etapes[11] = (Pos_t){(*salles)[10]->destination.x + 9*SIZE_TILE,(*salles)[10]->destination.y + 3*SIZE_TILE};


		etapeCourante = 0;
		entites[8] = EntiteCreate(renderer, SLIME_V, etapes, etapeCourante, nbEtapes);

        //ENTITE 9
		nbEtapes = 12;
		etapes = (Pos_t*)malloc(nbEtapes*sizeof(Pos_t));
            etapes[0] = (Pos_t){(*salles)[10]->destination.x + 12*SIZE_TILE,(*salles)[10]->destination.y + 1*SIZE_TILE};
            etapes[1] = (Pos_t){(*salles)[10]->destination.x + 12*SIZE_TILE,(*salles)[10]->destination.y + 2*SIZE_TILE};
            etapes[2] = (Pos_t){(*salles)[10]->destination.x + 12*SIZE_TILE,(*salles)[10]->destination.y + 3*SIZE_TILE};
            etapes[3] = (Pos_t){(*salles)[10]->destination.x + 11*SIZE_TILE,(*salles)[10]->destination.y + 3*SIZE_TILE};
            etapes[4] = (Pos_t){(*salles)[10]->destination.x + 10*SIZE_TILE,(*salles)[10]->destination.y + 3*SIZE_TILE};
            etapes[5] = (Pos_t){(*salles)[10]->destination.x + 9*SIZE_TILE,(*salles)[10]->destination.y + 3*SIZE_TILE};
            etapes[6] = (Pos_t){(*salles)[10]->destination.x + 8*SIZE_TILE,(*salles)[10]->destination.y + 3*SIZE_TILE};
            etapes[7] = (Pos_t){(*salles)[10]->destination.x + 8*SIZE_TILE,(*salles)[10]->destination.y + 2*SIZE_TILE};
            etapes[8] = (Pos_t){(*salles)[10]->destination.x + 8*SIZE_TILE,(*salles)[10]->destination.y + 1*SIZE_TILE};
            etapes[9] = (Pos_t){(*salles)[10]->destination.x + 9*SIZE_TILE,(*salles)[10]->destination.y + 1*SIZE_TILE};
            etapes[10] = (Pos_t){(*salles)[10]->destination.x + 10*SIZE_TILE,(*salles)[10]->destination.y + 1*SIZE_TILE};
            etapes[11] = (Pos_t){(*salles)[10]->destination.x + 11*SIZE_TILE,(*salles)[10]->destination.y + 1*SIZE_TILE};


		etapeCourante = 0;
		entites[9] = EntiteCreate(renderer, SLIME_V, etapes, etapeCourante, nbEtapes);

        //ENTITE 10
		nbEtapes = 8;
		etapes = (Pos_t*)malloc(nbEtapes*sizeof(Pos_t));
            etapes[0] = (Pos_t){(*salles)[10]->destination.x + 1*SIZE_TILE,(*salles)[10]->destination.y + 7*SIZE_TILE};
            etapes[1] = (Pos_t){(*salles)[10]->destination.x + 2*SIZE_TILE,(*salles)[10]->destination.y + 7*SIZE_TILE};
            etapes[2] = (Pos_t){(*salles)[10]->destination.x + 2*SIZE_TILE,(*salles)[10]->destination.y + 8*SIZE_TILE};
            etapes[3] = (Pos_t){(*salles)[10]->destination.x + 2*SIZE_TILE,(*salles)[10]->destination.y + 9*SIZE_TILE};
            etapes[4] = (Pos_t){(*salles)[10]->destination.x + 2*SIZE_TILE,(*salles)[10]->destination.y + 10*SIZE_TILE};
            etapes[5] = (Pos_t){(*salles)[10]->destination.x + 1*SIZE_TILE,(*salles)[10]->destination.y + 10*SIZE_TILE};
            etapes[6] = (Pos_t){(*salles)[10]->destination.x + 1*SIZE_TILE,(*salles)[10]->destination.y + 9*SIZE_TILE};
            etapes[7] = (Pos_t){(*salles)[10]->destination.x + 1*SIZE_TILE,(*salles)[10]->destination.y + 8*SIZE_TILE};


		etapeCourante = 0;
		entites[10] = EntiteCreate(renderer, SLIME_V, etapes, etapeCourante, nbEtapes);

        //ENTITE 11
		nbEtapes = 8;
		etapes = (Pos_t*)malloc(nbEtapes*sizeof(Pos_t));
            etapes[0] = (Pos_t){(*salles)[10]->destination.x + 2*SIZE_TILE,(*salles)[10]->destination.y + 10*SIZE_TILE};
            etapes[1] = (Pos_t){(*salles)[10]->destination.x + 1*SIZE_TILE,(*salles)[10]->destination.y + 10*SIZE_TILE};
            etapes[2] = (Pos_t){(*salles)[10]->destination.x + 1*SIZE_TILE,(*salles)[10]->destination.y + 9*SIZE_TILE};
            etapes[3] = (Pos_t){(*salles)[10]->destination.x + 1*SIZE_TILE,(*salles)[10]->destination.y + 8*SIZE_TILE};
            etapes[4] = (Pos_t){(*salles)[10]->destination.x + 1*SIZE_TILE,(*salles)[10]->destination.y + 7*SIZE_TILE};
            etapes[5] = (Pos_t){(*salles)[10]->destination.x + 2*SIZE_TILE,(*salles)[10]->destination.y + 7*SIZE_TILE};
            etapes[6] = (Pos_t){(*salles)[10]->destination.x + 2*SIZE_TILE,(*salles)[10]->destination.y + 8*SIZE_TILE};
            etapes[7] = (Pos_t){(*salles)[10]->destination.x + 2*SIZE_TILE,(*salles)[10]->destination.y + 9*SIZE_TILE};


		etapeCourante = 0;
		entites[11] = EntiteCreate(renderer, SLIME_V, etapes, etapeCourante, nbEtapes);

        //ENTITE 12
		nbEtapes = 14;
		etapes = (Pos_t*)malloc(nbEtapes*sizeof(Pos_t));
            etapes[0] = (Pos_t){(*salles)[10]->destination.x + 15*SIZE_TILE,(*salles)[10]->destination.y + 3*SIZE_TILE};
            etapes[1] = (Pos_t){(*salles)[10]->destination.x + 15*SIZE_TILE,(*salles)[10]->destination.y + 2*SIZE_TILE};
            etapes[2] = (Pos_t){(*salles)[10]->destination.x + 15*SIZE_TILE,(*salles)[10]->destination.y + 1*SIZE_TILE};
            etapes[3] = (Pos_t){(*salles)[10]->destination.x + 16*SIZE_TILE,(*salles)[10]->destination.y + 1*SIZE_TILE};
            etapes[4] = (Pos_t){(*salles)[10]->destination.x + 17*SIZE_TILE,(*salles)[10]->destination.y + 1*SIZE_TILE};
            etapes[5] = (Pos_t){(*salles)[10]->destination.x + 18*SIZE_TILE,(*salles)[10]->destination.y + 1*SIZE_TILE};
            etapes[6] = (Pos_t){(*salles)[10]->destination.x + 19*SIZE_TILE,(*salles)[10]->destination.y + 1*SIZE_TILE};
            etapes[7] = (Pos_t){(*salles)[10]->destination.x + 19*SIZE_TILE,(*salles)[10]->destination.y + 2*SIZE_TILE};
            etapes[8] = (Pos_t){(*salles)[10]->destination.x + 19*SIZE_TILE,(*salles)[10]->destination.y + 3*SIZE_TILE};
            etapes[9] = (Pos_t){(*salles)[10]->destination.x + 19*SIZE_TILE,(*salles)[10]->destination.y + 4*SIZE_TILE};
            etapes[10] = (Pos_t){(*salles)[10]->destination.x + 18*SIZE_TILE,(*salles)[10]->destination.y + 4*SIZE_TILE};
            etapes[11] = (Pos_t){(*salles)[10]->destination.x + 17*SIZE_TILE,(*salles)[10]->destination.y + 4*SIZE_TILE};
            etapes[12] = (Pos_t){(*salles)[10]->destination.x + 16*SIZE_TILE,(*salles)[10]->destination.y + 4*SIZE_TILE};
            etapes[13] = (Pos_t){(*salles)[10]->destination.x + 15*SIZE_TILE,(*salles)[10]->destination.y + 4*SIZE_TILE};


		etapeCourante = 0;
		entites[12] = EntiteCreate(renderer, SLIME_R, etapes, etapeCourante, nbEtapes);

        //ENTITE 13
		nbEtapes = 14;
		etapes = (Pos_t*)malloc(nbEtapes*sizeof(Pos_t));
            etapes[0] = (Pos_t){(*salles)[10]->destination.x + 15*SIZE_TILE,(*salles)[10]->destination.y + 4*SIZE_TILE};
            etapes[1] = (Pos_t){(*salles)[10]->destination.x + 15*SIZE_TILE,(*salles)[10]->destination.y + 3*SIZE_TILE};
            etapes[2] = (Pos_t){(*salles)[10]->destination.x + 15*SIZE_TILE,(*salles)[10]->destination.y + 2*SIZE_TILE};
            etapes[3] = (Pos_t){(*salles)[10]->destination.x + 15*SIZE_TILE,(*salles)[10]->destination.y + 1*SIZE_TILE};
            etapes[4] = (Pos_t){(*salles)[10]->destination.x + 16*SIZE_TILE,(*salles)[10]->destination.y + 1*SIZE_TILE};
            etapes[5] = (Pos_t){(*salles)[10]->destination.x + 17*SIZE_TILE,(*salles)[10]->destination.y + 1*SIZE_TILE};
            etapes[6] = (Pos_t){(*salles)[10]->destination.x + 18*SIZE_TILE,(*salles)[10]->destination.y + 1*SIZE_TILE};
            etapes[7] = (Pos_t){(*salles)[10]->destination.x + 19*SIZE_TILE,(*salles)[10]->destination.y + 1*SIZE_TILE};
            etapes[8] = (Pos_t){(*salles)[10]->destination.x + 19*SIZE_TILE,(*salles)[10]->destination.y + 2*SIZE_TILE};
            etapes[9] = (Pos_t){(*salles)[10]->destination.x + 19*SIZE_TILE,(*salles)[10]->destination.y + 3*SIZE_TILE};
            etapes[10] = (Pos_t){(*salles)[10]->destination.x + 19*SIZE_TILE,(*salles)[10]->destination.y + 4*SIZE_TILE};
            etapes[11] = (Pos_t){(*salles)[10]->destination.x + 18*SIZE_TILE,(*salles)[10]->destination.y + 4*SIZE_TILE};
            etapes[12] = (Pos_t){(*salles)[10]->destination.x + 17*SIZE_TILE,(*salles)[10]->destination.y + 4*SIZE_TILE};
            etapes[13] = (Pos_t){(*salles)[10]->destination.x + 16*SIZE_TILE,(*salles)[10]->destination.y + 4*SIZE_TILE};


		etapeCourante = 0;
		entites[13] = EntiteCreate(renderer, SLIME_V, etapes, etapeCourante, nbEtapes);

        //ENTITE 14
		nbEtapes = 14;
		etapes = (Pos_t*)malloc(nbEtapes*sizeof(Pos_t));
            etapes[0] = (Pos_t){(*salles)[10]->destination.x + 16*SIZE_TILE,(*salles)[10]->destination.y + 4*SIZE_TILE};
            etapes[1] = (Pos_t){(*salles)[10]->destination.x + 15*SIZE_TILE,(*salles)[10]->destination.y + 4*SIZE_TILE};
            etapes[2] = (Pos_t){(*salles)[10]->destination.x + 15*SIZE_TILE,(*salles)[10]->destination.y + 3*SIZE_TILE};
            etapes[3] = (Pos_t){(*salles)[10]->destination.x + 15*SIZE_TILE,(*salles)[10]->destination.y + 2*SIZE_TILE};
            etapes[4] = (Pos_t){(*salles)[10]->destination.x + 15*SIZE_TILE,(*salles)[10]->destination.y + 1*SIZE_TILE};
            etapes[5] = (Pos_t){(*salles)[10]->destination.x + 16*SIZE_TILE,(*salles)[10]->destination.y + 1*SIZE_TILE};
            etapes[6] = (Pos_t){(*salles)[10]->destination.x + 17*SIZE_TILE,(*salles)[10]->destination.y + 1*SIZE_TILE};
            etapes[7] = (Pos_t){(*salles)[10]->destination.x + 18*SIZE_TILE,(*salles)[10]->destination.y + 1*SIZE_TILE};
            etapes[8] = (Pos_t){(*salles)[10]->destination.x + 19*SIZE_TILE,(*salles)[10]->destination.y + 1*SIZE_TILE};
            etapes[9] = (Pos_t){(*salles)[10]->destination.x + 19*SIZE_TILE,(*salles)[10]->destination.y + 2*SIZE_TILE};
            etapes[10] = (Pos_t){(*salles)[10]->destination.x + 19*SIZE_TILE,(*salles)[10]->destination.y + 3*SIZE_TILE};
            etapes[11] = (Pos_t){(*salles)[10]->destination.x + 19*SIZE_TILE,(*salles)[10]->destination.y + 4*SIZE_TILE};
            etapes[12] = (Pos_t){(*salles)[10]->destination.x + 18*SIZE_TILE,(*salles)[10]->destination.y + 4*SIZE_TILE};
            etapes[13] = (Pos_t){(*salles)[10]->destination.x + 17*SIZE_TILE,(*salles)[10]->destination.y + 4*SIZE_TILE};


		etapeCourante = 0;
		entites[14] = EntiteCreate(renderer, SLIME_R, etapes, etapeCourante, nbEtapes);

        //ENTITE 15
		nbEtapes = 4;
		etapes = (Pos_t*)malloc(nbEtapes*sizeof(Pos_t));
            etapes[0] = (Pos_t){(*salles)[10]->destination.x + 3*SIZE_TILE,(*salles)[10]->destination.y + 13*SIZE_TILE};
            etapes[1] = (Pos_t){(*salles)[10]->destination.x + 2*SIZE_TILE,(*salles)[10]->destination.y + 13*SIZE_TILE};
            etapes[2] = (Pos_t){(*salles)[10]->destination.x + 1*SIZE_TILE,(*salles)[10]->destination.y + 13*SIZE_TILE};
            etapes[3] = (Pos_t){(*salles)[10]->destination.x + 2*SIZE_TILE,(*salles)[10]->destination.y + 13*SIZE_TILE};


		etapeCourante = 0;
		entites[15] = EntiteCreate(renderer, SLIME_R, etapes, etapeCourante, nbEtapes);

        //ENTITE 16
		nbEtapes = 4;
		etapes = (Pos_t*)malloc(nbEtapes*sizeof(Pos_t));
            etapes[0] = (Pos_t){(*salles)[10]->destination.x + 3*SIZE_TILE,(*salles)[10]->destination.y + 15*SIZE_TILE};
            etapes[1] = (Pos_t){(*salles)[10]->destination.x + 3*SIZE_TILE,(*salles)[10]->destination.y + 14*SIZE_TILE};
            etapes[2] = (Pos_t){(*salles)[10]->destination.x + 3*SIZE_TILE,(*salles)[10]->destination.y + 13*SIZE_TILE};
            etapes[3] = (Pos_t){(*salles)[10]->destination.x + 3*SIZE_TILE,(*salles)[10]->destination.y + 14*SIZE_TILE};


		etapeCourante = 0;
		entites[16] = EntiteCreate(renderer, SLIME_R, etapes, etapeCourante, nbEtapes);

        //ENTITE 17
		nbEtapes = 4;
		etapes = (Pos_t*)malloc(nbEtapes*sizeof(Pos_t));
            etapes[0] = (Pos_t){(*salles)[10]->destination.x + 1*SIZE_TILE,(*salles)[10]->destination.y + 14*SIZE_TILE};
            etapes[1] = (Pos_t){(*salles)[10]->destination.x + 2*SIZE_TILE,(*salles)[10]->destination.y + 14*SIZE_TILE};
            etapes[2] = (Pos_t){(*salles)[10]->destination.x + 2*SIZE_TILE,(*salles)[10]->destination.y + 15*SIZE_TILE};
            etapes[3] = (Pos_t){(*salles)[10]->destination.x + 1*SIZE_TILE,(*salles)[10]->destination.y + 15*SIZE_TILE};


		etapeCourante = 0;
		entites[17] = EntiteCreate(renderer, SLIME_R, etapes, etapeCourante, nbEtapes);

        //ENTITE 18
		nbEtapes = 4;
		etapes = (Pos_t*)malloc(nbEtapes*sizeof(Pos_t));
            etapes[0] = (Pos_t){(*salles)[10]->destination.x + 2*SIZE_TILE,(*salles)[10]->destination.y + 15*SIZE_TILE};
            etapes[1] = (Pos_t){(*salles)[10]->destination.x + 1*SIZE_TILE,(*salles)[10]->destination.y + 15*SIZE_TILE};
            etapes[2] = (Pos_t){(*salles)[10]->destination.x + 1*SIZE_TILE,(*salles)[10]->destination.y + 14*SIZE_TILE};
            etapes[3] = (Pos_t){(*salles)[10]->destination.x + 2*SIZE_TILE,(*salles)[10]->destination.y + 14*SIZE_TILE};


		etapeCourante = 0;
		entites[18] = EntiteCreate(renderer, SLIME_R, etapes, etapeCourante, nbEtapes);

        //ENTITE 19
		nbEtapes = 4;
		etapes = (Pos_t*)malloc(nbEtapes*sizeof(Pos_t));
            etapes[0] = (Pos_t){(*salles)[10]->destination.x + 1*SIZE_TILE,(*salles)[10]->destination.y + 15*SIZE_TILE};
            etapes[1] = (Pos_t){(*salles)[10]->destination.x + 1*SIZE_TILE,(*salles)[10]->destination.y + 14*SIZE_TILE};
            etapes[2] = (Pos_t){(*salles)[10]->destination.x + 2*SIZE_TILE,(*salles)[10]->destination.y + 14*SIZE_TILE};
            etapes[3] = (Pos_t){(*salles)[10]->destination.x + 2*SIZE_TILE,(*salles)[10]->destination.y + 15*SIZE_TILE};


		etapeCourante = 0;
		entites[19] = EntiteCreate(renderer, SLIME_V, etapes, etapeCourante, nbEtapes);

        //ENTITE 20
		nbEtapes = 8;
		etapes = (Pos_t*)malloc(nbEtapes*sizeof(Pos_t));
            etapes[0] = (Pos_t){(*salles)[10]->destination.x + 9*SIZE_TILE,(*salles)[10]->destination.y + 7*SIZE_TILE};
            etapes[1] = (Pos_t){(*salles)[10]->destination.x + 10*SIZE_TILE,(*salles)[10]->destination.y + 7*SIZE_TILE};
            etapes[2] = (Pos_t){(*salles)[10]->destination.x + 11*SIZE_TILE,(*salles)[10]->destination.y + 7*SIZE_TILE};
            etapes[3] = (Pos_t){(*salles)[10]->destination.x + 11*SIZE_TILE,(*salles)[10]->destination.y + 8*SIZE_TILE};
            etapes[4] = (Pos_t){(*salles)[10]->destination.x + 11*SIZE_TILE,(*salles)[10]->destination.y + 9*SIZE_TILE};
            etapes[5] = (Pos_t){(*salles)[10]->destination.x + 10*SIZE_TILE,(*salles)[10]->destination.y + 9*SIZE_TILE};
            etapes[6] = (Pos_t){(*salles)[10]->destination.x + 9*SIZE_TILE,(*salles)[10]->destination.y + 9*SIZE_TILE};
            etapes[7] = (Pos_t){(*salles)[10]->destination.x + 9*SIZE_TILE,(*salles)[10]->destination.y + 8*SIZE_TILE};


		etapeCourante = 0;
		entites[20] = EntiteCreate(renderer, SLIME_R, etapes, etapeCourante, nbEtapes);

        //ENTITE 21
		nbEtapes = 8;
		etapes = (Pos_t*)malloc(nbEtapes*sizeof(Pos_t));
            etapes[0] = (Pos_t){(*salles)[10]->destination.x + 10*SIZE_TILE,(*salles)[10]->destination.y + 7*SIZE_TILE};
            etapes[1] = (Pos_t){(*salles)[10]->destination.x + 11*SIZE_TILE,(*salles)[10]->destination.y + 7*SIZE_TILE};
            etapes[2] = (Pos_t){(*salles)[10]->destination.x + 11*SIZE_TILE,(*salles)[10]->destination.y + 8*SIZE_TILE};
            etapes[3] = (Pos_t){(*salles)[10]->destination.x + 11*SIZE_TILE,(*salles)[10]->destination.y + 9*SIZE_TILE};
            etapes[4] = (Pos_t){(*salles)[10]->destination.x + 10*SIZE_TILE,(*salles)[10]->destination.y + 9*SIZE_TILE};
            etapes[5] = (Pos_t){(*salles)[10]->destination.x + 9*SIZE_TILE,(*salles)[10]->destination.y + 9*SIZE_TILE};
            etapes[6] = (Pos_t){(*salles)[10]->destination.x + 9*SIZE_TILE,(*salles)[10]->destination.y + 8*SIZE_TILE};
            etapes[7] = (Pos_t){(*salles)[10]->destination.x + 9*SIZE_TILE,(*salles)[10]->destination.y + 7*SIZE_TILE};


		etapeCourante = 0;
		entites[21] = EntiteCreate(renderer, SLIME_R, etapes, etapeCourante, nbEtapes);

        //ENTITE 22
		nbEtapes = 8;
		etapes = (Pos_t*)malloc(nbEtapes*sizeof(Pos_t));
            etapes[0] = (Pos_t){(*salles)[10]->destination.x + 11*SIZE_TILE,(*salles)[10]->destination.y + 7*SIZE_TILE};
            etapes[1] = (Pos_t){(*salles)[10]->destination.x + 11*SIZE_TILE,(*salles)[10]->destination.y + 8*SIZE_TILE};
            etapes[2] = (Pos_t){(*salles)[10]->destination.x + 11*SIZE_TILE,(*salles)[10]->destination.y + 9*SIZE_TILE};
            etapes[3] = (Pos_t){(*salles)[10]->destination.x + 10*SIZE_TILE,(*salles)[10]->destination.y + 9*SIZE_TILE};
            etapes[4] = (Pos_t){(*salles)[10]->destination.x + 9*SIZE_TILE,(*salles)[10]->destination.y + 9*SIZE_TILE};
            etapes[5] = (Pos_t){(*salles)[10]->destination.x + 9*SIZE_TILE,(*salles)[10]->destination.y + 8*SIZE_TILE};
            etapes[6] = (Pos_t){(*salles)[10]->destination.x + 9*SIZE_TILE,(*salles)[10]->destination.y + 7*SIZE_TILE};
            etapes[7] = (Pos_t){(*salles)[10]->destination.x + 10*SIZE_TILE,(*salles)[10]->destination.y + 7*SIZE_TILE};


		etapeCourante = 0;
		entites[22] = EntiteCreate(renderer, SLIME_R, etapes, etapeCourante, nbEtapes);

        //ENTITE 23
		nbEtapes = 8;
		etapes = (Pos_t*)malloc(nbEtapes*sizeof(Pos_t));
            etapes[0] = (Pos_t){(*salles)[10]->destination.x + 11*SIZE_TILE,(*salles)[10]->destination.y + 8*SIZE_TILE};
            etapes[1] = (Pos_t){(*salles)[10]->destination.x + 11*SIZE_TILE,(*salles)[10]->destination.y + 9*SIZE_TILE};
            etapes[2] = (Pos_t){(*salles)[10]->destination.x + 10*SIZE_TILE,(*salles)[10]->destination.y + 9*SIZE_TILE};
            etapes[3] = (Pos_t){(*salles)[10]->destination.x + 9*SIZE_TILE,(*salles)[10]->destination.y + 9*SIZE_TILE};
            etapes[4] = (Pos_t){(*salles)[10]->destination.x + 9*SIZE_TILE,(*salles)[10]->destination.y + 8*SIZE_TILE};
            etapes[5] = (Pos_t){(*salles)[10]->destination.x + 9*SIZE_TILE,(*salles)[10]->destination.y + 7*SIZE_TILE};
            etapes[6] = (Pos_t){(*salles)[10]->destination.x + 10*SIZE_TILE,(*salles)[10]->destination.y + 7*SIZE_TILE};
            etapes[7] = (Pos_t){(*salles)[10]->destination.x + 11*SIZE_TILE,(*salles)[10]->destination.y + 7*SIZE_TILE};


		etapeCourante = 0;
		entites[23] = EntiteCreate(renderer, SLIME_R, etapes, etapeCourante, nbEtapes);

        //ENTITE 24
		nbEtapes = 8;
		etapes = (Pos_t*)malloc(nbEtapes*sizeof(Pos_t));
            etapes[0] = (Pos_t){(*salles)[10]->destination.x + 11*SIZE_TILE,(*salles)[10]->destination.y + 9*SIZE_TILE};
            etapes[1] = (Pos_t){(*salles)[10]->destination.x + 10*SIZE_TILE,(*salles)[10]->destination.y + 9*SIZE_TILE};
            etapes[2] = (Pos_t){(*salles)[10]->destination.x + 9*SIZE_TILE,(*salles)[10]->destination.y + 9*SIZE_TILE};
            etapes[3] = (Pos_t){(*salles)[10]->destination.x + 9*SIZE_TILE,(*salles)[10]->destination.y + 8*SIZE_TILE};
            etapes[4] = (Pos_t){(*salles)[10]->destination.x + 9*SIZE_TILE,(*salles)[10]->destination.y + 7*SIZE_TILE};
            etapes[5] = (Pos_t){(*salles)[10]->destination.x + 10*SIZE_TILE,(*salles)[10]->destination.y + 7*SIZE_TILE};
            etapes[6] = (Pos_t){(*salles)[10]->destination.x + 11*SIZE_TILE,(*salles)[10]->destination.y + 7*SIZE_TILE};
            etapes[7] = (Pos_t){(*salles)[10]->destination.x + 11*SIZE_TILE,(*salles)[10]->destination.y + 8*SIZE_TILE};

		etapeCourante = 0;
		entites[24] = EntiteCreate(renderer, SLIME_R, etapes, etapeCourante, nbEtapes);

        //ENTITE 25
		nbEtapes = 8;
		etapes = (Pos_t*)malloc(nbEtapes*sizeof(Pos_t));
            etapes[0] = (Pos_t){(*salles)[10]->destination.x + 9*SIZE_TILE,(*salles)[10]->destination.y + 9*SIZE_TILE};
            etapes[1] = (Pos_t){(*salles)[10]->destination.x + 9*SIZE_TILE,(*salles)[10]->destination.y + 8*SIZE_TILE};
            etapes[2] = (Pos_t){(*salles)[10]->destination.x + 9*SIZE_TILE,(*salles)[10]->destination.y + 7*SIZE_TILE};
            etapes[3] = (Pos_t){(*salles)[10]->destination.x + 10*SIZE_TILE,(*salles)[10]->destination.y + 7*SIZE_TILE};
            etapes[4] = (Pos_t){(*salles)[10]->destination.x + 11*SIZE_TILE,(*salles)[10]->destination.y + 7*SIZE_TILE};
            etapes[5] = (Pos_t){(*salles)[10]->destination.x + 11*SIZE_TILE,(*salles)[10]->destination.y + 8*SIZE_TILE};
            etapes[6] = (Pos_t){(*salles)[10]->destination.x + 11*SIZE_TILE,(*salles)[10]->destination.y + 9*SIZE_TILE};
            etapes[7] = (Pos_t){(*salles)[10]->destination.x + 10*SIZE_TILE,(*salles)[10]->destination.y + 9*SIZE_TILE};

		etapeCourante = 0;
		entites[25] = EntiteCreate(renderer, SLIME_R, etapes, etapeCourante, nbEtapes);

        //ENTITE 26
		nbEtapes = 8;
		etapes = (Pos_t*)malloc(nbEtapes*sizeof(Pos_t));
            etapes[0] = (Pos_t){(*salles)[10]->destination.x + 9*SIZE_TILE,(*salles)[10]->destination.y + 8*SIZE_TILE};
            etapes[1] = (Pos_t){(*salles)[10]->destination.x + 9*SIZE_TILE,(*salles)[10]->destination.y + 7*SIZE_TILE};
            etapes[2] = (Pos_t){(*salles)[10]->destination.x + 10*SIZE_TILE,(*salles)[10]->destination.y + 7*SIZE_TILE};
            etapes[3] = (Pos_t){(*salles)[10]->destination.x + 11*SIZE_TILE,(*salles)[10]->destination.y + 7*SIZE_TILE};
            etapes[4] = (Pos_t){(*salles)[10]->destination.x + 11*SIZE_TILE,(*salles)[10]->destination.y + 8*SIZE_TILE};
            etapes[5] = (Pos_t){(*salles)[10]->destination.x + 11*SIZE_TILE,(*salles)[10]->destination.y + 9*SIZE_TILE};
            etapes[6] = (Pos_t){(*salles)[10]->destination.x + 10*SIZE_TILE,(*salles)[10]->destination.y + 9*SIZE_TILE};
            etapes[7] = (Pos_t){(*salles)[10]->destination.x + 9*SIZE_TILE,(*salles)[10]->destination.y + 9*SIZE_TILE};

		etapeCourante = 0;
		entites[26] = EntiteCreate(renderer, SLIME_R, etapes, etapeCourante, nbEtapes);

        //ENTITE 27
		nbEtapes = 1;
		etapes = (Pos_t*)malloc(nbEtapes*sizeof(Pos_t));
            etapes[0] = (Pos_t){(*salles)[10]->destination.x + 10*SIZE_TILE,(*salles)[10]->destination.y + 8*SIZE_TILE};

		etapeCourante = 0;
		entites[27] = EntiteCreate(renderer, SLIME_V, etapes, etapeCourante, nbEtapes);

        //ENTITE 28
		nbEtapes = 8;
		etapes = (Pos_t*)malloc(nbEtapes*sizeof(Pos_t));
            etapes[0] = (Pos_t){(*salles)[10]->destination.x + 18*SIZE_TILE,(*salles)[10]->destination.y + 9*SIZE_TILE};
            etapes[1] = (Pos_t){(*salles)[10]->destination.x + 19*SIZE_TILE,(*salles)[10]->destination.y + 9*SIZE_TILE};
            etapes[2] = (Pos_t){(*salles)[10]->destination.x + 19*SIZE_TILE,(*salles)[10]->destination.y + 10*SIZE_TILE};
            etapes[3] = (Pos_t){(*salles)[10]->destination.x + 19*SIZE_TILE,(*salles)[10]->destination.y + 11*SIZE_TILE};
            etapes[4] = (Pos_t){(*salles)[10]->destination.x + 18*SIZE_TILE,(*salles)[10]->destination.y + 11*SIZE_TILE};
            etapes[5] = (Pos_t){(*salles)[10]->destination.x + 17*SIZE_TILE,(*salles)[10]->destination.y + 11*SIZE_TILE};
            etapes[6] = (Pos_t){(*salles)[10]->destination.x + 17*SIZE_TILE,(*salles)[10]->destination.y + 10*SIZE_TILE};
            etapes[7] = (Pos_t){(*salles)[10]->destination.x + 17*SIZE_TILE,(*salles)[10]->destination.y + 9*SIZE_TILE};

		etapeCourante = 0;
		entites[28] = EntiteCreate(renderer, SLIME_R, etapes, etapeCourante, nbEtapes);

        //ENTITE 29
		nbEtapes = 8;
		etapes = (Pos_t*)malloc(nbEtapes*sizeof(Pos_t));
            etapes[0] = (Pos_t){(*salles)[10]->destination.x + 18*SIZE_TILE,(*salles)[10]->destination.y + 11*SIZE_TILE};
            etapes[1] = (Pos_t){(*salles)[10]->destination.x + 17*SIZE_TILE,(*salles)[10]->destination.y + 11*SIZE_TILE};
            etapes[2] = (Pos_t){(*salles)[10]->destination.x + 17*SIZE_TILE,(*salles)[10]->destination.y + 10*SIZE_TILE};
            etapes[3] = (Pos_t){(*salles)[10]->destination.x + 17*SIZE_TILE,(*salles)[10]->destination.y + 9*SIZE_TILE};
            etapes[4] = (Pos_t){(*salles)[10]->destination.x + 18*SIZE_TILE,(*salles)[10]->destination.y + 9*SIZE_TILE};
            etapes[5] = (Pos_t){(*salles)[10]->destination.x + 19*SIZE_TILE,(*salles)[10]->destination.y + 9*SIZE_TILE};
            etapes[6] = (Pos_t){(*salles)[10]->destination.x + 19*SIZE_TILE,(*salles)[10]->destination.y + 10*SIZE_TILE};
            etapes[7] = (Pos_t){(*salles)[10]->destination.x + 19*SIZE_TILE,(*salles)[10]->destination.y + 11*SIZE_TILE};

		etapeCourante = 0;
		entites[29] = EntiteCreate(renderer, SLIME_R, etapes, etapeCourante, nbEtapes);

        //ENTITE 30
		nbEtapes = 1;
		etapes = (Pos_t*)malloc(nbEtapes*sizeof(Pos_t));
            etapes[0] = (Pos_t){(*salles)[10]->destination.x + 18*SIZE_TILE,(*salles)[10]->destination.y + 10*SIZE_TILE};

		etapeCourante = 0;
		entites[30] = EntiteCreate(renderer, SLIME_R, etapes, etapeCourante, nbEtapes);

        //ENTITE 31
		nbEtapes = 1;
		etapes = (Pos_t*)malloc(nbEtapes*sizeof(Pos_t));
            etapes[0] = (Pos_t){(*salles)[10]->destination.x + 16*SIZE_TILE,(*salles)[10]->destination.y + 8*SIZE_TILE};

		etapeCourante = 0;
		entites[31] = EntiteCreate(renderer, SLIME_R, etapes, etapeCourante, nbEtapes);

        //ENTITE 32
		nbEtapes = 1;
		etapes = (Pos_t*)malloc(nbEtapes*sizeof(Pos_t));
            etapes[0] = (Pos_t){(*salles)[10]->destination.x + 16*SIZE_TILE,(*salles)[10]->destination.y + 9*SIZE_TILE};

		etapeCourante = 0;
		entites[32] = EntiteCreate(renderer, SLIME_R, etapes, etapeCourante, nbEtapes);

        //ENTITE 33
		nbEtapes = 1;
		etapes = (Pos_t*)malloc(nbEtapes*sizeof(Pos_t));
            etapes[0] = (Pos_t){(*salles)[10]->destination.x + 16*SIZE_TILE,(*salles)[10]->destination.y + 10*SIZE_TILE};

		etapeCourante = 0;
		entites[33] = EntiteCreate(renderer, SLIME_R, etapes, etapeCourante, nbEtapes);

        //ENTITE 34
		nbEtapes = 1;
		etapes = (Pos_t*)malloc(nbEtapes*sizeof(Pos_t));
            etapes[0] = (Pos_t){(*salles)[10]->destination.x + 16*SIZE_TILE,(*salles)[10]->destination.y + 11*SIZE_TILE};

		etapeCourante = 0;
		entites[34] = EntiteCreate(renderer, SLIME_R, etapes, etapeCourante, nbEtapes);

        //ENTITE 35
		nbEtapes = 1;
		etapes = (Pos_t*)malloc(nbEtapes*sizeof(Pos_t));
            etapes[0] = (Pos_t){(*salles)[10]->destination.x + 16*SIZE_TILE,(*salles)[10]->destination.y + 12*SIZE_TILE};

		etapeCourante = 0;
		entites[35] = EntiteCreate(renderer, SLIME_R, etapes, etapeCourante, nbEtapes);

        //ENTITE 36
		nbEtapes = 1;
		etapes = (Pos_t*)malloc(nbEtapes*sizeof(Pos_t));
            etapes[0] = (Pos_t){(*salles)[10]->destination.x + 16*SIZE_TILE,(*salles)[10]->destination.y + 13*SIZE_TILE};

		etapeCourante = 0;
		entites[36] = EntiteCreate(renderer, SLIME_R, etapes, etapeCourante, nbEtapes);

        //ENTITE 37
		nbEtapes = 1;
		etapes = (Pos_t*)malloc(nbEtapes*sizeof(Pos_t));
            etapes[0] = (Pos_t){(*salles)[10]->destination.x + 16*SIZE_TILE,(*salles)[10]->destination.y + 14*SIZE_TILE};

		etapeCourante = 0;
		entites[37] = EntiteCreate(renderer, SLIME_R, etapes, etapeCourante, nbEtapes);

        //ENTITE 38
		nbEtapes = 1;
		etapes = (Pos_t*)malloc(nbEtapes*sizeof(Pos_t));
            etapes[0] = (Pos_t){(*salles)[10]->destination.x + 16*SIZE_TILE,(*salles)[10]->destination.y + 15*SIZE_TILE};

		etapeCourante = 0;
		entites[38] = EntiteCreate(renderer, SLIME_R, etapes, etapeCourante, nbEtapes);

        //ENTITE 39
		nbEtapes = 1;
		etapes = (Pos_t*)malloc(nbEtapes*sizeof(Pos_t));
            etapes[0] = (Pos_t){(*salles)[10]->destination.x + 18*SIZE_TILE,(*salles)[10]->destination.y + 15*SIZE_TILE};

		etapeCourante = 0;
		entites[39] = EntiteCreate(renderer, SLIME_V, etapes, etapeCourante, nbEtapes);


	(*salles)[10]->entites = entites;
	(*salles)[10]->nbObjectifs = 9;
	(*salles)[10]->nbObjectifsVivants = 9;	
	(*salles)[10]->nbEntites = nbEntites;

}

void SalleDestroyAll(Salle_t * salles[NB_ROOM]){
	for (int i =0; i<NB_ROOM; i++){
		SalleDestroy(salles[i]);
	}
	free(salles);
}
