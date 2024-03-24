// Purpose: This a Program of 4 different cipher programs 
// Author: Seif Eldeen Hassan            Email: seifeldeen568@gmail.com      
// Version: 1.0
// Date: 3/18/2024

#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <array>
#include <cctype>
#include <cstdlib>
#include <limits>

using namespace std;

////////// Simple Substitution Cipher ////////////////////////////////////////////////////////////////////////////////          

// Function to check if the key is valid
bool check_key(string key) {
  
    if (key.size() != 5) {
        return false;
    }
    for (int i = 0; i < key.size(); ++i) {
        if (!isalpha(key[i])) {
            return false;
        }
        for (int j = i + 1; j < key.size(); ++j) {
            if (tolower(key[i]) == tolower(key[j])) {
                cout << "Invalid, Key contains duplicate characters.\n"; 
                return false; 
            }
        }
    }
    return true;
}

// Function to get and validate the key
string check_key(){
  string key ;
   while (true) {
   cout << "Please Enter key of 5 unique letters\n";
   getline(cin , key);
   if (check_key(key)){
    return key;
   }
   else{
    continue;
   }
}
}

// Function to create a new alphabet based on the key
string create_new_alphabet(string key){
  string new_alpha;
  for (int i = 0 ; i < key.size() ; i++ ){
    new_alpha += tolower(key[i]);
  }
  int stop = 0;
  for (int c = 97  ; c <= 122 ; c++){
      for (int i = 0 ; i < key.size() ; i++){
        if (char(c) == tolower(key[i])){
            stop ++;
        }
      }
      if (stop == 0){
        new_alpha += char(c);
      }
      else{
        stop = 0;
      }
    }
    return new_alpha;
}

// Function to cipher a message
void Cipher(){
    string word , key , new_alpha ,ciphered_message;
    cout << "Please Enter the message\n";
    getline (cin , word);
    key = check_key();
    new_alpha = create_new_alphabet(key);
    
    for (char c : word){
      if (isalpha(c)){
         int index = int(towlower(c)) - 97;
         ciphered_message += tolower(new_alpha[index]);
      }
      else {
         ciphered_message += c;
      } 
    }
    cout << "The Ciphered message is: " << ciphered_message << endl;
  
}

// Function to decipher a message
void Decipher(){
  string word , key , new_alphabet ,Deciphered_message ;
    cout << "Please Enter the Ciphered message\n";
    getline (cin , word);
    key = check_key();
    new_alphabet = create_new_alphabet(key);
    for (char c : word){
      if (isalpha(c)){
         int index = new_alphabet.find(tolower(c));
         Deciphered_message += toupper(char(97+index));
      }
      else{
        Deciphered_message += c;
      }

    } 
    cout << "The Deciphered message is: " << Deciphered_message << endl;
}

// Main function for the simple substitution cipher
int simple_substitution_cipher(){
  while (true){
    cout << " \033[3;32m ╔═══━━━─── • ───━━━═══╗ \033[0m" << endl;
    cout << " \033[3;32m   Simple Substitution   \033[0m" << endl; 
    cout << " \033[3;32m ╚═══━━━─── • ───━━━═══╝ \033[0m" << endl;
    cout << "1) Cipher \n";
    cout << "2) Decipher \n";
    cout << "3) Exit to Main Menu\n";
    string choice ; 
    getline(cin , choice);
    if (choice == "1" ){
      Cipher();
    }
    else if (choice == "2"){
      Decipher();
    }
    else if (choice == "3"){
      return 1;
    }
    else{
      cout << "Invalid, Please Choose 1/2/3\n";
    }
  }
  
}

////////// Baconian Cipher ///////////////////////////////////////////////////////////////////////////////////

// Function to convert a decimal number to binary
string Decimal_to_Binary(int number, int size)
{
    string Binary_number = "", new_bin; // Initialize variables to store binary representation
    int remainder;
    while (number > 0)
    {
        remainder = number % 2; // Get the remainder when dividing by 2
        Binary_number = to_string(remainder) + Binary_number; // Append the remainder to the binary string
        number = trunc(number / 2); // Update the number by integer division
    }
    new_bin = Binary_number; // Store the binary number in a new variable
    // Append leading zeros
    for (int i = 0; i < size - Binary_number.size(); i++)
    {
        new_bin = "0" + new_bin; // Add leading zeros to make the binary number of desired size
    }
    return new_bin; // Return the binary representation
}

