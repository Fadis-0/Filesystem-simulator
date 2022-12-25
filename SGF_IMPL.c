#include "SGF_IMPL.h"

// Lire la commande de l'utilisateur et l'executer
void command(TSysteme systeme){
	char cmd[100];
	char *adresse = (char *)malloc(100);
	char *dest = (char *)malloc(100);
	char *nom = (char *)malloc(100);
	TChemin ad = NULL;
	TChemin cible = NULL;
	int taille;
	char *substrings[50];
	char *str_copy = (char *)malloc(100);
	int i, num_substrings;
	char input[100];
	
	do{
		// Lire la commande de l'utilisateur
		printf("commande > ");
		fflush(stdin);
		scanf("%[^\n]", cmd);
		getchar();
		
		// Vérifier si la commande est "ls"
		if (strcmp(cmd, "ls") == 0){
			// Afficher le contenu d'un répertoire dans le système de fichiers
			printf(" [Afficher le contenu d'un repertoire]");
			// Saisir l'adresse et le nom de répertoire
			printf("\n Adresse : ");
			scanf("%s", adresse);
			printf(" Nom : ");
			scanf("%s", nom);
			// Obtenir le chemin spécifié par "adresse"
			ad = chemin(systeme, adresse);
			// Afficher le contenu du répertoire
			if (ad != NULL) ls(systeme, ad, nom);
			// Si l'adresse n'existe pas, afficher un message d'erreur
			else printf("\n Adresse n'existe pas\n\n");
		}
		
		// Vérifier si la commande est "rm"
		else if (strcmp(cmd, "rm") == 0){
			// Supprimer un fichier ou un répertoire du système de fichiers
			printf(" [Supprimer un repertoire / fichier]");
			// Saisir l'adresse et le nom de répertoire ou fichier
			printf("\n Adresse : ");
			scanf("%s", adresse);
			printf(" Nom : ");
			scanf("%s", nom);
			// Obtenir le chemin spécifié par "adresse"
			ad = chemin(systeme, adresse);
			if (ad != NULL){
				// Obtenir le fichier ou le répertoire spécifié par "nom"
				TSysteme file = getDirFile(systeme, ad, nom);
				// Supprimer le fichier ou le répertoire
				if (file != NULL) rm(&(systeme), ad, nom);
				// Si le fichier ou le répertoire n'existe pas, afficher un message d'erreur
				else printf("\n %s n'existe pas!", nom);
			}
			// Si l'adresse n'existe pas, afficher un message d'erreur
			else printf("\n Adresse n'existe pas");
			printf("\n\n");
		}
		
		// Vérifier si la commande est "rm -m"
		else if (strcmp(cmd, "rm -m") == 0){
			// Supprimer plusieurs fichiers ou répertoires du système de fichiers
			printf(" [Supprimer des repertoires / fichiers]");
			// Saisir l'adresse et les nom des répertoires ou fichiers
			printf("\n Adresse : ");
			scanf("%s", adresse);
			printf(" Noms : ");
			fflush(stdin);
			scanf("%[^\n]", nom);
			// Obtenir le chemin spécifié par "adresse"
			ad = chemin(systeme, adresse);
			if (ad != NULL){
				// Initialiser la liste de noms
				for (i = 0; i < 50; i++) {
       			 substrings[i] = NULL;
    			}
				// Faire une copie de "nom"
				str_copy = strdup(nom);
				// Séparer la liste de noms "str_copy" en noms individuels et retourner le nombre de noms dans "num_substrings"
  			  num_substrings = getMultiple(str_copy, ' ', substrings);
    			// Si il n'y a qu'un nom dans la liste, afficher un message d'erreur
    			if(num_substrings == 1) printf("\n Utiliser 'rm' pour supprimer un seul fichier / repertoire");
    			// Sinon, supprimer chaque fichier ou répertoire de la liste
    			else {
    				for (i = 0; i < num_substrings; i++) {
    					printf("");
    					// Obtenir le fichier ou répertoire spécifié par le nom actuel
    					TSysteme file = getDirFile(systeme, ad, substrings[i]);
    					// Supprimer le fichier ou répertoire
						if (file != NULL) rm(&(systeme), ad, substrings[i]);
						// Si le fichier ou répertoire n'existe pas, afficher un message d'erreur
						else printf("\n %s n'existe pas!", substrings[i]);
    				}
    			}
  			  printf("\n\n");
				// Libérer la copie de la liste de noms
  			  free(str_copy);
			}
			// Si l'adresse n'existe pas, afficher un message d'erreur
			else printf("\n Adresse n'existe pas\n\n");
		}
		
		// Vérifier si la commande est "mkdir"
		else if (strcmp(cmd, "mkdir") == 0){
			// Ajouter un répertoire
			printf(" [Ajouter un repertoire]");
			// Saisir l'adresse et le nom du répertoire à ajouter
			printf("\n Adresse : ");
			scanf("%s", adresse);
			printf(" Nom : ");
			scanf("%s", nom);
			// Obtenir le chemin spécifié par "adresse"
			ad = chemin(systeme, adresse);
			// Si le chemin n'existe pas, afficher un message d'erreur
			if (ad == NULL) printf("\n Adresse n'existe pas\n\n");
			// Sinon, ajouter le répertoire
			else mkdir(&(systeme), ad, nom);
		}
		
		// Vérifier si la commande est "mkfile"
		else if (strcmp(cmd, "mkfile") == 0){
			// Ajouter un fichier
			printf(" [Ajouter un fichier]");
			// Saisir l'adresse et le nom du fichier à ajouter
			printf("\n Adresse : ");
			scanf("%s", adresse);
			printf(" Nom : ");
			scanf("%s", nom);
			// Saisir la taille du fichier
			while (1) {
    			printf(" Taille : ");
    			fflush(stdin);
				fgets(input, 100, stdin);
				// Vérifier si la taille est un entier
   			 if (check_integer(input)) {
    				sscanf(input, "%d", &taille);
    				break;
    			}
    			// Sinon, afficher un message d'erreur
    			else printf(" Entrée non valide, réessayer S'il vous plaît.\n");
  		  }
			// Si le stockage est plein, afficher un message d'erreur
			if((systeme->Taille)+taille > stockage) printf("\n Espace de stockage plein!\n\n");
			else{
				// Obtenir le chemin spécifié par "adresse"
				ad = chemin(systeme, adresse);
				// Si le chemin n'existe pas, afficher un message d'erreur
				if (ad == NULL) printf("\n Adresse n'existe pas\n\n");
				// Sinon, ajouter le fichier
				else mkfile(&(systeme), ad, nom, taille);
			}
		}
		
		// Vérifier si la commande est "cpdir"
		else if (strcmp(cmd, "cpdir") == 0){
			// Copier un répertoire dans le système de fichiers
			printf(" [Coupier un repertoire]");
			// Saisir l'adresse source et le nom du répertoire à copier
			printf("\n Adresse source : ");
			scanf("%s", adresse);
			printf(" Nom : ");
			scanf("%s", nom);
			// Saisir l'adresse cible où copier le répertoire
			printf(" Adresse cible  : ");
			scanf("%s", dest);	
			// Obtenir le chemin source spécifié par "adresse"
			ad = chemin(systeme, adresse);
			// Si le chemin source n'existe pas, afficher un message d'erreur
			if(ad == NULL) printf("\n Adresse source n'existe pas\n\n");
			else{
				// Obtenir le répertoire spécifié par "nom" dans le chemin "ad"
				TSysteme dir = getDirFile(systeme, ad, nom);
				// Si le répertoire n'existe pas, afficher un message d'erreur
				if(dir == NULL) printf("\n %s n'existe pas!\n\n", nom);
				// Si le nom spécifié est un fichier, afficher un message d'erreur
				else if(dir->Rep == 0){
					printf("\n %s est un fichier!", nom);
					printf("\n Utiliser 'cpfile' pour copier un fichier\n\n");
				}
				else{
					// Si le stockage est plein, afficher un message d'erreur
					if(calcAll(systeme)+calcAll(dir) > stockage) printf("\n Espace de stockage plein!\n\n");
					else{
						// Obtenir le chemin cible spécifié par "dest"
						cible = chemin(systeme, dest);
						// Si le chemin cible n'existe pas, afficher un message d'erreur
						if(cible == NULL) printf("\n Adresse cible n'existe pas\n\n");
						// Sinon, copier le repertoire
						else cp(&(systeme), cible, dir);
					}
				}
			}
		}
		
		// Vérifier si la commande est "cpfile"
		else if (strcmp(cmd, "cpfile") == 0){
			// Copier un fichier dans le système de fichiers
			printf(" [Coupier un fichier]");
			// Saisir l'adresse source et le nom du fichier à copier
			printf("\n Adresse source : ");
			scanf("%s", adresse);
			printf(" Nom : ");
			scanf("%s", nom);
			// Saisir l'adresse cible où copier le fichier
			printf(" Adresse cible  : ");
			scanf("%s", dest);	
			// Obtenir le chemin source spécifié par "adresse"
			ad = chemin(systeme, adresse);
			// Si le chemin source n'existe pas, afficher un message d'erreur
			if(ad == NULL) printf("\n Adresse source n'existe pas\n\n");
			else{
				// Obtenir le fichier spécifié par "nom" dans le chemin "ad"
				TSysteme file = getDirFile(systeme, ad, nom);
				// Si le fichier n'existe pas, afficher un message d'erreur
				if(file == NULL) printf("\n %s n'existe pas\n\n", nom);
				// Si le nom spécifié est un répertoire, afficher un message d'erreur
				else if(file->Rep == 1){
					printf("\n %s est un repertoire!", nom);
					printf("\n Utiliser 'cpdir' pour copier un repertoire\n\n");
				}
				else{
					// Si le stockage est plein, afficher un message d'erreur
					if(calcAll(systeme)+file->Taille > stockage) printf("\n Espace de stockage plein!\n\n");
					else{
						// Obtenir le chemin cible spécifié par "dest"
						cible = chemin(systeme, dest);
						// Si le chemin cible n'existe pas, afficher un message d'erreur
						if(cible == NULL) printf("\n Adresse cible n'existe pas\n\n");
						// Sinon, copier le fichier
						else cp(&(systeme), cible, file);
					}
				}
			}
		}
		
		// Vérifier si la commande est "exist"
		else if (strcmp(cmd, "exist") == 0){
			// Rechercher un répertoire / fichier dans le système de fichiers
			printf(" [Rechercher un repertoire / fichier]");
			// Saisir le nom du répertoire / fichier à rechercher
    		printf("\n Nom : ");
    		scanf("%s", nom);
    		
    		printf("\n");
    		// Appeler la fonction "exist" pour rechercher le répertoire / fichier spécifié
			exist(systeme, nom, systeme, systeme);
			printf("\n");
		}
		
		// Vérifier si la commande est "exist -m"
		else if (strcmp(cmd, "exist -m") == 0){
			// Chercher plusieurs répertoires ou fichiers dans le système de fichiers
			printf(" [Rechercher des repertoires / fichiers]");
			// Saisir les noms des répertoires ou fichiers à chercher
			printf("\n Noms : ");
			fflush(stdin);
			scanf("%[^\n]", nom);
			// Initialiser la liste de noms
			for (i = 0; i < 50; i++) substrings[i] = NULL;
    		// Faire une copie de "nom"
			str_copy = strdup(nom);
			// Séparer la liste de noms "str_copy" en noms individuels et retourner le nombre de noms dans "num_substrings"
  		  num_substrings = getMultiple(str_copy, ' ', substrings);
  		  printf("\n");
    		for (i = 0; i < num_substrings; i++) {
    			printf("");
    			// Appeler la fonction "exist" pour rechercher le répertoire / fichier actuel
      		  exist(systeme, substrings[i], systeme, systeme);
  		  }
  		  printf("\n");
  		  free(str_copy);
		}
		
		// Vérifier si la commande est "sys"
		else if (strcmp(cmd, "sys") == 0){
			// Afficher tous les répertoires et fichiers du système de fichiers, en commençant par la racine
			printAll(systeme, 0);
		}
		
		// Vérifier si la commande est "espace"
		else if (strcmp(cmd, "espace") == 0){
			// Afficher l'espace utilisé, l'espace libre et l'espace total dans le système de fichiers
			printf("\n Used  : %d\n Free  : %d\n Total : %d\n\n", calcAll(systeme), stockage-calcAll(systeme), stockage);
		}
		
		// Vérifier si la commande est "clear"
		else if (strcmp(cmd, "clear") == 0){
			// Effacer le contenu de la console
			system("cls || clear");
		}
		
		// Sinon
		else{
			printf("\n commande n'existe pas!\n\n");
			continue;
		}

	} while (1);
}

