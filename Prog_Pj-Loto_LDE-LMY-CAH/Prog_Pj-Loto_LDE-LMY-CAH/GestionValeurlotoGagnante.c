//-----------------------------------------------------------------------------------//
// Nom du projet 		: ProjetLoto
// Nom du fichier 		: GestionValeurlotoGagnante.c
// Date de création 	: 18.05.2026
// Date de modification : 18.05.2026
//
// Auteur 				: LMY (Loïc Marmy)
//
// Description          : programme principale 
//
//
// Remarques			: lien pour les lib standard:
//						-> https://www.rocq.inria.fr/secret/Anne.Canteaut/COURS_C/annexe.html
//						-> 
//
//----------------------------------------------------------------------------------//
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "LotoRules.h"
#include "GestionLoto.h"
#include "GestionValeurlotoGagnante.h"

// nom fonction  : InsertValue
// paramètre In  : str_Rules* r
// paramètre out : 
// paramètre in/out : str_Value* v
// description  : Entree et gestions des valeurs de l'utilisateur
//----------------------------------------------------------------------------------
void InsertValue(str_Value* v, str_Rules* r)
{
    int nbElements = (r->NumCompl == 'o') ? 7 : 6;
    int i = 0;

    printf("\n--- Saisie de votre grille (%d numeros) ---\n", nbElements);
    printf("Astuce : Tapez 's' pour supprimer le precedent, 'a' pour le modifier.\n\n");

    while (i < nbElements)
    {
        // Détermination des bornes selon qu'on saisit un numéro normal ou le complémentaire
        int minCourant = (r->NumCompl == 'o' && i == nbElements - 1) ? r->NumComplMin : r->ValMin;
        int maxCourant = (r->NumCompl == 'o' && i == nbElements - 1) ? r->NumComplMax : r->ValMax;

        if (r->NumCompl == 'o' && i == nbElements - 1)
            printf("Entrez le numero complementaire (entre %d et %d) : ", minCourant, maxCourant);
        else
            printf("Entrez le numero %d (entre %d et %d) : ", i + 1, minCourant, maxCourant);

        // Lecture sous forme de texte pour intercepter les commandes 's' ou 'a'
        char input[20];
        scanf("%19s", input);

        // Commande de suppression
        if (strcmp(input, "s") == 0 || strcmp(input, "S") == 0)
        {
            i = DeleteLastValue(v, i); // Recule l'index de saisie et met la case à 0
            continue;
        }

        // Commande de modification
        if (strcmp(input, "a") == 0 || strcmp(input, "A") == 0)
        {
            ModifiedLastValue(v, i); // Modifie la dernière case saisie
            continue;
        }

        // Conversion du texte en entier si ce n'est pas une commande
        int val = atoi(input);

        // 1. Vérification des limites
        if (val < minCourant || val > maxCourant)
        {
            printf("Erreur : Le numero %d est hors limites !\n", val);
            continue;
        }

        // 2. Vérification des doublons (uniquement par rapport aux numéros déjà saisis)
        bool duplicate = false;
        for (int j = 0; j < i; j++)
        {
            if (v->tbValue[j] == val)
            {
                printf("Erreur : Le numero %d a deja ete saisi !\n", val);
                duplicate = true;
                break;
            }
        }

        // Si tout est correct, on enregistre et on passe au numéro suivant
        if (!duplicate)
        {
            v->tbValue[i] = val;
            i++;
            
        }
    }
    printf("Grille validee avec succes !\n\n");
    printf("Numeros choisi: ");
    for (int j = 0; j < nbElements; j++)
    {
        printf("%d ", v->tbValue[j]);
    }
    printf("\n");
}

// Fonction
// nom fonction		: DeleteLastValue
// paramètre In		: 
// paramètre out	: newIndex
// paramètre in/out	: str_Value* v, Nbelement
// description		: Suppession de la dernire valeur entree
//----------------------------------------------------------------------------------
int DeleteLastValue(str_Value* v, char Nbelement)
{
	int newIndex;
	// Sécurité : Si le tableau est déjà vide (0 élément), on ne peut rien supprimer
	if (Nbelement <= 0)
	{
		printf("Aucun numero a supprimer dans la saisie actuelle.\n");
		return 0; // Le nouvel index reste à 0
	}

	// On remet à 0 la dernière case remplie (l'indice est Nbelement - 1)
	v->tbValue[Nbelement - 1] = 0;

	// On calcule le nouvel index (le nombre d'éléments diminue de 1)
	newIndex = Nbelement - 1;

	return newIndex;
}

