#include "jeu.h"
#include "ia.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

//static int nb_tours_update = 0;

/*
 * @Brief Fonction qui permet d'initialiser la structure Data_board
 * @param : P_data_board -> pointeur sur la structure à initialiser
 * @param : int -> nombre de joueur humain
 * @return : P_data_board -> retourne l'adresse de l a structure initialiser
*/
P_data_board init_data_board(const int nb_joueur, const int nb_humain)
{
    P_data_board Data_board = malloc(sizeof(*Data_board));
    if (Data_board == NULL)
    {
        fprintf(stderr, "Erreur d'allocation de la structure Data_board\n");
    }

    //Initialisation du tableau de char qui represente les joueurs
    Data_board->p_array_owner = init_array_owner(nb_joueur, nb_humain);

    //Initialisation du tableau 2D qui represente le plateau de jeu
    init_game_board(Data_board->Board);

    //---------------------------------------------IMPORTANT--------------------------------------------------------------------------------------------------
    /*------C'est en commentaire car c est une fonctionalite que j'integrerais par la suite pour optimiser mon ia.-------------------
    --------Cependant, afin d'optimiser l'ia actuel au maximum pour le premier rendu, je vais desactiver cette fonctionalité-------*/
    //---------------------------------------------------------------------------------------------------------------------------------------

    //Initialisation du tableau de structure qui represente les pions de chaque joueur
    //Data_board->P_array_player_army = init_array_player(nb_joueur);

    //Calcule des voisins de chaque case du plateau de jeu
    calc_neightbour(Data_board);

    //initialisation du tableau de structure qui represente les pions libres
    Data_board->P_array_free = init_array_free();

    //Initialisation du nombre de joueur
    Data_board->nb_player = nb_joueur;

    //Initialisation du nombre de pions libres
    Data_board->nb_free = X * Y;

    return Data_board;
}

/*
 * @Brief Fonction qui permet d'initialiser le tableau de structure player_army qui represente les cases vides du plateau de jeu
 * @param : void
 * @return : Player_army* -> retourne l'adresse du tableau de structure initialiser
*/
Player_army *init_array_free()
{
    Player_army *p_array_free = malloc(sizeof(*p_array_free) * X * Y);
    if (p_array_free == NULL)
    {
        fprintf(stderr, "Erreur d'allocation du tableau de structure qui represente les pions libres\n");
    }
    
    unsigned int compteur = 0;
    for(int i = 0; i < X; i++)
    {
        for(int j = 0; j < Y; j++)
        {
            p_array_free[compteur].x = i;
            p_array_free[compteur].y = j;
            compteur++;
        }
    }
    
    return p_array_free;
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
            P_game_board[i][j].owner = 48; // vide = 0(48 en ascci)
            P_game_board[i][j].evaluation = -999; // -999 si pas d'evaluation
            P_game_board[i][j].P_array_neightbour = init_array_neightbour();
        }
    }

    fprintf(stdout, "Initialisation du tableau 2D qui represente le plateau de jeu\n");
}

/*
 * @Brief Fonction qui permet d'initialiser le tableau de charactere qui permettra de representer les joueurs par un charactere fournit par le tableau
 * @param : nb_player -> nombre de joueur
 * @param : nb_humain -> nombre de joueur humain
 * @return : pointer to char -> retourne l'adresse du tableau de charactere
*/
char *init_array_owner(const int nb_player, int nb_humain)
{
    char *array_owner = malloc(sizeof(char) * nb_player * 2);
    if (array_owner == NULL)
    {
        fprintf(stderr, "Erreur d'allocation du tableau de char qui represente les joueurs\n");
    }

    int caractere = 65;
    for(int i = 0; i < nb_player; i++)
    {
        for(int j = 0; j < 2; j++)
        {
            if(j < 1)
            {
                array_owner[i * 2 + j] = caractere; // 65 = A, 66 = B...
                caractere++;
            }
            else
            {
                if(nb_humain > 0)
                {
                    array_owner[i * 2 + j] = 48; // 0 = Humain
                    nb_humain--;
                }
                else
                {
                    array_owner[i * 2 + j] = 49; // 1 = IA
                }
            }
        } 
    }

    fprintf(stderr, "Initialisation du tableau de char qui represente les joueurs\n");

    return array_owner;
}