// Imprimer le contenu du système de fichiers
void printAll(TSysteme systeme, int level) {
  // Imprimer le nom du répertoire ou du fichier courant et son niveau d'indentation
  for (int i = 0; i < level; i++) printf("-");
  printf("%s", systeme->Nom);
  // Si le noeud courant est un fichier, imprimer sa taille en bytes
  if (systeme->Rep == 0) printf(" (%d bytes)", systeme->Taille);
  printf("\n");
  // Si le noeud courant est un répertoire, parcourir ses enfants récursivement
  if (systeme->Rep == 1) {
    TSysteme child = systeme->Fils;
    while (child != NULL) {
      printAll(child, level + 1);
      child = child->Frere;
    }
  }
  
}

// Récupère le chemin du noeud avec le nom spécifié dans l'arborescence de système de fichiers
TChemin getPath(TSysteme systeme, char* nom) {
  // Si le noeud actuel a le nom spécifié, renvoyer son chemin
  if (strcmp(systeme->Nom, nom) == 0) {
    TChemin path = NULL;
    insertPath(&path, systeme->Nom);
    return path;
  }
  // Si le noeud actuel est un répertoire, chercher dans ses enfants
  if (systeme->Rep == 1) {
    TSysteme child = systeme->Fils;
    while (child != NULL) {
      TChemin path = getPath(child, nom);
      if (path != NULL) {
        // Si le noeud a été trouvé dans un enfant, préfixer le nom du noeud actuel au chemin
        insertPath(&path, systeme->Nom);
        return path;
      }
      child = child->Frere;
    }
  }
  // Si le noeud n'a pas été trouvé dans l'arborescence sous-jacente, renvoyer NULL
  return NULL;
}

