#include "jeu.h"

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
    for (int i=0; i<COMBO_LENGHT; i--) {
        result += get_nuplet(board, x, y, dir, joueur);
        //pas sûr de ça faut que je vérifie
        x += dir.x;
        y += dir.y;
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

//