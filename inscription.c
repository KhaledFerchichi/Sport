// inscription.c
#include "inscription.h"

InscriptionCours inscriptions[MAX_INSCRIPTIONS];
int nb_inscriptions = 0;

void ajouter_inscription(InscriptionCours *ins) {
    if (nb_inscriptions < MAX_INSCRIPTIONS) {
        inscriptions[nb_inscriptions] = *ins;
        nb_inscriptions++;
        sauvegarder_inscriptions();
    }
}

void charger_inscriptions(void) {
    FILE *f = fopen(FICHIER_INSCRIPTIONS, "r");
    if (f == NULL) return;
    char line[300];
    nb_inscriptions = 0;
    while (fgets(line, sizeof(line), f)) {
        InscriptionCours ins;
        sscanf(line, "%d|%[^|]|%[^|]|%[^|]|%d|%d",
               &ins.id_entraineur, ins.cours, ins.equipements, ins.jour,
               &ins.heure_debut, &ins.heure_fin);
        inscriptions[nb_inscriptions++] = ins;
    }
    fclose(f);
}

void sauvegarder_inscriptions(void) {
    FILE *f = fopen(FICHIER_INSCRIPTIONS, "w");
    if (f == NULL) return;
    for (int i = 0; i < nb_inscriptions; i++) {
        InscriptionCours *ins = &inscriptions[i];
        fprintf(f, "%d|%s|%s|%s|%d|%d\n",
                ins->id_entraineur, ins->cours, ins->equipements, ins->jour,
                ins->heure_debut, ins->heure_fin);
    }
    fclose(f);
}

void supprimer_inscriptions_entraineur(int id_entraineur) {
    int write_idx = 0;
    for (int read_idx = 0; read_idx < nb_inscriptions; read_idx++) {
        if (inscriptions[read_idx].id_entraineur != id_entraineur) {
            if (write_idx != read_idx) {
                inscriptions[write_idx] = inscriptions[read_idx];
            }
            write_idx++;
        }
    }
    nb_inscriptions = write_idx;
    sauvegarder_inscriptions();
}
