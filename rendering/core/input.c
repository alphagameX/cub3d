#include "../../cub3d.h"

int key_aleady_press(int key, int *tab, int limit) {
    int i = 0;
    while(i < limit && tab[i] != -1) {
        if(tab[i] == key)
            return (1);
        i++;
    }
    return (0);
}

void wait_mode_fix(t_move *moves, int pos) {
    moves->wait_mode[pos] = -1;
    moves->nb_move--;
    if(pos + 1 < 10 && moves->wait_mode[pos + 1] != -1) {
        while(pos + 1 < 10) {
            moves->wait_mode[pos] = moves->wait_mode[pos + 1];
            pos++;
        }
    }
}

int set_move(int key_code, t_move *moves) {
    if(key_aleady_press(key_code, moves->wait_mode, moves->nb_move) == 0) {
        moves->wait_mode[moves->nb_move] = key_code;
        moves->nb_move++;
    }
    return (1);
}

int unset_move(int key_code, t_move *moves) {
    int i = 0;

    while(i < moves->nb_move) {
        if(moves->wait_mode[i] == key_code) {
            wait_mode_fix(moves, i);
            return (1);
        }
        i++;
    }
    return (1);
}