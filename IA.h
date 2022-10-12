#ifndef IA_H
#define IA_H

#include <stdio.h>
#include <stdlib.h>
#include "config.h"
#include "salle.h"
#include "joueur.h"
#include "manager.h"

typedef enum {
    NORD,
    SUD,
    OUEST,
    EST
} Cadran_t;

typedef enum {
    ADJ,
    PRO,
    LOI
} Distance_t;

typedef struct {
    Cadran_t cadranPPA;
    Distance_t distancePPA;
    Cadran_t cadranPPE;
    Distance_t distancePPE;
    Direction_t actionPrec;
} Perceptions_t;

typedef struct {
    Perceptions_t etat;
    Direction_t action;
    int recompense;
} Iteration_t;



float ** IAChargerUneQTable(char * nomFichier);

float *** IAChargerToutesLesQTables();

void IASauvegarderUneQTable(float ** qTable, char * nomFichier);

void IASauvegarderToutesLesQTables(float *** qTables);

void IALibererUneQTable(float ** qTable);

void IALibererToutesLesQTables(float *** qTables);

int IARun(SDL_Renderer * renderer, float **qtable, Salle_t * salle, Iteration_t * run, float espilon, SDL_bool voir_entrainement, Joueur_t * joueur, int nbIterationMax, int sdlDelay, int fakeRun);

Perceptions_t IAProchainEtat(Salle_t * salle, Joueur_t * joueur, Direction_t action, SDL_bool * run_on, int * recompense);

Direction_t IAAction(float epsilon, float * qligne);

float * SelectLigneQtable(float ** qtable, Perceptions_t etat);

int distanceEntite(Joueur_t * joueur, Entite_t * entite);

Cadran_t CadranEntite(Joueur_t * joueur, Entite_t * entite);

void IARenforcement(Iteration_t * run, int TailleRun, float ** qtableA , float ** qtableB);

float MaxQligne(float * qligne);




#endif //IA_H
