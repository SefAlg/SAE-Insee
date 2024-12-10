#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define longueurmax 100

typedef struct StockPrenom {
    char prenom[longueurmax];
    struct StockPrenom *next;
} StockPrenom;

typedef struct Statistiques {
    int nombreTotal;
    int anneePremiereApparition;
    int anneeDerniereApparition;
} Statistiques;

void libererListe(StockPrenom **liste);
int existePrenom(StockPrenom *liste, const char *prenom);
void ajouterPrenom(StockPrenom **liste, const char *prenom);
Statistiques statistiquesPrenom(FILE *fichier, const char *prenom, int distinguerSexes);
void compterPersonnes(FILE *fichier);
void nombrePrenomSexeDistinct(FILE *fichier);
void nombrePrenomTotal(FILE *fichier);

