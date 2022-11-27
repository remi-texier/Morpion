#ifndef JEU_H
#define JEU_H
//Norme snake case
//Tout en miniscule et separation par underscore
    // creation enum,struct ->maj pour la premiere lettre et separation par underscore, pour le reste tout en minuscule
    // const, Macro ->tout en maj
    // variable -> tout en minuscule et separer par underscore
    //nom fonction -> comme variable


//---------------------------------------------IMPORTANT--------------------------------------------------------------------------------------------------
/*------Certaines parties sont en commentaire car se sont des fonctionalitées que j'integrerais par la suite pour optimiser mon ia.-------------------
--------Cependant, afin d'optimiser l'ia actuel au maximum pour le premier rendu, je vais desactiver cette fonctionalité-------*/
//---------------------------------------------------------------------------------------------------------------------------------------

//Librairie(s) standard
#include <stdbool.h>

//Macro pour predefinir la taille du tableau qui se fera avec le preprocesseur
#define X 7
#define Y 6

//Structure qui represente une case voisine
// [0] -> case du haut à 12 heures et on fait le tour dans le sens des aiguilles d'une montre jusqu'à [_]
typedef struct neightbour
{
    int x; // Si vide -> -1
    int y;
    //Voir pour mettre d'autre infos si necessaire
    //...
}Neightbour, *P_neightbour;

//Structure qui represente une case du plateau de jeu
typedef struct Cell
{
    int x, y;
    unsigned char owner; // vide = 0(48 en ascci), voir tableau de char pour les autres joueurs
    int evaluation; //-999 si pas d'evaluation
    P_neightbour P_array_neightbour; // tableau de case voisine 
    //Voir pour mettre d'autre infos si necessaire
    //...
    
}Game_board, *P_game_board;

//Structure qui represente une case appartenant à un joueur/ia/vide
//----------------IMPORTANT------------------
//Cette structure permettra  de stocker dans un tableau des infos de tous les pions de chaque joueur d'une partie afin de faciliter les calculs si on souhaite par exemple calculer le nombre de pions d'un joueur ou par exemple acceder rapidement à une case vide sans devoir parcourir tout le plateau,
//ou encore eviter de devoir parcourir le gros tableau 2D à la recherche des infos des cases presente dans un n_uplet puisque qu'il suffira de regarder si les positions presentes dans le n_tuple (predefini à l'avance...) sont presentes dans le tableau qui va contenir les positions de chaque pions de chaque joueur
//--------------------------------------------
typedef struct Player_army
{
    int x, y;
    //Voir pour mettre d'autre infos si necessaire
    //...
}Player_army, *P_player_army;

//Structure qui represente les données à manipuler pour gerer le plateau de jeu
typedef struct Data_board
{
    Game_board Board[X][Y];
    //P_player_army P_array_player_army;//Tableau à X (joueur1, joueur2... dans un ordre connu à l'avance) et Y dimensions (allocation dynamique en un seule bloc avec des realloc à chaque tour), x -> nb joueur(exemple : x[0] -> joueur 1 et à un tour x, il possede n pions sur le plateau y[0] -> infos pions numero 1 à mettre en corelation avec tableau de la map complete), y -> nb de pions utilise par un joueur( + 1 à chaque tour pour tout les joueurs puisqu'ils joueront forcement un pion(meme nombre de pion pour tout les joueurs))
    char *p_array_owner; // tableau de char qui representera plusieurs charactere qu'on associera à un joueur ([0] -> joueur 1, joueur n -> [n]...) et une deuxieme dimension avec le type : 0->humain et 1 -> IA
    P_player_army P_array_free; // tableau de case vide
    int nb_player; // nombre de joueur
    int nb_free; // nombre de case vide
}Data_board, *P_data_board;

/*
 * @Brief Fonction qui permet d'initialiser la structure Data_board
 * @param : P_data_board -> pointeur sur la structure à initialiser
 * @param : int -> nombre de joueur humain
 * @return : P_data_board -> retourne l'adresse de l a structure initialiser
*/
P_data_board init_data_board(const int nb_joueur, const int nb_humain);

/*
 * @Brief Fonction qui permet d'initialiser le tableau de structure player_army qui represente les cases vides du plateau de jeu
 * @param : void
 * @return : Player_army* -> retourne l'adresse du tableau de structure initialiser
*/
Player_army *init_array_free();

/*
 * @Brief Fonction qui permet d'initialiser le tableau de structure Game_board
 * @param : P_data_board -> pointeur sur la structure Data_board en const car on ne veut pas modifier l'adress pointer par le pointeur de tableau
 * @return : void
*/
void init_game_board(Game_board (* const P_game_board)[Y]);