/*
 * @Brief Fonction qui permet d'initialiser le tableau de structure qui represente les pions voisins d'une case
 * @param : void
 * @return : P_array_pawn -> retourne l'adresse du tableau de structure
*/
P_neightbour init_array_neightbour()
{
    P_neightbour array_neightbour = malloc(sizeof(*array_neightbour) * 8);
    if (array_neightbour == NULL)
    {
        fprintf(stderr, "Erreur d'allocation du tableau de structure qui represente les voisins\n");
    }

    for(int i = 0; i < 8; i++)
    {
        array_neightbour[i].x = -1;
        array_neightbour[i].y = -1;
    }

    //fprintf(stderr, "Initialisation du tableau de structure qui represente les voisins\n");

    return array_neightbour;   
}

//---------------------------------------------IMPORTANT--------------------------------------------------------------------------------------------------
/*------C'est en commentaire car c est une fonctionalite que j'integrerais par la suite pour optimiser mon ia.-------------------
--------Cependant, afin d'optimiser l'ia actuel au maximum pour le premier rendu, je vais desactiver cette fonctionalité-------*/
//---------------------------------------------------------------------------------------------------------------------------------------

/*Player_army *init_array_player(const int nb_player)
{
    P_player_army array_player = malloc(sizeof(*array_player) * (nb_player + 1));
    if (array_player == NULL)
    {
        fprintf(stderr, "Erreur d'allocation du tableau de structure qui represente les pions\n");
    }

    for(int i = 0; i < nb_player; i++)
    {
        array_player[i].x = -1;
        array_player[i].y = -1;
    }

    fprintf(stderr, "Initialisation du tableau de structure qui represente les pions de chaque joueur(s)\n");

    return array_player;
}*/

/*
 * @Brief Fonction qui permet de calculer les voisins de chaque case du plateau de jeu
 * @param : P_data_board -> pointeur sur la structure Data_board en const car on ne veut pas modifier l'adress pointer par le pointeur de tableau
 * @return : void
*/
void calc_neightbour(Data_board * const P_data_board)
{
    for (int i = 0; i < X; i++)
    {
        for (int j = 0; j < Y; j++)
        {
            //Premiere case voisine
            if((j - 1) >= 0 && (j - 1) < Y)
            {
                P_data_board->Board[i][j].P_array_neightbour[0].x = i;
                P_data_board->Board[i][j].P_array_neightbour[0].y = j - 1;
            }
            else
            {
                P_data_board->Board[i][j].P_array_neightbour[0].x = -1;
                P_data_board->Board[i][j].P_array_neightbour[0].y = -1;
            }

            //Deuxieme case voisine
            if((j - 1) >= 0 && (j - 1) < Y && (i + 1) >= 0 && (i + 1) < X)
            {
                P_data_board->Board[i][j].P_array_neightbour[1].x = i + 1;
                P_data_board->Board[i][j].P_array_neightbour[1].y = j - 1;
            }
            else
            {
                P_data_board->Board[i][j].P_array_neightbour[1].x = -1;
                P_data_board->Board[i][j].P_array_neightbour[1].y = -1;
            }

            //Troisieme case voisine
            if((i + 1) >= 0 && (i + 1) < X)
            {
                P_data_board->Board[i][j].P_array_neightbour[2].x = i + 1;
                P_data_board->Board[i][j].P_array_neightbour[2].y = j;
            }
            else
            {
                P_data_board->Board[i][j].P_array_neightbour[2].x = -1;
                P_data_board->Board[i][j].P_array_neightbour[2].y = -1;
            }

            //Quatrieme case voisine
            if((j + 1) >= 0 && (j + 1) < Y && (i + 1) >= 0 && (i + 1) < X)
            {
                P_data_board->Board[i][j].P_array_neightbour[3].x = i + 1;
                P_data_board->Board[i][j].P_array_neightbour[3].y = j + 1;
            }
            else
            {
                P_data_board->Board[i][j].P_array_neightbour[3].x = -1;
                P_data_board->Board[i][j].P_array_neightbour[3].y = -1;
            }

            //Cinquieme case voisine
            if((j + 1) >= 0 && (j + 1) < Y)
            {
                P_data_board->Board[i][j].P_array_neightbour[4].x = i;
                P_data_board->Board[i][j].P_array_neightbour[4].y = j + 1;
            }
            else
            {
                P_data_board->Board[i][j].P_array_neightbour[4].x = -1;
                P_data_board->Board[i][j].P_array_neightbour[4].y = -1;
            }

            //Sixieme case voisine
            if((j + 1) >= 0 && (j + 1) < Y && (i - 1) >= 0 && (i - 1) < X)
            {
                P_data_board->Board[i][j].P_array_neightbour[5].x = i - 1;
                P_data_board->Board[i][j].P_array_neightbour[5].y = j + 1;
            }
            else
            {
                P_data_board->Board[i][j].P_array_neightbour[5].x = -1;
                P_data_board->Board[i][j].P_array_neightbour[5].y = -1;
            }

            //Septieme case voisine
            if((i - 1) >= 0 && (i - 1) < X)
            {
                P_data_board->Board[i][j].P_array_neightbour[6].x = i - 1;
                P_data_board->Board[i][j].P_array_neightbour[6].y = j;
            }
            else
            {
                P_data_board->Board[i][j].P_array_neightbour[6].x = -1;
                P_data_board->Board[i][j].P_array_neightbour[6].y = -1;
            }

            //Huitieme case voisine
            if((j - 1) >= 0 && (j - 1) < Y && (i - 1) >= 0 && (i - 1) < X)
            {
                P_data_board->Board[i][j].P_array_neightbour[7].x = i - 1;
                P_data_board->Board[i][j].P_array_neightbour[7].y = j - 1;
            }
            else
            {
                P_data_board->Board[i][j].P_array_neightbour[7].x = -1;
                P_data_board->Board[i][j].P_array_neightbour[7].y = -1;
            }    
        }
    }

    fprintf(stderr, "Calcul des voisins de chaque case du plateau de jeu\n");
}