// Fonction
// nom fonction		: ModifiedLastValue
// paramètre In		: 
// paramètre out	: 
// paramètre in/out	: str_Value* v, Nbelement
// description		: Modification de la derniere valeur entree
//----------------------------------------------------------------------------------
void ModifiedLastValue(str_Value* v, char Nbelement)
{
	// Sécurité : Si le tableau est déjà vide (0 élément), on ne peut rien supprimer
	if (Nbelement <= 0)
	{
		printf("Aucun numero a modifier dans la saisie actuelle.\n");
	}
	else
	{
		Nbelement = Nbelement - 1;
		printf("modifier la valeur %d ", v->tbValue[Nbelement]);
		scanf("%d", &v->tbValue[Nbelement]);
		printf("Nouvelle valeur est %d ", v->tbValue[Nbelement]);
	}
}


#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "LotoRules.h"
#include "GestionLoto.h"
#include "GestionValeurlotoGagnante.h"

// Fonction
// nom fonction		: MostWinning
// paramètre In		: str_Value* v, nbNumbers, str_Rules* r, rank
// paramètre out	: bestVal
// description		: Recherche le X-ème (rank) numéro le plus gagnant
//----------------------------------------------------------------------------------
int MostWinning(str_Value* v, int nbNumbers, str_Rules* r, int rank)
{
    int freq[1000] = { 0 };

    // 1. Parcours de tout l’historique pour compter les fréquences
    for (int i = 0; i < v->nbHistoRows; i++)
    {
        for (int j = 0; j < nbNumbers; j++)
        {
            int val = v->tbHistoTirage[i][j];
            if (val >= r->ValMin && val <= r->ValMax)
                freq[val]++;
        }
    }
    int bestVal = r->ValMin;
    int bestFreq = -1;

    // 2. Recherche du numéro le plus fréquent pas encore sélectionné dans les rangs précédents
    for (int n = r->ValMin; n <= r->ValMax; n++)
    {
        bool dejaChoisi = false;
        for (int k = 0; k < rank; k++)
        {
            if (v->tbMostWinning[k] == n)
            {
                dejaChoisi = true;
                break;
            }
        }

        // Si le numéro n'a pas encore été pris et possède une meilleure fréquence
        if (!dejaChoisi && freq[n] > bestFreq)
        {
            bestFreq = freq[n];
            bestVal = n;
        }
    }
    return bestVal;
}


// Fonction
// nom fonction		: LeastWinning
// paramètre In		: str_Value* v, nbNumbers, str_Rules* r, rank
// paramètre out	: worstVal
// description		: Recherche le X-ème (rank) numéro le moins gagnant
//----------------------------------------------------------------------------------
int LeastWinning(str_Value* v, int nbNumbers, str_Rules* r, int rank)
{
    int freq[1000] = { 0 };

    // 1. Parcours de tout l’historique 
    for (int i = 0; i < v->nbHistoRows; i++)
    {
        for (int j = 0; j < nbNumbers; j++)
        {
            int val = v->tbHistoTirage[i][j];
            if (val >= r->ValMin && val <= r->ValMax)
                freq[val]++;
        }
    }

    int worstVal = r->ValMin;
    int worstFreq = 999999; // Initialisation haute pour la recherche de minimum

    // 2. Recherche du numéro le moins fréquent pas encore sélectionné
    for (int n = r->ValMin; n <= r->ValMax; n++)
    {
        bool dejaChoisi = false;
        for (int k = 0; k < rank; k++)
        {
            if (v->tbLeastWinning[k] == n)
            {
                dejaChoisi = true;
                break;
            }
        }
        // Si le numéro est libre et a une fréquence plus faible
        if (!dejaChoisi && freq[n] < worstFreq)
        {
            worstFreq = freq[n];
            worstVal = n;
        }
    }
    return worstVal;
}
