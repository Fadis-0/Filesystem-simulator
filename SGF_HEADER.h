#ifndef SGF_HEADER_H
#define SGF_HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

typedef struct noeudArb *TSysteme;
typedef struct noeudArb
{
	char Nom[16];
	int Rep;
	int Taille;

	TSysteme Fils;
	TSysteme Frere;
} noeudArb;

typedef struct noeudCh *TChemin;
typedef struct noeudCh
{
	char Nom[16];
	TChemin Suivant;
} noeudCh;

TSysteme creerNoeudTSysteme(char *nom, int rep, int taille);
TChemin creerNoeudTChemin(char *nom);
void initialiserTSysteme(TSysteme *arbre);
void afficherTSysteme(TSysteme arbre, int niveau);
TChemin stringToTChemin(TSysteme arbre, char *chemin);
bool check(char *input);
int calcSize(TSysteme arbre);
void afficherTChemin(TChemin chemin);
void addToPath(TChemin *chemin, char *nom);
TChemin which(TSysteme systeme, char* nom);
void search(TSysteme systeme, char* nom, TSysteme parent, TSysteme original);
void ls(TSysteme arbre, TChemin chemin, char *name);
bool rm(TSysteme *arbre, TChemin chemin, char *name);
bool mk(TSysteme *arbre, TChemin chemin, char *nom, int rep, int taille);
TSysteme getNodeByName(TSysteme arbre, TChemin chemin, char *nom);
bool ajouterFils(TSysteme arbre, TChemin destinationChemin, TSysteme child);
int getMultiple(char *str, char delimiter, char *substrings[]);

void saveNode(FILE *fp, TSysteme node);
void savePreorder(FILE *fp, TSysteme root);
TSysteme restorePreorder(FILE *fp);
void saveFileSystem(TSysteme root, const char *filename);
TSysteme restoreFileSystem(FILE *fp);

#endif