bool update_data_board(P_data_board const p_data_board, const int x, const int y, const char owner)
{
    //Verifie que le x et y est bien dans le plateau
    if(x >= 0 && x < X && y >= 0 && y < Y)
    {
        //Verifie que la case n'est pas deja occuper
        if(p_data_board->Board[x][y].owner == 48)
        {
            //Verifie que le owner est bien un des deux joueurs
            /*for(int i = 0; i < p_data_board->nb_player; i++)
            {
                for(int j = 0; j < 2; j++)
                {
                    if(j == 0)
                    {
                        if(p_data_board->p_array_owner[i * 2 + j] == owner)
                        {
                            fprintf(stderr, "Owner est bon\n");
                            break;
                        }
                    }
                }
            }*/

            //printf("aucun proprietaire\n");

        }
        else
        {
            fprintf(stderr, "Erreur : La case (%d, %d) du plateau de jeu est deja occuper par le joueur %c\n", x, y, p_data_board->Board[x][y].owner);
            return false;
        }
    }
    else
    {
        fprintf(stderr, "Erreur : La case (%d, %d) du plateau de jeu n'existe pas\n", x, y);
        return false;
    }

    //On met a jour le plateau de jeu
    p_data_board->Board[x][y].owner = owner;

    //---------------------------------------------IMPORTANT--------------------------------------------------------------------------------------------------
    /*------C'est en commentaire car c est une fonctionalite que j'integrerais par la suite pour optimiser mon ia.-------------------
    --------Cependant, afin d'optimiser l'ia actuel au maximum pour le premier rendu, je vais desactiver cette fonctionalité-------*/
    //---------------------------------------------------------------------------------------------------------------------------------------

    //On met a jour le tableau de joueur
    //reallocation tableau joueur
    /*P_player_army P_new_player_army = realloc(p_data_board->P_array_player_army, sizeof(Player_army) * p_data_board->nb_player * (1 + nb_tours_update));

    if(P_new_player_army == NULL)
    {
        fprintf(stderr, "Erreur allocation memoire au niveau de l'update nouveau tableau player army\n");
        exit(1);
    }

    p_data_board->P_array_player_army = P_new_player_army;
    P_new_player_army = NULL;

    //On met a jour le tableau de joueur
    int pos = 0;
    for(int i = 0; i < p_data_board->nb_player; i++)
    {
        if(p_data_board->p_array_owner[i] == owner)
        {
            pos = i;
            break;
        }
    }

    p_data_board->P_array_player_army[pos * (1 + nb_tours_update) + ((1 + nb_tours_update) - 1)].x = x;
    p_data_board->P_array_player_army[pos * (1 + nb_tours_update) + ((1 + nb_tours_update) - 1)].y = y;
    */
     
     //---------------------------------------------IMPORTANT--------------------------------------------------------------------------------------------------
    /*------C'est en commentaire car c est une fonctionalite que j'integrerais par la suite pour optimiser mon ia.-------------------
    --------Cependant, afin d'optimiser l'ia actuel au maximum pour le premier rendu, je vais desactiver cette fonctionalité-------*/
    //---------------------------------------------------------------------------------------------------------------------------------------
    p_data_board->nb_free--;
    //on met a jour le tableau de case vide
    /*for(int i = 0; i < (p_data_board->nb_free); i++)
    {
        if(p_data_board->P_array_free[i].x == x && p_data_board->P_array_free[i].y == y)
        {
            p_data_board->P_array_free[i].x = -1;
            p_data_board->P_array_free[i].y = -1;
            
            //Allocation du nouveau tableau de case vide
            P_player_army P_new_array_free = malloc(sizeof(Player_army) * p_data_board->nb_free - 1);
            if(P_new_array_free == NULL)
            {
                fprintf(stderr, "Erreur allocation memoire au niveau de l'update nouveau tableau free\n");
                exit(1);
            }

            //On copie les anciennes cases dans le nouveau tableau
            int i  = 0;
            for(int j = 0; j < p_data_board->nb_free; j++)
            {
                if(p_data_board->P_array_free[j].x != -1 && p_data_board->P_array_free[j].y != -1)
                {
                    P_new_array_free[i].x = p_data_board->P_array_free[j].x;
                    P_new_array_free[i].y = p_data_board->P_array_free[j].y;
                    i++;
                }
                else
                {
                    continue;
                }
            }

            //On libere l'ancien tableau
            free(p_data_board->P_array_free);

            //On met a jour le nouveau tableau
            p_data_board->P_array_free = P_new_array_free;
            P_new_array_free = NULL;
            p_data_board->nb_free--;

            break;
        }
    }*/

    return true;//On retourne true si tout c'est bien passe
}

