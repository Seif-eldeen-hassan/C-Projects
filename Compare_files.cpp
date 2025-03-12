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


// Function to append ".txt" to the file name
void openfile(string& file_name){
    file_name += ".txt";
}

/////////////////////////////////////////
///////////// Compare Char //////////////

// Function to compare two strings character by character
int compare_char(string line1 , string line2, int lineindex){
    // Iterate through the characters of both strings
     for(int i = 0 ; i < line1.size() ; i++){
          if(line1[i] != line2[i]){
               return lineindex;    // Return line index if a mismatch is found
          }
     }
     return -1;     // Return -1 if no mismatch is found
}

// Function to display the differences between two lines by highlighting mismatched characters in red
void display_line1_char(string line1 , string line2){
     for(int i = 0 ; i < max(line1.size(),line2.size()) ; i++){
          if(line1[i] != line2[i]){
               cout << RED << line1[i] << RESET;    // Highlight mismatched characters
          }
          else{
               cout << line1[i];
          }
     }
}

// Similar function to display the differences in the second line
void display_line2_char(string line1 , string line2){
     for(int i = 0 ; i < max(line1.size(),line2.size()) ; i++){
          if(line1[i] != line2[i]){
               cout << RED << line2[i] << RESET;    // Highlight mismatched characters
          }
          else{
               cout << line2[i];
          }
     }
}

// Function to compare two files line by line and check for character mismatches
void check_char(string file_name1 , string file_name2){
     int file1_len = 0 , file2len = 0 , wrong_line = 0 ;
     vector <string> vec_file1;
     vector <string> vec_file2;
     string word;
     // Read the first file into vec_file1
     ifstream file1 (file_name1);
     ifstream file2 (file_name2);
     while(getline(file1 , word)){
          vec_file1.push_back(word);
         file1_len++;
     }
     // Read the second file into vec_file2
     while(getline(file2 , word)){
          vec_file2.push_back(word);
          file2len++;
     }
     bool identical = true;
     // Compare the files line by line
     for(int i = 0 ; i < file1_len ; i++){                                                
          int line_index = compare_char(vec_file1[i] , vec_file2[i], wrong_line);
          if(line_index != -1){
               cout << "Different in Line " << wrong_line+1 << endl;
               cout << YELLOW << "File 1 ---> "<< RESET;
               display_line1_char(vec_file1[line_index] , vec_file2[line_index]);
               cout << endl;
               cout << YELLOW << "File 2 ---> "<< RESET;
               display_line2_char(vec_file1[line_index] , vec_file2[line_index]);
               cout << endl;
               identical = false;
          }
          wrong_line++;

     }   
     if(identical){
        cout << GREEN <<"The two files are identical ✅ \n" << RESET;
     }    
}

/////////////////////////////////////////
///////////// Compare Word //////////////

// Function to extract words from a line and store them in both 'words' and 'all_words'
vector<string> extract_words(const string& line , vector <string>& all_words) {
    vector<string> words;
    string word = "";

    for (char ch : line) {
        if (ch == ' ') {
            if (!word.empty()) {
                words.push_back(word);
                all_words.push_back(word);  // Store word in the global list
                word = "";  
            }
        } else {
            word += ch;  // Add character to the current word
        }
    }

    if (!word.empty()) {
        words.push_back(word);
        all_words.push_back(word);
    }
    return words;  // Return list of words from the line
}

int file1_len = 0 , file2len = 0  ;
vector <vector<string>> vec_file1;
vector <vector<string>> vec_file2;    

// Function to find which line a word is located in for file 1
int find_line_file1(int word_num){
    int total = 0;
    for(int i = 0 ; i < file1_len ; i++){
        total += vec_file1[i].size();
        if(total >= word_num){
            return i+1;     // Return the line number where the word is found
        }
    }
}

