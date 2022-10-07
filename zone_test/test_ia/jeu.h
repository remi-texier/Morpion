#ifndef JEU_H
#define JEU_H
//Norme snake case
//Tout en miniscule et separation par underscore
    // creation enum,struct ->maj pour la premiere lettre et separation par underscore, pour le reste tout en minuscule
    // const, Macro ->tout en maj
    // variable -> tout en minuscule et separer par underscore
    //nom fonction -> comme variable

#define X 4
#define Y 4

//Enumeration qui cree un type joueur ou Ia
typedef struct Symbol
{
    char symbol;
}Symbol, *P_symbol;

//Structure qui represente une case voisine
typedef struct neightbour
{
    char x;
    char y;
}Neightbour, *P_neightbour;

//Structure qui represente une case du plateau de jeu
typedef struct Cell
{
    Symbol Owner;
    char x;
    char y;
    float evaluation;
    P_neightbour P_arr_neightbour;
}Cell, *P_cell;

//Structure qui represente une case appartenant a un ia
typedef struct Symbol_tokens
{
    int x, y;
    int evaluation;
}Symbol_tokens, *P_symbol_tokens;

//Structure qui represente les données à manipuler pour gerer le plateau de jeu
typedef struct Data_board
// {
//     Game_board Board[X][Y];
//     P_Ia_army P_board_ia;//Allouer dynamiquement
//     P_player_army P_board_player;//Allouer dynamiquement
// }Data_board, *P_data_board;
#endif