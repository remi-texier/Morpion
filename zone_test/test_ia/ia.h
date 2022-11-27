#ifndef IA_H
#define IA_H

#include "jeu.h"

#define MINEVAL -100000;
#define MAXEVAL 100000;

void coup_ordi(P_data_board const P_data, int prof, int n_tuple, char player);
int minimax(P_data_board const P_data, int prof, int n_tuple, bool Est_Max);

//--------------------------------------------IMPORTANT-------------------------------------------//
//L ia est en cours de developpement donc sont niveau est definit à facile
// Pour le moment elle est capable de jouer qu'avec deux joueurs (brider dans les parametres du jeu)
//--------------------------------------------IMPORTANT-------------------------------------------//

/*
 * Fonction qui permet de calculer le coup de l'IA
* @param p_data_board : pointeur sur la structure de donnée du jeu
* @param prof : profondeur de l'arbre de recherche
* @param n_tuple : nombre de pions alignés pour gagner
* @param courant_player : joueur courant 
*/
void calcIA(P_data_board p_data_board, int prof, int n_tuple, char player);
 

/*
 * Fonction de calcul de l'IA
* @param p_data_board : pointeur sur la structure de donnée du jeu
* @param prof : profondeur de l'arbre de recherche
* @param n_tuple : nombre de pions alignés pour gagner
* @param alpha : valeur de alpha
* @param beta : valeur de beta
* @return : score de l'IA
*/
int calcMin(P_data_board p_data_board, int prof, int n_tuple, int alpha, int beta);

/*
 * Fonction de calcul de l'IA
* @param p_data_board : pointeur sur la structure de donnée du jeu
* @param prof : profondeur de l'arbre de recherche
* @param n_tuple : nombre de pions alignés pour gagner
* @param alpha : valeur de alpha
* @param beta : valeur de beta
* @return : alpha
*/
int calcMax(P_data_board p_data_board, int prof, int n_tuple, int alpha, int beta);

unsigned char get_symbol(const P_data_board databoard);


/*
    * Fonction qui permet de calculer le score d'une case
    * @param : nombre de pions alignés
    * @param : nombre de pions joueur
    *@return : score de la case
*/
int calcScore(int cntpion, int cntjoueur);

/*
    * Fonction qui permet d'evaluer le score d'une case
    * @param : Pointeur sur la structure de donnée du jeu
    * @param : nombre de pions alignés pour gagner
    *@return : score de la case
*/
int evalue(const P_data_board const p_data_board, int n_tuple);

/*
    * Fonction qui permet de compter le nombre de pions
    * @param : Pointeur sur la structure de donnée du jeu
    *@return : nombre de pions
*/
int comptePions(P_data_board p_data_board);


#endif