bool update_evaluation(P_data_board const p_data_board, const int x, const int y, const int evaluation)
{
    //Verifie que le x et y est bien dans le plateau
    if(x >= 0 && x < X && y >= 0 && y < Y)
    {
        fprintf(stderr, "La case (%d, %d) du plateau de jeu existe\n", x, y);
    }
    else
    {
        fprintf(stderr, "Erreur : La case (%d, %d) du plateau de jeu n'existe pas\n", x, y);
        return false;
    }

    //On met a jour le plateau de jeu
    p_data_board->Board[x][y].evaluation = evaluation;

    return true;//On retourne true si tout c'est bien passe
}

void print_board_game(P_data_board const p_data_board)
{
    int col;
    int lgn;
    int compteur = 0;

    putchar('\n');
    for (col = 0; col < Y; ++col)
        printf("  %d ", col);

    putchar('\n');
    putchar('+');

    for (col = 1; col <= Y; ++col)
        printf("---+");

    putchar('\n');

    for (lgn = 0; lgn < X; ++lgn)
    {
        putchar('|');

        for (col = 0; col < Y; ++col)
            if (isalpha(p_data_board->Board[col][lgn].owner))
                printf(" %c |", p_data_board->Board[col][lgn].owner);
            else
                printf(" %c |", ' ');
        
        if(compteur <= Y)
        {
            printf("  %d ", compteur);
            compteur++;
        }

        putchar('\n');
        putchar('+');

        for (col = 1; col <= Y; ++col)
            printf("---+");

        putchar('\n');
    }

    putchar('\n');
}

static int vider_tampon(FILE *fp)
{
    /*
     * Vide les données en attente de lecture du flux spécifié.
     */

    int c;

    do
        c = fgetc(fp);
    while (c != '\n' && c != EOF);

    return ferror(fp) ? 0 : 1;
}


