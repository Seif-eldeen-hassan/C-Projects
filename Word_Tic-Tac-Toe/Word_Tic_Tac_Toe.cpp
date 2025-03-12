#include "Word_Tic_Tac_Toe.h"
#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

// Color codes (define macros)
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"

template <typename T>
Word_Tic_Tac_Board<T>::Word_Tic_Tac_Board(){
    this->rows = 3;
    this->columns = 3;
    this->board = new char*[this->rows];
    for(int i = 0 ; i < this->rows ; i++){
        this->board[i] = new char[this->columns];
        for(int j = 0 ; j < this->columns ; j++){
            this->board[i][j] = ' ';
        }
    }
    this->n_moves = 0;
}

template <typename T>
bool Word_Tic_Tac_Board<T>::update_board(int x, int y, T mark){
    if (x < 0 || x >= this->rows) {
        if(is_computer_word){
            return false;
        }
            cout << RED << "Invalid move: Row " << x << " is out of bounds." << RESET << endl;
            return false;
        
    }
    if (y < 0 || y >= this->columns) {
        if(is_computer_word){
            return false;
        }
             cout << RED <<"Invalid move: Column " << y << " is out of bounds for row " << x << "." << RESET << endl;
            return false; 
       
    }
    if (this->board[x][y] != ' ') {
        if(is_computer_word){
            return false;
        }
            cout << RED << "Invalid move: Cell (" << x << ", " << y << ") is already occupied." << RESET << endl;
             return false;
        
    }
     // Update the board
    this->board[x][y] = toupper(mark);
    this->n_moves++;
    return true;
}

template <typename T>
void Word_Tic_Tac_Board<T>::display_board(){
     int r = 0;
    for(int m = 0 ; m < 3 ; m++){
        for(int i = 0 ; i < 3 ; i++ ){
            cout << "+-----";
        }
        cout << "+" << endl;
        for(int i = 0 ; i < 3 ; i++){
            cout << "|  " << this->board[r][i] << "  ";
        }
        cout << "|" << endl;
        r++;
    }
    for(int i = 0 ; i < 3 ; i++ ){
            cout << "+-----";
    }
        cout << "+" << endl;
}

template <typename T>
bool Word_Tic_Tac_Board<T>::Default_dic(){
    ifstream file ("dic.txt");
    if(!file){
        cout << RED << "Error: Unable to open file 'dic.txt' "<< RESET << endl;
        return 0;
    }
    string get , capital;
    while(file >> get){
        for(char c : get){
            capital += toupper(c);
        }
        Words.push_back(capital);
        capital ="";
    }
    return 1;
}

template <typename T>
void Word_Tic_Tac_Board<T>::Get_Words(){
    while(true){
        string file_name , get , capital ;
        cout << "Pleases Enter The file name of the dic: ";
        getline(cin,file_name);
        if(file_name.size() < 5){
            file_name += ".txt";
        }
        if(file_name.substr(file_name.size()-4) != ".txt"){
            file_name += ".txt";
        }
        ifstream file (file_name);
        if(!file){
            cout << RED << "Error: Unable to open file " + file_name << RESET << endl;
            continue;
        }
        cout << GREEN << file_name << " opened successfully\n" << RESET;
        while(file >> get){
        for(char c : get){
            capital += toupper(c);
        }
        Words.push_back(capital);
        capital ="";
        }
        break;
    }

}

template <typename T>
bool Word_Tic_Tac_Board<T>::Search_Word(char first_letter , char second_letter , char third_letter){
    string word = {first_letter, second_letter, third_letter};
    string reversed_word = {third_letter, second_letter, first_letter};
    
    for(string s : Words){
        if(word == s || reversed_word == s) return 1;
    }
    return 0;
}

template <typename T>
bool Word_Tic_Tac_Board<T>::is_win(){
    // Check horizontal win
    if(Search_Word(this->board[0][0],this->board[0][1],this->board[0][2]) || Search_Word(this->board[1][0],this->board[1][1],this->board[1][2])||
       Search_Word(this->board[2][0],this->board[2][1],this->board[2][2]) ){
        return 1;
    }
    // Check vertical win
    if(Search_Word(this->board[0][0],this->board[1][0],this->board[2][0]) || Search_Word(this->board[0][1],this->board[1][1],this->board[2][1])||
       Search_Word(this->board[0][2],this->board[1][2],this->board[2][2]) ){
        return 1;
    }
    // Check diagonal win
    if(Search_Word(this->board[0][0],this->board[1][1],this->board[2][2]) || Search_Word(this->board[0][2],this->board[1][1],this->board[2][0]) ) return 1;

    return 0; // No win detected

}

