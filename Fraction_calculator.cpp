// Purpose: This a Rational number calculator
// Author: Seif Eldeen Hassan            Email: seifeldeen568@gmail.com      
// Version: 1.0
// Date: 3/13/2024


#include <iostream>
#include <string>
#include <cmath>
#include <iomanip>
#include <regex>
using namespace std;

// Function to check if a string contains only digits
bool check_isdigit(string text){
    for (char ch : text)
  {
    if (!isdigit(ch)) 
        return false;
  }
  return true;
}

// Function to prompt the user to try again or exit
int check_tryagain(){
    while (true)
    {
    cout << "Do you want try again ?\n";
    cout << "1) Try again\n";
    cout << "2) Exit  \n";
    string Choice;
    cin >> Choice;
    cin.ignore();
    if (Choice == "1")
      return(1);
    else if (Choice == "2")
      return(0);
    else 
      cout << "Invalid, Please Choose 1/2 \n";
    }
}

// Function to remove spaces from a string
string removeSpaces(string str) {
    string result;
    for (char space : str) {
        if (space != ' ') {
            result += space;
        }
    }
    return result;
}
// ##### Omar adel gabr ################################ ID:20230259 ########## VALIDATION ##############
// Function to check if the input string is a valid mathematical expression
bool check_math(const string& input) {
    regex pattern("\\s*(\\+)?-?\\d+(\\.\\d+)?(\\s*/\\s*(\\+)?-?\\d+(\\.\\d+)?)?(\\s*[+\\-*/]\\s*(\\+)?-?\\d+(\\.\\d+)?(\\s*/\\s*(\\+)?-?\\d+(\\.\\d+)?)?)*\\s*$");
    return regex_match(input, pattern);

}



//#############################################################################################################

// Function to calculate the greatest common divisor (GCD)
int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// Function to count the number of negative signs in a string
int check_negative(string number){
    int count = 0;
    for (char c: number){
        if (c == '-'){
            count++; 
        }
    }
    return count;
}

// Function to remove positive sign from a string
string remove_postive_sign(string number){
    string new_number ;
    for (char c: number){
        if (c != '+'){
             new_number += c ;
        }
    }
    return new_number;
 
}

// Function to remove negative signs from a string
string remove_negative_signs(string number){
    string without_neg;
    for (char c : number){
        if (c != '-' ){
            without_neg += c;
        }
    }
    return(without_neg);
}