// Insère un nouveau noeud dans le chemin
void insertPath(TChemin *ch, char *nom) {
  // Créer un nouveau noeud de chemin
  TChemin newChemNode = malloc(sizeof(struct noeudCh));
  // Assigner le nom donné au noeud
  newChemNode->Nom = nom;
  // Faire pointer le nouveau noeud vers le début du chemin actuel
  newChemNode->Suivant = *ch;
  // Faire pointer le début du chemin vers le nouveau noeud
  *ch = newChemNode;
}


// Chercher un fichier ou un répertoire
void exist(TSysteme systeme, char* nom, TSysteme parent, TSysteme original) {
  // Si le noeud actuel a le nom spécifié, affiche un message avec le nom du parent
  if (strcmp(systeme->Nom, nom) == 0) {
    // Obtient le chemin du parent
    TChemin ch = getPath(original, parent->Nom);
    printf("%s existe dans : ", nom);
    print(ch);
    printf("\n");
  }
 // Si le noeud actuel est un répertoire, recherche ses enfants
 if (systeme->Rep == 1) {
    TSysteme child = systeme->Fils;
    while (child != NULL) {
      exist(child, nom, systeme, original);
      child = child->Frere;
    }
  }
}

// Retourner un répertoire ou un fichier à partir de son adresse et son nom
TSysteme getDirFile(TSysteme systeme, TChemin adresse, char* nom){
	// Stocke le chemin à parcourir dans une variable temporaire
	TChemin temp = adresse->Suivant;
	// Initialise deux variables de type TSysteme, une pour stocker le système de fichiers et l'autre pour stocker les résultats de recherche
	TSysteme sys = systeme, res;
	// Tant qu'il reste des éléments dans le chemin à parcourir
	while (temp != NULL){
		// Rechercher l'élément du chemin dans le système de fichiers
		res = recherche(sys, temp->Nom);
		// Si l'élément a été trouvé
		if (res != NULL){
			// Mettre à jour "sys" avec le résultat de la recherche
			sys = res;
			// Passer à l'élément suivant du chemin à parcourir
			temp = temp->Suivant;
		}
		else{
			sys = NULL;
			break;
		}
	}
	// Si l'adresse existe, rechercher le répertoire / fichier spécifié
	if (sys != NULL){
		sys = recherche(sys, nom);
		if (sys != NULL) {
			// Créer un nouveau noeud avec les informations du répertoire / fichier
			TSysteme dir = newNode(sys->Nom, sys->Rep, sys->Taille);
			// Mettre à jour les enfants du nouveau noeud avec ceux de l'élément trouvé
			dir->Fils = sys->Fils;
			return dir;
		}
		else return NULL;	
	}
	else return NULL;	
}

