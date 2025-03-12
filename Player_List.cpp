#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
using namespace std;

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"


class players{
public:
    string name;
    int score;
    players* next;  // Pointer to the next player in the list
};

// Class to manage the top 10 list of players
class top_list {
private:
    int players_num;
    players* top;  // Pointer to the top player (highest score)

public:
    top_list() {
        top = NULL;  
        players_num = 0; 
    }

    // Check if the list is empty
    bool isempty() {
        return top == NULL;
    }

    // Function to add a player to the list
    void addplayer(string nm, int pts) {
        players* new_player = new players;  // Create a new player node
        new_player->name = nm;
        new_player->score = pts;
        new_player->next = NULL;

        // If the list is empty, the new player becomes the top player
        if (isempty()) {
            top = new_player;  
        } 

        // If the new player's score is higher than the top player's score, insert at the top
        else if (pts > top->score) {
            new_player->next = top;
            top = new_player;
        } 
        // Otherwise, find the correct position in the list and insert the player
        else {
            players* it = top;
            while (it->next != NULL && pts < it->next->score) {
                it = it->next;
            }
            new_player->next = it->next;
            it->next = new_player;
        }
        players_num++;  
    }

    // Function to display the top 10 players
    void Display(){
        int order = 1;
        players* it = top;
        cout << GREEN << "      ＜Top 10 List>  \n" << RESET;
        // Display only the top 10 players
        if(players_num > 10){
           for(int i = 0 ; i < 10 ; i++){
            cout << YELLOW << order << "- " << RESET << it->name << fixed << setw(12) << it->score << endl;
            it = it->next;
            order++;
           } 
        }
        // Display all players if there are fewer than 10
        else{
            while(it != NULL){
                cout << YELLOW << order << "- " << RESET << it->name << fixed << setw(12) << it->score << endl;
                it = it->next;
                order++;
            }
        }
        cout << GREEN << "---------------------------------\n" << RESET;
    }

    // Function to search for a player by name
    pair<int, string> search_player(string nm) {
        int player_count = 1;
        players* it = top;
        // Search through the list of players
        while (it != NULL) {
            if (nm == it->name) {
                return make_pair(it->score, player_count <= 10 ? "The player is in the top 10" : "The player is not in the top 10");
            }
            it = it->next;
            player_count++;
        }
        return make_pair(0, "The player is not found"); // Return if the player isn't found
    }


};

// Function to handle player list operations
void player_list() {
    top_list players_list;  
    string choice;

    while (true) {
        // Menu for player list management
        cout << BLUE << "┌─── ∘°❉°∘ ───┐┌─── ∘°❉°∘ ───┐ \n";
        cout << "|         Players List       |\n";
        cout << "└─── °∘❉∘° ───┘└─── °∘❉∘° ───┘ \n" << RESET;
        cout << "1) Add Player\n";
        cout << "2) Display Top 10 list\n";
        cout << "3) Search for player\n";
        cout << "4) Main Menu\n";
        cout << "---> ";
        getline(cin,choice);

        if (choice == "1") {    // Add a player
            string name;
            int score;  
            cout << "Please Type the player name: ";
            cin >> name;
            cin.ignore();
            cout << "Please Type the player score: ";
            cin >> score;  
            cin.ignore();
            cout << endl;
            players_list.addplayer(name, score);
            cout << GREEN << "Player Added successfully" << RESET << endl;
        } 
        else if (choice == "2") {   // Display top 10 players
            players_list.Display();
        } 
        else if (choice == "3") {   // Search for a player by name
            string name;
            cout << "Please Type the player name: ";
            cin >> name;
            cin.ignore();
            cout << endl; 
            pair<int, string> answer = players_list.search_player(name);
            cout << name << " Score is: "  << answer.first<<"," << YELLOW <<  "  Status: " << RESET << answer.second << endl;
        } 
        else if (choice == "4"){    // Exit the player list menu
            break;
        }
        else {
            cout << RED << "Please Choose a Valid choice" << RESET << endl << endl;
        }
    }

}