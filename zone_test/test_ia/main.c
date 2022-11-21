#include "jeu.h"
#include "test.h"
#include "ia.h"
#define JOUEUR 2

int main()
{
    //--------------------------------------------Test-------------------------------------------
    /*P_data_board P_data = init_data_board(JOUEUR, 1);
    print_data_struct(P_data, JOUEUR);
    test_function_update(P_data, 1, 2, 'A', 1);
    test_function_update(P_data, 2, 2, 'A', 1);
    
    //test_function_update(P_data, 2, 1, 'A', 1);
    //test_function_update(P_data, 3, 1, 'A', 1);
    
    
    
    //test_function_n_tuple_free_case(P_data);
    //to_cancel_move(P_data, 0, 0);
    //print_data_struct(P_data, JOUEUR);
    test_function_n_tuple_free_case(P_data);
    //Test ia
    //int rese = evalue(P_data, 2);
    //printf("----------------Score : %d", rese);
    calcIA(P_data,4 , 4, 'B');//4 -> directe, 5 et 6 -> 3 à 4 secondes
    print_board_game(P_data);
    free_memory(P_data);
    printf("Fin du programme\n");
    //loop_game();*/
    //--------------------------------------------Test-------------------------------------------

    //Boucle de jeu
    loop_game();

    return 0;
}