// Cppier un répertoire ou un fichier
void cp(TSysteme *systeme, TChemin adresse, TSysteme rep){
	// Si le système de fichiers est vide, on ne fait rien
	if ((*systeme) == NULL) return;
	else{
		// Si le noeud courant est celui indiqué par l'adresse
		if (strcmp((*systeme)->Nom, adresse->Nom) == 0) {
			// On réappelle la fonction sur le fils du noeud courant
			if(adresse->Suivant != NULL) cp(&((*systeme)->Fils), adresse->Suivant, rep);	
			else{
				// Si le noeud courant n'a pas de fils
				if((*systeme)->Fils == NULL){
					// On ajoute le noeud `rep` comme premier fils du noeud courant
					(*systeme)->Fils = rep;
					// On affiche un message de confirmation
					if(rep->Rep == 1) printf("\n Repertoire %s ajouté dans %s\n\n", rep->Nom, (*systeme)->Nom);
					else if(rep->Rep == 0) printf("\n Fichier %s ajouté dans %s\n\n", rep->Nom, (*systeme)->Nom);	
				}
				else{
					// Si le noeud `rep` n'est pas déjà présent dans la liste des fils du noeud courant
					if( recherche(*systeme, rep->Nom) == NULL){
						// On ajoute le noeud `rep` comme frère du premier fils du noeud courant
						TSysteme temp = (*systeme)->Fils->Frere;
						(*systeme)->Fils->Frere = rep;
						(*systeme)->Fils->Frere->Frere = temp;
						// On affiche un message de confirmation
						if(rep->Rep == 1) printf("\n Repertoire %s ajouté dans %s\n\n", rep->Nom, (*systeme)->Nom);
						else if(rep->Rep == 0) printf("\n Fichier %s ajouté dans %s\n\n", rep->Nom, (*systeme)->Nom);
					}
					// Si le noeud `rep` est déjà présent dans la liste des fils du noeud courant
					else{
						// On affiche un message indiquant que le noeud `rep` existe déjà selon son type
						if(rep->Rep == 1) printf("\n Le repertoire existe!\n\n");
						if(rep->Rep == 0) printf("\n Le fichier existe!\n\n");
					}
				}
			}
		}
		// Si le noeud courant n'est pas celui indiqué par l'adresse
		else cp(&((*systeme)->Frere), adresse, rep);
	}
}

