#include "ia.h"
#include <stdio.h>
#include "generateur_aleatoir.h"

static char courant_player;
//static int evalue_cnt = 0;

void calcIA(P_data_board p_data_board, int prof, int n_tuple, char player)
{
    int i,j,tmp;
    int maxi=-1,maxj=-1;
    int alpha = MINEVAL;
    int beta = MAXEVAL;

    courant_player = player;

    //Si la profondeur est nulle ou la partie est finie,
    //on ne fait pas le calcul
    if(prof != 0 || check_free_case(p_data_board) == true || check_n_tuplet(p_data_board, n_tuple) == '0')
    {
        //On parcourt les cases vide du plateau
        for(i=0;i<X; i++)
        {
            for(j=0;j<Y; j++)
            {
                //Si la case est vide
                if(p_data_board->Board[i][j].owner == '0')
                {
                    //printf("\ncoupsfree calcia : %d / %d\n", i, j);

                    //On simule qu'on joue cette case
                    bool test = update_data_board(p_data_board, i, j, player);

                    // test
                    //printf("------------coupmax : %d / %d --- ", i, j);

                    //On appelle la fonction calcMin pour lancer l'IA
                    tmp = calcMin(p_data_board, prof-1, n_tuple, alpha, beta);

                    //Si ce score est plus grand
                    if(alpha<tmp)
                    {
                        //On le choisit
                        alpha = tmp;
                        maxi = i;
                        maxj = j;
                    }

                    //On annule le coup
                    //printf("\ntmp : %d\n", tmp);
                    to_cancel_move(p_data_board, i, j);
                    //printf("\ntmp2 : %d\n", tmp);
                }
            }   
        }
    }
   
    //On jouera le coup maximal
    bool test_2 = update_data_board(p_data_board, maxi, maxj, player);
}

int calcMin(P_data_board p_data_board, int prof, int n_tuple, int alpha, int beta)
{
    int i,j,tmp;

    //Si on est √† la profondeur voulue, on retourne l'√©valuation
    if(prof == 0)
    {
        tmp = evalue(p_data_board, n_tuple);
        //printf("\nevaluemin prof %d : %d\n", prof, tmp);
        return tmp;
    }

    //Si la partie est finie, on retourne l'√©valuation de jeu
    if(check_free_case(p_data_board) == false || check_n_tuplet(p_data_board, n_tuple) != '0')
    {
        tmp = evalue(p_data_board, n_tuple);
        //printf("\nevaluemin prof 1 : %d\n", tmp);
        return tmp;
    }

    //On parcourt le plateau de jeu et on le joue si la case est vide
    for(i=0;i<X; i++)
    {
        for(j=0;j<Y; j++)
        {
            if(p_data_board->Board[i][j].owner == '0')
            {
                //printf("\ncoupsfree calcmin : %d / %d\n", i, j);

                //On simule qu'on joue cette case
                bool test = update_data_board(p_data_board, i, j, 'A');

                //printf("coupmin : %d / %d --- ", i, j);


                //On appelle la fonction calcMax pour lancer l'IA
                tmp = calcMax(p_data_board, prof-1, n_tuple, alpha, beta);

                //On annule le coup
                to_cancel_move(p_data_board, i, j);

                //Mis a jour de beta
                if(beta > tmp)
                {
                    beta = tmp;
                }

                if(beta <= alpha)
                {
                    return beta;
                }
            }
        }   
    }
    return beta;
}

int calcMax(P_data_board p_data_board, int prof, int n_tuple, int alpha, int beta)
{
    int i,j,tmp;

    //Si on est √† la profondeur voulue, on retourne l'√©valuation
    if(prof == 0)
    {
        tmp = evalue(p_data_board, n_tuple);

        //printf("\nevaluemax prof %d : %d\n", prof, tmp);
        return tmp;
    }

    //Si la partie est finie, on retourne l'√©valuation de jeu
    if(check_free_case(p_data_board) == false || check_n_tuplet(p_data_board, n_tuple) != '0')
    {
        tmp = evalue(p_data_board, n_tuple);
        //printf("\nevaluemax prof 1 : %d\n", tmp);
        return tmp;
    }

    //On parcourt le plateau de jeu et on le joue si la case est vide
    for(i=0;i<X; i++)
    {
        for(j=0;j<Y; j++)
        {
            if(p_data_board->Board[i][j].owner == '0')
            {
                //On simule qu'on joue cette case
                bool test = update_data_board(p_data_board, i, j, courant_player);

                //printf("coupmax : %d / %d --- ", i, j);


                //On appelle la fonction calcMax pour lancer l'IA
                tmp = calcMin(p_data_board, prof-1, n_tuple, alpha, beta);

                //On annule le coup
                to_cancel_move(p_data_board, i, j);

                if(alpha < tmp)
                {
                    alpha = tmp;
                }

                if(beta <= alpha)
                {
                    return alpha;
                }
            }
        }   
    }
    return alpha;
}


int calcScore(int cntpion, int cntjoueur)
{
    
    int multiplicateur = 10;
    //printf("\ninter3--/cntpion : %d, cntjoueur : %d, multiplicateur : %d", cntpion, cntjoueur, multiplicateur);

    for(int i = 0; i <= cntpion; i++) // En fonction du n_tuplet
    {
        if(i > 0)
        {
            if(cntpion == i)
            {
                return cntjoueur * multiplicateur;
            }
            //printf("\n--/cntpion : %d, cntjoueur : %d, i : %d, multiplicateur : %d", cntpion, cntjoueur, i, multiplicateur);
            multiplicateur += 20;
        }
    }

    return 0;      
}

