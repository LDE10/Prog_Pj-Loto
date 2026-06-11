//--------------------------------------------------------------------------//
// Nom du projet		: Prog_pj-Loto
// Nom du fichier		: GestionAffichage
// Date de création		: 18.05.2026
// Date de modification : 
//
// Auteur				: LDE
//
// Version				: 0.0
//
// Description			: Gestion de l'affichage
// 
//--------------------------------------------------------------------------//
//-- librairie standard --//
#include <stdio.h>
#include <string.h>
//librairie perso
#include "GestionAffichage.h"


// fonction
// nom fonction  : ValG
// paramètre In  : tbMostWinning, tbLeastWinning
// paramètre out : -
// paramètre in/out : -
// description  : Affiche le numéro les plus sortie et le moins sorti
void ValG(int* tbMostWinning, int* tbLeastWinning)
{
	printf("Le chiffre le plus gagnant est %d\n",tbMostWinning[0]);
	printf("Le chiffre le moins gagnant est %d\n", tbLeastWinning[0]);
}
// fonction
// nom fonction  : Bestchiffres
// paramètre In  : tbMostWinning, tbLeastWinning
// paramètre out : -
// paramètre in/out : -
// description  : Afficher les chiffres les plus et moins gagnant
void Bestchiffres(int* tbMostWinning, int* tbLeastWinning)
{
	printf("les 6 meilleurs chiffres sorties le plus souvent sont\n %d, %d, %d, %d, %d, %d\n",
		tbMostWinning[0], tbMostWinning[1], tbMostWinning[2], tbMostWinning[3], tbMostWinning[4], tbMostWinning[5]);

	printf("les 6 chiffres les moins sorties sont\n %d, %d, %d, %d, %d, %d\n",
		tbLeastWinning[0], tbLeastWinning[1], tbLeastWinning[2], tbLeastWinning[3], tbLeastWinning[4], tbLeastWinning[5]);
}