// Ces 2 functions calcule la taille totale des noeuds enfants d'un noeud d'arbre
int calcAll(TSysteme systeme) {
    // Si le noeud courant est un répertoire, calculer la taille de ses enfants
    int size = 0;
    if (systeme->Rep == 1) {
        TSysteme child = systeme->Fils;
        // Tant qu'il y a des enfants à parcourir
        while (child != NULL) {
            size += calcSize(child); // On ajoute la taille de l'enfant courant au total
            child = child->Frere; // On passe à l'enfant suivant
        }
    }
    return size; // On retourne la taille totale
}
// ...
int calcSize(TSysteme systeme) {
    // Si le noeud courant est un fichier, retourner sa taille
    if (systeme->Rep == 0) {
        return systeme->Taille;
    }

    // Si le noeud courant est un répertoire, calculer la taille de ses enfants
    int size = 0;
    TSysteme child = systeme->Fils;
    // Tant qu'il y a des enfants à parcourir
    while (child != NULL) {
        size += calcSize(child); // On ajoute la taille de l'enfant courant au total
        child = child->Frere; // On passe à l'enfant suivant
    }
    return size; // On retourne la taille totale
}

void mkdir(TSysteme *systeme, TChemin adresse, char *nom){
	if ((*systeme) == NULL) return;
	else{
		// Si le noeud courant est celui indiqué par l'adresse
		if (strcmp((*systeme)->Nom, adresse->Nom) == 0) {
			// Si le noeud de chemin courant n'est pas le dernier de l'adresse, on réappelle la fonction sur le fils du noeud courant
			if(adresse->Suivant != NULL) mkdir(&((*systeme)->Fils), adresse->Suivant, nom);
			else{
				// On crée un nouveau noeud répertoire avec le nom donné
				char *s = (char *)malloc(100);
				strcpy(s, nom);
				TSysteme dir = newNode(s, 1, 0);
				// Si le noeud courant n'a pas de fils
				if((*systeme)->Fils == NULL){
					// On ajoute le noeud `dir` comme premier fils du noeud courant
					(*systeme)->Fils = dir;
					printf("\n Repertoire %s ajouté dans %s\n\n", nom, (*systeme)->Nom);	
				}
				else{
					// Si le répertoire n'existe pas déjà dans les fils du noeud courant
					if( recherche(*systeme, nom) == NULL){
						// On ajoute le répertoire comme frère du premier fils du noeud courant
						TSysteme temp = (*systeme)->Fils->Frere;
						(*systeme)->Fils->Frere = dir; 
						(*systeme)->Fils->Frere->Frere = temp;
						printf("\n Repertoire %s ajouté dans %s\n\n", nom, (*systeme)->Nom);
					}
					// Si un répertoire avec le meme nom existe, afficher un message d'erreur
					else printf("\n Le repertoire existe!\n\n");
				}
			}
		}
		else mkdir(&((*systeme)->Frere), adresse, nom);
	}
}