template <typename T>
bool Word_Tic_Tac_Board<T>::is_draw(){
    if (this->n_moves == 9 && !is_win()) return 1;
    else return 0;
}

template <typename T>
bool Word_Tic_Tac_Board<T>::game_is_over(){
    return is_win() || is_draw();
}

template <typename T>
Word_Tic_Tac_Player<T>::Word_Tic_Tac_Player(string n , T sy) : Player<T>(n , sy){}

template <typename T>
void Word_Tic_Tac_Player<T>::getmove(int& x, int& y){
    char l;
    cout <<"\nPlease Enter your move x and y (X = Row , Y = column) separated by spaces: ";
    cin >> x >> y;
    cin.ignore();
    cout <<"\nPlease Enter your letter: ";
    cin >> l;
    this->symbol = toupper(l);
}

template <typename T>
Word_Tic_Tac_RandomPlayer<T>::Word_Tic_Tac_RandomPlayer(T sy) : RandomPlayer<T>(sy){
     this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0))); 
}

template <typename T>
void Word_Tic_Tac_RandomPlayer<T>::getmove(int& x, int& y){
    x = rand() % 3;
    y = rand() % 3;
    this->symbol = 'A' + (rand() % 26);
}

void UI_Word::Main_Program(){
        string choice;
        Player<char>* players[2];
        Word_Tic_Tac_Board<char>* B = new Word_Tic_Tac_Board<char>();
        string player1Name, player2Name;
        cout << "===============================================================\n\n";
        cout << "               Welcome to the Word - Tic - Tac - Toe Game!\n";
        cout << "     A fun twist on the classic Tic-Tac-Toe game in word style.\n\n";
        cout << "                    Controls:\n";
        cout << "                    1. Enter the row (X)\n";
        cout << "                    2. Enter the column (Y)\n";
        cout << "                    3. Get 3 in a row to WIN!\n\n";
        cout << "         Are you ready to test your strategy and luck? 🎮\n\n";
        cout << "===============================================================\n\n";
        string dic_choice;
        while(true){
            cout << "Do you want to use the default dictionary or use your dictionary? \n";
            cout << "1) Deafult dictionary\n";
            cout << "2) My Dictionary\n";
            getline(cin,dic_choice);
            if(dic_choice == "1"){
                if(B->Default_dic() == 0){
                    return;
                }
                break;
            }
            else if(dic_choice == "2"){
                B->Get_Words();
                break;
            }
            else{
                cout << RED << "Invalid Choice, Please Choose 1 or 2\n" << RESET;
            }
        }
      
        cout << "Enter Player 1 name: ";
        getline(cin,player1Name);
        while (true){
            cout << "Choose Player 1 type:\n";
            cout << "1. Human\n";
            cout << "2. Random Computer\n";
            getline(cin,choice);
            if(choice == "1"){
                players[0] = new Word_Tic_Tac_Player<char>(player1Name, 'N');
                break;
            }
            else if(choice == "2"){
                players[0] = new Word_Tic_Tac_RandomPlayer<char>('N');
                is_computer_word = true;
                break;
            }
            else{
                cout << RED << "Invalid choice for Player 1." << RESET << endl;
                continue;
            }

        }
        
        // Set up player 2
        cout << "Enter Player 2 name: ";
        getline(cin,player2Name);
        while(true){
            cout << "Choose Player 2 type:\n";
            cout << "1. Human\n";
            cout << "2. Random Computer\n";
            getline(cin,choice);

            if(choice == "1"){
                players[1] = new Word_Tic_Tac_Player<char>(player2Name, 'O');
                break;
            }
            else if(choice == "2"){
                players[1] = new Word_Tic_Tac_RandomPlayer<char>('O');
                is_computer_word = true;
                break;
            }
            else{
                cout << RED << "Invalid choice for Player 2." << RESET << endl;
                continue;
            }
        }

        // Create the game manager and run the game
        GameManager<char> word_tic_tac_game(B, players);
        word_tic_tac_game.run();

        // Clean up
        delete B;
        for (int i = 0; i < 2; ++i) {
            delete players[i];
        }

}
    








