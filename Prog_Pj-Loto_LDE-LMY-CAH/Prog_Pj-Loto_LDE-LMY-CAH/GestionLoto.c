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
#include <string.h>
#include <Windows.h>
#include "LotoRules.h"
#include "GestionLoto.h"
#include "GestionValeurlotoGagnante.h"

#define PATH "..\\LotoConfig\\"


char length;
char Name[100];
char* strtxt;
int tirage;

// Fonction
// nom fonction		: ExistingFile
// paramètre In		: 
// paramètre out	: 
// paramètre in/out	: 
// description		: permet la récupération des règles du loto
//----------------------------------------------------------------------------------
void ExistingFile()
{
    strcpy(FilePath, PATH);

    printf("\n--- Fichiers Loto existants ---\n");
    WIN32_FIND_DATAA findFileData;
    char searchPath[250];

    // On combine le chemin du dossier avec "*.txt" pour chercher dedans
    sprintf(searchPath, "%s*.txt", PATH);
    HANDLE hFind = FindFirstFileA(searchPath, &findFileData);

    if (hFind == INVALID_HANDLE_VALUE)
        printf("Aucun fichier .txt trouve ou dossier inexistant.\n");
    else
    {
        do
        {
            printf("- %s\n", findFileData.cFileName);
        } while (FindNextFileA(hFind, &findFileData) != 0);
        FindClose(hFind);
    }
    printf("-------------------------------\n\n");
}

// Fonction
// nom fonction		: ConfigFile
// paramètre In		: 
// paramètre out	: 
// paramètre in/out	: str_Rules
// description		: permet la configuration du loto
//----------------------------------------------------------------------------------
void ConfigFile()
{
    FILE* fp1 = NULL;
    char test;
    scanf("%84s", Name);
    regle.NameLoto = Name;

    length = (char)strlen(Name);
    if (length <= 70)                                    //Vérification taille du nom
    {
        /* printf("%s\n", regle.NameLoto);*/
        strcat(FilePath, Name);
        strtxt = strstr(FilePath, ".txt");    //Recherche du nom.txt deja existant
        if (strtxt == NULL)                              //Si n'existe pas le creer
            strcat(FilePath, ".txt");

        fp1 = fopen(FilePath, "r");
        if (fp1 == NULL)                                //Vérification d'un fichier existant
        {
            printf("Fichier inexistant, creation du fichier\n");
            printf("Configuration des regle\n");
            ConfigRules(&regle);                         //Fonction configuration des regles
        }
        else
        {
            printf("Fichier trouve !\n");
            test = fgetc(fp1);
            if (test == EOF)
            {
                printf("Fichier vide !\n");
                printf("Configuration des règle\n");
                ConfigRules(&regle);                      //Fonction configuration des regles  
            }
            else
                RecupData(&regle, fp1);                 //Fonction recuperation des regles deja creer
        }
    }
    else
        printf("Nom trop long !\n");
}

// Fonction
// nom fonction		: ModeLoto
// paramètre In		: 
// paramètre out	: 
// paramètre in/out	: str_Rules
// description		: permet de choisir le mode du loto
//----------------------------------------------------------------------------------
char ModeLoto(char* Mode)
{
    do
    {
        scanf("%6s", Mode);
        if (strcmp(Mode, "Simu") == 0 || strcmp(Mode, "simu") == 0)
        {
            strcpy(Mode, "Simu");
            printf(" Mode %s\n", Mode);
            return 1;
        }
        else if (strcmp(Mode, "Normal") == 0 || strcmp(Mode, "normal") == 0)
        {
            strcpy(Mode, "Normal");
            printf(" Mode %s\n", Mode);
            return 0;
        }
        else
            printf("mode invalide\n");

    } while ((strcmp(Mode, "Simu") != 0) && (strcmp(Mode, "Normal") != 0));

}

void ChoiceValue(int* tbValue, char Mode, str_Rules *r)
{
    if (Mode == 0)
    {
        for (int i = 0; i < 6; i++)
        {
            tbValue[i] = rand() % (r->ValMax - r->ValMin + 1) + r->ValMin;
        }
    }
    else
    {
        //InsertValue();
    }

}

// Fonction
// nom fonction		: Tirage
// paramètre In		: variable du mode
//                    structure des règles
// paramètre out	: 
// paramètre in/out	: 
// description		: permet de tirer les numéro
// ----------------------------------------------------------------------------------
int Tirage(str_Rules* d, int* tbTirage, int LastVal, char Mode)
{
    int Doublon;
    do
    {
        tirage = rand() % (d->ValMax - d->ValMin + 1) + d->ValMin;

        // 2. Vérifier si ce numéro existe déjà dans les cases précédentes
        Doublon = 0; // On part du principe qu'il est unique
        for (int j = 0; j < LastVal; j++)
        {
            if (tbTirage[j] == tirage)
            {
                Doublon = 1; // Trouvé ! C'est un doublon
                break;          // Pas la peine de continuer à chercher pour ce tirage
            }
        }

    } while (Doublon == 1);

    return tirage;
}

// Fonction
// nom fonction		: Win
// paramètre In		: variable du mode
//                    structure des règles
// paramètre out	: 
// paramètre in/out	: 
// description		: permet de tirer les numéro
void Win(int* tbTirage, int *tbValue, int* tbWin)
{

    for (int j = 0; j < 6; j++)
    { 
        for (int i = 0; i < 6; i++)
        {
            if (tbTirage[j] == tbValue[i])
            {
                tbWin[j] = tbTirage[j];
                printf("win");
            }
        }
        
    }
}