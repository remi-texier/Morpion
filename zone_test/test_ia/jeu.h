#ifndef JEU_H
#define JEU_H
//Norme snake case
//Tout en miniscule et separation par underscore
    // creation enum,struct ->maj pour la premiere lettre et separation par underscore, pour le reste tout en minuscule
    // const, Macro ->tout en maj
    // variable -> tout en minuscule et separer par underscore
    //nom fonction -> comme variable

//Macro pour predefinir la taille du tableau qui se fera avec le preprocesseur
#define X 4
#define Y 4

//Structure qui represente une case voisine
typedef struct neightbour
{
    int x;
    int y;
    //Voir pour mettre d'autre infos si necessaire
    //...
}Neightbour, *P_neightbour;

//Structure qui represente une case du plateau de jeu
typedef struct Game_board
{
    int x, y;
    unsigned char owner;
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
    P_player_army P_array_player_army;//Tableau à X (joueur1, joueur2... dans un ordre connu à l'avance) et Y dimensions (allocation dynamique en un seule bloc avec des realloc à chaque tour), x -> nb joueur(exemple : x[0] -> joueur 1 et à un tour x, il possede n pions sur le plateau y[0] -> infos pions numero 1), y -> nb de pions utilise par un joueur( + 1 à chaque tour pour tout les joueurs puisqu'ils joueront forcement un pion(meme nombre de pion pour tout les joueurs))
    char *p_array_owner; // tableau de char qui representera plusierus charactere qu'on associera à un joueur
}Data_board, *P_data_board;
#endif