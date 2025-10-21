#ifndef CENTRE_H
#define CENTRE_H
#define MAX_NOM 100
#define MAX_ADRESSE 200
#define MAX_VILLE 50
#define MAX_TELEPHONE 20
#define MAX_EMAIL 100

typedef struct {
  int id_centre;
  char nom[MAX_NOM];
  char adresse[MAX_ADRESSE];
  char ville[MAX_VILLE];
  int capacite;
  char telephone[MAX_TELEPHONE];
  char email[MAX_EMAIL];
  int actif;
}Centre;

void ajouter_centre(Centre *nouveau_centre);
void modifier_centre(int id_centre,Centre *centre_modifie);
void supprimer_centre(int id_centre);
Centre* rechercher_centre_par_id(int id_centre);
centre* rechercher_centre_par_nom(const char *nom);
void afficher_tous_centres();
int obtenir_nombre_centres();

#endif
