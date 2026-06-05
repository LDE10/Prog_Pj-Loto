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

// Fonction
// nom fonction		: 
// paramètre In		: str_Rules* r
// paramètre out	: 
// paramètre in/out	: str_Value* v
// description		: Entree des valeurs et gestions
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
// nom fonction		: 
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
// nom fonction		: 
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

int MostWinning(str_Value* v, int nbNumbers, int valMin, int valMax)
{
    // Tableau de fréquence d'apparition de la valeur
    int freq[256] = { 0 };

    // Parcours de tout l’historique
    for (int i = 0; i < v->nbHistoRows; i++)
    {
        for (int j = 0; j < nbNumbers; j++)
        {
            int val = v->tbHistoTirage[i][j];
            if (val >= valMin && val <= valMax)
                freq[val]++;
        }
    }

   // Initialisation de la meilleure valeur a la valeur minimum
    int bestVal = valMin;
    // Initialisation de la meilleure fréquence a une petite valeur pour etre sur d'etre plus grand
    int bestFreq = -1;

    // Recherche de la valeur la plus fréquente
    for (int n = valMin; n <= valMax; n++)
    {
        if (freq[n] > bestFreq)
        {
            bestFreq = freq[n];
            bestVal = n;
        }
    }

    // Retourne la valeur la plus fréquente
    return bestVal;
}

int LeastWinning(str_Value* v, int nbNumbers, int valMin, int valMax)
{
    // Tableau de fréquence d'apparition de la valeur
    int freq[256] = { 0 };

    // Parcours de tout l’historique
    for (int i = 0; i < v->nbHistoRows; i++)
    {
        for (int j = 0; j < nbNumbers; j++)
        {
            int val = v->tbHistoTirage[i][j];
            if (val >= valMin && val <= valMax)
                freq[val]++;
        }
    }

    // Initialisation de la pire valeur a la valeur minimum
    int worstVal = valMin;
    // Initialisation de la pire fréquence a une tres grande valeur pour etre sur d'etre plus petit
    int worstFreq = 999999;

    // Recherche de la valeur la moins fréquente
    for (int n = valMin; n <= valMax; n++)
    {
        if (freq[n] < worstFreq)
        {
            worstFreq = freq[n];
            worstVal = n;
        }
    }

    // Retourne la valeur la moins fréquente
    return worstVal;
}