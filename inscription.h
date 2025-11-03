// inscription.h
#ifndef INSCRIPTION_H
#define INSCRIPTION_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INSCRIPTIONS 500
#define FICHIER_INSCRIPTIONS "inscriptions.txt"

typedef struct {
    int id_entraineur;
    char cours[50];
    char equipements[100];
    char jour[20];
    int heure_debut;
    int heure_fin;  // Pas de minutes dans ta Glade, donc simple
} InscriptionCours;

void ajouter_inscription(InscriptionCours *ins);
void charger_inscriptions(void);
void sauvegarder_inscriptions(void);
void supprimer_inscriptions_entraineur(int id_entraineur);

#endif
