#ifndef TEST_H
#define TEST_H

#include "jeu.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*
 * @Brief Fonction qui permet d'afficher le contenu des differentes structures
 * @param : P_data_board -> adresse de la structure à liberer
 * @param : nb_joueur -> nombre de joueur de la partie
 * @return : void
*/
void print_data_struct(const P_data_board const P_data, const int nb_joueur);

/*
 * @Brief Fonction qui permet de tester les fonctions de mise à jour d'un coup
 * @param : P_game_board -> adresse du tableau de structure à liberer
 * @param : x -> coordonnée x du coup
 * @param : y -> coordonnée y du coup
 * @param : owner -> joueur qui joue le coup
 * @param : evaluation -> evaluation du coup
 * @return : void
*/
void test_function_update(const P_data_board const P_data, const int x, const int y, const char owner, const int evaluation);

/*
 * @Brief Fonction qui permet de tester le check n_tuplet et si il y a encore de la place pour jouer
 * @param : P_data_board -> adresse de la structure à liberer
 * @return : void
*/
void test_function_n_tuple_free_case(const P_data_board const P_data);

#endif