// Function to convert a binary number to decimal
int Binary_to_Decimal(int number)
{
    int power = 0, sum = 0, length = to_string(number).size(); // Initialize variables for calculation
    while (power < length)
    {
        sum = sum + ((pow(2, power)) * ((number) % 10)); // Update the sum by adding the binary digit multiplied by 2 raised to power
        power++;
        number = trunc(number / 10); // Remove the last digit of the binary number
    }
    return sum; // Return the decimal representation
}

// Function to cipher a message using Baconian cipher
void Cipher_message()
{
    string word, cipherd_text; // Initialize variables to store input word and ciphered text
    vector<int> decimal_numbers; // Initialize a vector to store decimal representations of characters
    vector<string> Binary_word; // Initialize a vector to store binary representations of characters
    cout << "Please Enter The message to cipher\n";
    getline(cin, word); // Input the message
    // Convert each character to its decimal representation
    for (char c : word)
    {
        if (isalpha(c))
        {
            c = toupper(c); // Convert character to uppercase
            decimal_numbers.push_back(int(c) - 65); // Store the decimal representation in the vector
        }
    }
    // Convert each decimal number to a 5-bit binary representation
    for (int i = 0; i < decimal_numbers.size(); i++)
    {
        Binary_word.push_back(Decimal_to_Binary(decimal_numbers[i], 5)); // Store the binary representation in the vector
    }
    // Construct the ciphered text by replacing 0s with 'a' and 1s with 'b'
    for (int i = 0; i < Binary_word.size(); i++)
    {
        for (char number : Binary_word[i])
        {
            if (number == '0')
            {
                cipherd_text += "a"; // Append 'a' for 0
            }
            else if (number == '1')
            {
                cipherd_text += "b"; // Append 'b' for 1
            }
        }
        cipherd_text += " "; // Add space between characters
    }
    cout << "The Ciphered text: " << cipherd_text << endl << endl; // Output the ciphered text
}

// Function to decipher a message using Baconian cipher
void Decipher_message()
{
  string Ciphered_text, get_ciphered, get_binary_text, deciphered_text; // Initialize variables to store input text and deciphered text
  vector<string> ciphered_word;   // Initialize a vector to store ciphered words
  vector<string> binary_text;    // Initialize a vector to store binary representations of characters
  cout << "Please Enter The message to Decipher\n";
  getline(cin, Ciphered_text); 

  // Extract ciphered words from the input text
  for (char c : Ciphered_text)
  {
      if (c == 'a' || c == 'b')
      {
          get_ciphered += c; // Append characters to form a ciphered word
      }
      else
      {
          ciphered_word.push_back(get_ciphered); // Store the ciphered word in the vector
          get_ciphered = ""; // Reset the temporary variable
      }
  }
  ciphered_word.push_back(get_ciphered); // Store the last ciphered word
  
  // Convert each ciphered word to its binary representation
  for (string pattern : ciphered_word)
  {
      for (char c : pattern){
          if (c == 'a')
          {
              get_binary_text += "0"; // Append '0' for 'a'
          }
          else if (c == 'b')
          {
              get_binary_text += "1"; // Append '1' for 'b'
          }
      }
      binary_text.push_back(get_binary_text); // Store the binary representation in the vector
      get_binary_text = ""; // Reset the temporary variable
  }

  // Convert each binary representation to its decimal representation and then to the corresponding character
  for (string f : binary_text){
      deciphered_text += char(Binary_to_Decimal(stoi(f)) + 65); // Convert decimal representation to character
  }
  cout << "The Deciphered text: " << deciphered_text << endl << endl; // Output the deciphered text
  }

  // Function to perform Baconian cipher operations
  int Baconian()
  {
  while (true)
  {
      cout << " \033[3;32m ╔═══━━━─── • ───━━━═══╗ \033[0m" << endl;
      cout << " \033[3;32m         Baconian        \033[0m" << endl;
      cout << " \033[3;32m ╚═══━━━─── • ───━━━═══╝ \033[0m" << endl;
      cout << "1) Cipher \n";
      cout << "2) Decipher \n";
      cout << "3) Exit to Main Menu\n";
      string choice;
      getline(cin, choice); 
      if (choice == "1")
      {
          Cipher_message(); // Perform cipher operation
      }
      else if (choice == "2")
      {
          Decipher_message(); // Perform decipher operation
      }
      else if (choice == "3")
      {
          return 1; // Return to main menu
      }
      else
      {
          cout << "Invalid, Please Choose 1/2/3\n"; // Handle invalid input
      }
  }
  }


