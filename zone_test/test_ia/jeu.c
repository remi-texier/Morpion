#include "jeu.h"
#include <stdio.h>
#include <stdlib.h>

/*
 * @Brief Fonction qui permet d'initialiser la structure Data_board
 * @param : void
 * @return : P_data_board -> retourne l'adresse de l a structure initialiser
*/
P_data_board *init_data_board()
{
    P_data_board Data_board = malloc(sizeof(*Data_board));
    if (Data_board == NULL)
    {
        fprintf(stderr, "Erreur d'allocation de la structure Data_board\n");
    }

    //Initialisation du tableau de char qui represente les joueurs
    Data_board->p_array_owner = init_array_owner(NB_PLAYER);

    //Initialisation du tableau 2D qui represente le plateau de jeu
    //...

    //Initialisation du tableau de structure qui represente les pions de chaque joueur
    //...
}

/*
 * @Brief Fonction qui permet d'initialiser le tableau de structure Game_board
 * @param : P_data_board -> pointeur sur la structure Data_board en const car on ne veut pas modifier l'adress pointer par le pointeur de tableau
 * @return : void
*/
void init_game_board(Game_board (* const P_game_board)[Y])
{
    for (int i = 0; i < X; i++)
    {
        for (int j = 0; j < Y; j++)
        {
            P_game_board[i][j].x = i;
            P_game_board[i][j].y = j;
            P_game_board[i][j].owner = 0;// a modif
            P_game_board[i][j].evaluation = -999;// a modif
            //P_game_board[i][j].P_array_neightbour = init_array_neightbour(i, j);
        }
    }
}

/*
 * @Brief Fonction qui permet d'initialiser le tableau de charactere qui permettra de representer les joueurs par un charactere fournit par le tableau
 * @param : nb_player -> nombre de joueur
 * @return : pointer to char -> retourne l'adresse du tableau de charactere
*/
char *init_array_owner(const int nb_player)
{
    char *array_owner = malloc(sizeof(char) * nb_player);
    if (array_owner == NULL)
    {
        fprintf(stderr, "Erreur d'allocation du tableau de char qui represente les joueurs\n");
    }

    for(int i = 0; i < nb_player; i++)
    {
        for(int j = 65; j < 65 + nb_player; j++)
        {
            array_owner[i] = j;// 65 = A, 66 = B...
        }
    }
    return array_owner;
}






























































/*
// int get_possibilities(int** board, vec dir) {
//     int possibilities = 0;
//     for (int i = 0; i < COMBO_LENGHT; i++) {
//         if ;
//     }
//     return possibilities;
// }

//fonction qui fait la somme des resultat des get_nuplet, pour toute une ligne
int get_full_line(int** board, int x, int y, Vec dir, Symbol joueur) {
    int result = 0;
    for (int i=0; i>-COMBO_LENGHT; i--) {
        result += get_nuplet(board, x, y, dir, joueur);
        x -= dir.x;
        y -= dir.y;
    }
    return result;
}


//retourne le nombre d'elements commun dans un n-uplet, retourne 0 si il y en a des différents
int get_nuplet(int** board, int x, int y, Vec dir, Symbol joueur) {
    int num_symbols = 0;
    for (int i=0; i<COMBO_LENGHT; i++) {
        //si case = joueur on continue, sinon la ligne est fermée
        Symbol case = board[x+(i*dir.x)][y+(i*dir.y]
        if ( case != joueur && case != EMPTY) {
            return 0;
        }
        else num_symbols++;
    }
    return num_symbols;
}
*/
//
