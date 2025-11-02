#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "centre.h"

#define FICHIER_CENTRES "centres.txt"

// Fonction pour ajouter un centre
void ajouter_centre(Centre *nouveau_centre) {
    FILE *f = fopen(FICHIER_CENTRES, "a");
    if (f != NULL) {
        fprintf(f, "%d|%s|%s|%s|%d|%s|%s|%d\n",
                nouveau_centre->id_centre,
                nouveau_centre->nom,
                nouveau_centre->adresse,
                nouveau_centre->ville,
                nouveau_centre->capacite,
                nouveau_centre->telephone,
                nouveau_centre->email,
                nouveau_centre->actif);
        fclose(f);
    }
}

// Fonction pour rechercher un centre par ID
Centre* rechercher_centre_par_id(int id_centre) {
    static Centre resultat;
    FILE *f = fopen("centres.txt", "r");
    
    if (f != NULL) {
        char ligne[500];
        
        while (fgets(ligne, sizeof(ligne), f)) {
            sscanf(ligne, "%d|%[^|]|%[^|]|%[^|]|%d|%[^|]|%[^|]|%d",
                   &resultat.id_centre,
                   resultat.nom,
                   resultat.adresse,
                   resultat.ville,
                   &resultat.capacite,
                   resultat.telephone,
                   resultat.email,
                   &resultat.actif);
            
            if (resultat.id_centre == id_centre) {
                fclose(f);
                return &resultat;
            }
        }
        fclose(f);
    }
    return NULL;
}

// Fonction pour rechercher un centre par nom
Centre* rechercher_centre_par_nom(const char *nom) {
    static Centre resultat;
    FILE *f = fopen(FICHIER_CENTRES, "r");
    
    if (f != NULL) {
        char ligne[500];
        
        while (fgets(ligne, sizeof(ligne), f)) {
            sscanf(ligne, "%d|%[^|]|%[^|]|%[^|]|%d|%[^|]|%[^|]|%d",
                   &resultat.id_centre,
                   resultat.nom,
                   resultat.adresse,
                   resultat.ville,
                   &resultat.capacite,
                   resultat.telephone,
                   resultat.email,
                   &resultat.actif);
            
            if (strcmp(resultat.nom, nom) == 0) {
                fclose(f);
                return &resultat;
            }
        }
        fclose(f);
    }
    return NULL;
}

// Fonction pour obtenir le nombre total de centres
int obtenir_nombre_centres() {
    FILE *f = fopen(FICHIER_CENTRES, "r");
    int count = 0;
    
    if (f != NULL) {
        char ligne[500];
        while (fgets(ligne, sizeof(ligne), f)) {
            count++;
        }
        fclose(f);
    }
    return count;
}

// Fonction pour modifier un centre existant
void modifier_centre(int id_centre, Centre *centre_modifie) {
    FILE *f = fopen("centres.txt", "r");
    FILE *temp = fopen("temp.txt", "w");
    
    if (f != NULL && temp != NULL) {
        char ligne[500];
        int trouve = 0;
        
        while (fgets(ligne, sizeof(ligne), f)) {
            Centre centre_actuel;
            sscanf(ligne, "%d|%[^|]|%[^|]|%[^|]|%d|%[^|]|%[^|]|%d",
                   &centre_actuel.id_centre,
                   centre_actuel.nom,
                   centre_actuel.adresse,
                   centre_actuel.ville,
                   &centre_actuel.capacite,
                   centre_actuel.telephone,
                   centre_actuel.email,
                   &centre_actuel.actif);
            
            if (centre_actuel.id_centre == id_centre) {
                // Écrire le centre modifié
                fprintf(temp, "%d|%s|%s|%s|%d|%s|%s|%d\n",
                        centre_modifie->id_centre,
                        centre_modifie->nom,
                        centre_modifie->adresse,
                        centre_modifie->ville,
                        centre_modifie->capacite,
                        centre_modifie->telephone,
                        centre_modifie->email,
                        centre_modifie->actif);
                trouve = 1;
            } else {
                // Recopier les autres centres
                fputs(ligne, temp);
            }
        }
        
        fclose(f);
        fclose(temp);
        
        if (trouve) {
            remove("centres.txt");
            rename("temp.txt", "centres.txt");
        } else {
            remove("temp.txt");
        }
    }
}

// Fonction pour supprimer un centre
void supprimer_centre(int id_centre) {
    FILE *f = fopen("centres.txt", "r");
    FILE *temp = fopen("temp.txt", "w");
    
    if (f != NULL && temp != NULL) {
        char ligne[500];
        int trouve = 0;
        
        while (fgets(ligne, sizeof(ligne), f)) {
            Centre centre_actuel;
            sscanf(ligne, "%d|%[^|]|%[^|]|%[^|]|%d|%[^|]|%[^|]|%d",
                   &centre_actuel.id_centre,
                   centre_actuel.nom,
                   centre_actuel.adresse,
                   centre_actuel.ville,
                   &centre_actuel.capacite,
                   centre_actuel.telephone,
                   centre_actuel.email,
                   &centre_actuel.actif);
            
            if (centre_actuel.id_centre != id_centre) {
                // Recopier tous les centres SAUF celui à supprimer
                fputs(ligne, temp);
            } else {
                trouve = 1;
            }
        }
        
        fclose(f);
        fclose(temp);
        
        if (trouve) {
            remove("centres.txt");
            rename("temp.txt", "centres.txt");
        } else {
            remove("temp.txt");
        }
    }
}

// FONCTION AFFICHER TOUS LES CENTRES - CORRIGÉE
void afficher_tous_centres() {
    FILE *f = fopen(FICHIER_CENTRES, "r");
    
    if (f != NULL) {
        char ligne[500];
        Centre centre;
        int count = 0;
        
        printf("\n=== LISTE DE TOUS LES CENTRES ===\n");
        
        while (fgets(ligne, sizeof(ligne), f)) {
            if (sscanf(ligne, "%d|%[^|]|%[^|]|%[^|]|%d|%[^|]|%[^|]|%d",
                   &centre.id_centre,
                   centre.nom,
                   centre.adresse, 
                   centre.ville,
                   &centre.capacite,
                   centre.telephone,
                   centre.email,
                   &centre.actif) == 8) {
                
                printf("ID: %d | Nom: %s\n", centre.id_centre, centre.nom);
                printf("Adresse: %s, %s\n", centre.adresse, centre.ville);
                printf("Capacité: %d | Tel: %s\n", centre.capacite, centre.telephone);
                printf("Email: %s | Statut: %s\n", centre.email, centre.actif ? "Actif" : "Inactif");
                printf("-----------------------------------\n");
                
                count++;
            }
        }
        
        fclose(f);
        
        if (count == 0) {
            printf("Aucun centre trouvé.\n");
        } else {
            printf("Total: %d centre(s)\n", count);
        }
        
    } else {
        printf("Erreur: Impossible d'ouvrir le fichier centres.txt\n");
    }
}
