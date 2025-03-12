#ifndef _Word_Tic_Tac_Toe
#define _Word_Tic_Tac_Toe
#include <vector>
#include "BoardGame_Classes.h"

bool is_computer_word = false;

template <typename T>
class Word_Tic_Tac_Board : public Board<T>{
    private:
        vector <string> Words;
    public:
        Word_Tic_Tac_Board();
        bool update_board(int x, int y, T mark);
        void display_board();
        bool Default_dic();
        void Get_Words();
        bool Search_Word(char first_letter , char second_letter , char third_letter);
        bool is_win();
        bool is_draw();
        bool game_is_over();
};

template <typename T>
class Word_Tic_Tac_Player : public Player<T>{
    public:
        Word_Tic_Tac_Player(string name , T sy);
        void getmove(int& x, int& y);
};

template <typename T>
class Word_Tic_Tac_RandomPlayer : public RandomPlayer<T>{
    public:
        Word_Tic_Tac_RandomPlayer(T sy);
        void getmove(int& x, int& y);

};

class UI_Word{
    public:
        void Main_Program();  
};



#endif