#ifndef GESTION_ENTRAINEURS_H
#define GESTION_ENTRAINEURS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ENTRAINEURS 100
#define FICHIER_ENTRAINEURS "entraineurs.txt"

typedef struct {
    int id;
    char nom[100];
    char prenom[100];
    char sexe[10];
    char num_tel[20];
    char specialite[100];
    char email[100];
    char mot_de_passe[50];
    int jour_naiss;
    int mois_naiss;
    int annee_naiss;
    char centre_sportif[100];
    char jour_dispo[20];
    int heure_debut;
    int heure_fin;
    int prive;
} Entraineur;

void ajouter_entraineur(Entraineur *e);
void modifier_entraineur(int id, Entraineur *e);
Entraineur* rechercher_entraineur(int id);
void supprimer_entraineur(int id);
void rafraichir_liste_entraineurs(void);
void formater_date(int jour, int mois, int annee, char *buffer);

void charger_entraineurs(void);
void sauvegarder_entraineurs(void);

#endif