void mkfile(TSysteme *systeme, TChemin adresse, char *nom, int taille){
	if ((*systeme) == NULL) return;
	else{
		// Si le noeud courant est celui indiqué par l'adresse
		if (strcmp((*systeme)->Nom, adresse->Nom) == 0) {
			// Si le noeud de chemin courant n'est pas le dernier de l'adresse, on réappelle la fonction sur le fils du noeud courant
			if(adresse->Suivant != NULL) mkfile(&((*systeme)->Fils), adresse->Suivant, nom, taille);
			else{
				// On crée un nouveau noeud fichier avec le nom donné
				char *s = (char *)malloc(100);
				strcpy(s, nom);
				TSysteme fil = newNode(s, 0, taille);
				// Si le noeud courant n'a pas de fils
				if((*systeme)->Fils == NULL){
					// On ajoute le noeud `dir` comme premier fils du noeud courant
					(*systeme)->Fils = fil;
					(*systeme)->Taille += taille;
					printf("\n Fichier %s ajouté dans %s\n\n", nom, (*systeme)->Nom);	
				}
				else{
					// Si le fichier n'existe pas déjà dans les fils du noeud courant
					if( recherche(*systeme, nom) == NULL){
						// On ajoute le fichier comme frère du premier fils du noeud courant
						TSysteme temp = (*systeme)->Fils->Frere;
						(*systeme)->Fils->Frere = fil;
						(*systeme)->Fils->Frere->Frere = temp;
						(*systeme)->Taille += taille;
						printf("\n Fichier %s ajouté dans %s\n\n", nom, (*systeme)->Nom);
					}
					// Si un fichier avec le meme nom existe, afficher un message d'erreur
					else printf("\n Le fichier existe!\n\n");
				}
			}
		}
		else mkfile(&((*systeme)->Frere), adresse, nom, taille);	
	}
}

void rm(TSysteme *systeme, TChemin adresse, char *nom) {
    // Si le système de fichiers est vide, on ne fait rien
    if ((*systeme) == NULL) return;
    else{
        // Si le noeud courant est celui indiqué par l'adresse
        if (strcmp((*systeme)->Nom, adresse->Nom) == 0) {
            // Si le noeud courant n'est pas le dernier de l'adresse
            if(adresse->Suivant != NULL){
                // On réappelle la fonction sur le fils du noeud courant
                rm(&((*systeme)->Fils), adresse->Suivant, nom);
            }
            else{
                // On appelle la fonction helper sur les fils du noeud courant
                rm_helper(&((*systeme)->Fils), nom);
            }
        }
        else {
            // On réappelle la fonction sur les frères du noeud courant
            rm(&((*systeme)->Frere), adresse, nom);
        }
    }
}
void rm_helper(TSysteme* systeme, char *nom){
    // Si le système de fichiers est vide, on ne fait rien
    if ((*systeme) == NULL) return;
    else {
        // Si le nom du noeud courant est celui du fichier/répertoire à supprimer
        if(strcmp((*systeme)->Nom, nom) == 0){
            printf("\n Supprimé : %s", (*systeme)->Nom);
            // Si le noeud courant a un frère
            if((*systeme)->Frere != NULL){
                // On remplace le noeud courant par son frère
                *systeme = (*systeme)->Frere;
            }
            else{
                // Sinon, on supprime le noeud courant
                *systeme = NULL;
                free((*systeme));
            }
        }
        // Sinon, on appelle la fonction sur les frères du noeud courant
        else rm_helper(&((*systeme)->Frere), nom);
    }
}


