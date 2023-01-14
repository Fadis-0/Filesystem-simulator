#include "SGF_HEADER.h"

int main() {
  
  int espace, choix;
  char input[16];
  TSysteme arbre = NULL;
  
  printf("1 : Recuperer la structure stocke\n");
  printf("2 : Initialiser la structure par defaut.\n");

  printf("\nchoix : ");
  scanf("%d", &choix);

  if(choix == 1){
    FILE *fp = NULL;
    fp = fopen("arbre.txt", "rb");
    if(fp != NULL){
    	arbre = restoreFileSystem(fp);
    	fclose(fp);
    }
    else initialiserTSysteme(&arbre);
    
  }
  else if(choix == 2){
    // Create the root node and some child nodes
    initialiserTSysteme(&arbre);
    printf("\narbre initialiser par defaut\n");
  }

  while (true) {
    printf("\nTaille (bytes) : ");
	  scanf("%s", input); 
    if (check(input)) {
      sscanf(input, "%d", &espace);
      break;
    }
    else printf("Entrée non valide!\n\n");
  }
  
  
  int taille;
  char com[16];
  char a_node[16];
  char n_node[16];
  char n_nodes[320];
  char *copy;
  char cible[16];
  TChemin path = NULL;
  TChemin c_path = NULL;

  while(true){
  	int totalSize = calcSize(arbre);
  	system("cls || clear");
  	printf("------------------------\n");
  	printf("Occupé: %d (bytes)\nLibre : %d (bytes)\nTotal : %d (bytes)", totalSize, espace-totalSize, espace);
  	printf("\n------------------------\n\n");
  	afficherTSysteme(arbre, 0);
  	printf("\n------------------------\n\n");
  	
  	printf("$_operation : ");
  	scanf("%s", com); 
  	
  	if(strcmp(com, "ls")==0){
  		printf("\nAdresse de Repertoire : ");
  		scanf("%s", a_node);
  		printf("Nom de Repertoire : ");
  		scanf("%s", n_node);
  		
  		path = stringToTChemin(arbre, a_node);
  		
  		if(path == NULL || a_node[0] != '/') printf("\nChemin n'existe pas\n");
  		else ls(arbre, path, n_node);
  		
  		free(path);
  		printf("\n\nTaper [Entré] pour continue...");
  		getchar();
  		getchar();
  	}
    else if(strcmp(com, "ls+")==0){
      printf("\nAdresse de Repertoire : ");
      scanf("%s", a_node);
      printf("Nom de Repertoire : ");
      scanf("%s", n_node);
      
      path = stringToTChemin(arbre, a_node);
      
      if(path == NULL || a_node[0] != '/') printf("\nChemin n'existe pas\n");
      else {
          printf("\n");
          TSysteme node = getNodeByName(arbre, path, n_node);
          afficherTSysteme(node, 0);
      }
      
      free(path);
      printf("\n\nTaper [Entré] pour continue...");
      getchar();
      getchar();
    }
  	else if (strcmp(com, "rm") == 0){
      printf("\nAdresse : ");
      scanf("%s", a_node);
      getchar();
      printf("Noms (1, plusieurs, *) : ");
      scanf("%[^\n]", n_nodes);
      path = stringToTChemin(arbre, a_node);

      if(path == NULL || a_node[0] != '/') printf("\nChemin n'existe pas\n");
      else {
        char *noms[320];
        for (int i = 0; i < 320; i++) noms[i] = NULL; 
        copy = strdup(n_nodes);
        int num_noms = getMultiple(copy, ' ', noms);
        
        printf("\n");

        for (int i = 0; i < num_noms; i++) {
          bool success = rm(&arbre, path, noms[i]);
          if (strcmp(noms[i], "*") == 0){
            printf("le contenu de %s a été supprimé avec succès.\n", a_node);
            break;
          }
          if (success) printf("\"%s\" a été supprimé avec succès.\n", noms[i]);
        } 
      } 
      
      free(path);
      printf("\n\nTaper [Entré] pour continue...");
      getchar();
      getchar();
    }
  	else if(strcmp(com, "mkdir")==0){
  		printf("\nAdresse de repertoire : ");
  		scanf("%s", a_node);
  		printf("Nom de repertoire : ");
  		scanf("%s", n_node);
  		
  		path = stringToTChemin(arbre, a_node);
  		
  		if(path == NULL || a_node[0] != '/') printf("\nChemin n'existe pas\n");
  		else {
  			bool success = mk(&arbre, path, n_node, 1, 0);
  			if (success) printf("\n\"%s\" a été ajouté avec succès.\n", n_node);
  		}
  		
  		free(path);
  		printf("\n\nTaper [Entré] pour continue...");
  		getchar();
  		getchar();
  	}
  	else if(strcmp(com, "mkfile")==0){
  		printf("\nAdresse de fichier : ");
  		scanf("%s", a_node);
  		printf("Nom de fichier : ");
  		scanf("%s", n_node);
      
      char in[16];
      while (true) {
        printf("Taille de fichier : ");
        scanf("%s", in); 
        if (check(in)) {
          sscanf(in, "%d", &taille);
          break;
        }
        else printf("Entrée non valide!\n\n");
      }

  		path = stringToTChemin(arbre, a_node);
  		
  		if(path == NULL || a_node[0] != '/') printf("\nChemin n'existe pas\n");
  		else {
  			if (totalSize+taille <=   espace){
          bool success = mk(&arbre, path, n_node, 0, taille);
          if (success) printf("\n\"%s\" a été ajouté avec succès.\n", n_node);
        }
        else printf("\nEspace de stockage est plein!\n");
  		}
  		
  		free(path);
  		printf("\n\nTaper [Entré] pour continue...");
  		getchar();
  		getchar();
  	}
  	else if(strcmp(com, "cpdir")==0){
      printf("\nAdresse de repertoire : ");
      scanf("%s", a_node);
      printf("Nom de repertoire : ");
      scanf("%s", n_node);
      printf("Adresse cible : ");
      scanf("%s", cible);
      
      path = stringToTChemin(arbre, a_node);
      c_path = stringToTChemin(arbre, cible);

      
      if(path == NULL || a_node[0] != '/') printf("\nChemin source n'existe pas\n");
      else {
        if(c_path == NULL || cible[0] != '/') printf("\nChemin cible n'existe pas\n");
        else{          
          TSysteme node = getNodeByName(arbre, path, n_node);
          if(node != NULL){
            if(totalSize+calcSize(node) <= espace){
              bool success = ajouterFils(arbre, c_path, node);
              if(success) printf("\n\"%s\" a été ajouté avec succès dans %s.\n", n_node, cible);
            }
            else printf("\nEspace de stockage est plein!\n");
          }
        }
      }

      free(path);
      free(c_path);
      printf("\n\nTaper [Entré] pour continue...");
      getchar();
      getchar();
    }
    else if(strcmp(com, "cpfile")==0){
      printf("\nAdresse de fichier : ");
      scanf("%s", a_node);
      printf("Nom de fichier : ");
      scanf("%s", n_node);
      printf("Adresse cible : ");
      scanf("%s", cible);
      
      path = stringToTChemin(arbre, a_node);
      c_path = stringToTChemin(arbre, cible);

      
      if(path == NULL || a_node[0] != '/') printf("\nChemin source n'existe pas\n");
      else {
        if(c_path == NULL || cible[0] != '/') printf("\nChemin cible n'existe pas\n");
        else{
          TSysteme node = getNodeByName(arbre, path, n_node);
          if(node != NULL){
            if(totalSize+node->Taille <= espace){
              bool success = ajouterFils(arbre, c_path, node);
              if(success) printf("\n\"%s\" a été ajouté avec succès dans %s.\n", n_node, cible);
            }
            else printf("\nEspace de stockage est plein!\n");
          }
        }
      }

      
      free(path);
      free(c_path);
      printf("\n\nTaper [Entré] pour continue...");
      getchar();
      getchar();  
    }

    else if (strcmp(com, "cp") == 0){
      printf("\nAdresse source : ");
      scanf("%s", a_node);
      getchar();
      printf("Noms (1, plusieurs, *) : ");
      scanf("%[^\n]", n_nodes);
      getchar();
      printf("Adresse cible : ");
      scanf("%s", cible);
      
      path = stringToTChemin(arbre, a_node);
      c_path = stringToTChemin(arbre, cible);

      if(path == NULL || a_node[0] != '/') printf("\nChemin source n'existe pas\n");
      else {
        if(c_path == NULL || cible[0] != '/') printf("\nChemin cible n'existe pas\n");
        else{
          char *noms[320];
          for (int i = 0; i < 320; i++) noms[i] = NULL; 
          copy = strdup(n_nodes);
          int num_noms = getMultiple(copy, ' ', noms);
          
          printf("\n");

          for (int i = 0; i < num_noms; i++) {
            TSysteme node = getNodeByName(arbre, path, noms[i]);
            if(node != NULL){
              if (strcmp(noms[i], "*") == 0){
                while(node != NULL){
                  TSysteme n = getNodeByName(arbre, path, node->Nom);
                  if(calcSize(arbre)+calcSize(n) <= espace){
                    bool success = ajouterFils(arbre, c_path, n);
                  }
                  else printf("\"%s\" n'a pas été copié : Espace de stockage est plein!\n", n->Nom);
                  node = node->Frere;
                }
                printf("le contenu de %s a été copié avec succès dans %s.\n", a_node, cible);
                break;
              }
              if(calcSize(arbre)+calcSize(node) <= espace){
                bool success = ajouterFils(arbre, c_path, node);
                if (success) printf("\"%s\" a été copié avec succès.\n", noms[i]);
              }
              else printf("\"%s\" n'a pas été copié : Espace de stockage est plein!\n", noms[i]);
            }            
          }
        }
      } 
      
      free(path);
      printf("\n\nTaper [Entré] pour continue...");
      getchar();
      getchar();
    }
  
    else if(strcmp(com, "exist")==0){
      printf("\nNoms (1, plusieurs) : ");
      getchar();
      scanf("%[^\n]", n_nodes);
      
      
      char *noms[320];
      for (int i = 0; i < 320; i++) noms[i] = NULL; 
      copy = strdup(n_nodes);
      int num_noms = getMultiple(copy, ' ', noms);
        
      for (int i = 0; i < num_noms; i++) {
        printf("\n");
        search(arbre, noms[i], arbre, arbre);        
      } 
       
    
      printf("\n\nTaper [Entré] pour continue...");
  	  getchar();
  	  getchar();
    }
    else if(strcmp(com, "save")==0){
      saveFileSystem(arbre, "arbre.dat");
      break;
    } 
    else{
  		printf("\ncommande n'existe pas!");
  		printf("\n\nTaper [Entré] pour continue...");
  		getchar();
  		getchar();
  		continue;
    }
    printf("\n");
  }
  return 0;
}