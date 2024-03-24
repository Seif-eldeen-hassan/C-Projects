
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <tuple>
#include <cmath>
using namespace std;

tuple<int, string ,double , double , double> Identify_Integration(string trig){
  string str_m = "" , trig_function ="" , str_nemo = "" , denomenator = "";
  double  a = 0 , nemo_a = 0 , demo_a = 0   ;
  int m = 0 , count = 0;
  for (int i = 0 ; i < trig.size() ; i++){
    if (trig[i] == 'x'){
      i--;
      while (isdigit(trig[i])){
       str_m = trig[i] + str_m;
       i--;
      }
      m = stoi(str_m);
      break;
    }
    
  } 
   for (int i = 0 ; i < trig.size() ; i++){
     if (trig[i] == '/'){
      count ++ ;
      denomenator = trig.substr(i+1 , trig.size());
     i--;
     while (isdigit(trig[i])){
       str_nemo = trig[i] + str_nemo;
       i--;
      }
      break;
      
    }
    
    
   }
   if  (count == 0){
      a = 1;
      nemo_a = 1;
      demo_a = 1;
   }
   else{
      a =  stod(str_nemo)/stod(denomenator);
      nemo_a = stod(str_nemo);
      demo_a = stod(denomenator);
   }


  for (int i = 0 ; i < trig.size() ; i++){
    if (trig[i] == 'S' || trig[i] == 's'){
      trig_function = "Sin";
      break;
    }
    else if (trig[i] == '-' && (trig[i+1] == 'S' || trig[i+1] == 's')){
      trig_function = "-Sin";
      break;
    }
    else if (trig[i] == 'C' || trig[i] == 'c' ){
      trig_function = "Cos";
      break;
    }
    else if (trig[i] == '-' && (trig[i+1] == 'c' || trig[i+1] == 'C') ){
      trig_function = "-Cos";
      break;
    }
  }
      
 return {m, trig_function , a , nemo_a , demo_a};
}


string Do_Integration(string trig){
  auto [m , trig_function , a , nemo_a , demo_a ] = Identify_Integration(trig);
  string new_function ;
  if (trig_function == "Sin" ){
    a = -a/m;
    long long result_nemo = nemo_a * 1;
    long long result_demo = demo_a * m ;
    new_function = "-Cos(" + to_string(m) +"x) * " +  to_string(result_nemo) + "/" + to_string(result_demo);

  }
  else if (trig_function == "-Sin"){
    a = a/m;
    long long result_nemo = nemo_a * 1;
    long long result_demo = demo_a * m ;
    new_function = "Cos(" + to_string(m) +"x) * " +  to_string(result_nemo) + "/" + to_string(result_demo);
  }
  else if (trig_function == "Cos"){
    a = a/m;
    long long result_nemo = nemo_a * 1;
    long long result_demo = demo_a * m ;
    new_function = "Sin(" + to_string(m) +"x) * " +  to_string(result_nemo) + "/" + to_string(result_demo);

  }
  else if (trig_function == "-Cos"){
    a = -a/m;
    long long result_nemo = nemo_a * 1;
    long long result_demo = demo_a * m ;
    new_function = "-Sin(" + to_string(m) +"x) * " +  to_string(result_nemo) + "/" + to_string(result_demo);
  }
  return new_function;

}

int main() {
 int t;
 string trig , new_1;
 cout << "Please Enter The Trignometric Function [± sin(mx) , ± cos(mx)] \n";
 getline(cin , trig);
 new_1 = trig;
 cout << "Please Enter n times of integration \n";
 cin >> t;
 cin.ignore();
 for (int i = 0 ; i < t ; i++){
  new_1 = Do_Integration(new_1);
 }
 cout << "∫ " + trig + " is: " + new_1;
  
}
