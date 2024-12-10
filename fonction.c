#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fonction.h"


// fonction qui libere la liste :: avec boucle qui libere la memoire et pose au suivant jusqua ce que la liste soit vide (NULL)
void libererListe(StockPrenom **liste) {
    while (*liste != NULL) {
        StockPrenom *temp = *liste;
        *liste = (*liste)->next;
        free(temp);
    }
}
// fonction qui verifie si dans la liste le prenom existe deja
// grace a la fonction strcmp, si egaux renvoie 1
int existePrenom(StockPrenom *liste, const char *prenom) {
    while (liste != NULL) {
        if (strcmp(liste->prenom, prenom) == 0) {
            return 1;
        }
        liste = liste->next;
    }
    return 0;
}
// fonction qui ajoute un nouveau prenom dans la liste chainée ''StockPrenom'' 
void ajouterPrenom(StockPrenom **liste, const char *prenom) {
    StockPrenom *nouveau = (StockPrenom *)malloc(sizeof(StockPrenom));
    if (nouveau == NULL) {
        fprintf(stderr, "Erreur d'allocation mémoire.\n");
        exit(1);
    }

//copie du prenom
    strcpy(nouveau->prenom, prenom);
    nouveau->next = *liste;
    *liste = nouveau;
}


Statistiques statistiquesPrenom(FILE *fichier, const char *prenom, int distinguerSexes) {
    rewind(fichier);

    char ligne[longueurmax];
    Statistiques stats = {0, 0, 0};
    int prenomTrouve = 0;

    while (fgets(ligne, longueurmax, fichier) != NULL) {
        char *sexe = strtok(ligne, ";");
        char *nomPrenom = strtok(NULL, ";");
        char *anneeStr = strtok(NULL, ";");
        int nombre = atoi(strtok(NULL, ";"));

        if (strcmp(nomPrenom, prenom) == 0 && (!distinguerSexes || (distinguerSexes && ((sexe[0] == '1') || (sexe[0] == '2'))))) {
            int annee = (strcmp(anneeStr, "XXXX") == 0) ? -1 : atoi(anneeStr);

            if (!prenomTrouve || (annee != -1 && (annee < stats.anneePremiereApparition || stats.anneePremiereApparition == 0))) {
                stats.anneePremiereApparition = annee;
                prenomTrouve = 1;
            }

            if (annee != -1 && annee > stats.anneeDerniereApparition) {
                stats.anneeDerniereApparition = annee;
            }

            stats.nombreTotal += nombre;
        }
    }

    return stats;
}

void compterPersonnes(FILE *fichier) {
    char ligne[longueurmax];
    int totalPersonnes = 0;

    fgets(ligne, longueurmax, fichier);

    while (fgets(ligne, longueurmax, fichier) != NULL) {
        char *token = strtok(ligne, ";");

        for (int i = 0; i < 3; i++) {
            token = strtok(NULL, ";");
        }

        int nombre = atoi(strtok(NULL, ";"));

        totalPersonnes += nombre;
    }

    printf("Le nombre total de personnes est : %d\n", totalPersonnes);
}

void nombrePrenomSexeDistinct(FILE *fichier) {
    rewind(fichier);

    char ligne[longueurmax];
    StockPrenom *prenomsHommes = NULL;
    StockPrenom *prenomsFemmes = NULL;

    int totalHommes = 0;
    int totalFemmes = 0;

    fgets(ligne, longueurmax, fichier);

    while (fgets(ligne, longueurmax, fichier) != NULL) {
        char *sexe = strtok(ligne, ";");
        char *prenom = strtok(NULL, ";");
        int nombre = atoi(strtok(NULL, ";"));

        if (sexe[0] == '1') {
            if (!existePrenom(prenomsHommes, prenom)) {
                ajouterPrenom(&prenomsHommes, prenom);
                totalHommes += 1;
            }
        } else if (sexe[0] == '2') {
            if (!existePrenom(prenomsFemmes, prenom)) {
                ajouterPrenom(&prenomsFemmes, prenom);
                totalFemmes += 1;
            }
        }
    }

    libererListe(&prenomsHommes);
    libererListe(&prenomsFemmes);

    printf("Le nombre de prénoms masculins distincts est : %d\n", totalHommes);
    printf("Le nombre de prénoms féminins distincts est : %d\n", totalFemmes);
}

void nombrePrenomTotal(FILE *fichier) {
    rewind(fichier);

    char ligne[longueurmax];
    StockPrenom *prenomsHommes = NULL;
    StockPrenom *prenomsFemmes = NULL;

    int totalHommes = 0;
    int totalFemmes = 0;

    fgets(ligne, longueurmax, fichier);

    while (fgets(ligne, longueurmax, fichier) != NULL) {
        char *sexe = strtok(ligne, ";");
        char *prenom = strtok(NULL, ";");
        int nombre = atoi(strtok(NULL, ";"));

        if (sexe[0] == '1') {
            if (!existePrenom(prenomsHommes, prenom)) {
                ajouterPrenom(&prenomsHommes, prenom);
                totalHommes += 1;
            }
        } else if (sexe[0] == '2') {
            if (!existePrenom(prenomsFemmes, prenom)) {
                ajouterPrenom(&prenomsFemmes, prenom);
                totalFemmes += 1;
            }
        }
    }

    libererListe(&prenomsHommes);
    libererListe(&prenomsFemmes);

    printf("Le nombre de prénoms distincts est : %d\n", totalHommes + totalFemmes);
}

