#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include"Dictionnaire.h"

#define Taille_Tableau 200

void InitialiseLettreTrouvee(char* trouvee, char* secret);
char LireCaractere();
int OccurenceCarChaine(char* strg, char c, char* trouvee);
void AfficheMotSecret(char* secret, char* trouvee);
int Gagne(char* trouvee);