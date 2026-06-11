//-----------------------------------------------------------------------------------//
// Nom du projet 		: ProjetLoto
// Nom du fichier 		: GestionValeurlotoGagnante.h
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
#ifndef GESTIONLOTO_H
#define GESTIONLOTO_H
typedef struct
{
    int* tbTirage;
    int* tbMostWinning;
    int* tbLeastWinning;
    int* tbValue;
    int* tbWin;
    int** tbHistoTirage; // Tableau dynamique à 2 dimensions [lignes][colonnes]
    int nbHistoRows;     // Nombre de tirages stockés dans l'historique
} str_Value;

extern str_Value Value;


void ExistingFile();
void ConfigFile();
char ModeLoto(char* Mode);
void ChoiceValue(int* tbValue, char Mode, char NbCompl, str_Rules* r);
int Tirage(str_Rules* d, int* tbTirage, int LastVal);
void Win(str_Value* v, str_Rules* r);
void RecupHisto(str_Value* v, FILE* fp1, int nbNumbers, char InputUser);
void AddTirageToHisto(str_Value* v, int nbNumbers);
void SaveAllData(str_Rules* r, str_Value* v, FILE* fp1, int nbNumbers);
void freetb();
char Input();
#endif//-----------------------------------------------------------------------------------//
// Nom du projet 		: ProjetLoto
// Nom du fichier 		: GestionValeurlotoGagnante.h
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
#ifndef GESTIONLOTO_H
#define GESTIONLOTO_H
typedef struct
{
    int* tbTirage;
    int* tbMostWinning;
    int* tbLeastWinning;
    int* tbValue;
    int* tbWin;
    int** tbHistoTirage; // Tableau dynamique à 2 dimensions [lignes][colonnes]
    int nbHistoRows;     // Nombre de tirages stockés dans l'historique
} str_Value;

extern str_Value Value;


void ExistingFile();
void ConfigFile();
char ModeLoto(char* Mode);
void ChoiceValue(int* tbValue, char Mode, char NbCompl, str_Rules* r);
int Tirage(str_Rules* d, int* tbTirage, int LastVal);
void Win(str_Value* v, str_Rules* r);
void RecupHisto(str_Value* v, FILE* fp1, int nbNumbers, char InputUser);
void AddTirageToHisto(str_Value* v, int nbNumbers);
void SaveAllData(str_Rules* r, str_Value* v, FILE* fp1, int nbNumbers);
void freetb();
char Input();
#endif
