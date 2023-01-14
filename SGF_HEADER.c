#include "SGF_HEADER.h"

void ls(TSysteme arbre, TChemin chemin, char *name) {
  // Traverse the file system tree to find the specified directory
  TSysteme currentNode = arbre;
  TChemin currentPath = chemin;
  if (currentPath->Suivant == NULL && strcmp(currentPath->Nom, "/") == 0){
  	currentNode = arbre;
  }
  else{
 	 while (currentPath != NULL) {
   	 bool found = false;
   	 TSysteme child = currentNode->Fils;
  	  while (child != NULL) {
    	  if (strcmp(child->Nom, currentPath->Nom) == 0) {
     	   currentNode = child;
     	   found = true;
    	    break;
   	   }
    	  child = child->Frere;
  	  }
  	  if (!found) {
    	  printf("\nRépertoire \"%s\" n'existe pas.\n", name);
    	  return;
    	}
  	  currentPath = currentPath->Suivant;
  	}
  }

  // Search for a child with the specified name in the directory
  bool found = false;
  TSysteme child = currentNode->Fils;
  while (child != NULL) {
    if (strcmp(child->Nom, name) == 0) {
      found = true;
      break;
    }
    child = child->Frere;
  }
  if (!found) {
    printf("\nRépertoire \"%s\" n'existe pas.\n", name);
    return;
  }

  // List the contents of the child
  if (child->Rep == 1) {
    // If the child is a directory, list its children
    printf("\n|%s\n", child->Nom);
    TSysteme grandchild = child->Fils;
    if(grandchild == NULL) printf(" |(vide)\n");
    while (grandchild != NULL) {
      printf(" |%s\n", grandchild->Nom);
      grandchild = grandchild->Frere;
    }
  } else {
    // If the child is a file, print its size in bytes
    printf("\n%s (%d bytes) : est un fichier!\n", child->Nom, child->Taille);
  }
}

bool rm(TSysteme *arbre, TChemin chemin, char *name) {
  // Traverse the file system tree to find the specified directory
  TSysteme currentNode = *arbre;
  TChemin currentPath = chemin;
  if (currentPath->Suivant == NULL && strcmp(currentPath->Nom, "/") == 0){
  	currentNode = *arbre;
  }
  else{
  	while (currentPath != NULL) {
  	  bool found = false;
   	 TSysteme child = currentNode->Fils;
  	  while (child != NULL) {
    	  if (strcmp(child->Nom, currentPath->Nom) == 0) {
      	  currentNode = child;
     	   found = true;
     	   break;
     	 }
   	   child = child->Frere;
   	 }
   	 if (!found) {
     	 printf("\"%s\" n'existe pas.\n", name);
    	  return false;
   	 }
  	  currentPath = currentPath->Suivant;
  	}
  }

  // Search for a child with the specified name in the current directory
  TSysteme *prevChild = &currentNode->Fils;
  TSysteme child = currentNode->Fils;
  while (child != NULL) {
    if (strcmp(child->Nom, name) == 0 || strcmp(name, "*") == 0) {
      break;
    }
    prevChild = &child->Frere;
    child = child->Frere;
  }
  if (child == NULL) {
    printf("\"%s\" n'existe pas!\n", name);
    return false;
  }

  // Remove the child from the file system tree
  if (strcmp(name, "*") == 0){
    while(child != NULL){
      *prevChild = child->Frere;
      free(child);
      child = child->Frere;
    }
  }
  else {
    *prevChild = child->Frere;
    free(child);
  }
  return true;
}

