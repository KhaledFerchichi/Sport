#include <stdio.h>
#include <string.h>
#include "centre.h"

int main() {
    printf("=== TEST COMPLET DU MODULE CENTRES ===\n\n");
    
    // TEST 1: Ajouter des centres
    printf("1. AJOUT DE CENTRES...\n");
    Centre c1 = {1, "Sport Plus", "123 Rue des Sports", "Paris", 150, "01 45 67 89 10", "contact@sportplus.fr", 1};
    Centre c2 = {2, "Fit City", "456 Avenue Fitness", "Lyon", 200, "04 78 90 12 34", "info@fitcity.fr", 1};
    Centre c3 = {3, "Gym Center", "789 Boulevard Sport", "Marseille", 100, "04 91 23 45 67", "contact@gymcenter.fr", 0};
    
    ajouter_centre(&c1);
    ajouter_centre(&c2);
    ajouter_centre(&c3);
    printf("✅ 3 centres ajoutés\n");
    
    // TEST 2: Recherche par ID
    printf("\n2. RECHERCHE PAR ID...\n");
    Centre *resultat_id = rechercher_centre_par_id(2);
    if (resultat_id != NULL) {
        printf("✅ Centre ID 2 trouvé: %s\n", resultat_id->nom);
    } else {
        printf("❌ Centre ID 2 non trouvé\n");
    }
    
    // TEST 3: Recherche par nom
    printf("\n3. RECHERCHE PAR NOM...\n");
    Centre *resultat_nom = rechercher_centre_par_nom("Sport Plus");
    if (resultat_nom != NULL) {
        printf("✅ 'Sport Plus' trouvé: ID %d\n", resultat_nom->id_centre);
    } else {
        printf("❌ 'Sport Plus' non trouvé\n");
    }
    
    // TEST 4: Nombre de centres
    printf("\n4. NOMBRE DE CENTRES...\n");
    int nombre = obtenir_nombre_centres();
    printf("✅ Nombre total de centres: %d\n", nombre);
    
    // TEST 5: Modification
    printf("\n5. MODIFICATION D'UN CENTRE...\n");
    Centre modif = {2, "Fit City MODIFIE", "999 Nouvelle Adresse", "Lyon", 250, "04 00 00 00 00", "nouveau@fitcity.fr", 1};
    modifier_centre(2, &modif);
    printf("✅ Centre ID 2 modifié\n");
    
    // TEST 6: Suppression
    printf("\n6. SUPPRESSION D'UN CENTRE...\n");
    supprimer_centre(3);
    printf("✅ Centre ID 3 supprimé\n");
    
    // TEST 7: Nouveau nombre après suppression
    printf("\n7. VERIFICATION APRES SUPPRESSION...\n");
    nombre = obtenir_nombre_centres();
    printf("✅ Nouveau nombre de centres: %d\n", nombre);
    
    printf("\n=== TEST TERMINÉ ===\n");
    printf("📁 Vérifiez le fichier 'centres.txt' pour voir les données\n");
    
    return 0;
}

