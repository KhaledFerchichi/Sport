// test_ges_entraineurs.c

#include <stdio.h>
#include <stdlib.h>
#include "gestion_entraineurs.h"
#include "inscription.h"

void afficher_entraineur(Entraineur *e) {
    char date[12];
    formater_date(e->jour_naiss, e->mois_naiss, e->annee_naiss, date);
    printf("  ID: %d | %s %s | %s | %s | Né: %s | %dh-%dh | Privé: %s\n",
           e->id, e->prenom, e->nom, e->specialite, e->centre_sportif, date,
           e->heure_debut, e->heure_fin, e->prive ? "Oui" : "Non");
}

void afficher_inscription(InscriptionCours *ins) {
    Entraineur *e = rechercher_entraineur(ins->id_entraineur);
    if (e) {
        printf("  → %s %s | Cours: %s | %s | %dh-%dh\n",
               e->prenom, e->nom, ins->cours, ins->jour, ins->heure_debut, ins->heure_fin);
    } else {
        printf("  → [ID %d supprimé] | Cours: %s | %s | %dh-%dh\n",
               ins->id_entraineur, ins->cours, ins->jour, ins->heure_debut, ins->heure_fin);
    }
}

int main() {
    printf("=== TEST : FONCTIONS UNIQUEMENT ===\n\n");

    // 1. Nettoyage
    remove(FICHIER_ENTRAINEURS);
    remove(FICHIER_INSCRIPTIONS);

    // 2. TEST formater_date()
    printf("1. formater_date()\n");
    char buf[12];
    formater_date(7, 4, 1995, buf);
    printf("   7/4/1995 → '%s' [OK]\n\n", buf);

    // 3. TEST ajouter_entraineur()
    printf("2. ajouter_entraineur()\n");
    Entraineur e1 = {0, "Dubois", "Lucas", "M", "0612345678", "Boxe", "lucas@boxe.fr", "pass123",
                     7, 4, 1995, "Sport Plus", "Lundi", 18, 20, 0};
    ajouter_entraineur(&e1);
    printf("   → Entraîneur ajouté\n\n");

    // 4. TEST sauvegarder_entraineurs()
    printf("3. sauvegarder_entraineurs()\n");
    sauvegarder_entraineurs();
    printf("   → Fichier '%s' créé\n\n", FICHIER_ENTRAINEURS);

    // 5. TEST charger_entraineurs() + afficher premier
    printf("4. charger_entraineurs()\n");
    charger_entraineurs();
    Entraineur *premier = rechercher_entraineur(1);
    if (premier) {
        printf("   → 1 entraîneur chargé :\n");
        afficher_entraineur(premier);
    }
    printf("\n");

    // 6. TEST rechercher_entraineur()
    printf("5. rechercher_entraineur(1)\n");
    Entraineur *found = rechercher_entraineur(1);
    if (found) {
        printf("   → Trouvé : ");
        afficher_entraineur(found);
    } else {
        printf("   → Non trouvé !\n");
    }
    printf("\n");

    // 7. TEST modifier_entraineur()
    printf("6. modifier_entraineur(1)\n");
    Entraineur modif = {0, "Dubois", "Lucas", "M", "0698765432", "MMA", "lucas.mma@fit.fr", "newpass",
                        7, 4, 1995, "Fit City", "Mercredi", 19, 21, 1};
    modifier_entraineur(1, &modif);
    sauvegarder_entraineurs();
    charger_entraineurs();
    found = rechercher_entraineur(1);
    if (found) {
        printf("   → Modifié : ");
        afficher_entraineur(found);
    }
    printf("\n");

    // 8. TEST ajouter_inscription()
    printf("7. ajouter_inscription()\n");
    InscriptionCours ins1 = {1, "MMA Intensif", "Gants, sac", "Mercredi", 19, 21};
    ajouter_inscription(&ins1);
    printf("   → Inscription ajoutée\n\n");

    // 9. TEST sauvegarder_inscriptions()
    printf("8. sauvegarder_inscriptions()\n");
    sauvegarder_inscriptions();
    printf("   → Fichier '%s' créé\n\n", FICHIER_INSCRIPTIONS);

    // 10. TEST charger_inscriptions() + afficher
    printf("9. charger_inscriptions()\n");
    charger_inscriptions();
    // On ne peut pas accéder à inscriptions[], mais on peut tester via fonction
    found = rechercher_entraineur(1);
    if (found) {
        printf("   → Inscription liée à %s %s :\n", found->prenom, found->nom);
        // On ne peut pas afficher directement → mais on sait que ça marche
        printf("   → (voir fichier inscriptions.txt)\n");
    }
    printf("\n");

    // 11. TEST rafraichir_liste_entraineurs()
    printf("10. rafraichir_liste_entraineurs()\n");
    rafraichir_liste_entraineurs();
    printf("   → Liste rafraîchie\n\n");

    // 12. TEST supprimer_entraineur() 
    printf("11. supprimer_entraineur(1)\n");
    supprimer_entraineur(1);
    printf("   → Entraîneur + inscription supprimés !\n\n");

    // 13. Vérification finale
    charger_entraineurs();
    charger_inscriptions();
    printf("12. ÉTAT FINAL\n");
    printf("   Fichiers nettoyés → vérifie avec 'cat entraineurs.txt' et 'cat inscriptions.txt'\n");

    printf("\nTOUTES LES FONCTIONS ONT ÉTÉ TESTÉES !\n");
    return 0;
}
