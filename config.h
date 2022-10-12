#ifndef CONFIG_H
#define CONFIG_H

//Scaling salle
#define ZOOM 3
#define SIZE_TILE 16*ZOOM
#define SCREEN_WIDTH SIZE_TILE*20
#define SCREEN_HEIGHT SIZE_TILE*17
#define PLAYER_SPEED SIZE_TILE

//Parametrage salle
#define NB_TYPE_POPULATION 2
#define NB_MAX_ENTITES 20
#define NB_ROOM 11 // MODIFIER AUSSI la table markov dans manager.c

//Parametrage IA
#define NB_ETATS 720 // MODIFIER AUSSI les fichiers qtables

//#define NB_ITERATIONS 200
//#define SALLE_ENTRAINEMENT 0
//#define NB_RUN 100

#define RECOMPENSE_SLIME 5
#define RECOMPENSE_FIN 20

#define KHI 0.05
#define GAMMA 0.991



typedef struct {
	int x;
	int y;
} Pos_t;

typedef enum {
	AUCUNE,
	HAUT,
	BAS,
	GAUCHE,
	DROITE
} Direction_t;

typedef enum{
    MENU,
    JOUER,
    ENTRAINER
} Page_t;

#endif // CONFIG_H
