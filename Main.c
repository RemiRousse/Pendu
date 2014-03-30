#include"Main.h"

void main()
{
	// Version 2 : Ajout de la gestion d'un dicitonnaire dans un fichier
	// **Il y a TOUJOURS des ameliorations en cours de développement (même si pour le moment je vois pas trop)... KEEP SMILE**

	char motSecret[Taille_Tableau] = {'\0'}; //Va contenir le mot secret, parmi les mots du dictionnaire (Dictionnaire.txt)
	char lettreTrouvee[Taille_Tableau] = {'\0'}; // lettreTrouve[i] = 1 si la ieme lettre du mot secret a été trouvé, 0 si elle n'a pas été trouvée, '\0' si le mot secret est terminé
	char chaineVide[Taille_Tableau] = {'\0'}; // chaine qui reste vide, sert simplement à réinitialiser motSecret et lettreTrouvee au debut de chaque partie
	char maLettre = 0;
	char recommence = 0;
	int trouveLettre = 0;
	int coupsRestants = 10;
	int victoire = 0;
	int fichierOuvert = 0;

	do
	{
		//On réinitialise les variables pour les prochaines parties
		strcpy(chaineVide, motSecret);
		strcpy(chaineVide, lettreTrouvee);
		victoire = 0;
		coupsRestants = 10;

		system("cls");
		printf("BIENVENUE DANS LE PENDU !");
		printf("\n\nVous avez droit a 10 erreurs pour trouver le mot");
		printf("\n\nA vous de jouer ! \n\n");

		fichierOuvert = Dictionnaire(motSecret); //On va aller remplir motSecret par un des mots de Dictionnaire.txt dans la fonction dictionnaire
		if (fichierOuvert == 0) //Si le fichier a bien été ouvert, un mot a été choisi
		{
			//On peut alors commencer le jeu

			//Initialise le tableau lettreTrouvee : passe à 0 les X 1eres lettres (X : nombre de lettres du mot secret)
			InitialiseLettreTrouvee(lettreTrouvee, motSecret);

			while (coupsRestants >= 0 && victoire == 0) //Tant qu'on n'a pas perdu, ou que le mot n'est pas trouvé
			{
				printf("\n\n");
				system("pause");
				system("cls");
				printf("   *** JEU DU PENDU ***\n");
				printf(" ________________________\n");

				//Affiche le nombre de coups restants
				printf("\n\nIl vous reste %d coups", coupsRestants);

				//Affiche le mot secret, avec les lettres déjà trouvées démasquées
				printf("\nQuel est le mot secret ?  ");
				AfficheMotSecret(motSecret, lettreTrouvee);

				//Saisie d'une lettre
				printf("\nSaisir une lettre : ");
				maLettre = LireCaractere();

				//Recherche de la lettre dans le mot
				trouveLettre = OccurenceCarChaine(motSecret, maLettre, lettreTrouvee);

				//Si la lettre est présente
				if (trouveLettre != 0) //On l'ajoute dans les lettres trouvées
				{
					printf("Bravo ! La lettre \"%c\" est bien dans le mot cache !", maLettre);
					victoire = Gagne(motSecret, lettreTrouvee);
				}
				//Si la lettre n'est pas présente
				else
				{
					printf("Dommage, la lettre \"%c\" n'est pas dans le mot cache !", maLettre);

					//On diminue le nombre de coups restants
					coupsRestants--;
				}

			}

			if (victoire == 1) //L'utilisateur a gagné la partie
			{
				printf("\n\n\nVICTOIRE !\n");
				printf("Le mot etait bien : ");
				AfficheMotSecret(motSecret, lettreTrouvee);
			}
			else //L'utilisateur a perdu toutes ses vies sans avoir trouvé le mot
			{
				printf("\n\n\nLOSER, T AS PERDU !\n");
				printf("Le mot secret etait... ");
				AfficheMotSecret(motSecret, lettreTrouvee);
			}

			printf("\n\n\n");
			system("pause");

		//On demande s'il veut recommencer UNIQUEMENT SI le fichier a pu être ouvert	
		printf("\n\nVoulez-vous recommencer ? (O/N)");
		printf("\nVotre choix : ");
		scanf("%c", &recommence);
		recommence = toupper(recommence);

		}
		else //Le fichier n'a pas pu être ouvert
		{
			//On ferme l'application, si ça marche pas ça marche pas (et pis c'est tout)
			printf("\nErreur : Le dictionnaire n a pas pu etre charge");
			printf("\nReesayez plus tard, ou contactez le super programmeur de cette application\n\n");
			system("pause");

		}

	} while (recommence == 'O' && fichierOuvert == 0);

	system("cls");
	printf("\n\tA plus tard !\n\n");
	system("pause");

}

//Initialise la chaine trouvee
void InitialiseLettreTrouvee(char* trouvee, char* secret)
{
	int i = 0;

	while (secret[i] != '\0') //Tant qu'on n'est pas arrivé à la fin du mot secret
	{
		trouvee[i] = '0'; //On définit les caracteres de trouvee à 0

		i++;
	}
}

char LireCaractere()
{
	char caractere = 0;

	//Permet de vider le buffer clavier si ça n'a pas été fait avant
	do
	{
		caractere = getchar();
	} while (caractere == '\n');

	caractere = toupper(caractere); //Passage du caractere en majuscule

	//Vide le buffer clavier : ici, supprime le '\n' entré pour valider la saisie du caractere
	while (getchar() != '\n');

	return caractere; //on retourne le 1er caratere lu, en majuscule


}

int OccurenceCarChaine(char* strg, char c, char* trouvee)
{
	int i = 0, j = 0;
	int trouve = 0;

	while (strg[i] != '\0') //On parcourt les caracteres de la chaine tant qu'on n'est pas arrivés à la fin
	{
		if (strg[i] == c) //Si on trouve le caractere
		{
			trouvee[i] = '1'; //On passe la ieme case de trouvee à 1
			trouve = 1;
		}
		i++;
	}
	return trouve;
}

void AfficheMotSecret(char* secret, char* trouvee)
{
	int i = 0;

	while (secret[i] != '\0')
	{
		if (trouvee[i] == '1') //Si la ieme lettre est trouvée
		{
			printf("%c", secret[i]); //On l'affiche
		}
		else
		{
			printf("*"); //Sinon on la laisse masquée
		}
		i++;
	}
}

int Gagne(char* secret, char* trouvee)
{
	int tailleSecret = strlen(secret);
	int nbLettresTrouvees = 0;
	int i = 0;

	while (trouvee[i] != '\0')
	{
		if (trouvee[i] == '1') //On compte le nombre de lettres trouvées
		{
			nbLettresTrouvees++;
		}
		i++;
	}

	if (tailleSecret == nbLettresTrouvees) //Si on a trouvé autant de lettres qu'en contient le mot
	{
		return 1;
	}

	return 0;
}