int main() {
  cout << "◤━━━━━━━━━━━◥◤━━━━━━━━━━━◥\n";
  cout << "       Fraction Calc        \n";
  cout << "◤━━━━━━━━━━━◥◤━━━━━━━━━━━◥\n";
  // Main program loop
  while (true){
  string word, first_num, second_num , operation ;
    int count = 0 , divisions =0 , operations = 0 ;
    // Get user input
    cout << "Please Enter the Math expression\n";
    cout << "➺  ";
    getline(cin, word);
    word = removeSpaces(word);

    // Check if the input is a valid mathematical expression
    if (!check_math(word)){
    cout << "Invalid Math expression\n";
    continue;
    }
    // Get the two numbers from the math expression
    for (int i = 0; i < word.size(); i++) {
        if (word[i] == '/') {
            count++;
            if (count == 2) {
                first_num = word.substr(0, i);
                second_num = word.substr(i + 1, word.size()); 
                operation = word.substr(i, 1);
                break;
            }
        } 
        else if ((word[i] == '+' && isdigit(word[i+1]) && isdigit(word[i-1])) || 
                  (word[i] == '+' && word[i+1] == '+') ||(word[i] == '+' && word[i+1] == '-') ||
                  word[i] == '*' || (word[i] == '-' && isdigit(word[i+1]) && isdigit(word[i-1])) ||
                  (word[i] == '-' && word[i+1] == '-') || (word[i] == '-' && word[i+1] == '+')) {

            first_num = word.substr(0, i);
            second_num = word.substr(i + 1, word.size());
            operation = word.substr(i, 1); 
            break;
        }
    }
    string numerator_1, denominator_1,  numerator_2, denominator_2;


////////////////////// Handle Numbers without operations /////////////////////////////////////////////////////////////////////////

    if (first_num.size() == 0 && second_num.size() == 0 && operation.size() == 0){
         for (int i = 0; i < word.size(); i++) {
        if (word[i] == '/') {
            numerator_1 = word.substr(0, i );
            denominator_1 = word.substr(i + 1, word.size());
            operation = "/";
            break;
        }
        else{
            numerator_1 = word.substr(0, i+1 );
            denominator_1 = "1";
        }
        
       }
       double gcd_1 = gcd(stod(numerator_1) , stod(denominator_1));
       if (stod(denominator_1) / gcd_1 == 1){
         cout << "The Result is: " << stod(numerator_1) / gcd_1 << endl;
       } 
       else if  (stod(denominator_1) == 0){
        cout << "Error: Division by zero."<< endl;
        continue;
       }
       else{
          cout << "The Result is: " << stod(numerator_1) / gcd_1 << "/" << stod(denominator_1) / gcd_1 << endl;
       }
       if (check_tryagain() == 1){
         continue;
       }
       else{
        cout << "Thank you for using rational number calculator ⭐";
        exit(0);
       }
       
    
  }

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    double num_1 = 1 , num_2 = 1 , result = 0.0  , int_numerator_1 = 1 , int_demo_1 , int_numerator_2 = 1 , int_demo_2 , result_nemo , result_demo ; 

// check if there is negative sign and remove it
    if (check_negative(first_num) == 1){
        num_1 = -1;
        int_numerator_1 = -1;
        first_num = remove_negative_signs(first_num);
    }
    if (check_negative(second_num) == 1){
        num_2 = -1;
        int_numerator_2 = -1;
        second_num = remove_negative_signs(second_num);
    }
// remove any postive sign
    first_num = remove_postive_sign(first_num);
    second_num =remove_postive_sign(second_num);
    
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////// Get the 1st numerator and demo and 2nd numerator and demo ////////////////////////////////////

    for (int i = 0; i < first_num.size(); i++) {
        if (first_num[i] == '/') {
            numerator_1 = first_num.substr(0, i );
            denominator_1 = first_num.substr(i + 1, first_num.size());
            break;
        }
        else{
            numerator_1 = first_num.substr(0, i+1 );
            denominator_1 = "1";
        }
    }

     num_1 *= stod(numerator_1) / stod(denominator_1); // calculate the 1st number to use it in the decimal result
     int_numerator_1 *= stod(numerator_1), int_demo_1 = stod(denominator_1) ; // get the numerator and denominator in int type

    
     for (int i = 0; i < second_num.size(); i++) {
        if (second_num[i] == '/') {
            numerator_2 = second_num.substr(0, i );
            denominator_2 = second_num.substr(i + 1, second_num.size());
            break;
        }
        else{
            numerator_2 = second_num.substr(0, i+1 );
            denominator_2 = "1";
        }
    }

     num_2 *= stod(numerator_2) / (stod(denominator_2)); // calculate the 2nd number to use it in the decimal result
     int_numerator_2 *= stod(numerator_2) , int_demo_2 = stod(denominator_2) , result_nemo , result_demo  ; // get the numerator and denominator in int type
     
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

     if (denominator_1 == "0" || denominator_2 == "0") {
        cout << "Error: Division by zero." << endl;
        continue;
    }    // check if there is n/0 and Print (Error)


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////// Make the operations to get result numerator and result denominator///////////////////////////////////////

    if (operation == "+"){
        result = num_1 + num_2;
        result_nemo = (int_numerator_1 * int_demo_2) + (int_demo_1 * int_numerator_2);
        result_demo = int_demo_1 * int_demo_2 ;
    }
    else if (operation == "-"){
        result = num_1 - num_2;
        result_nemo = (int_numerator_1 * int_demo_2) - (int_demo_1 * int_numerator_2);
        result_demo = int_demo_1 * int_demo_2 ;
    }
    else if (operation == "/"){
        result = num_1 / num_2;
        result_nemo = int_numerator_1 * int_demo_2;
        result_demo = int_demo_1 * int_numerator_2 ;
    }
    else if (operation == "*"){
        result = num_1 * num_2;
        result_nemo = int_numerator_1 * int_numerator_2;
        result_demo = int_demo_1 * int_demo_2;
    } 
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    int Common_Divisor = gcd(result_nemo, result_demo);
    result_nemo /= Common_Divisor ;
    result_demo /= Common_Divisor ;          // divide on the gcd to simplify the fraction


///////////////////////////// Handling some special cases /////////////////////////////////////////////////////////////////////////////

    if (result_nemo == 0){
        cout << "The Result is: 0 " << endl; 
    }
    else if ( result_nemo == result_demo ){
        cout << "The Result is: 1 " << endl; 
    }
    else if (result_demo == 1){
        cout << "The Result is: " << result_nemo << endl;   
    }
    else if (result_nemo < 0 && result_demo < 0 ){
        cout << "The Result is: " << result_nemo*-1 << "/" << result_demo*-1 << "  >>  " << result  << endl;
    }
    else{
        cout << "The Result is: " << result_nemo << "/" << result_demo << "  >>  " << result  << endl;   
    }
    
    // Prompt user to try again or exit
    int check = check_tryagain();
    if (check == 0){
        cout << "Thank you for using rational number calculator ⭐";
        exit(0);
    }
    else if (check == 1){
        continue;  
    }
 }
 
 return 0;
}