/*
 * @Brief Fonction qui permet d'initialiser le tableau de charactere qui permettra de representer les joueurs par un charactere fournit par le tableau
 * @param : nb_player -> nombre de joueur
 * @param : nb_humain -> nombre de joueur humain
 * @return : pointer to char -> retourne l'adresse du tableau de charactere
*/
char *init_array_owner(const int nb_player, int nb_humain);

/*
 * @Brief Fonction qui permet d'initialiser le tableau de structure qui represente les pions voisins d'une case
 * @param : void
 * @return : P_array_pawn -> retourne l'adresse du tableau de structure
*/
P_neightbour init_array_neightbour();

/*
 * @Brief Fonction qui permet d'initialiser le tableau de structure qui represente les pions de chaque joueur
 * @param : void
 * @return : P_array_pawn -> retourne l'adresse du tableau de structure
*/
//Player_army *init_array_player(const int nb_player);

/*
 * @Brief Fonction qui permet de calculer les voisins de chaque case du plateau de jeu
 * @param : P_data_board -> pointeur sur la structure Data_board en const car on ne veut pas modifier l'adress pointer par le pointeur de tableau
 * @return : void
*/
void calc_neightbour(Data_board * const P_data_board);

/*
 * @Brief Fonction qui permet de mettre la structure Data_board 
 * @param : P_data_board -> pointeur sur la structure Data_board en const car on ne veut pas modifier l'adress pointer par le pointeur de tableau
 * @param : x -> position x de la case
 * @param : y -> position y de la case
 * @return : bool -> retourne true ou false si il y a eu une erreur
*/
bool update_data_board(P_data_board const p_data_board, const int x, const int y, const char owner);

/*
 * @Brief Fonction qui permet de donner une valeur d'evaluation à une case
 * @param : P_data_board -> pointeur sur la structure Data_board en const car on ne veut pas modifier l'adress pointer par le pointeur de tableau
 * @param : x -> position x de la case
 * @param : y -> position y de la case
 * @return : bool -> retourne true ou false si il y a eu une erreur
*/
bool update_evaluation(P_data_board const p_data_board, const int x, const int y, const int evaluation);

/*
 * @Brief Fonction qui permet d'afficher le plateau de jeu
 * @param : P_data_board -> pointeur sur la structure Data_board en const car on ne veut pas modifier l'adress pointer par le pointeur de tableau
 * @param : x -> position x de la case
 * @param : y -> position y de la case
 * @return : bool -> retourne true ou false si il y a eu une erreur
*/
void print_board_game(P_data_board const p_data_board);

/*
 * @Brief Fonction qui permet de savoir si il y a un n tuplet sur le plateau de jeu
 * @param : P_data_board -> pointeur sur la structure Data_board en const car on ne veut pas modifier l'adress pointer par le pointeur de tableau
 * @param : n -> nombre de pion a aligner pour gagner
 * @return : char -> retourne le charactere du joueur qui a gagner ou '0' si il n'y a pas de gagnant
*/
char check_n_tuplet(const P_data_board const p_data_board, const int n);


/*
 * @Brief Fonction qui permet de savoir si il y a encore des cases vide sur le plateau de jeu
 * @param : P_data_board -> pointeur sur la structure Data_board en const car on ne veut pas modifier l'adress pointer par le pointeur de tableau
 * @return : bool -> retourne true ou false si il y a encore des cases vide
*/
bool check_free_case(const P_data_board const p_data_board);

//Fonction pour demander à chaque joueur de jouer et rentrer son coup
/*
 * @Brief Fonction qui permet de demander à chaque joueur de jouer et rentrer son coup ainsi que les ia
 * @param : P_data_board -> pointeur sur la structure Data_board en const car on ne veut pas modifier l'adress pointer par le pointeur de tableau
 * @param : n_tuplet -> nombre de pion a aligner pour gagner
 * @return : void
*/
void play_turn(const P_data_board const p_data_board, const int n_tuplet);

/*
 * @Brief Fonction qui permet de demander à chaque joueur d'annuler son coup
 * @param : P_data_board -> pointeur sur la structure Data_board en const car on ne veut pas modifier l'adress pointer par le pointeur de tableau
 * @param : x -> position x de la case
 * @param : y -> position y de la case
 * @return : void
*/
void to_cancel_move(P_data_board  p_data_board, int x, int y);

/*
 * @Brief Fonction qui permet de liberer la memoire du jeu
 * @param : P_data_board -> pointeur sur la structure Data_board en const car on ne veut pas modifier l'adress pointer par le pointeur de tableau
 * @return : void
*/
void free_memory(P_data_board p_data_board);

/*
 * @Brief Fonction qui de gerer le menu
 * @param : P_data_board -> pointeur sur la structure Data_board en const car on ne veut pas modifier l'adress pointer par le pointeur de tableau
 * @return : void
*/
void loop_game();


#endif