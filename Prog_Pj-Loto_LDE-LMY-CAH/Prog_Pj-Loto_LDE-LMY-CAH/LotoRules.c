//-----------------------------------------------------------------------------------//
// Nom du projet 		: Prog_Pj-Loto
// Nom du fichier 		: LotoRules.c
// Date de création 	: 18.05.2026
// Date de modification : xx.xx.xxxx
//
// Auteur 				: CAH (Ch. Allenbach)
//                        
//
// Version 				: 0.0
//
// Description          : fonctions de configuration et de récupération des règles des lotos
//
//
// Remarques :            lien pour la table ASCII :
// 						  -> http://www.asciitable.com/
// 						  
//----------------------------------------------------------------------------------//
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "LotoRules.h"



// Fonction
// nom fonction		: ConfigRules
// paramètre In		: 
// paramètre out    : 
// paramètre in/out	: str_Rules
// description		: permet de configurer les règles du loto
//----------------------------------------------------------------------------------
void ConfigRules(str_Rules* r)
{
    do
    {
        printf("Entrez la valeur Min du loto: ");
        scanf("%d", &r->ValMin);

        printf("Entrez la valeur Max du loto: ");
        scanf("%d", &r->ValMax);
        if (r->ValMax < r->ValMin)
            printf("Valeur max plus petite que valeur min\n ");
        if (r->ValMin <= 0)
            printf("Erreur : Les valeurs doivent être strictement superieures à 0.\n\n");

        if ((r->ValMax - r->ValMin + 1) < 7)
        {
            printf("Erreur : La plage entre Min et Max doit contenir au moins 7 numeros.\n");
        }
    } while((r->ValMax <= r->ValMin) || ((r->ValMin <= 0) || ((r->ValMax - r->ValMin + 1) < 7)));
    

    printf("Numeros complementaires ? [o/n] : ");
    scanf(" %c", &r->NumCompl);

    if (r->NumCompl == 'o' || r->NumCompl == 'O')
    {
        printf("Numero chance actif\n");
        do
        {
          printf("Entrez la valeur MIN du numero complementaire: ");
          scanf("%d", &r->NumComplMin);

          printf("Entrez la valeur MAX du numero complementaire: ");
          scanf("%d", &r->NumComplMax);
          if (r->NumComplMax < r->NumComplMin)
              printf("valeur max trop plus petite que valeur min\n");
        } while (r->NumComplMax < r->NumComplMin);
        NbCompl = 7;
    }
    else
    {
        printf("Numero chance inactif\n");
        r->NumComplMin = 0;
        r->NumComplMax = 0;
        NbCompl = 6;
    }
}

// Fonction
// nom fonction		: WriteConfig
// paramètre In		: fp1
// paramètre out	: 
// paramètre in/out	: str_Rules
// description		: permet d'écrire la configurer des règles du loto dans le fichier
//----------------------------------------------------------------------------------
void WriteConfig(str_Rules* r, FILE* fp1)
{
    
    fprintf(fp1, "regle du loto:\n");
    fprintf(fp1, "Valeur Min du loto: %d\n", r->ValMin);
    fprintf(fp1, "Valeur Max du loto: %d\n", r->ValMax);
    if (r->NumCompl == 'o' || r->NumCompl == 'O')
        fprintf(fp1, "Numero chance actif\n");
    else
        fprintf(fp1, "Numero chance inactif\n");

    fprintf(fp1, "valeur Min du numero complementaire: %d\n", r->NumComplMin);
    fprintf(fp1, "valeur Max du numero complementaire: %d\n", r->NumComplMax);

    fprintf(fp1, "\nTirage:\n");
}

// Fonction
// nom fonction		: RecupData
// paramètre In		: fp1
// paramètre out	: 
// paramètre in/out	: str_Rules
// description		: permet la récupération des règles du loto
//----------------------------------------------------------------------------------
void RecupData(str_Rules* d, FILE* fp1)
{
    char buffer[256];
    char messageAffiche = 0;

    while (fgets(buffer, sizeof(buffer), fp1) != NULL)
    {
        // 1. Si on rencontre l'historique des tirages, on arrête immédiatement de lire !
        if (strstr(buffer, "Tirage:") != NULL)
        {
            break;
        }

        // 2. Tri sélectif et exclusif des lignes (du plus précis au moins précis)
        if (strstr(buffer, "Valeur Min du loto:") != NULL)
        {
            sscanf(buffer, "Valeur Min du loto: %d", &d->ValMin);
            printf("Valeur Min du loto: %d\n", d->ValMin);
        }
        else if (strstr(buffer, "Valeur Max du loto:") != NULL)
        {
            sscanf(buffer, "Valeur Max du loto: %d", &d->ValMax);
            printf("Valeur Max du loto: %d\n", d->ValMax);
        }
        else if (strstr(buffer, "valeur Min du numero complementaire:") != NULL)
        {
            sscanf(buffer, "valeur Min du numero complementaire: %d", &d->NumComplMin);
            printf("valeur Min du numero complementaire: %d\n", d->NumComplMin);
        }
        else if (strstr(buffer, "valeur Max du numero complementaire:") != NULL)
        {
            sscanf(buffer, "valeur Max du numero complementaire: %d", &d->NumComplMax);
            printf("valeur Max du numero complementaire: %d\n", d->NumComplMax);
        }
        else if (strstr(buffer, "Numero chance") != NULL)
        {
            if (strstr(buffer, "inactif") != NULL)
            {
                d->NumCompl = 'n';
                if (messageAffiche == 0) {
                    printf("Pas de numero chance\n");
                    messageAffiche = 1;
                    NbCompl = 6;
                }
            }
            else
            {
                d->NumCompl = 'o';
                if (messageAffiche == 0) {
                    printf("Numero chance actif\n");
                    messageAffiche = 1;
                    NbCompl = 7;
                }
            }
        }
    }
}


