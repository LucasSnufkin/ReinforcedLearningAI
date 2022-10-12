#ifndef MANAGER_H
#define MANAGER_H

#include <SDL2/SDL_ttf.h>
#include "config.h"
#include "entite.h"
#include "salle.h"
#include "joueur.h"

typedef enum {
    BOUTON_JOUER,
    BOUTON_ENTRAINER,
    BOUTON_VOIR,
    BOUTON_AUCUN
} Bouton_t;

int ManagerProchaineSalle(int typeSalle);

SDL_bool ManagerDeplacementJoueur(Joueur_t * joueur, Salle_t * salle, Direction_t direction, int * salleCourante, int * recompense);

void ManagerDeplacementEnnemi(Entite_t * ennemi);

void ManagerKillEnemies(Joueur_t * joueur, Salle_t * salle, int * recompense);

void ManagerAffichageVictoire(SDL_Renderer * renderer);

void ManagerDeplacementEntites(Entite_t ** entite, int nbEntites);

void ManagerDisplayMenu(SDL_Renderer * renderer, SDL_bool voir_entrainement, SDL_Texture * textureFond, SDL_Texture * textureTitre, SDL_Texture * textureJouer, SDL_Texture * textureEntrainer, SDL_Texture * textureVoir, Bouton_t * hoveredButton);

void ManagerMenu(SDL_Renderer * renderer, Page_t * page, SDL_bool * voir_entrainement);

Bouton_t ManagerDetecterBouton(Sint32 x, Sint32 y);

void ManagerGestionInputs(SDL_bool *cont, Direction_t *direction, Bouton_t * bouton, Bouton_t * hoveredButton);

void ManagerResetSalle(Joueur_t * joueur, Salle_t * salle);

void ManagerJouer(SDL_Renderer * renderer, Salle_t **salles);

void ManagerEntrainerIA(SDL_Renderer * renderer, Salle_t *salle, SDL_bool voir_entrainement, int nbIterationMax, int nbRunMax, int idSalle, int sdlDelay, int fakeRun);

float ManagerNewEps(int nbRun, int nbRunMax);

void ManagerChargerParamsEntrainement(int *nbIterationMax, int *nbRunMax, int *salleEntrainement, int *sdlDelay, int *fakeRun);

void ManagerAdditionQtable(float ** qtableAdditionnee, float ** qtableA ,float ** qtableB);

#endif //MANAGER_H
