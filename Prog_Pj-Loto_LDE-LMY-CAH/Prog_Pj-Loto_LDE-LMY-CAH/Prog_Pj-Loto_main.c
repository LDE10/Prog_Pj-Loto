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
        // enregistre le premier caractère entré par l'utilisateur
        InputUser = Input();

        switch (InputUser)
        {
        case 'G':
        case 'g':

            printf("\nGestion de fichier\n");
            // fonction de lecture des fichier existant dans le dossier ConfigLoto(chemin relatif depuis 
            // la racine du projet)
            ExistingFile();                                 
            // vérification de si un stream est ouvert. empeche d'ouvrir un autre fichier
            if (fp1 == NULL)
            {
                printf("Nom du loto : ");
                // configuration du fichier/loto
                ConfigFile();                    
                
                // ouverture du stream en mode lecture
                fp1 = fopen(FilePath, "r");
                // allocation des tableaux
                Value.tbValue = (int*)malloc(NbCompl * sizeof(int));
                Value.tbTirage = (int*)malloc(NbCompl * sizeof(int));
                Value.tbMostWinning = (int*)malloc(6 * sizeof(int));
                Value.tbLeastWinning = (int*)malloc(6 * sizeof(int));
                // affiche le nombre de tirage déjà éffectué dans le fichier
                RecupHisto(&Value, fp1, NbCompl, InputUser);
                for (int y = 0; y < 6; y++)
                {
                    // trouve les 6 numéros sorti le plus souvent
                    Value.tbMostWinning[y] = MostWinning(&Value, NbCompl, &regle, y);
                    // trouve les 6 numéros sorti le moins souvent
                    Value.tbLeastWinning[y] = LeastWinning(&Value, NbCompl, &regle, y);
                }
                
                // affiche les numéros le plus et le moins sorti
                Bestchiffres(Value.tbMostWinning, Value.tbLeastWinning);
                // affiche le numéro le plus et le moins sorti
                ValG(Value.tbMostWinning, Value.tbLeastWinning);
                printf("\n\n");
            }
            else
                printf("un fichier est deja ouvert. Veuillez quitter et relancer\n\n");
            break;
        case 'M':
        case 'm':
            // vérification de si un stream est ouvert. empeche de choisir un mode si aucun fichier est ouvert
            if (fp1 != NULL)
            {
                printf("Choix du mode Simu/Normal pour %s\n", regle.NameLoto);
                // Sélection du mode
                simu = ModeLoto(Mode);
            }
            else
                printf("\nFichier non ouvert !\n");
            break;

        case 'T':
        case 't':
            printf("\nTirage pour %s\n", regle.NameLoto);
            int Compl = (regle.NumCompl == 'o') ? 7 : 6;
            // vérification de si un stream est ouvert. empeche le tirage si aucun fichier est ouvert
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
                // alloue le tableau de win au nombre de numéro du loto
                Value.tbWin = (int*)malloc(NbCompl * sizeof(int));
                
                // comparaison de numéro choisi et tiré
                Win(&Value, &regle);
                free(Value.tbWin);
                printf("\n");
            }
            else
                printf("\nFichier non ouvert !\n");
            break;
        case 'R':
        case 'r':
            // vérification de si un stream est ouvert. empeche d'afficher les règles si aucun fichier est ouvert

            if (fp1 != NULL)
            {
                // ouverture d'un stream en mode lecture pour afficher les règles
                fpregle = fopen(FilePath, "r");
                if (fpregle != NULL)
                    // récupération des règles
                    RecupData(&regle, fpregle);
                fclose(fpregle);
            }
            else
                printf("\nFichier non ouvert !\n");

            break;
        case 'H':
        case 'h':
            // vérification de si un stream est ouvert. empeche d'afficher l'historique si aucun fichier est ouvert

            if (fp1 != NULL)
            {
                RecupHisto(&Value, fp1, NbCompl, InputUser);
                // 1. Remplissage complet des tableaux (Boucle uniquement pour le calcul)
                for (int y = 0; y < 6; y++)
                {
                    // trouve les 6 numéros sorti le plus souvent
                    Value.tbMostWinning[y] = MostWinning(&Value, NbCompl, &regle, y);
                    // trouve les 6 numéros sorti le moins souvent
                    Value.tbLeastWinning[y] = LeastWinning(&Value, NbCompl, &regle, y);
                }
                // affiche les numéros le plus et le moins sorti
                Bestchiffres(Value.tbMostWinning, Value.tbLeastWinning);
                // affiche le numéro le plus et le moins sorti
                ValG(Value.tbMostWinning, Value.tbLeastWinning);
            }
            else
                printf("\nFichier non ouvert !\n");
            break;
        case 'Q':
        case 'q':
            // permet la sortie de la boucle
            out = 1;
            break;

        default:
            printf("\nerreur de saisie\n\n");
        }
        // sortie de boucle
    } while (out == 0);

    if (fp1 != NULL)
    {
        fclose(fp1);
        // ouverture du stream en mode écriture
        fp1 = fopen(FilePath, "w");
        // écrit toutes les data dans le fichier
        SaveAllData(&regle, &Value, fp1, NbCompl);
        fclose(fp1);
    }
    // libére toute la mémoire allouée
    freetb();
}
