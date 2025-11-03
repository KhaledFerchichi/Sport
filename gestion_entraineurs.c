#include "gestion_entraineurs.h"

Entraineur entraineurs[MAX_ENTRAINEURS];
int nb_entraineurs = 0;

void ajouter_entraineur(Entraineur *e) {
    if (nb_entraineurs < MAX_ENTRAINEURS) {
        e->id = nb_entraineurs + 1;
        entraineurs[nb_entraineurs] = *e;
        nb_entraineurs++;
        sauvegarder_entraineurs();
    }
}

void modifier_entraineur(int id, Entraineur *e) {
    Entraineur *found = rechercher_entraineur(id);
    if (found != NULL) {
        *found = *e;
        found->id = id;
        sauvegarder_entraineurs();
    }
}

Entraineur* rechercher_entraineur(int id) {
    int i;
    for (i = 0; i < nb_entraineurs; i++) {
        if (entraineurs[i].id == id) {
            return &entraineurs[i];
        }
    }
    return NULL;
}

void supprimer_entraineur(int id) {
    int i, j;
    for (i = 0; i < nb_entraineurs; i++) {
        if (entraineurs[i].id == id) {
            for (j = i; j < nb_entraineurs - 1; j++) {
                entraineurs[j] = entraineurs[j + 1];
            }
            nb_entraineurs--;
            sauvegarder_entraineurs();
            return;
        }
    }
}

void formater_date(int jour, int mois, int annee, char *buffer) {
    sprintf(buffer, "%02d/%02d/%04d", jour, mois, annee);
}

void rafraichir_liste_entraineurs(void) {
    charger_entraineurs();
    // Appelé dans callbacks pour remplir treeview
}

void sauvegarder_entraineurs(void) {
    FILE *f = fopen(FICHIER_ENTRAINEURS, "w");
    if (f != NULL) {
        int i;
        for (i = 0; i < nb_entraineurs; i++) {
            Entraineur *e = &entraineurs[i];
            fprintf(f, "%d|%s|%s|%s|%s|%s|%s|%s|%d|%d|%d|%s|%s|%d|%d|%d\n",
                    e->id, e->nom, e->prenom, e->sexe, e->num_tel, e->specialite, e->email, e->mot_de_passe,
                    e->jour_naiss, e->mois_naiss, e->annee_naiss, e->centre_sportif, e->jour_dispo,
                    e->heure_debut, e->heure_fin, e->prive);
        }
        fclose(f);
    }
}

void charger_entraineurs(void) {
    FILE *f = fopen(FICHIER_ENTRAINEURS, "r");
    if (f == NULL) return;
    nb_entraineurs = 0;
    char line[500];
    while (fgets(line, sizeof(line), f)) {
        Entraineur e;
        sscanf(line, "%d|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%d|%d|%d|%[^|]|%[^|]|%d|%d|%d",
               &e.id, e.nom, e.prenom, e.sexe, e.num_tel, e.specialite, e.email, e.mot_de_passe,
               &e.jour_naiss, &e.mois_naiss, &e.annee_naiss, e.centre_sportif, e.jour_dispo,
               &e.heure_debut, &e.heure_fin, &e.prive);
        entraineurs[nb_entraineurs++] = e;
    }
    fclose(f);
}
