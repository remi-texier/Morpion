

int get_possibilities(int** board, vec dir) {
    int possibilities = 0;
    for (int i = 0; i < COMBO_LENGHT; i++) {
        if ;
    }
    return possibilities;
}

int get_full_line(int** board, int x, int y, Vec dir) {
    
}

int get_line(int** board, int x, int y, Vec dir, Symbol symbol) {
    int num_symbols = 0;
    for (int i = 0; i < COMBO_LENGHT; i++) 
    {
        Symbol case = board[x+(i*dir.x)][y+(i*dir.y]
        if ( case != symbol && case != EMPTY) !(case == symbol)
            return -1;
        else num_symbols++;
    }
    return num_symbols;
}