TSysteme recherche(TSysteme racine, char *nom){
    // On crée un pointeur vers le premier fils de la racine
    TSysteme temp = racine->Fils;
    // On parcourt les fils de la racine
    while (temp != NULL){
        // Si le nom du fils courant correspond à celui recherché
        if (strcmp(temp->Nom, nom) == 0) 
            // On retourne le noeud
            return temp;
        // On passe au fils suivant
        temp = temp->Frere;
    }
    // Si aucun noeud correspondant n'a été trouvé, on retourne NULL
    return NULL;
}

void ls(TSysteme systeme, TChemin adresse, char *nom){
	// Initialisation de variables pour parcourir l'arborescence
	TChemin temp = adresse->Suivant;
	TSysteme sys = systeme, res;

	// Parcours de l'arborescence jusqu'à arriver au répertoire spécifié dans l'adresse
	while (temp != NULL){
		res = recherche(sys, temp->Nom);
		if (res != NULL){
			sys = res;
			temp = temp->Suivant;
		}
		else{
			sys = NULL;
			break;
		}
	}
	// Si le répertoire spécifié existe, on affiche ses fils
	if (sys != NULL){
		sys = recherche(sys, nom);
		if (sys != NULL) printFils(sys);
		else printf("\n Repertoire n'existe pas\n\n");
	}
	// Si l'adresse n'existe pas, on affiche un message d'erreur
	else printf("\n Adresse n'existe pas\n");
}


TSysteme verify(TSysteme systeme, TChemin adresse){
	// Création d'un pointeur vers le noeud suivant de l'adresse
	TChemin temp = adresse->Suivant;
	// Création d'un pointeur vers le système de fichiers courant
	TSysteme sys = systeme, res;
	// Tant qu'il y a un noeud suivant dans l'adresse
	while (temp != NULL){
		// On cherche le noeud dans le système de fichiers courant
		res = recherche(sys, temp->Nom);
		// Si on trouve le noeud
		if (res != NULL){
			// On met à jour le système de fichiers courant
			sys = res;
			// On passe au noeud suivant de l'adresse
			temp = temp->Suivant;
		}
		else{
			// Si on ne trouve pas le noeud, on met à jour le système de fichiers courant pour qu'il soit NULL
			sys = NULL;
			// On sort de la boucle
			break;
		}
	}
	// On retourne le système de fichiers courant
	return sys;
}


TChemin chemin(TSysteme s, char *nom){
    // Si le nom du chemin commence par '/'
    if (nom[0] == '/'){
        // On crée une copie de la chaîne de caractères nom
        char *copy = strdup(nom);
        // On crée un pointeur qui servira à parcourir la copie
        char *str = strtok(copy, "/");
        // On crée un nouveau noeud de chemin qui correspond à la racine
        TChemin chem = newChemNode("/");
        // On parcourt la copie
        while (str != NULL){
            // On insère chaque sous-chaîne séparée par '/' dans le chemin en créant un nouveau noeud pour chacune
            insert(&chem, str);
            // On passe à la sous-chaîne suivante
            str = strtok(NULL, "/");
        }
        // On libère la mémoire allouée pour la copie
        free(copy);
        // Si le chemin n'existe pas dans le système de fichiers, on retourne NULL
        if(verify(s, chem) == NULL) return NULL;
        // Sinon, on retourne le chemin
        else return chem;
    }
    // Si le nom du chemin ne commence pas par '/', on retourne NULL
    else return NULL;	
}

void insert(TChemin *ch, char *nom){
	// Création d'un nouveau noeud de chemin
	TChemin new = newChemNode(nom);
	// Si le chemin est vide, on initialise le premier noeud
	if (*ch == NULL) *ch = new;
	else{
		// On parcourt les noeuds de chemin jusqu'à arriver au dernier
		TChemin node = *ch;
		while (node->Suivant != NULL) node = node->Suivant;
		// On ajoute le nouveau noeud à la fin du chemin
		node->Suivant = new;
	}
}


TChemin newChemNode(char *nom){
    // Alloue de la mémoire pour un nouveau noeud
    TChemin node = (TChemin)malloc(sizeof(noeudCh));
    // Assigne le nom au nouveau noeud
    node->Nom = nom;
    // Initialise le suivant du noeud comme étant NULL
    node->Suivant = NULL;
    return (node);
}

