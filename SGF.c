#include "SGF_IMPL.h"

int main(int argc, char *argv[]) {
	
	espace();
	TSysteme systeme = init();
	
	printf("\n...Arbre initialisé...\n\n");
	
	command(systeme);

	return 0;
}