////////// Vignere Cipher ////////////////////////////////////////////////////////////////////////////////////

// Function to generate the key for Vigenère cipher
pair<string, string> make_the_key(string word, string key){
  string new_key, Capital_key, captial_word; 
  double word_size;
  int length; 
  word_size = word.size(); 
  length = ceil(word_size / key.size()); 

  // Capitalize the word
  for (char c : word){
      if (isalpha(c)){
          captial_word += toupper(c);
      }
      else{
          captial_word += c;
      }
  }

  // Generate a key with the same length as the word
  for (int i = 0; i < length; i++){
      new_key += key;
  }
  new_key = new_key.substr(0, word.size()); // Truncate the key if it's longer than the word

  // Place any special characters from the word into the new_key
  for (int i = 0; i < word.size(); i++){
      if (!isalpha(word[i])){
          new_key[i] = word[i];
      }
  }

  // Capitalize the key
  for (char c : new_key){
      if (isalpha(c)){
          Capital_key += toupper(c);
      }
      else{
          Capital_key += c;
      }
  }

  return make_pair(captial_word, Capital_key); // Return the pair of capitalized word and key
}

// Function to cipher a message using Vigenère cipher
void cipher_message()
{
  string ciphered_text, word, key; 
  cout << "Please Enter the message to Cipher\n";
  getline(cin, word); 
  cout << "Please Enter the key\n";
  getline(cin, key); 
  pair<string, string> p = make_the_key(word, key); // Generate the key
  string capital_word = p.first;
  string Capital_key = p.second;

  // Cipher each character of the message
  for (int i = 0; i < word.size(); i++){
      if (!isalpha(word[i])){
          ciphered_text += word[i];
      }
      else{
          ciphered_text += char((((int(capital_word[i]) + int(Capital_key[i])) % 26) + 65)); // Perform Vigenère cipher operation
      }
  }
  cout << "The Ciphered text: " << ciphered_text << endl; // Output the ciphered text
}

// Function to decipher a message encrypted with Vigenère cipher
void Decipher_vignere_message()
{
  string Deciphered_Text, word, key; 
  cout << "Please Enter the message to Decipher\n";
  getline(cin, word); 
  cout << "Please Enter the key\n";
  getline(cin, key); 
  pair<string, string> p = make_the_key(word, key); // Generate the key
  string capital_word = p.first;
  string Capital_key = p.second;

  // Decipher each character of the message
  for (int i = 0; i < word.size(); i++)
  {
      if (!isalpha(word[i]))
      {
          Deciphered_Text += word[i];
      }
      else
      {
          char deciphered_char = capital_word[i] - (Capital_key[i] - 65);
          if (deciphered_char < 65)
          {
              deciphered_char += 26; // Handle wraparound for negative values
          }
          Deciphered_Text += deciphered_char; // Append the deciphered character
      }
  }
  cout << "The Deciphered Text: " << Deciphered_Text << endl; // Output the deciphered text
}

// Function to perform Vigenère cipher operations
int Vignere()
{
  while (true)
  {
      cout << " \033[3;32m ╔═══━━━─── • ───━━━═══╗ \033[0m" << endl;
      cout << " \033[3;32m         Vignere         \033[0m" << endl;
      cout << " \033[3;32m ╚═══━━━─── • ───━━━═══╝ \033[0m" << endl;
      cout << "1) Cipher \n";
      cout << "2) Decipher \n";
      cout << "3) Exit to Main Menu\n";
      string choice;
      getline(cin, choice);
      if (choice == "1")
      {
          cipher_message(); // Perform cipher operation
      }
      else if (choice == "2")
      {
          Decipher_vignere_message(); // Perform decipher operation
      }
      else if (choice == "3")
      {
          return 1; // Return to main menu
      }
      else
      {
          cout << "Invalid, Please Choose 1/2/3\n"; // Handle invalid input
      }
  }
}