// Function to find which line a word is located in for file 2
int find_line_file2(int word_num){
    int total = 0;
    for(int i = 0 ; i < file2len ; i++){
        total += vec_file2[i].size();
        if(total >= word_num){
            return i+1;     // Return the line number where the word is found
        }
    }
}

// Function to compare words from both files
int compare_words(vector <string> f1_words , vector <string> f2_words ){
    int word_number = 0;
    for(int i = 0 ; i < f1_words.size() ; i++){
        word_number++;
        if(f1_words[i] != f2_words[i]){
            return word_number;     // Return the word number where the mismatch occurs
        }
    }
    return -1;      // Return -1 if words are identical
}

// Function to retrieve a specific line from the file and highlight the different word
string get_line(string file_name, int line_number, const string& different_word) {
    vector<string> empty;
    ifstream file(file_name);
    string line;
    int currentLine = 0;

    // Loop through the file to find the desired line
    while (getline(file, line)) {
        currentLine++;
        if (currentLine == line_number) {
            vector<string> words = extract_words(line, empty);
            string result_line = "";
            for (const string& word : words) {
                if (word == different_word) {
                    result_line += RED + word + RESET + " ";    // Highlight the different word
                } else {
                    result_line += word + " ";      // Add the rest of the words as normal
                }
            }
            return result_line;     // Return the formatted line
        }
    }
    return "";
}

// Function to compare files by words
void compare_word(string file_name1 , string file_name2){
    vector <string> all1_words;
    vector <string> all2_words;
    string word;
    // Read words from the first file
    ifstream file1 (file_name1);
    ifstream file2 (file_name2);
    while(getline(file1 , word)){
         vec_file1.push_back(extract_words(word , all1_words));
         file1_len++;
    }
    // Read words from the second file
    while(getline(file2 , word)){
          vec_file2.push_back(extract_words(word , all2_words));
          file2len++;
    }
    int check = compare_words(all1_words , all2_words);
    if(check != -1){
        int line_1_num = find_line_file1(check) ;
        cout << YELLOW << "File 1  (line " << line_1_num << " ) ----> " << RESET;
        cout << get_line(file_name1 , line_1_num , all1_words[check-1] ) << endl;
        int line_2_num = find_line_file2(check) ;
        cout << YELLOW << "File 2  (line " << line_2_num << " ) ----> " << RESET;
        cout << get_line(file_name2 , line_2_num , all2_words[check-1]) << endl; 
    }
    else{
        cout << GREEN <<"The two files are identical ✅ \n" << RESET;
    }
}

////////////////////

// Function to handle file comparison operations
void compare(){
    string file1 , file2 , choice;
    cout << BLUE;
    cout << "▣▣▣▣▣▣▣▣▣▣▣▣▣▣▣▣▣▣▣▣▣▣▣▣▣▣▣▣▣\n";
    cout << "▣▣▣▣▣▣" << RESET << " File Comparison " << BLUE << "▣▣▣▣▣▣\n";
    cout << "▣▣▣▣▣▣▣▣▣▣▣▣▣▣▣▣▣▣▣▣▣▣▣▣▣▣▣▣▣\n";
    cout << RESET;
    cout << "Please Enter the name of the first file: ";
    getline(cin,file1);
    cout << "Please Enter the name of the second file: ";
    getline(cin,file2);
    openfile(file1);
    openfile(file2);
    while(true){
    cout << YELLOW <<"▣▣▣▣▣▣▣▣▣▣▣▣▣▣\n" << RESET;
    cout << "1) Compare by characters\n";
    cout << "2) Compare by words\n";
    cout << "3) Main Menu\n";
    cout << "---> ";
    getline(cin,choice);
    if(choice == "1"){
        check_char(file1 , file2);  // Compare by characters
    }
    else if(choice == "2"){
        compare_word(file1 , file2);    // Compare by words
    }
    else if (choice == "3"){
        break;      // Return to the main menu
    }   
    else{
        cout << RED << "Wrong Choice, Please choose 1 or 2\n" << RESET;
    }

}

}