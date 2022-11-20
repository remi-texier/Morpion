#include "test.h"

/*
 * @Brief Fonction qui permet d'afficher le contenu des differentes structures
 * @param : P_data_board -> adresse de la structure à liberer
 * @param : nb_joueur -> nombre de joueur
 * @return : void
*/
void print_data_struct(const P_data_board const P_data, const int nb_joueur)
{
    //Affichage du tableau Game_board
    int compteur = 0;
    for(int i = 0; i < X; i++)
    {
        for(int j = 0; j < Y; j++)
        {
            printf("\n-------------Case %d---------------\n", compteur);
            printf("-%d /", P_data->Board[i][j].evaluation);
            printf("-%c /", P_data->Board[i][j].owner);
            printf("-%d /", P_data->Board[i][j].x);
            printf("-%d /", P_data->Board[i][j].y);

            //Affichage case voisine*
            printf("\nCase voisine : \n");
            for(int k = 0; k < 8; k++)
            {
                printf("-%d /", P_data->Board[i][j].P_array_neightbour[k].x);
                printf("-%d /", P_data->Board[i][j].P_array_neightbour[k].y);
            }
            compteur++;
        }
        printf("\n");
    }

    //Affichage du tableau de char qui represente les joueurs
    printf("\nTableau de char qui represente les joueurs\n");
    for(int i = 0; i < nb_joueur; i++)
    {
        for (size_t j = 0; j < 2; j++)
        {
            printf("-%c /", P_data->p_array_owner[i * 2 + j]);
            printf("//");
        }
    }

    //Affichage du tableau de structure qui represente les pions de chaque joueur
    /*if(activ)
    {
        printf("Affichage v1\n");
        
        printf("\nTableau de structure qui represente les pions de chaque joueur\n");
        for(int i = 0; i < nb_joueur; i++)
        {
            printf("-%d /", P_data->P_array_player_army[i].x);
            printf("-%d /", P_data->P_array_player_army[i].y);
        }
    }
    else
    {
        printf("\nAffichage des joueurs v2\n");
        for(int i = 0; i < nb_joueur; i++)
        {
            for(int j = 0; j < (taille_array_player + 1); j++)
            {
                printf("-%d /", P_data->P_array_player_army[i * (1 + taille_array_player) + j].x);
                printf("-%d /", P_data->P_array_player_army[i * (1 + taille_array_player) + j].y);
            }
        }
    }*/

    //Affichage du tableau de structure qui represente les pions libres
    printf("\nTableau de structure qui represente les pions libres\n");
    for(int i = 0; i < P_data->nb_free; i++)
    {
        printf("-%d /", P_data->P_array_free[i].x);
        printf("-%d /", P_data->P_array_free[i].y);
    }
}

void test_function_update(const P_data_board const P_data, const int x, const int y, const char owner, const int evaluation)
{
    //Test de la fonction update
    printf("---------------Test de la fonction update general-------------------\n");
    bool state = update_data_board(P_data, x, y, owner);
    if(state)
    {
        printf("La fonction update a fonctionne\n");
    }
    else
    {
        printf("La fonction update n'a pas fonctionne\n");
    }

    printf("\n--------------Test de la fonction update evaluation---------------\n");
    bool state_2 = update_evaluation(P_data, x, y, evaluation);
    if(state_2)
    {
        printf("La fonction update_evaluation a fonctionne\n");
    }
    else
    {
        printf("La fonction update_evaluation n'a pas fonctionne\n");
    }
    
    //print_data_struct(P_data, P_data->nb_player);
}

void test_function_n_tuple_free_case(const P_data_board const P_data)
{
    //Test de la fonction n_tuple_free_case
    printf("---------------Test de la fonction n_tuple_free_case-------------------\n");
    bool nb_free = check_free_case(P_data);
    if(nb_free)
    {
    }
    else
    {
        printf("il n y a plus de case libre\n");
    }

    //Test de la fonction n_tuple
    printf("---------------Test de la fonction n_tuple-------------------\n");
    char nb_tuple = check_n_tuplet(P_data, 3);
    printf("\n");
    if(nb_tuple =='0')
    {
        printf("il n y a pas de n-tuplet\n");
    }
    else
    {
        printf("il y a un n-tuplet\n");
        printf("Le joueur %c a gagne\n", nb_tuple);
    }
}

