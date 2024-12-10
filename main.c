#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "fonction.h"



int main() {
    FILE *fichier = fopen("dpt2022.csv", "r");

    if (fichier == NULL) {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier.\n");
        return 1;
    }

    int choix;
    int sousChoix;

    do {
        printf("Menu:\n");
        printf("0 - Quitter\n");
        printf("1 - Compter le nombre total de personnes\n");
        printf("2 - Compter le nombre de prenoms\n");
        printf("3 - Statistiques sur un prenom\n");

        printf("Entrez votre choix : ");

        if (scanf("%d", &choix) != 1) {
            fprintf(stderr, "Erreur de saisie. Veuillez entrer un nombre.\n");
            while (getchar() != '\n');
            continue;
        }
        switch (choix) {
            case 0:
                printf("Programme terminé.\n");
                break;
            case 1:
                compterPersonnes(fichier);
                break;
            case 2:
                printf("1 - Distinguer les sexes\n");
                printf("0 - Sans distinguer les sexes\n");
                printf("Entrez votre choix : ");
                scanf("%d", &sousChoix);

                switch (sousChoix) {
                    case 0:
                        nombrePrenomTotal(fichier);
                        break;
                    case 1:
                        nombrePrenomSexeDistinct(fichier);
                        break;
                    default:
                        printf("Choix non valide. Veuillez entrer 0 ou 1.\n");
                }
                break;
            case 3: {
                char prenomRecherche[longueurmax];
                printf("Entrez le prénom : ");
                scanf("%s", prenomRecherche);

                Statistiques stats = statistiquesPrenom(fichier, prenomRecherche, 0);
                printf("Statistiques pour le prénom '%s':\n", prenomRecherche);
                printf("Nombre total d'individus : %d\n", stats.nombreTotal);
                printf("Année de première apparition : %d\n", stats.anneePremiereApparition);
                printf("Année de dernière apparition : %d\n", stats.anneeDerniereApparition);
                rewind(fichier);

                break;
            }
            default:
                printf("Choix non valide. Veuillez entrer un nombre entre 0 et 3.\n");
        }
    } while (choix != 0);

    fclose(fichier);
    return 0;
}