int evalue(const P_data_board const p_data_board, int n_tuplet)
{
    int score = 0;
    int cntpion = 0;
    int cntjoueur = 0;
    /*int x = 0;
    int y = 0;
    int save_y = 0;*/

    //print_board_game(p_data_board);
    //printf("check n_tuplet : %c\n", check_n_tuplet(p_data_board, n_tuplet));

    //Si le jeu est fini (plus de case libre)
    if(check_n_tuplet(p_data_board, n_tuplet) != '0' || check_free_case(p_data_board) !=  true)
    {
        //Si l'IA a gagn√©, on retourne 1000 - le nombre de pions
        if(check_n_tuplet(p_data_board, n_tuplet) == courant_player)
        {
            //printf("\nIA a gagn√©\n");
            return 1000-comptePions(p_data_board);
        }
        else if(check_n_tuplet(p_data_board, n_tuplet) == '0')
        {
            //printf("\nMatch nul\n");
            //Egalite -> on retourne 0
            return 0;
        }
        else
        {
            //printf("\nIA a perdu\n");
            //Si l'IA a perdu, on retourne -1000 + le nombre de pions
            return -1000+comptePions(p_data_board);
        }
    }

    // Deuxieme phase
    int save_x = 0;
    int save_y = 0;
    int x_inter = 0;
    int y_inter = 0;

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
                for(int k = 0; k < 8; k++)
                {
                    save_x = i;
                    save_y = j;
                    cntpion = 0;
                    cntjoueur = 0;
                    for(int l = 0; l < n_tuplet; l++)
                    {
                        bool check = p_data_board->Board[save_x][save_y].owner != '0';
                        if(check == true)
                        {
                            cntpion++;
                            if(p_data_board->Board[save_x][save_y].owner == courant_player)
                            {
                                //On incr√©mente le compteur
                                cntjoueur++;
                            } 
                            else if(p_data_board->Board[save_x][save_y].owner != courant_player)
                            {
                                //On d√©cr√©mente le compteur
                                cntjoueur--;
                            }
                                
                            //On ajoute au score cette nouvelle participation
                            score += calcScore(cntpion,cntjoueur);
                        }
                        if(p_data_board->Board[save_x][save_y].P_array_neightbour[k].x != -1 && p_data_board->Board[save_x][save_y].P_array_neightbour[k].y != -1)
                        {
                            x_inter = p_data_board->Board[save_x][save_y].P_array_neightbour[k].x;
                            y_inter = p_data_board->Board[save_x][save_y].P_array_neightbour[k].y;
                            save_x = x_inter;
                            save_y = y_inter;
                        }
                        else
                        {
                            break;
                        }
                    }
                }
            } 
        }
    }
    
    
    
    
    
    

    //On parcourt chaque case du plateau et on parcour chaque direction sur un n-tuplet
    //Parcour le plateau de jeu pour verifier si il y a un gagnant
    /*for(int i = 0; i < X; i++)
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
                for(int k = 0; k < 8; k++)
                {
                    //reset des compteurs
                    cntpion = 0;
                    cntjoueur = 0;
                    int cpt = 0;
                    x = i;
                    y = j;
                    while(true)
                    {
                        //printf("\n----cpt %d - k %d", cpt, k);
                        cpt++;
                        if(cpt > n_tuplet)
                        {
                            cpt--;
                            break;
                        }
                        //on increment le nombre de pion
                        cntpion++;

                        //printf("\n owner : %c", p_data_board->Board[x][y].owner);
                        //printf("\n i %d - j %d", i, j);
                        //printf("\n tab : %d %d", x, y);
                        //printf("\n neight : %d %d", p_data_board->Board[x][y].P_array_neightbour[k].x, p_data_board->Board[x][y].P_array_neightbour[k].y);
                        //Si c'est le m√™me type du joueur courant
                        if(p_data_board->Board[x][y].owner == courant_player)
                        {
                            //On incr√©mente le compteur
                            cntjoueur++;
                        } 
                        else if(p_data_board->Board[x][y].owner != courant_player && p_data_board->Board[x][y].owner != '0')
                        {
                            //On d√©cr√©mente le compteur
                            cntjoueur--;
                        }
                            
                        //On ajoute au score cette nouvelle participation
                        //printf("\nscore intermediaire : %d", score);
                        score += calcScore(cntpion,cntjoueur);
                        //printf("\nscore intermediaire2 : %d", score);
                        
                        //printf("\n neight : %d %d", p_data_board->Board[x][y].P_array_neightbour[k].x, p_data_board->Board[x][y].P_array_neightbour[k].y);

                        if(p_data_board->Board[x][y].P_array_neightbour[k].x == -1 || p_data_board->Board[x][y].P_array_neightbour[k].y == -1)
                        {
                            break;
                        }
                        //printf("\n neight : %d %d", p_data_board->Board[x][y].P_array_neightbour[k].x, p_data_board->Board[x][y].P_array_neightbour[k].y);
                        //printf("\n tab2 : %d %d", x, y);
                        save_y = p_data_board->Board[x][y].P_array_neightbour[k].y;
                        x = p_data_board->Board[x][y].P_array_neightbour[k].x;
                        //y = p_data_board->Board[x][y].P_array_neightbour[k].y;
                        y = save_y;
                        
                        //y = save_y;
                        //printf("\n tab3 : %d %d", x, y);
                    }
                }
            } 
        }
    }*/
    return score;
}

int comptePions(P_data_board p_data_board)
{
    return ((X * Y) - p_data_board->nb_free);
}