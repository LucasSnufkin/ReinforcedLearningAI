#include "IA.h"


float ** IAChargerUneQTable(char * nomFichier) {
    FILE * fichier = NULL;
    float ** qTable = NULL;
    char str[500];

    fichier = fopen(nomFichier, "r");

    if(fichier == NULL) {
        fprintf(stderr, "Impossible d'ouvrir le fichier %s en r\n", nomFichier);
    }
    else {
        qTable = (float**)malloc(NB_ETATS*sizeof(float**));

        for(int i = 0; i < NB_ETATS; i++) {
            qTable[i] = (float*)malloc(5*sizeof(float));
            fgets(str, 500, fichier);
            sscanf(str, "%f|%f|%f|%f|%f", &qTable[i][0], &qTable[i][1], &qTable[i][2], &qTable[i][3], &qTable[i][4]);
        }

        fclose(fichier);
    }

    return qTable;
}


float *** IAChargerToutesLesQTables() {
    char nomFichier[30];
    float *** qTables;

    qTables = (float***)malloc(NB_ROOM*sizeof(float***));

    for(int i = 0; i < NB_ROOM; i++) {
        sprintf(nomFichier, "QTables/QTable_Salle_%d", i);
        qTables[i] = IAChargerUneQTable(nomFichier);
    }

    return qTables;
}


void IASauvegarderUneQTable(float ** qTable, char * nomFichier) {
    FILE * fichier = NULL;

    fichier = fopen(nomFichier, "w+");

    if(fichier == NULL) {
        fprintf(stderr, "Impossible d'ouvrir le fichier %s en w+\n", nomFichier);
    }
    else {
        for(int i = 0; i < NB_ETATS; i++) {
            fprintf(fichier, "%f|%f|%f|%f|%f\n", qTable[i][0], qTable[i][1], qTable[i][2], qTable[i][3], qTable[i][4]);
        }
        fclose(fichier);
    }
}


void IASauvegarderToutesLesQTables(float *** qTables) {
    char nomFichier[30];

    for(int i = 0; i < NB_ROOM; i++) {
        sprintf(nomFichier, "QTables/QTable_Salle_%d", i);
        IASauvegarderUneQTable(qTables[i], nomFichier);
    }
}


void IALibererUneQTable(float ** qTable) {
    for(int i = 0; i < NB_ETATS; i++) {
        free(qTable[i]);
    }
    free(qTable);
}


void IALibererToutesLesQTables(float *** qTables) {
    for(int i = 0; i < NB_ROOM; i++) {
        IALibererUneQTable(qTables[i]);
    }
    free(qTables);
}

int IARun(SDL_Renderer * renderer, float ** qtable, Salle_t * salle, Iteration_t* run, float epsilon, SDL_bool voir_entrainement, Joueur_t * joueur, int nbIterationMax, int sdlDelay, int fakeRun){
    SDL_bool run_on = SDL_TRUE;
    int nbIter = 1;
    
    run[0].etat = IAProchainEtat(salle, joueur, HAUT, &run_on, &(run[0].recompense));
    run[0].action = IAAction(epsilon, SelectLigneQtable(qtable, run[0].etat));
    while (nbIter<nbIterationMax-1 && run_on){
        if (voir_entrainement){
			SDL_RenderClear(renderer);
			SalleDisplay(renderer, salle);
			JoueurDisplay(renderer, joueur);

			SDL_RenderPresent(renderer);
			SDL_Delay(sdlDelay);
		}
        ManagerDeplacementEntites(salle->entites, salle->nbEntites);
        run[nbIter].etat = IAProchainEtat(salle,joueur, run[nbIter-1].action, &run_on, &(run[nbIter].recompense));
        run[nbIter].recompense-=1;
        run[nbIter].action = IAAction(epsilon, SelectLigneQtable(qtable, run[nbIter].etat));
        if (fakeRun) fprintf(stderr, "Iteration %d :\nPerceptions : (CadranPPA : %d | distancePPA : %d | CadranPPE : %d | distancePPE : %d | actionPrec : %d)\nAction : %d\nRecompense : %d\nEpsilon : %f\n\n",
                nbIter,
                run[nbIter].etat.cadranPPA, run[nbIter].etat.distancePPA, run[nbIter].etat.cadranPPE, run[nbIter].etat.distancePPE, run[nbIter].etat.actionPrec,
                (int)run[nbIter].action,
                (int)run[nbIter].recompense,
                epsilon);
        
        nbIter++;
    }

    return nbIter;
}

