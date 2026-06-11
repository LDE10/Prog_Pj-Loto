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
// 						  
//----------------------------------------------------------------------------------//
#ifndef LOTORULES_H
#define LOTORULES_H
typedef struct
{
	char* NameLoto;
	int ValMax;
	int ValMin;
	char NumCompl;
	int NumComplMax;
	int NumComplMin;
} str_Rules;

extern str_Rules regle;

extern char NbCompl;

extern char FilePath[100];
extern char length;
extern char Name[100];
extern char* strtxt;


void ConfigRules(str_Rules* r);
void RecupData(str_Rules* d, FILE* fp1);
void WriteConfig(str_Rules* r, FILE* fp1);
#endif
