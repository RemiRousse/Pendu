#include"Dictionnaire.h"

int Dictionnaire (char* motChoisi)
{
	//Le dictionnaire contient plusieurs mots
	//Tous �crits en majuscule et sans accent
	//Un mot par ligne

	FILE* dictionnaire = NULL;
	int nbMots = 0;
	int numeroMotChoisi = 0;

	//Initialise la fonction de g�n�ration d'un nombre al�atoire
	srand(time(NULL));

	//Ouverture du fichier Dictionnaire.txt contenant les diff�rents mots
	dictionnaire = fopen(".\\..\\Data\\Dictionnaire.txt", "r");

	//dictionnaire = fopen("C:\\Users\\Mousse\\Documents\\Visual Studio 2012\\Projects\\Pendu\\Data\\Dictionnaire.txt", "r");

	if (dictionnaire != NULL) //Si l'ouverture du fichier a r�ussi
	{
		//On compte le nombre de mots dans le fichier
		nbMots = CompteNombreMots(dictionnaire);

		//On pioche au hasard un num�ro de ligne
		numeroMotChoisi = Aleatoire(1, nbMots);

		//On selectionne le mot de la ligne pioch�e
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

	rewind(fichier); //On replace le curseur au d�but du fichier

	//On va enregistrer dans motChoisi chaque ligne, une par une, en rempla�ant � chaque fois la ligne pr�c�dente
	while (i >= 0)
	{
		fgets(motChoisi, 200, fichier); //Le mot choisi est bien enregistr�, mais il y a aussi le '\n' de fin de ligne !
		i--; //On d�cr�mente le nombre de lignes � parcourir
	}

	while (motChoisi[j] != '\0') //Tant qu'on n'est pas � la fin de la ligne
	{
		if (motChoisi[j] == '\n') //Si le caractere est un '\n'
		{
			motChoisi[j] = '\0'; //On le supprime
		}
		j++;
	}
}