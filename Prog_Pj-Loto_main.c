//-----------------------------------------------------------------------------------//
// Nom du projet 		: Prog_Pj-Loto
// Nom du fichier 		: Prog_Pj-Loto_main.c
// Date de création 	: 18.05.2026
// Date de modification : xx.xx.xxxx
//
// Auteur 				: CAH (Ch. Allenbach)
//                        
//
// Version 				: 0.0
//
// Description          : 
//
//
// 						  
//----------------------------------------------------------------------------------//
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <Windows.h>
#include "LotoRules.h"


#define PATH "..\\LotoConfig\\"  // remonte de 1 dossier depuis la racine du projet
char Mode[6];
char simulation = 0;
char length;
char out = 0;
char InputUser;
char Name[100];
char FilePath[200];

char* strtxt;
FILE* fp1 = NULL;


void main()
{
    out = 0; // faux, reste dans la boucle
    str_Rules regle;
    char Buff[10];
    do {
        printf("gestion fichiers G,mode M, trirage T, Q pour Quitter \n");
        scanf(" %c", &InputUser);

        switch (InputUser)
        {
        case 'G':
        case 'g':
            printf("Gestion de fichier\n");
            strcpy(FilePath, PATH);

            printf("\n--- Fichiers Loto existants ---\n");
            WIN32_FIND_DATAA findFileData;
            char searchPath[250];

            // On combine le chemin du dossier avec "*.txt" pour chercher dedans
            sprintf(searchPath, "%s*.txt", PATH);
            HANDLE hFind = FindFirstFileA(searchPath, &findFileData);

            if (hFind == INVALID_HANDLE_VALUE) {
                printf("Aucun fichier .txt trouve ou dossier inexistant.\n");
            }
            else {
                do {
                    printf("- %s\n", findFileData.cFileName);
                } while (FindNextFileA(hFind, &findFileData) != 0);
                FindClose(hFind);
            }
            printf("-------------------------------\n\n");
            // --- FIN DE L'AJOUT ---
           
            printf("Nom du fichier loto : ");
            scanf("%99s", Name);

            length = (char)strlen(Name);
            if (length <= 70)                                   //Vérification taille du nom
            {
                strcat(FilePath, Name);
                strtxt = strstr(FilePath, ".txt");              //Recherche de l'extensionn .txt deja existant
                if (strtxt == NULL)                             //Si n'existe pas l'ajouter
                    strcat(FilePath, ".txt");

                fp1 = fopen(FilePath, "r");
                if (fp1 == NULL)                                //Vérification d'un fichier existant
                {
                    printf("Fichier inexistant, creation du fichier\n");
                    fp1 = fopen(FilePath, "w+");
                    
                    ConfigRules(&regle);                        //Fonction configuration des regles  
                }
                else
                {
                    printf("Fichier trouve !\n");
                    if (fgets(Buff, sizeof(Buff), fp1))
                    {
                        rewind(fp1);
                        RecupData(&regle, fp1);                 //Fonction recuperation des regles deja creer
                    }
                    else
                    {
                        printf("Fichier vide !\n");
                        ConfigRules(&regle);
                    }
                }
            }
            else
                printf("Nom trop long !\n");
            break;
        case 'M':
        case 'm':
            // Saisie
            if (fp1 != NULL)
            {
                do
                {
                    printf("Choix du mode Simu/Normal\n");
                    scanf("%5s", Mode);
                    if (strcmp(Mode, "Simu") == 0 || strcmp(Mode, "simu") == 0)
                    {
                        simulation = 1;
                        strcpy(Mode, "Simu");
                    }
                    else if (strcmp(Mode, "Normal") == 0 || strcmp(Mode, "normal") == 0)
                    {
                        simulation = 0;
                        strcpy(Mode, "Normal");
                    }
                    else
                        printf("mode invalide");
                } while ((strcmp(Mode, "Simu") != 0) && (strcmp(Mode, "Normal") != 0));
            }
            else
            {
                printf("Fichier non ouvert !\n");
                InputUser = 'G';
            }
            break;

        case 'T':
        case 't':
            printf("Tirage\n");
            if (fp1 != NULL)
            {
                fp1 = fopen(FilePath, "a");
                // fonctions du tirage

            }
            else
            {
                printf("Fichier non ouvert !\n");
                InputUser = 'G';
            }
            break;

        case 'Q':
        case 'q':
            out = 1;
            break;
        }

    } while (out == 0);
    if (fp1 != NULL)
    {
        WriteConfig(&regle, fp1);
        fclose(fp1);
    }
}