bool mk(TSysteme *arbre, TChemin chemin, char *nom, int rep, int taille) {
  // Traverse the file system tree to find the parent directory of the new directory
  TSysteme currentNode = *arbre;
  if (chemin->Suivant == NULL && strcmp(chemin->Nom, "/") == 0){
  	currentNode = *arbre;
  }
  else{
    while (chemin != NULL) {
      // Check if the current node has a child with the current name
      bool found = false;
      TSysteme child = currentNode->Fils;
      while (child != NULL) {
        if (strcmp(child->Nom, chemin->Nom) == 0) {
          // If the child is found, move to the next name
          currentNode = child;
          found = true;
          break;
        }
        child = child->Frere;
      }
      if (!found) {
        // If the current name is not found in the children of the current node, the path is invalid
        return false;
      }
      chemin = chemin->Suivant;
    }
  
    if(currentNode->Rep == 0){
    	 printf("\n\"%s\" n'a pas été ajouté!\n", nom);
    	 return false;
    }
  }

  // Check if the parent directory already has a child with the same name as the new directory
  TSysteme child = currentNode->Fils;
  while (child != NULL) {
    if (strcmp(child->Nom, nom) == 0) {
      // If a child with the same name is found, return an error
      printf("\nError: %s deja existe\n", nom);
      return false;
    }
    child = child->Frere;
  }

  // Create the new directory and add it as a child of the parent
  TSysteme new_n = NULL;
  if(rep == 1) {
  	new_n = creerNoeudTSysteme(nom, 1, 0);
  }
  else if(rep == 0){
  	new_n = creerNoeudTSysteme(nom, 0, taille);
  }
  new_n->Frere = currentNode->Fils;
  currentNode->Fils = new_n;
  return true;
}

TSysteme getNodeByName(TSysteme arbre, TChemin chemin, char *nom) {
  // Follow the path to the node at the end of the path
  TSysteme currentNode = arbre;
  if (chemin->Suivant == NULL && strcmp(chemin->Nom, "/") == 0){
  	currentNode = arbre;
  }
  else{
    while (chemin != NULL) {
      bool found = false;
      TSysteme child = currentNode->Fils;
      while (child != NULL) {
        if (strcmp(child->Nom, chemin->Nom) == 0) {
          currentNode = child;
          found = true;
          break;
        }
        child = child->Frere;
      }
      if (!found) {
        printf("\nError: Chemin n'existe pas\n");
        return NULL;
      }
      chemin = chemin->Suivant;
    }
  }

  // Search for the node with the given name among the children of the current node
  TSysteme foundNode = NULL;
  TSysteme child = currentNode->Fils;
  while (child != NULL) {
    if (strcmp(child->Nom, nom) == 0 || strcmp(nom, "*") == 0) {
      foundNode = child;
      break;
    }
    child = child->Frere;
  }
  if (foundNode == NULL) {
      printf("\nError: %s n'existe pas\n", nom);
    return NULL;
  }

  // Make a copy of the found node and set its siblings to NULL
  TSysteme copy = creerNoeudTSysteme(foundNode->Nom, foundNode->Rep, foundNode->Taille);
  copy->Fils = foundNode->Fils;
  if(strcmp(nom, "*") != 0) copy->Frere = NULL;
  else copy->Frere = foundNode->Frere;

  return copy;
}

TChemin which(TSysteme arbre, char* nom) {
  if (strcmp(arbre->Nom, nom) == 0) {
    TChemin path = NULL;
    addToPath(&path, arbre->Nom);
    return path;
  }
  if (arbre->Rep == 1) {
    TSysteme child = arbre->Fils;
    while (child != NULL) {
      TChemin path = which(child, nom);
      if (path != NULL) {
        addToPath(&path, arbre->Nom);
        return path;
      }
      child = child->Frere;
    }
  }
  return NULL;
}

void addToPath(TChemin *chemin, char *nom) {
  TChemin c_node = creerNoeudTChemin(nom);
  c_node->Suivant = *chemin;
  *chemin = c_node;
}

void search(TSysteme systeme, char* nom, TSysteme parent, TSysteme original) {
  if (strcmp(systeme->Nom, nom) == 0) {
    TChemin ch = which(original, parent->Nom);
    printf("%s existe dans : ", nom);
    afficherTChemin(ch);
    printf("\n");
  }
 if (systeme->Rep == 1) {
    TSysteme child = systeme->Fils;
    while (child != NULL) {
      search(child, nom, systeme, original);
      child = child->Frere;
    }
  }
}

