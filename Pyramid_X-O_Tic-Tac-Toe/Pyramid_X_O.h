#ifndef _Pyramid_X_O_H
#define _Pyramid_X_O_H

#include "BoardGame_Classes.h"
bool is_computer_pyr = false;

template <typename T>
class Pyramid_X_O_Board : public Board<T>{
    public:
        Pyramid_X_O_Board();
        bool update_board(int x, int y, T mark);
        void display_board();
        bool is_win();
        bool is_draw();
        bool game_is_over();
};

template <typename T>
class Pyramid_X_O_Player : public Player<T>{
    public:
        Pyramid_X_O_Player(string name , T sy);
        void getmove(int& x, int& y );
};

template <typename T>
class Pyramid_X_O_RandomPlayer : public RandomPlayer<T>{
    public:
        Pyramid_X_O_RandomPlayer(T sy);
        void getmove(int& x, int& y);
};

class UI_Pyramid{
    public:
        void Main_Program();  
};

#endif