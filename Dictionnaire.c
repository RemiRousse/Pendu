#include"Dictionnaire.h"

int Dictionnaire (char* motChoisi)
{
	//Le dictionnaire contient plusieurs mots
	//Tous écrits en majuscule et sans accent
	//Un mot par ligne

	FILE* dictionnaire = NULL;
	int nbMots = 0;
	int numeroMotChoisi = 0;

	//Initialise la fonction de génération d'un nombre aléatoire
	srand(time(NULL));

	//Ouverture du fichier Dictionnaire.txt contenant les différents mots
	dictionnaire = fopen(".\\..\\Data\\Dictionnaire.txt", "r");

	//dictionnaire = fopen("C:\\Users\\Mousse\\Documents\\Visual Studio 2012\\Projects\\Pendu\\Data\\Dictionnaire.txt", "r");

	if (dictionnaire != NULL) //Si l'ouverture du fichier a réussi
	{
		//On compte le nombre de mots dans le fichier
		nbMots = CompteNombreMots(dictionnaire);

		//On pioche au hasard un numéro de ligne
		numeroMotChoisi = Aleatoire(1, nbMots);

		//On selectionne le mot de la ligne piochée
		SelectMotChoisi(dictionnaire, numeroMotChoisi, motChoisi);
	}
	else
	{
		//Le fichier n'est pas ouvert : on quittera l'application

		return 1;
	}


	return 0;
}

int CompteNombreMots(FILE* fichier)
{

}

int Aleatoire(int min, int max)
{
	return (rand() % (max - min + 1)) + min;
}

void SelectMotChoisi(FILE* fichier, int numMot, char* motChoisi)
{
	int i = numMot - 1; //i est le nombre de lignes qu'on doit parcourir avant d'arriver sur la bonne
	int j = 0;

	rewind(fichier); //On replace le curseur au début du fichier

	//On va enregistrer dans motChoisi chaque ligne, une par une, en remplaçant à chaque fois la ligne précédente
	while (i >= 0)
	{
		fgets(motChoisi, 200, fichier); //Le mot choisi est bien enregistré, mais il y a aussi le '\n' de fin de ligne !
		i--; //On décrémente le nombre de lignes à parcourir
	}

	while (motChoisi[j] != '\0') //Tant qu'on n'est pas à la fin de la ligne
	{
		if (motChoisi[j] == '\n') //Si le caractere est un '\n'
		{
			motChoisi[j] = '\0'; //On le supprime
		}
		j++;
	}
}