char check_n_tuplet(const P_data_board const p_data_board, const int n)
{
    int save_x = 0;
    int save_y = 0;
    char save_owner = ' ';

    if(n < 0)
    {
        fprintf(stderr, "Erreur : Le nombre de pion a aligner doit etre superieur a 0\n");
        return '0';
    }

    if(n > X || n > Y)
    {
        fprintf(stderr, "Erreur : Le nombre de pion a aligner doit etre inferieur a la taille du plateau de jeu\n");
        return '0';
    }

    //Parcour le plateau de jeu pour verifier si il y a un gagnant
    for(int i = 0; i < X; i++)
    {
        for(int j = 0; j < Y; j++)
        {
            //On verifie si la case est vide
            if(p_data_board->Board[i][j].owner == 48)
            {
                continue;
            }
            else
            {
                save_owner = p_data_board->Board[i][j].owner;
                for(int k = 0; k < 8; k++)
                {
                    save_x = i;
                    save_y = j;
                    //printf("n = %d\n", n);
                    for(int l = 0; l < n; l++)
                    {
                        bool check = p_data_board->Board[save_x][save_y].owner == save_owner;
                        if(check)
                        {
                            if(p_data_board->Board[save_x][save_y].P_array_neightbour[k].x != -1 && p_data_board->Board[save_x][save_y].P_array_neightbour[k].y != -1)
                            {
                                save_x = p_data_board->Board[save_x][save_y].P_array_neightbour[k].x;
                                save_y = p_data_board->Board[save_x][save_y].P_array_neightbour[k].y;
                            }
                            else
                            {
                                break;
                            }
                        }
                        if(l == n - 1 && check)
                        {
                            return save_owner;
                        }
                    }
                }
            } 
        }
    }

    return '0';
}

bool check_free_case(const P_data_board const p_data_board)
{
    if(p_data_board->nb_free == 0)
    {
        return false;
    }
    else
    {
        return true;
    }
}

void play_turn(const P_data_board const p_data_board, const int n_tuplet)
{
    while(true)
    {
        // On verifie que l'utilisateur souhaite continuer la partie
        bool state = false;
        char c = '0';
        if (!vider_tampon(stdin))
        {
            fprintf(stderr, "Erreur lors de la vidange du tampon\n");
            exit(1);
        }
        while (1)
        {
            printf("Souhaitez-vous continuer cette partie ? (O -> oui, N -> non) :");

            if (scanf("%c", &c) != 1)
            {
                fprintf(stderr, "Erreur lors de la saisie\n");
                state = true;

                if (!vider_tampon(stdin))
                {
                    fprintf(stderr, "Erreur lors de la vidange du tampon\n");
                    exit(1);
                }
            }
            if (state == false && (c == 'O' || c == 'N'))
            {
                break;
            }
            else
            {
                fprintf(stderr, "Plait-il ?\n"); 
                state = false;
            }
        }

        if(c == 'N')
        {
            break;
        }

        //On demande au joueur de jouer
        char owner = '0';
        for(int i = 0; i < p_data_board->nb_player; i++)
        {
            for(int j = 0; j < 2; j++)
            {
                if(j == 0)
                {
                    owner = p_data_board->p_array_owner[i * 2 + j];
                }

                //Si le joueur est un humain
                if(j == 1 && p_data_board->p_array_owner[i * 2 + j] == '0')
                {
                    int x = 0;
                    int y = 0;
                    bool state = false;
                    while (1)
                    {
                        //On affiche le plateau de jeu
                        print_board_game(p_data_board);

                        printf("Joueur %d : Entrez la position de la case que vous voulez jouer (x, y) : ", i + 1);

                        if (scanf("%d, %d", &x, &y) != 2)
                        {
                            fprintf(stderr, "Erreur lors de la saisie\n");
                            state = true;

                            if (!vider_tampon(stdin))
                            {
                                fprintf(stderr, "Erreur lors de la vidange du tampon\n");
                                exit(1);
                            }
                        }

                        if (state == false && x >= 0 && x < X && y >= 0 && y < Y)
                        {
                            //Mise à jour du plateau de jeu
                            if(update_data_board(p_data_board, x, y, owner))
                            {
                                printf("La case (%d, %d) a ete jouee par le joueur %d (symbole : %c)\n", x, y, i + 1, owner);
                                break;
                            }
                            else
                            {
                                printf("La case (%d, %d) n a pas pu etre jouee (voir detail erreur...)\n", x, y);
                                fprintf(stderr, "Plait-il ?\n");
                            }  
                        }
                        else
                        {
                            fprintf(stderr, "Plait-il ?\nVerifiez que les coordonnees saisies sont correctes\n"); 
                            state = false;
                        } 
                    } 

                    //On affiche le plateau de jeu
                    print_board_game(p_data_board);

                    //On verifie si il y a un gagnant
                    char winner = check_n_tuplet(p_data_board, n_tuplet);
                    //printf("\nwinner = %c", winner);
                    if(winner != '0')
                    {
                        printf("Le joueur %c a gagne la partie\n", winner);

                        // Fin du jeu
                        printf("Fin du jeu\n");

                        return;
                    }

                    //On verifie si il reste des cases libres
                    if(check_free_case(p_data_board) == false)
                    {
                        printf("Il n'y a plus de case libre, la partie est terminee\n");

                        // Fin du jeu
                        printf("Fin du jeu\n");

                        return;
                    } 
                }
                else if(j == 1 && p_data_board->p_array_owner[i * 2 + j] == '1')
                {
                    //On affiche le plateau de jeu
                    //print_board_game(p_data_board);

                    //Appel fonction dermination coup IA
                    calcIA(p_data_board, 3, n_tuplet, owner);

                    //On affiche le plateau de jeu
                    print_board_game(p_data_board);

                    //On verifie si il y a un gagnant
                    char winner = check_n_tuplet(p_data_board, n_tuplet);
                    //printf("\nwinner = %c", winner);
                    if(winner != '0')
                    {
                        printf("Le joueur %c a gagne la partie\n", winner);

                        // Fin du jeu
                        printf("Fin du jeu\n");

                        return;
                    }

                    //On verifie si il reste des cases libres
                    if(check_free_case(p_data_board) == false)
                    {
                        printf("Il n'y a plus de case libre, la partie est terminee\n");

                        // Fin du jeu
                        printf("Fin du jeu\n");

                        return;
                    }
                }
            }

            //On verifie si il y a un gagnant
            /*char winner = check_n_tuplet(p_data_board, n_tuplet);
            if(winner != '0')
            {
                break;
            }

            //On verifie si il reste des cases libres
            if(check_free_case(p_data_board) == false)
            {
                break;
            }*/
        }
    }
    //printf("Merci d avoir joue à notre jeu\nCreated by : \nDevelopeur : \n - Loris Benaitier \nChef de projet : \n -Prenom Nom\n Autre : \n -Prenom Nom\n - Prenom Nom\n");
}

