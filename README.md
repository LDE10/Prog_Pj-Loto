# Prog_Pj-Loto

## À propos

Le projet consiste à réaliser un programme en C, permettant de faire une analyse (statistique) des numéros de loto que l’on a joué.

## Table des matières

- 🪧 [OBJECTIF](#OBJECTIF)
- 📦 [Prérequis](#prérequis)
- 🚀 [Installation](#installation)
- 🛠️ [Utilisation](#utilisation)
- 📚 [Documentation](#documentation)

## Prérequis

exemple du rendu final

<img width="425" height="277" alt="image" src="https://github.com/user-attachments/assets/a6587d39-e90f-4303-aec3-39a5e9e3dd37" />

## Utilisation
(Important :warning:) Lancer le code avec ce fichier Prog_Pj-Loto_LDE-LMY-CAH.vcxproj ou le .sln.

Au lancement du programme l'utilisateur aura  6 choix possible :

<img width="955" height="222" alt="image" src="https://github.com/user-attachments/assets/738c11f4-ff43-4681-8fd4-1c3ef72c37f3" />

G (Ficher) : Sélection d'un ficher ou création de fichier

<img width="407" height="357" alt="image" src="https://github.com/user-attachments/assets/b945033c-fcc0-4d13-a625-4b83fa028ea3" />


Si un nom de fichier n'éxiste pas, l'utilisateur à le choix d'en créer un nouveau
<img width="777" height="210" alt="image" src="https://github.com/user-attachments/assets/9e7cbed5-d23c-42c8-8067-2cf48be0ca49" />



M (Mode) : Sélection de deux modes : simulation ou normal

  * Simulation : le jeu se fera automatiquement en affichant les résultats
  * Normal : l'utilisateur pourra choisir 6 chiffre lors du tirage

<img width="442" height="66" alt="image" src="https://github.com/user-attachments/assets/590fde67-66f4-483e-9999-88d625dccac7" />


T (Tirage) : le tirage du loto changera en fonction du mode choisi. En mode normal l'utilisateur à le choix de modifier un numéro choisi 

  * Mode simu :

<img width="767" height="247" alt="image" src="https://github.com/user-attachments/assets/29809bbd-bf66-4b8b-893d-7763668886b1" />

  * Mode normal :

<img width="842" height="647" alt="image" src="https://github.com/user-attachments/assets/788639ab-d8ce-47ce-93a4-2dcb3a9913a6" />

:warning: Attention : L'utilisateur ne peut pas choisir le tirage sans avoir choisi un fichier. Le mode est par défaut séléctionné en mode simulation


R (Règle) : Affiche les informations concernant les conditions de jeu du fichier choisi (ex : valeur min et max, numéro complémentaire etc)

<img width="482" height="120" alt="image" src="https://github.com/user-attachments/assets/ae9f5b30-73ad-4dac-8cd3-7fe7d65e44bc" />


H (Historique) : Affiche toute la liste des tirages effectués jusqu'à présent

<img width="647" height="212" alt="image" src="https://github.com/user-attachments/assets/ad630438-7a64-4519-ba89-b4ccc7b879a5" />

:warning: Attention : Lors des permiers tirages les 6 moins bon numéros sont pris dans l'ordre croissant. Il éxiste plus de 6 chiffres qui sont moins bon, plus il y aura de tirage plus le résultat sera précis


Q (Quitter) : Ferme le programme et sauvegarde les tirages effectués dans le fichier choisi

<img width="687" height="26" alt="image" src="https://github.com/user-attachments/assets/035b89d2-00e1-4ec4-b3e3-ebbf31f16f7d" />

### Langages & Frameworks

Codé entièrement en C avec VisualStudio : [Main](https://github.com/LDE10/Prog_Pj-Loto/tree/main/Prog_Pj-Loto_LDE-LMY-CAH/Prog_Pj-Loto_LDE-LMY-CAH)

## Documentation

[Cahier des charges](https://github.com/LDE10/Prog_Pj-Loto/blob/main/PROJET_PROG_V02.pdf)

Journal de travail :
 * [Journal de travail groupe](https://github.com/LDE10/Prog_Pj-Loto/blob/main/journal_de_travail/journal_de_travail_Groupe.pdf)
 * [CAH](https://github.com/LDE10/Prog_Pj-Loto/blob/main/journal_de_travail/journal_de_travail_CAH.pdf)
 * [LDE](https://github.com/LDE10/Prog_Pj-Loto/blob/main/journal_de_travail/journal_de_travail_LDE.pdf)
 * [LMY](https://github.com/LDE10/Prog_Pj-Loto/blob/main/journal_de_travail/journal_de_travail_LMY.pdf)
 

Structogramme : 
 * [Main](https://github.com/LDE10/Prog_Pj-Loto/blob/main/Structogramme/Prog_Pj-Loto_LDE-LMY-CAH_main.pdf)
 * [Affichage Gestion](https://github.com/LDE10/Prog_Pj-Loto/tree/main/Structogramme/AffichageGestion)
 * [Gestion Loto](https://github.com/LDE10/Prog_Pj-Loto/tree/main/Structogramme/GestionLoto)
 * [Gestion Valeur Gagnant](https://github.com/LDE10/Prog_Pj-Loto/tree/main/Structogramme/GestionValeurLotoGagnant)
 * [Loto Rules](https://github.com/LDE10/Prog_Pj-Loto/tree/main/Structogramme/LotoRules)
