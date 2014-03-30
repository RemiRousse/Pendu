#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<time.h>

int Dictionnaire (char* motChoisi);
int CompteNombreMots(FILE* fichier);
int Aleatoire(int min, int max);
void SelectMotChoisi(FILE* fichier, int numMot, char* motChoisi);