Perceptions_t IAProchainEtat(Salle_t * salle, Joueur_t * joueur, Direction_t action, SDL_bool * run_on, int * recompense){
    int distanceCourant = RAND_MAX;
    int distanceMinV= distanceCourant;
    int distanceMinR= distanceCourant;
    *run_on = !ManagerDeplacementJoueur(joueur, salle, action, NULL, recompense);
    Perceptions_t Etat;
    Etat.distancePPA = LOI;
    Etat.distancePPE = LOI;
    Etat.cadranPPA = NORD;
    Etat.cadranPPE = SUD;
    
    if(salle->nbObjectifsVivants > 0){
        for(int i=0; i<salle->nbEntites; i++){
            distanceCourant = distanceEntite(joueur,(salle->entites)[i]);
            if(((salle->entites)[i]->type == SLIME_V ) && ((salle->entites)[i]->etat == VIVANT ) && ( distanceCourant < distanceMinV )){
                distanceMinV= distanceCourant;
                Etat.distancePPA = (distanceCourant == 1)? ADJ : (distanceCourant== 2)? PRO : LOI;
                Etat.cadranPPA = CadranEntite(joueur,(salle->entites)[i]);
            }
            else if(((salle->entites)[i]->type == SLIME_R ) && (distanceCourant < distanceMinR)){
                distanceMinR= distanceCourant;
                Etat.distancePPE = (distanceCourant == 1)? ADJ : (distanceCourant== 2)? PRO : LOI;
                Etat.cadranPPE = CadranEntite(joueur,(salle->entites)[i]);
            }
        }
    }
    else{
        int distanceX = (joueur->destination.x - salle->spawn.x)/(SIZE_TILE);
        if(distanceX<0) distanceX= -distanceX;
        int distanceY = (joueur->destination.y - salle->destination.y)/(SIZE_TILE);
        if(distanceY<0) distanceY= -distanceY;
        distanceCourant= distanceX + distanceY;
        Etat.distancePPA = (distanceCourant == 1)? ADJ : (distanceCourant== 2)? PRO : LOI;
        Etat.cadranPPA = (joueur->destination.x<= salle->spawn.x)? NORD: OUEST;
    }

    Etat.actionPrec = action;

    return Etat;
}


Direction_t IAAction(float epsilon, float * qligne){
    float res = (float)rand()/(float)RAND_MAX;
    int idir = 0;
    if (res<epsilon){
        idir = rand() % 5;

    }
    else{
        for (int i=0;i<5;i++){
            if (qligne[i]>qligne[idir]){
                idir = i;
            }
        }
    }
    return (Direction_t)idir;
}

float * SelectLigneQtable(float ** qtable, Perceptions_t etat){
    int index = 0;
    index += etat.cadranPPA;
    index += etat.distancePPA * 4;
    index += etat.cadranPPE * 4 * 3;
    index += etat.distancePPE * 4 * 3 * 4;
    index += etat.actionPrec * 4 * 3 * 4 * 3;

    return qtable[index];
}


int distanceEntite(Joueur_t * joueur,Entite_t * entite){
    int distanceX = (joueur->destination.x - entite->destination.x)/(SIZE_TILE);
    if(distanceX<0) distanceX= -distanceX;
    int distanceY = (joueur->destination.y - entite->destination.y)/(SIZE_TILE);
    if(distanceY<0) distanceY= -distanceY;

    return distanceX+distanceY;
}

Cadran_t CadranEntite(Joueur_t * joueur,Entite_t * entite){
    int distanceX = (joueur->destination.x - entite->destination.x)/(SIZE_TILE);
    int distanceY = (joueur->destination.y - entite->destination.y)/(SIZE_TILE);
    Cadran_t cadran;
    if(distanceY>0){
        if(distanceX<0){
            cadran= OUEST;
        }
        else{
            cadran=NORD;
        }
    }
    else if(distanceY<0){
        if(distanceX>0){
            cadran=EST;
        }
        else{
            cadran=SUD;
        }
    }
    else{
        if (distanceX<0){
            cadran= OUEST;
        }
        else{
            cadran= EST;
        }
    }

    return cadran;
}

void IARenforcement(Iteration_t * run, int TailleRun, float ** qtableA, float ** qtableB){
    float * qligne;
    float * qligneSuiv;
    float ** qtableEchange = qtableA;
    for(int i=TailleRun-2; i>=0; i--){
        
        if(rand() % 2 == 0){
            qtableEchange = qtableA;
            qtableA = qtableB;
            qtableB = qtableEchange;
        }

        qligne = SelectLigneQtable(qtableA, run[i].etat);        
        qligneSuiv = SelectLigneQtable(qtableB, run[i+1].etat);

        qligne[run[i].action] += (float)KHI * ((float)run[i+1].recompense + (float)GAMMA * MaxQligne(qligneSuiv) - qligne[run[i].action]);
    }

}


float MaxQligne(float * qligne){
    float max=0;
    for(int i=0; i<5; i++){
        max =(qligne[i]>max)? qligne[i] : max;
    }
    return max;
}
