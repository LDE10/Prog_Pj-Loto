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
#include <stdlib.h> 
#include <time.h>   
#include "LotoRules.h"   
#include "GestionLoto.h"
#include "GestionValeurlotoGagnante.h"
#include "GestionAffichage.h"

str_Value Value;
str_Rules regle;
char NbCompl;

int main()
{

    char Mode[7];
    char InputUser;
    char newIndex;
    char simu = 1;
    char out = 0;       // variable de sortie de boucle
    char c;
    FILE* fp1 = NULL;
    FILE* fpregle = NULL;
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ \n");
    printf("|                    Projet de programation LOTO                            |  \n");
    printf("|                     Fait par : CAH, LDE, LMY                              |  \n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ \n");

    do {
        printf("G pour choisir le fichiers \nM pour changer Mode \nT pour lancer un Tirage \n");
        printf("R pour afficher les regle\nH pour afficher l'historique \nQ pour Quitter \n");
        InputUser = Input();

        switch (InputUser)
        {
        case 'G':
        case 'g':

            printf("\nGestion de fichier\n");
            ExistingFile();                                 // fonction de lecture des fichier existant
            if (fp1 == NULL)
            {
                printf("Nom du loto : ");

                ConfigFile();                               // configuration du fichier/loto
                fp1 = fopen(FilePath, "r");
                Value.tbValue = (int*)malloc(NbCompl * sizeof(int));
                Value.tbTirage = (int*)malloc(NbCompl * sizeof(int));
                Value.tbMostWinning = (int*)malloc(6 * sizeof(int));
                Value.tbLeastWinning = (int*)malloc(6 * sizeof(int));

                for (int y = 0; y < 6; y++)
                {
                    Value.tbMostWinning[y] = MostWinning(&Value, NbCompl, &regle, y);
                    Value.tbLeastWinning[y] = LeastWinning(&Value, NbCompl, &regle, y);
                }

                // 2. Affichage APRÈS la fin de la boucle
                Bestchiffres(Value.tbMostWinning, Value.tbLeastWinning);
                ValG(Value.tbMostWinning, Value.tbLeastWinning);
                printf("\n\n");
            }
            else
                printf("un fichier est deja ouvert. Veuillez quitter et relancer\n\n");
            break;
        case 'M':
        case 'm':
            if (fp1 != NULL)
            {
                printf("Choix du mode Simu/Normal pour %s\n", regle.NameLoto);

                simu = ModeLoto(Mode);
            }
            else
                printf("\nFichier non ouvert !\n");
            break;

        case 'T':
        case 't':
            printf("\nTirage pour %s\n", regle.NameLoto);
            if (fp1 != NULL)
            {

                // Le reste de votre code (srand, ChoiceValue, Tirage...) reste identique
                srand(time(NULL));
                // valeurs entrées par l'utilisateur ou aléatoirement
                ChoiceValue(Value.tbValue, simu, NbCompl, &regle);
                // fonctions du tirage
                printf("Numero tire:  ");
                for (int i = 0; i < NbCompl; i++)
                {
                    // On passe : les règles, le tableau entier, et l'index 'i' actuel
                    Value.tbTirage[i] = Tirage(&regle, Value.tbTirage, i);
                    printf("%d ", Value.tbTirage[i]);
                }
                printf("\n");
                // ajout du dernier tirage dans l'historique
                AddTirageToHisto(&Value, NbCompl);
                Value.tbWin = (int*)malloc(NbCompl * sizeof(int));
                Win(&Value, &regle);
                printf("\n");
            }
            else
                printf("\nFichier non ouvert !\n");
            break;

        case 'Q':
        case 'q':
            out = 1;
            break;

        case 'R':
        case 'r':
            if (fp1 != NULL)
            {
                fpregle = fopen(FilePath, "r");
                if (fpregle != NULL)
                    RecupData(&regle, fpregle);
                fclose(fpregle);
            }
            else
                printf("\nFichier non ouvert !\n");

            break;
        case 'H':
        case 'h':
            if (fp1 != NULL)
            {
                RecupHisto(&Value, fp1, NbCompl, InputUser);
                // 1. Remplissage complet des tableaux (Boucle uniquement pour le calcul)
                for (int y = 0; y < 6; y++)
                {
                    Value.tbMostWinning[y] = MostWinning(&Value, NbCompl, &regle, y);
                    Value.tbLeastWinning[y] = LeastWinning(&Value, NbCompl, &regle, y);
                }

                // 2. Affichage APRÈS la fin de la boucle
                Bestchiffres(Value.tbMostWinning, Value.tbLeastWinning);
                ValG(Value.tbMostWinning, Value.tbLeastWinning);
            }
            else
                printf("\nFichier non ouvert !\n");
            break;


        default:
            printf("\nerreur de saisie\n");
        }

        // affichage + traitement de donnée
    } while (out == 0);

    if (fp1 != NULL)
    {
        fclose(fp1);
        fp1 = fopen(FilePath, "w");
        SaveAllData(&regle, &Value, fp1, NbCompl);
        fclose(fp1);
    }
    freetb();
}