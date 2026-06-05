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
#ifndef GESTIONVALEURLOTOGAGNANTE_H
#define GESTIONVALEURLOTOGAGNANTE_H



void InsertValue(str_Value* v, str_Rules* r);
int DeleteLastValue(str_Value* v, char Nbelement);
void ModifiedLastValue(str_Value* v, char Nbelement);
int MostWinning(str_Value* v, int nbNumbers, str_Rules* r, int rank);
int LeastWinning(str_Value* v, int nbNumbers, str_Rules* r, int rank);
#endif