////////// Atbash Cipher ////////////////////////////////////////////////////////////////////////////////////

// Function to validate and retrieve a valid key (1 or 2) from the user
 string check_key_atbash(){
  while (true) {
    string key;
    getline(cin , key);
    if ((key == "1" || key == "2"))
        return key;
    else
      cout << "Invalid, Please Enter key 1 or 2 \n";
  }
}
  

// Function to perform the encryption or decryption based on the key
string cipher(string key , string word){
 string new_word ;
 if (key == "1"){
   // Cipher logic for key 1
   for (char i : word){
    if (65 <= int(i) && int(i) <= 90)
    new_word += (char((90 - (int(i)-65))));
    else if (97 <= int(i) && int(i) <= 122)
    new_word += toupper(char((122 - (int(i)-97))));
   }
 }
 else if (key == "2"){
   // Cipher logic for key 2
   for (char i : word){
     if (65 <= int(i) && int(i) <= 77)
       new_word += char((77 - (int(i)-65)));
     else if (97 <= int(i) && int(i) <= 109)
       new_word += toupper(char((109 - (int(i)-97))));
     else if (78 <= int(i) && int(i) <= 90)
       new_word += char((90 - (int(i)-78)));
     else if (110 <= int(i) && int(i) <= 122)
       new_word += toupper(char((122 - (int(i)-110))));
   }
 }
 return (new_word);
}


// Atbash Cipher Implementation
int Atbash() 
{
 while (true){
 cout << " \033[3;32m ╔═══━━━─── • ───━━━═══╗ \033[0m" << endl;
 cout << " \033[3;32m         Atbash         \033[0m" << endl; 
 cout << " \033[3;32m ╚═══━━━─── • ───━━━═══╝ \033[0m" << endl;
 cout << "1) Cipher \n";
 cout << "2) Decipher \n";
 cout << "3) Exit to Main menu \n";
 string Choice , new_word , word , key ;
 getline(cin , Choice);
 if (Choice == "1"){
      cout << "Please enter the message to cipher\n";
      getline (cin , word);
      cout << "Please enter the Key to cipher {1 or 2} \n";
      key = check_key_atbash();
      new_word = cipher(key , word);
      cout << "The Encrypted Text: " << new_word << endl << endl;
 }

 else if (Choice == "2")
 {
      cout << "Please enter the message to Decipher\n";
      getline (cin , word);
      cout << ("Please enter the Key to Decipher {1 or 2}\n");
      key = check_key_atbash();
      new_word = cipher(key , word);
      cout << "Decrypted Text: " << new_word << endl << endl ;

 }
 else if (Choice == "3"){
   return 1;
 }
 else 
    cout << "Invalid, Please Choose 1 or 2 or 3" << endl;

}
}

////////// Main Program ///////////////////////////////////////////////////////////////////////////////////

int main(){
  while (true) {
    int main_menu = 0;
    cout << "\033[3;32m ╔══════════════════╗╔══════════════════╗\033[0m" << endl;
    cout << "\033[3;32m             Cipher Programs             \033[0m" << endl;
    cout << "\033[3;32m ╚══════════════════╝╚══════════════════╝\033[0m" << endl;
    cout << "1) Simple Substitution Cipher\n";
    cout << "2) Baconian Cipher\n";
    cout << "3) Vignere Cipher\n";
    cout << "4) Atbash Cipher\n";
    cout << "5) Exit\n";
    string choice;
    getline(cin, choice);
        
    if (choice == "1") {
        main_menu = simple_substitution_cipher();
        if (main_menu == 1) {
            continue; // Go back to main menu
        }
    } else if (choice == "2") {
        main_menu = Baconian();
        if (main_menu == 1) {
            continue; 
        }
    } else if (choice == "3") {
        main_menu = Vignere();
        if (main_menu == 1) {
            continue; 
        }
    } else if (choice == "4") {
        main_menu = Atbash();
        if (main_menu == 1) {
            continue; 
        }
    } else if (choice == "5") {
      cout << "\033[3;31mExiting The Program......\033[0m" << endl;
      exit(0);
       
    } else {
        cout << "Invalid choice. Please Enter a number from 1 to 8.\n";
    }
}

    return 0;
}
  



 
                            


