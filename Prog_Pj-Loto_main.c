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


#define PATH "..\\LotoConfig\\"
char Mode[6];
char simulation;
char length;
char out = 0;
char InputUser;
char Name[100];
char FilePath[100];
char* strtxt;
FILE* fp1 = NULL;


void main()
{
    out = 0; // faux, reste dans la boucle
    str_Rules regle;
    do {
        printf("gestion fichiers G,mode M, trirage T, Q pour Quitter \n");
        scanf(" %c", &InputUser);

        switch (InputUser)
        {
        case 'G':
        case 'g':
            printf("Gestion de fichier\n");
            strcpy(FilePath, PATH);

            //// --- DÉBUT DE L'AJOUT : LISTER LES FICHIERS .TXT ---
            //printf("\n--- Loto existants ---\n");
            //WIN32_FIND_DATAA findFileData;
            //// On cherche tous les .txt dans le dossier courant
            //HANDLE hFind = FindFirstFileA("*.txt", &findFileData);

            //if (hFind == INVALID_HANDLE_VALUE) {
            //    printf("Aucun fichier .txt trouve.\n");
            //}
            //else {
            //    do {
            //        printf("- %s\n", findFileData.cFileName);
            //    } while (FindNextFileA(hFind, &findFileData) != 0);
            //    FindClose(hFind);
            //}
            //printf("-------------------------------\n\n");
            //// --- FIN DE L'AJOUT ---

            printf("Nom du fichier loto : ");
            scanf("%99s", Name);

            length = (char)strlen(Name);
            if (length <= 70)                                   //Vérification taille du nom
            {
                strcat(FilePath, Name);
                strtxt = strstr(FilePath, ".txt");              //Recherche du nom.txt deja existant
                if (strtxt == NULL)                             //Si n'existe pas le creer
                    strcat(FilePath, ".txt");

                fp1 = fopen(FilePath, "r");
                if (fp1 == NULL)                                //Vérification d'un fichier existant
                {
                    printf("Fichier inexistant, creation en cours du fichier\n");
                    fp1 = fopen(FilePath, "w");
                    if (fp1 != NULL)
                        ConfigRules(&regle);                    //Fonction configuration des regles  
                }
                else
                {
                    printf("Fichier trouve !\n");
                    RecupData(&regle, fp1);                      //Fonction recuperation des regles deja creer
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
                    scanf("%5s", &Mode);
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