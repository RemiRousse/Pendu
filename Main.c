#include"Main.h"

void main()
{
	// Version 2 : Ajout de la gestion d'un dicitonnaire dans un fichier
	// **Il y a TOUJOURS des ameliorations en cours de d�veloppement (m�me si pour le moment je vois pas trop)... KEEP SMILE**

	char motSecret[Taille_Tableau] = {'\0'}; //Va contenir le mot secret, parmi les mots du dictionnaire (Dictionnaire.txt)
	char lettreTrouvee[Taille_Tableau] = {'\0'}; // lettreTrouve[i] = 1 si la ieme lettre du mot secret a �t� trouv�, 0 si elle n'a pas �t� trouv�e, '\0' si le mot secret est termin�
	char chaineVide[Taille_Tableau] = {'\0'}; // chaine qui reste vide, sert simplement � r�initialiser motSecret et lettreTrouvee au debut de chaque partie
	char maLettre = 0;
	char recommence = 0;
	int trouveLettre = 0;
	int coupsRestants = 10;
	int victoire = 0;
	int fichierOuvert = 0;

	do
	{
		//On r�initialise les variables pour les prochaines parties
		strcpy(chaineVide, motSecret);
		strcpy(chaineVide, lettreTrouvee);
		victoire = 0;
		coupsRestants = 10;

		system("cls");
		printf("BIENVENUE DANS LE PENDU !");
		printf("\n\nVous avez droit a 10 erreurs pour trouver le mot");
		printf("\n\nA vous de jouer ! \n\n");

		fichierOuvert = Dictionnaire(motSecret); //On va aller remplir motSecret par un des mots de Dictionnaire.txt dans la fonction dictionnaire
		if (fichierOuvert == 0) //Si le fichier a bien �t� ouvert, un mot a �t� choisi
		{
			//On peut alors commencer le jeu

			//Initialise le tableau lettreTrouvee : passe � 0 les X 1eres lettres (X : nombre de lettres du mot secret)
			InitialiseLettreTrouvee(lettreTrouvee, motSecret);

			while (coupsRestants >= 0 && victoire == 0) //Tant qu'on n'a pas perdu, ou que le mot n'est pas trouv�
			{
				printf("\n\n");
				system("pause");
				system("cls");
				printf("   *** JEU DU PENDU ***\n");
				printf(" ________________________\n");

				//Affiche le nombre de coups restants
				printf("\n\nIl vous reste %d coups", coupsRestants);

				//Affiche le mot secret, avec les lettres d�j� trouv�es d�masqu�es
				printf("\nQuel est le mot secret ?  ");
				AfficheMotSecret(motSecret, lettreTrouvee);

				//Saisie d'une lettre
				printf("\nSaisir une lettre : ");
				maLettre = LireCaractere();

				//Recherche de la lettre dans le mot
				trouveLettre = OccurenceCarChaine(motSecret, maLettre, lettreTrouvee);

				//Si la lettre est pr�sente
				if (trouveLettre != 0) //On l'ajoute dans les lettres trouv�es
				{
					printf("Bravo ! La lettre \"%c\" est bien dans le mot cache !", maLettre);
					victoire = Gagne(motSecret, lettreTrouvee);
				}
				//Si la lettre n'est pas pr�sente
				else
				{
					printf("Dommage, la lettre \"%c\" n'est pas dans le mot cache !", maLettre);

					//On diminue le nombre de coups restants
					coupsRestants--;
				}

			}

			if (victoire == 1) //L'utilisateur a gagn� la partie
			{
				printf("\n\n\nVICTOIRE !\n");
				printf("Le mot etait bien : ");
				AfficheMotSecret(motSecret, lettreTrouvee);
			}
			else //L'utilisateur a perdu toutes ses vies sans avoir trouv� le mot
			{
				printf("\n\n\nLOSER, T AS PERDU !\n");
				printf("Le mot secret etait... ");
				AfficheMotSecret(motSecret, lettreTrouvee);
			}

			printf("\n\n\n");
			system("pause");

		//On demande s'il veut recommencer UNIQUEMENT SI le fichier a pu �tre ouvert	
		printf("\n\nVoulez-vous recommencer ? (O/N)");
		printf("\nVotre choix : ");
		scanf("%c", &recommence);
		recommence = toupper(recommence);

		}
		else //Le fichier n'a pas pu �tre ouvert
		{
			//On ferme l'application, si �a marche pas �a marche pas (et pis c'est tout)
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

	while (secret[i] != '\0') //Tant qu'on n'est pas arriv� � la fin du mot secret
	{
		trouvee[i] = '0'; //On d�finit les caracteres de trouvee � 0

		i++;
	}
}

char LireCaractere()
{
	char caractere = 0;

	//Permet de vider le buffer clavier si �a n'a pas �t� fait avant
	do
	{
		caractere = getchar();
	} while (caractere == '\n');

	caractere = toupper(caractere); //Passage du caractere en majuscule

	//Vide le buffer clavier : ici, supprime le '\n' entr� pour valider la saisie du caractere
	while (getchar() != '\n');

	return caractere; //on retourne le 1er caratere lu, en majuscule


}

int OccurenceCarChaine(char* strg, char c, char* trouvee)
{
	int i = 0, j = 0;
	int trouve = 0;

	while (strg[i] != '\0') //On parcourt les caracteres de la chaine tant qu'on n'est pas arriv�s � la fin
	{
		if (strg[i] == c) //Si on trouve le caractere
		{
			trouvee[i] = '1'; //On passe la ieme case de trouvee � 1
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
		if (trouvee[i] == '1') //Si la ieme lettre est trouv�e
		{
			printf("%c", secret[i]); //On l'affiche
		}
		else
		{
			printf("*"); //Sinon on la laisse masqu�e
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
		if (trouvee[i] == '1') //On compte le nombre de lettres trouv�es
		{
			nbLettresTrouvees++;
		}
		i++;
	}

	if (tailleSecret == nbLettresTrouvees) //Si on a trouv� autant de lettres qu'en contient le mot
	{
		return 1;
	}

	return 0;
}