/////////////////////////////////////// Pseudo-Code/////////////////////////////////////////////////////////////
// 1. Start

// 3. Define main function:

//     a. Display program title and description.
//     b. Start a loop for continuous operation:

//         i. Initialize variables: word, first_num, second_num, operation, count, divisions, and operations.

//         ii. Prompt the user to enter a mathematical expression.

//         iii. Read the input from the user.

//         iv. Remove any spaces from the input.

//         v. Check if the input is a valid mathematical expression using regex pattern.
//             If not valid, display an error message and continue to the next iteration of the loop.

//         vi. Extract the two numbers and operation from the input:
//             - Use a loop to get the numbers and operation.
//             - Identify the numbers and operation based on the presence of operators like '+', '-', '*', '/', and their positions.
//             - Break the loop once the numbers and operation are identified.

//         vii. Handle cases where there are numbers without operations:
//             - Check if both first_num and second_num are empty and operation is also empty.
//             - Extract the numerator and denominator for the number.
//             - Calculate the result or display an error message for division by zero.
//             - Prompt the user to try again or exit.

//         viii. Initialize variables for numerical operations: num_1, num_2, result, int_numerator_1, int_demo_1, int_numerator_2, int_demo_2, result_nemo, and result_demo.

//         ix. Check for negative signs in first_num and second_num and remove them.

//         x. Remove any positive signs from first_num and second_num.

//         xi. Extract the numerator and denominator for the first and second numbers.

//         xii. Convert the numerators and denominators to integers and perform calculations using double variables to get num_1 and num_2.

//         xiii. Check for division by zero and display an error message if encountered.

//         xiv. Perform mathematical operations based on the operation symbol:
//             - Addition
//             - Subtraction
//             - Multiplication
//             - Division
//             Update result, result_nemo, and result_demo accordingly.

//         xv. Calculate the greatest common divisor (GCD) of result_nemo and result_demo to simplify the fraction.

//         xvi. Display the result:
//             - Handle special cases like zero, one, or negative fractions.

//         xvii. Prompt the user to try again or exit.

// 4. End