bool ajouterFils(TSysteme arbre, TChemin destinationChemin, TSysteme child) {
  // Follow the path to the destination directory
  TSysteme destination = arbre;
  if (destinationChemin->Suivant == NULL && strcmp(destinationChemin->Nom, "/") == 0){
  	destination = arbre;
  }
  else{
    while (destinationChemin != NULL) {
      // Check if the current directory has a child with the current name
      bool found = false;
      TSysteme currentChild = destination->Fils;
      while (currentChild != NULL) {
        if (strcmp(currentChild->Nom, destinationChemin->Nom) == 0) {
          // If the child is found, move to the next name
          destination = currentChild;
          found = true;
          break;
        }
        currentChild = currentChild->Frere;
      }
      if (!found) {
        // If the current name is not found in the children of the current directory, the path is invalid
        printf("\nError: Destination n'existe pas\n");
        return false;
      }
      destinationChemin = destinationChemin->Suivant;
    }
  }

  // Check if the destination directory already has a child with the same name as the source directory
  TSysteme currentChild = destination->Fils;
  while (currentChild != NULL) {
    if (strcmp(currentChild->Nom, child->Nom) == 0) {
      printf("\nError: %s deja existe\n",child->Nom);
      return false;
    }
    currentChild = currentChild->Frere;
  }

  // Add the child to the list of children of the destination directory
  child->Frere = destination->Fils;
  destination->Fils = child;

  return true;
}

int calcSize(TSysteme arbre) {
  if (arbre->Rep == 0) {
    return arbre->Taille;
  }
 
  int totalSize = 0;
  TSysteme child = arbre->Fils;
  while (child != NULL) {
    totalSize += calcSize(child);
    child = child->Frere;
  }
  return totalSize;
}


TChemin stringToTChemin(TSysteme arbre, char *chemin) {
  if(strcmp(chemin, "/")==0) {
  	TChemin root = creerNoeudTChemin("/");
  	return root;
  }
  // Make a copy of the path string
  char *cheminCopy = strdup(chemin);

  // Split the path into its component names
  char *nom;
  char *delimiter = "/";
  nom = strtok(cheminCopy, delimiter);

  // Traverse the file system tree to find the nodes corresponding to each name in the path
  TSysteme currentNode = arbre;
  TChemin path = NULL;
  while (nom != NULL) {
    // Check if the current node has a child with the current name
    bool found = false;
    TSysteme child = currentNode->Fils;
    while (child != NULL) {
      if (strcmp(child->Nom, nom) == 0) {
        // If the child is found, add it to the path and move to the next name
        currentNode = child;
        TChemin newNode = creerNoeudTChemin(currentNode->Nom);
        newNode->Suivant = path;
        path = newNode;
        found = true;
        break;
      }
      child = child->Frere;
    }
    if (!found) {
      // If the current name is not found in the children of the current node, the path is invalid
      //freeTChemin(path);
      return NULL;
    }
    nom = strtok(NULL, delimiter);
  }

  // Reverse the linked list so that it is in the correct order
  TChemin reversedPath = NULL;
  while (path != NULL) {
    TChemin temp = path->Suivant;
    path->Suivant = reversedPath;
    reversedPath = path;
    path = temp;
  }

  return reversedPath;
}


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


void afficherTChemin(TChemin chemin) {
  // Print the names of all the nodes in the path
  if(strcmp(chemin->Nom, "/")==0 && chemin->Suivant == NULL){
  	printf("%s",chemin->Nom);
  	return;
  }
  else{
  chemin = chemin->Suivant;
 	 printf("/");
   while (chemin != NULL) {
  	  printf("%s/", chemin->Nom);
   	 chemin = chemin->Suivant;
 	 }
 	 
  }
}


void afficherTSysteme(TSysteme arbre, int niveau) {
  // Print the current node
  for (int i = 0; i < niveau; i++) printf(" ");
  printf("|");
  //for (int i = 0; i < niveau; i++) printf("-");
  printf("%s", arbre->Nom);
  // If the current node is a file, print its size in bytes
  if (arbre->Rep == 0) printf(" (%d bytes)", arbre->Taille);
  printf("\n");
  // If the current node is a directory, recursively traverse its children
  if (arbre->Rep == 1) {
    TSysteme child = arbre->Fils;
    while (child != NULL) {
      afficherTSysteme(child, niveau + 1);
      child = child->Frere;
    }
  }
}