void printFils(TSysteme rep){
    // On crée un pointeur vers le premier fils du répertoire
    TSysteme temp = rep->Fils;
    printf("\n %s\n", rep->Nom);
    // Si le répertoire n'a pas de fils
    if (temp == NULL)
        printf(" -(vide)\n");
    // On parcourt les fils du répertoire
    while (temp != NULL){
        printf(" -%s\n", temp->Nom);
        temp = temp->Frere;
    }
    printf("\n");
}

void print(TChemin chemin){
    // On crée un noeud temporaire qui pointe sur le fils du noeud courant
    TChemin temp = chemin->Suivant;
    printf("/"); // On affiche la racine du système de fichiers
    // Tant qu'il y a des noeuds à parcourir
    while (temp != NULL){
        printf("%s/", temp->Nom); // On affiche le nom du noeud courant et le séparateur '/'
        temp = temp->Suivant; // On passe au noeud suivant
    }
}

// Initialiser l'arbre
TSysteme init(){
    // Création des noeuds du système de fichiers
    TSysteme racine = newNode("/", 1, 0);
    TSysteme bin = newNode("bin", 1, 0);
    TSysteme home = newNode("home", 1, 0);
    TSysteme root = newNode("root", 1, 0);
    TSysteme run = newNode("run", 1, 0);
    TSysteme user = newNode("univ", 1, 0);
    TSysteme desk = newNode("bureau", 1, 0);
    TSysteme docs = newNode("Documents", 1, 0);
    TSysteme downs = newNode("Telechargement", 1, 0);

    // Création des liens entre les noeuds
    racine->Fils = bin;
    home->Fils = user;
    user->Fils = desk;

    bin->Frere = home;
    home->Frere = root;
    root->Frere = run;
    desk->Frere = docs;
    docs->Frere = downs;

    return racine; // On retourne la racine du système de fichiers
}


// Creer un noeud d'arbre
TSysteme newNode(char *nom, int rep, int taille){
    // Allouer de la mémoire pour le nouveau noeud
    TSysteme node = (TSysteme)malloc(sizeof(noeudArb));
    // Assigner les données à ce noeud
    node->Nom = nom;
    node->Rep = rep;
    node->Taille = taille;
    // Initialiser le fils et le frère à NULL
    node->Fils = NULL;
    node->Frere = NULL;
    return (node);
}

// Creer un noeud de chemin
TChemin newChemin(TSysteme noeud){
    // Allouer de la mémoire pour le nouveau noeud
    TChemin node = (TChemin)malloc(sizeof(noeudCh));
    // Assigner les données à ce noeud
    node->Nom = noeud->Nom;
    // Initialiser le fils et le frère à NULL
    node->Suivant = NULL;
    return (node);
}


// Séparer 'str' en plusieur 'substrings'
int getMultiple(char *str, char delimiter, char *substrings[]) {
    int i = 0; // Compteur pour parcourir le tableau `substrings`
    char *token = strtok(str, &delimiter); // On découpe la chaîne `str` en plusieurs sous-chaînes en utilisant le délimiteur `delimiter`

    // Tant qu'il y a des sous-chaînes à extraire
    while (token != NULL) {
        substrings[i++] = token; // On enregistre la sous-chaîne dans le tableau `substrings` et on incrémente le compteur
        token = strtok(NULL, &delimiter); // On continue à découper la chaîne `str` en utilisant le délimiteur `delimiter`
    }

    return i; // On retourne le nombre de sous-chaînes extraites
}


// Retourne 1 si 'input'' est un entier, 0 sinon
int check_integer(char *input) {
  // On parcourt tous les caractères de l'entrée
  for (int i = 0; input[i] != '\0' && input[i] != '\n'; i++) {
    // Si l'un des caractères n'est pas un chiffre, on renvoie 0 (faux)
    if (!isdigit(input[i])) {
      return 0;
    }
  }
  // Si tous les caractères sont des chiffres, on renvoie 1 (vrai)
  return 1;
}

// Lire la taille de l'espace de stockage
void espace() {
  char input[100];
  while (1) {
    // Saisir la taille de l'espace de stockage
    printf("Taille de l'espace de stockage : ");
	fgets(input, 100, stdin);
    // Si l'entrée est un entier
    if (check_integer(input)) {
      // Convertir l'entrée en entier et on l'enregistre dans la variable `stockage`
      sscanf(input, "%d", &stockage);
      break;
    }
    // Si l'entrée n'est pas un entier, on affiche un message d'erreur et on continue la boucle
    else printf("\n Entrée non valide, réessayer S'il vous plaît.\n\n");
  }
}