void to_cancel_move(P_data_board  p_data_board, int x, int y)
{
    //On annule le dernier coup joue
    //Verifie que le x et y est bien dans le plateau
    if(x >= 0 && x < X && y >= 0 && y < Y)
    {
        //printf("Annulation du dernier coup joue\n");
    }
    else
    {
        fprintf(stderr, "Erreur : La case (%d, %d) du plateau de jeu n'existe pas\n", x, y);
        return;
    }

    //On met a jour le plateau de jeu
    p_data_board->Board[x][y].owner = '0';
    
    //---------------------------------------------IMPORTANT--------------------------------------------------------------------------------------------------
    /*------C'est en commentaire car c est une fonctionalite que j'integrerais par la suite pour optimiser mon ia.-------------------
    --------Cependant, afin d'optimiser l'ia actuel au maximum pour le premier rendu, je vais desactiver cette fonctionalité-------*/
    //---------------------------------------------------------------------------------------------------------------------------------------
    
    //on met a jour le tableau de case vide
    //Reallocation du tableau
    p_data_board->nb_free++;
    /*P_player_army free_case = realloc(p_data_board->P_array_free, (p_data_board->nb_free) * sizeof(*free_case));

    //Si la reallocation a echoue
    if(free_case == NULL)
    {
        fprintf(stderr, "Erreur lors de la reallocation du tableau de case vide\n");
        return false;
    }

    //Add les nouvelles coordonnees au tableau de case vide
    //printf("\ntaille : %d", p_data_board->nb_free);

    free_case[p_data_board->nb_free - 1].x = x;
    free_case[p_data_board->nb_free - 1].y = y;
    
    //on met a jour la data board
    p_data_board->P_array_free = free_case;*/
}

void free_memory(P_data_board p_data_board)
{
    //liberer la memoir de neighbour
    for(int i = 0; i < X; i++)
    {
        for(int j = 0; j < Y; j++)
        {
            free(p_data_board->Board[i][j].P_array_neightbour);
            p_data_board->Board[i][j].P_array_neightbour = NULL;
        }
    }
    
    //liberer la memoire de owner
    free(p_data_board->p_array_owner);
    p_data_board->p_array_owner = NULL;

    //liberer memoir de free_case
    free(p_data_board->P_array_free);
    p_data_board->P_array_free = NULL;

    //liberer memoir de p_data_board
    free(p_data_board);
}