void initialiserTSysteme(TSysteme *arbre) {
    // Create the root node
    *arbre = creerNoeudTSysteme("/", 1, 0);
  
    // Create aditional nodes
    TSysteme bin = creerNoeudTSysteme("bin", 1, 0);
    TSysteme home = creerNoeudTSysteme("home", 1, 0);
    TSysteme root = creerNoeudTSysteme("root", 1, 0);
    TSysteme run = creerNoeudTSysteme("run", 1, 0);
    TSysteme univ = creerNoeudTSysteme("Univ8mai1945", 1, 0);
    TSysteme bureau = creerNoeudTSysteme("Bureau", 1, 0);
    TSysteme doc = creerNoeudTSysteme("Documents", 1, 0);
    TSysteme tel = creerNoeudTSysteme("Telechargements", 1, 0);

    // Création des liens entre les noeuds
    (*arbre)->Fils = bin;
    home->Fils = univ;
    univ->Fils = bureau;
    bin->Frere = home;
    home->Frere = root;
    root->Frere = run;
    bureau->Frere = doc;
    doc->Frere = tel;
}

bool check(char *input) {
  for (int i = 0; input[i] != '\0' && input[i] != '\n'; i++) if (!isdigit(input[i])) return false;
  return true;
}

TSysteme creerNoeudTSysteme(char *nom, int rep, int taille) {
  TSysteme nouveauNoeud = (TSysteme)malloc(sizeof(noeudArb));
  strcpy(nouveauNoeud->Nom, nom);
  nouveauNoeud->Rep = rep;
  nouveauNoeud->Taille = taille;
  nouveauNoeud->Fils = NULL;
  nouveauNoeud->Frere = NULL;
  return nouveauNoeud;
}

TChemin creerNoeudTChemin(char *nom) {
  TChemin nouveauNoeud = (TChemin)malloc(sizeof(noeudCh));
  strcpy(nouveauNoeud->Nom, nom);
  nouveauNoeud->Suivant = NULL;
  return nouveauNoeud;
}


void saveNode(FILE *fp, TSysteme node) {
  // Write the node's data to the file
  fwrite(node->Nom, sizeof(node->Nom), 1, fp);
  fwrite(&node->Rep, sizeof(node->Rep), 1, fp);
  fwrite(&node->Taille, sizeof(node->Taille), 1, fp);
}

void savePreorder(FILE *fp, TSysteme root) {
  if (root == NULL) return;
  
  // Write the current node to the file
  saveNode(fp, root);

  // Recursively save the children of the current node
  TSysteme child = root->Fils;
  while (child != NULL) {
    savePreorder(fp, child);
    child = child->Frere;
  }
}

TSysteme restorePreorder(FILE *fp) {
  // Read the current node's data from the file
  char nom[16];
  int rep;
  int taille;
  fread(nom, sizeof(nom), 1, fp);
  fread(&rep, sizeof(rep), 1, fp);
  fread(&taille, sizeof(taille), 1, fp);
  
  // Create a new TSysteme node with the data
  TSysteme node = creerNoeudTSysteme(nom, rep, taille);
  
  // If the node is a directory, restore its children
  if (rep == 1) {
    TSysteme child;
    while ((child = restorePreorder(fp)) != NULL) {
      // Link the child to the current node
      child->Frere = node->Fils;
      node->Fils = child;
    }
  }
  
  return node;
}

void saveFileSystem(TSysteme root, const char *filename) {
  FILE *fp = fopen(filename, "w");
  if (fp == NULL) {
    // Handle error
  }
  savePreorder(fp, root);
  fclose(fp);
}

TSysteme restoreFileSystem(FILE *fp) {
  TSysteme systeme = (TSysteme)malloc(sizeof(noeudArb));
  printf("Name : %s", systeme->Nom);
  if(systeme == NULL) return NULL;

  if(fread(systeme, sizeof(noeudArb), 1, fp) != 1){
    free(systeme);
    return NULL;
  }
  

  if(systeme->Rep == 1){
    TSysteme current = (TSysteme)malloc(sizeof(noeudArb));
    current = systeme;
    TSysteme child = (TSysteme)malloc(sizeof(noeudArb));
    child = restoreFileSystem(fp);
    current->Fils = child;
    while(child != NULL){
      current = child;
      child = restoreFileSystem(fp);
      current->Frere = child;
    }
  }
  else return NULL;

  return systeme;
}