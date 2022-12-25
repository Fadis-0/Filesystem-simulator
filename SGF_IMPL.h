#ifndef SGF_IMPL_H
#define SGF_IMPL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

typedef struct noeudArb *TSysteme;
typedef struct noeudArb
{
	char *Nom;
	int Rep;
	int Taille;

	TSysteme Fils;
	TSysteme Frere;
} noeudArb;

typedef struct noeudCh *TChemin;
typedef struct noeudCh
{
	char *Nom;
	TChemin Suivant;
} noeudCh;

TSysteme init();
TSysteme newNode(char *nom, int rep, int taille);
TChemin newChemin(TSysteme noeud);
void print(TChemin chemin);
void printFils(TSysteme rep);
TSysteme recherche(TSysteme racine, char *nom);
void ls(TSysteme systeme, TChemin adresse, char *nom);
void rm(TSysteme *systeme, TChemin adresse, char *nom);
TSysteme verify(TSysteme systeme, TChemin adresse);
void rm_helper(TSysteme* systeme, char *nom);
void mkdir(TSysteme *systeme, TChemin adresse, char *nom);
void mkfile(TSysteme *systeme, TChemin adresse, char *nom, int taille);
void cp(TSysteme *systeme, TChemin adresse, TSysteme rep);
TSysteme getDirFile(TSysteme systeme, TChemin adresse, char* nom);
TChemin chemin(TSysteme s, char *nom);
TChemin newChemNode(char *nom);
void insert(TChemin *ch, char *nom);
void command(TSysteme systeme);
void exist(TSysteme systeme, char* nom, TSysteme parent, TSysteme original);
int stockage;
void printAll(TSysteme systeme, int level);
void insertPath(TChemin *ch, char *nom);
TChemin getPath(TSysteme systeme, char* nom);
int calcAll(TSysteme systeme);
int calcSize(TSysteme systeme);
int getMultiple(char *str, char delimiter, char *substrings[]);
int check_integer(char *input);
void espace();

#endif