void loop_game()
{
    //Affichage regle du jeu
    printf("------------------------------------------------------------------------------------\n");
    printf("------------Bienvenue dans le jeu du Morpion (version : v1.0)-----------------------\n");
    printf("------------------------------------------------------------------------------------\n");

    //Rappel des regles du jeu
    printf("\n------------------------------------------------------------------------------------\n");
    printf("------------Rappel des regles du jeu du Morpion-------------------------------------\n");
    printf("------------------------------------------------------------------------------------\n");
    printf("Le but du jeu est de placer x pions de sa couleur sur une ligne, une colonne ou une diagonale.\n");
    printf("Le jeu se joue à x joueurs, chacun son tour, ils doivent placer un pion sur une case libre.\n");
    printf("Le premier joueur à aligner x pions de sa couleur gagne la partie.\n");
    printf("------------------------------------------------------------------------------------\n");

    //On demande le nombre de joueur
    bool state = false;
    int njoueur = 0;
    const int min_nb_player = 2;
    const int max_nb_player = 2;//brider à 2 pour le moment car l'ia n'est pas encore adapter au jeu à plus de 2 joueurs

    while (1)
    {
        printf("Combien de joueurs prennent part à cette partie (Max 2 pour le moment) ? ");

        if (scanf("%d", &njoueur) != 1)
        {
            fprintf(stderr, "Erreur lors de la saisie\n");
            state = true;

            if (!vider_tampon(stdin))
            {
                fprintf(stderr, "Erreur lors de la vidange du tampon\n");
                exit(1);
            }
        }

        if (state == false && njoueur >= min_nb_player && njoueur <= max_nb_player)
        {
            break;
        }
        else
        {
            fprintf(stderr, "Plait-il ?\n"); 
            state = false;
        } 
    }

    //Combien de joueur(s) humain(s) ?
    int nb_human_player = 0;
    while (1)
    {
        printf("Combien de joueur(s) humain(s) ? ");

        if (scanf("%d", &nb_human_player) != 1)
        {
            fprintf(stderr, "Erreur lors de la saisie\n");
            state = true;

            if (!vider_tampon(stdin))
            {
                fprintf(stderr, "Erreur lors de la vidange du tampon\n");
                exit(1);
            }
        } 

        if (state == false && nb_human_player >= 0 && nb_human_player <= njoueur)
        {
            break;
        }
        else
        {
            fprintf(stderr, "Plait-il ?\n"); 
            state = false;
        }
    }

    //Combien de joueur(s) IA(s) ?
    int nb_IA_player = njoueur - nb_human_player;

    //On demande le nombre de pion a aligner pour gagner//cas 2 err
    int nb_pion_aligner = 0;
    const int min_nb_pion_aligner = 3;
    const int max_nb_pion_aligner = X;

    while (1)
    {
        printf("Combien de pion(s) doit-on aligner pour gagner ? ");

        if (scanf("%d", &nb_pion_aligner) != 1)
        {
            fprintf(stderr, "Erreur lors de la saisie\n");
            state = true;

            if (!vider_tampon(stdin))
            {
                fprintf(stderr, "Erreur lors de la vidange du tampon\n");
                exit(1);
            }
        }   

        if (state == false && nb_pion_aligner >= min_nb_pion_aligner && nb_pion_aligner <= max_nb_pion_aligner)
        {
            break;
        }
        else
        {
            fprintf(stderr, "Plait-il ?\n"); 
            state = false;
        }
    }

    //Recapitulatif des information(s) choisie par l'utilisateur
    printf("\n------------------------------------------------------------------------------------\n");
    printf("------------Recapitulatif des information(s) choisie(s) par l'utilisateur------------\n");
    printf("------------------------------------------------------------------------------------\n");
    printf("Vous avez choisi de jouer avec %d joueur(s)\n -Humain(s) = %d\n -IA = %d\n", njoueur, nb_human_player, nb_IA_player);
    printf("Vous avez choisi de jouer avec %d pion(s) pour gagner\n", nb_pion_aligner);
    printf("------------------------------------------------------------------------------------\n");

    //On initialise le plateau de jeu
    P_data_board P_data = init_data_board(njoueur, nb_human_player);

    // boucle de jeu
    play_turn(P_data, nb_pion_aligner);

    //On libere la memoire
    free_memory(P_data);
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
