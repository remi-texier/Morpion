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
typedef enum State_board_case
{
    IA, JOUEUR, VIDE
}State;

//Structure qui represente le plateau de jeu
typedef struct Game_board
{
    int x, y;
    State Owner;
}Game_board, *P_game_board;

//Structure qui represente tous les pions de l'IA
typedef struct Ia_army
{
    int x, y;
}Ia_army, *P_Ia_army;

//Structure qui represente tous les pions du joueur
typedef struct Player_army
{
    int x, y;
}Player_army, *P_player_army;

//Structure qui represente les données du plateau de jeu
typedef struct Data_board
{
    Game_board Board[X][Y];
    P_Ia_army P_board_ia;//Allouer dynamiquement
    P_player_army P_board_player;//Allouer dynamiquement
}Data_board, *P_data_board;



#endif