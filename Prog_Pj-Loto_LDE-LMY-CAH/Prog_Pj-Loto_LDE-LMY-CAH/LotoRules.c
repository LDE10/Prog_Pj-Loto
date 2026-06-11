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
#include <string.h>
#include <Windows.h>
#include "LotoRules.h"   
#include "GestionLoto.h"
#include "GestionValeurlotoGagnante.h"

#define PATH "..\\LotoConfig\\"

int tirage;
char FilePath[100];
char length;
char Name[100];
char* strtxt;

// Fonction
// nom fonction		: Input
// paramètre In		: -
// paramètre out	: -
// paramètre in/out	: -
// description		: permet de récupérer l'entrée de l'utilisateur
// ----------------------------------------------------------------------------------
char Input()
{
    char InputUser;
    char testInput;
    char test;

    scanf(" %c", &InputUser);
    // permet de prendre en compte seulement le premier caractère entré
    while ((testInput = getchar()) != '\n' && testInput != EOF);
    return InputUser;
}


// Fonction
// nom fonction		: ExistingFile
// paramètre In		: 
// paramètre out	: 
// paramètre in/out	: 
// description		: permet d'affiché le fichier déja présent dans le dossier lotoConfig
//----------------------------------------------------------------------------------
void ExistingFile()
{
    WIN32_FIND_DATAA findFileData;
    char searchPath[250];
    strcpy(FilePath, PATH);

    printf("\n--- Fichiers Loto existants ---\n");
    
    // On combine le chemin du dossier avec "*.txt" pour chercher dedans
    strcpy(searchPath, PATH);      // Étape 1 : searchPath devient "..\\LotoConfig\\"
    strcat(searchPath, "*.txt");
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
// paramètre in/out	: 
// description		: permet la configuration du loto
//----------------------------------------------------------------------------------
void ConfigFile()
{
    FILE* fp1 = NULL;
    char test;
    char InputUser;
    
    scanf("%84s", Name);
    regle.NameLoto = Name;

    length = (char)strlen(Name);
    if (length <= 70)                                    //Vérification taille du nom
    {
        /* printf("%s\n", regle.NameLoto);*/
        strcat(FilePath, Name);
        strtxt = strstr(FilePath, ".txt");               //Recherche du nom.txt deja existant
        if (strtxt == NULL)                              //Si n'existe pas le creer
            strcat(FilePath, ".txt");

        fp1 = fopen(FilePath, "r");
        if (fp1 == NULL)                                //Vérification d'un fichier existant
        {
            printf("Fichier inexistant, creation du fichier\n");
            printf("voulez vous le cree o pour oui ");
            InputUser = Input();
            if (InputUser == 'o')
            {
                // ouverture du stream en mode écriture pour créer le fichier
                fp1 = fopen(FilePath, "w");
                fclose(fp1);
                printf("Configuration des regle\n");
                //Fonction configuration des regles
                ConfigRules(&regle);                         
            }
            else
                printf("fichier non cree\n");
        }
        else
        {
            printf("Fichier trouve !\n");
            // test de fichier vide
            test = fgetc(fp1);
            if ((test == EOF)||(test != 'r'))
            {
                printf("Fichier vide !\n");
                printf("Configuration des regle\n");
                // fichier vide configuration des regles
                ConfigRules(&regle);                        
            }
            else
            {
                //Fonction recuperation des regles deja creer
                RecupData(&regle, fp1);   
                // opérateur terner c'est un if sur une ligne si la condition est vrai la variable vaut 7 sinon ell vaut 6
                NbCompl = (regle.NumCompl == 'o') ? 7 : 6;
                InputUser = 'n';
                RecupHisto(&Value, fp1, NbCompl, InputUser);
            }
        }
    }
    else
        printf("Nom trop long !\n");
    fclose(fp1);
}

// Fonction
// nom fonction		: ModeLoto
// paramètre In		: 
// paramètre out	: 
// paramètre in/out	: Mode
// description		: permet de choisir le mode du loto
//----------------------------------------------------------------------------------
char ModeLoto(char* Mode)
{
    char mode = 2;
    do
    {
        scanf("%6s", Mode);
        if (strcmp(Mode, "Simu") == 0 || strcmp(Mode, "simu") == 0)
        {
            strcpy(Mode, "Simu");
            printf(" Mode %s\n", Mode);
            mode = 1;
        }
        else if (strcmp(Mode, "Normal") == 0 || strcmp(Mode, "normal") == 0)
        {
            strcpy(Mode, "Normal");
            printf(" Mode %s\n", Mode);
            mode = 0;
        }
        else
            printf("mode invalide\n");

    } while (mode == 2);
    return mode;
}

// Fonction
// nom fonction		: ChoiceValue
// paramètre In		: 
// paramètre out	: 
// paramètre in/out	: str_Rules
// description		: change le mode d'entré des numéros
//----------------------------------------------------------------------------------
void ChoiceValue(int* tbValue, char Mode, char NbCompl, str_Rules *r)
{
    int i = 0;
    if (Mode == 1)
    {
        printf("\nnumero choisi:");
        for (i = 0; i < NbCompl; i++)
        {
            // choisi aléatoirement les valeurs de l'utilisateur
            tbValue[i] = Tirage(&regle, tbValue, i);
            printf("%d ", tbValue[i]);
        }
        printf("\n");
    }
    else
    {
        // l'utilisateur insert ses valeurs 
        InsertValue(&Value,&regle);
    }
}

// Fonction
// nom fonction		: Tirage
// paramètre In		: LastVal
// paramètre out	: 
// paramètre in/out	: str_Rules, tbTirage
// description		: permet de tirer les numéros
// ----------------------------------------------------------------------------------
int Tirage(str_Rules* d, int* tbTirage, int LastVal)
{
    int Doublon;
    int i = 0;
    if ((d->NumCompl == 'o' || d->NumCompl == 'O') && (LastVal == 6))
        // On génère le numéro chance selon sa plage spécifique
        tirage = rand() % (d->NumComplMax - d->NumComplMin + 1) + d->NumComplMin;
    else
    {
        do
        {
            tirage = rand() % (d->ValMax - d->ValMin + 1) + d->ValMin;

            // Vérifier si ce numéro existe déjà dans les cases précédentes
            Doublon = 0; 
            for (i = 0; i < LastVal; i++)
            {
                if (tbTirage[i] == tirage)
                {
                    Doublon = 1; // Trouvé ! C'est un doublon
                    break;       
                }
            }
        } while (Doublon == 1);
    }
    return tirage;
}


// Fonction
// nom fonction		: Win
// paramètre In		: str_Value *v, str_Rules
// paramètre out	: 
// paramètre in/out	: 
// description		: compare les numéros tirés et les numéro entrés
// ----------------------------------------------------------------------------------
void Win(str_Value* v, str_Rules* r)
{
    int WinNumber = 0;
    // Déterminer combien il y a de numéros normaux (sans le complémentaire)
    int nbNormaux = (r->NumCompl == 'o' || r->NumCompl == 'O') ? (NbCompl - 1) : NbCompl;
    int i, j = 0;

    printf("\n--- Resultats du tirage ---\n");

    // comparaison de numéros
    for (j = 0; j < nbNormaux; j++)
    {
        for (i = 0; i < nbNormaux; i++)
        {
            if (v->tbTirage[j] == v->tbValue[i])
            {
                v->tbWin[j] = v->tbTirage[j];
                printf("Numero normal trouve : %d\n", v->tbValue[i]);
                WinNumber++; // On incrémente le nombre de trouvailles
                break; 
            }
        }
    }
    if(WinNumber == 0)
        printf("Aucun numero trouve !\n");
    // comparaison de numéros complaimentaire
    if (r->NumCompl == 'o' || r->NumCompl == 'O')
    {
        
        if (v->tbTirage[6] == v->tbValue[6])
        {
            v->tbWin[6] = v->tbTirage[6];
            printf("Numero complementaire trouve ! : %d\n", v->tbValue[6]);
        }
        else
            printf("Aucun numero complementaire trouve !\n");
    }
}

// Fonction
// nom fonction		: RecupHisto
// paramètre In		: fp1, nbNumbers
// paramètre out	: 
// paramètre in/out	: str_Value* v,
// description		: Récupère l'historique des tirages sous "Tirage:" et l'affiche
//----------------------------------------------------------------------------------
void RecupHisto(str_Value* v, FILE* fp1, int nbNumbers, char InputUser)
{
    char buffer[256];
    bool foundTirage = false;
    int firstVal;
    int col = 0;

    v->tbHistoTirage = NULL;
    v->nbHistoRows = 0;

    // Repositionnement du curseur au début du fichier 
    rewind(fp1);

    while (fgets(buffer, sizeof(buffer), fp1) != NULL)
    {
        // Ignorer tout le début tant qu'on n'a pas atteint "Tirage:"
        if (!foundTirage)
        {
            if (strstr(buffer, "Tirage:") != NULL)
            {
                foundTirage = true;
                if ((InputUser == 'h') || (InputUser == 'H'))
                    printf("\n--- Historique des Tirages ---\n");
            }
            continue;
        }

        //Traitement des lignes de tirages après "Tirage:"
        
        // On vérifie s'il y a bien des chiffres sur la ligne (évite les lignes vides)
        if (sscanf(buffer, "%d", &firstVal) == 1)
        {
            // Réallocation dynamique du tableau de pointeurs de lignes
            int** temp = realloc(v->tbHistoTirage, (v->nbHistoRows + 1) * sizeof(int*));
            if (temp == NULL)
            {
                printf("Erreur d'allocation memoire pour l'historique.\n");
                return;
            }
            v->tbHistoTirage = temp;

            // Allocation de la mémoire pour les colonnes de la ligne actuelle
            v->tbHistoTirage[v->nbHistoRows] = (int*)malloc(nbNumbers * sizeof(int));
            if (v->tbHistoTirage[v->nbHistoRows] == NULL)
            {
                printf("Erreur d'allocation memoire pour les valeurs du tirage.\n");
                return;
            }
            col = 0;
            // Découpage de la ligne avec strtok pour extraire chaque numéro séparé par un espace
            char* token = strtok(buffer, " \t\r\n");
            while (token != NULL && col < nbNumbers)
            {
                v->tbHistoTirage[v->nbHistoRows][col] = atoi(token);
                if ((InputUser == 'h') || (InputUser == 'H'))
                {
                    printf("%d ", v->tbHistoTirage[v->nbHistoRows][col]);
                }
                col++;
                token = strtok(NULL, " \t\r\n");
                if (((InputUser == 'h') || (InputUser == 'H')) && (col == nbNumbers))
                {
                    printf("\n");
                }
            }
            v->nbHistoRows++;
        }
    }
    printf("-------------------------------\n");
}

// Fonction
// nom fonction		: AddTirageToHisto
// paramètre In		: nbNumbers 
// paramètre out	: 
// paramètre in/out	: str_Value
// description		: Sauvegarde le tirage actuel (tbTirage) dans l'historique (tbHistoTirage)
//----------------------------------------------------------------------------------
void AddTirageToHisto(str_Value* v, int nbNumbers)
{
    int i = 0;
    // Réallocation du tableau de pointeurs pour ajouter une ligne
    int** temp = realloc(v->tbHistoTirage, (v->nbHistoRows + 1) * sizeof(int*));
    
    if (temp == NULL)
    {
        printf("Erreur d'allocation memoire pour la sauvegarde de l'historique.\n");
        return;
    }
    v->tbHistoTirage = temp;

    // Allocation de la mémoire pour les numéros de cette nouvelle ligne
    v->tbHistoTirage[v->nbHistoRows] = (int*)malloc(nbNumbers * sizeof(int));
    if (v->tbHistoTirage[v->nbHistoRows] == NULL)
    {
        printf("Erreur d'allocation de la ligne d'historique.\n");
        return;
    }

    // Copie des données de tbTirage vers la nouvelle ligne de tbHistoTirage
    for (i = 0; i < nbNumbers; i++)
    {
        v->tbHistoTirage[v->nbHistoRows][i] = v->tbTirage[i];
    }

    // Incrémentation du compteur de lignes globales de l'historique
    v->nbHistoRows++;
    printf("Tirage sauvegarde dans l'historique (Total : %d tirages).\n", v->nbHistoRows);
    
}

// Fonction
// nom fonction		: SaveAllData
// paramètre In		: str_Rules, str_Value, fp1, nbNumbers
// paramètre out	: 
// paramètre in/out	: 
// description		: Écrit les règles puis l'intégralité de l'historique de tirage dans le fichier
//----------------------------------------------------------------------------------
void SaveAllData(str_Rules* r, str_Value* v, FILE* fp1, int nbNumbers)
{
    int i, j = 0;
    if (fp1 == NULL)
    {
        printf("Erreur : Impossible d'ecrire, le fichier n'est pas ouvert.\n");
        return;
    }
    // Écrit l'entête "regle du loto:" et la section "Tirage:" dans le fichier
    WriteConfig(r, fp1);

    // Écrit toutes les lignes stockées 
    if (v->tbHistoTirage != NULL && v->nbHistoRows > 0)
    {
        for (i = 0; i < v->nbHistoRows; i++)
        {
            for (j = 0; j < nbNumbers; j++)
            {
                 //vérification si la toute première valeur est hors des bornes du loto. On n'écrit rien. 
                if (v->tbHistoTirage[i][j] < r->ValMin || v->tbHistoTirage[i][j] > r->ValMax)
                {
                    printf("Aucun tirage valide effectue. Annulation de l'ecriture des donnees brutes.\n");
                    return;
                }
                fprintf(fp1, "%d", v->tbHistoTirage[i][j]);

                // Ajoute un espace entre les numéros (sauf après le dernier numéro)
                if (j < nbNumbers - 1)
                {
                    fprintf(fp1, " ");
                }
            }
            fprintf(fp1, "\n"); // Saut de ligne après chaque tirage complet
        }
        printf("Sauvegarde reussie de %d tirage(s) dans le fichier.\n", v->nbHistoRows);
    }
    else
    {
        printf("Aucun tirage a sauvegarder.\n");
    }
}

// Fonction
// nom fonction		: freetb
// paramètre In		: -
// paramètre out	: -
// paramètre in/out	: -
// description		: Libère la mémoire alouée
//----------------------------------------------------------------------------------
void freetb()
{
    int i = 0;
    if (Value.tbHistoTirage != NULL)
    {
        for (i = 0; i < Value.nbHistoRows; i++)
        {
            free(Value.tbHistoTirage[i]); // Libère chaque ligne
        }
        free(Value.tbHistoTirage);        // Libère le tableau de pointeurs
    }
    free(Value.tbValue);
    free(Value.tbWin);
    free(Value.tbMostWinning);
    free(Value.tbLeastWinning);
}

