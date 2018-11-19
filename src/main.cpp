/*

the shell code i use to compile the program:
g++ main.cpp -g -Wall -Wextra -pthread -std=c++11


*/
#include <string>
#include <fstream>
//#include <iostream>
#include <regex>
using namespace std;
bool isVowel(char);
int main (){

  //new struct for a linked list node
	struct Node {
	  string word = "";
	  int freq = 0;
	};

  //string to put the lines of the file into
	string data;
  //opens file stream
   ifstream partA, partB, stopwords;
   //opens the file from the argument
   partA.open("tokenization-input-part-A.txt");
   partB.open("tokenization-input-part-B.txt");
   stopwords.open("stopwords.txt");
   string sWords[419];

   for (int i = 0; stopwords >> data; i++){
    sWords[i] = data;
    sWords[i+1] = "";
   }
   stopwords.close();
   /*for (int i = 0; i < 419; i++){
    cout << sWords[i] << "\n";
   }*/
   string* ptA = new string[1000];
   int i = 0;
   while(partA >> data){
    ptA[i] = data;
    i++;
   }


   /*for(int j = 0; j < 1000; j++){
    if(ptA[j] != "")
      cout << ptA[j] << "\n";
   }*/


   for(int j = 0; j < 1000; j++){
      unsigned int k;
      for(k = 0; k < ptA[j].length(); k++){
        if (!isalnum(ptA[j][k]))
          break;
      }
      
      //if(ptA[j] != "")
      //  cout << ptA[j] << " " << k << "\n";
      
      if(k != ptA[j].length()){
        if(ptA[j][k] != '.'){
          if (k == 0){
            ptA[j] = ptA[j].substr(1, (ptA[j].length() - 1));
            j--;
          }
          else if (k == (ptA[j].length() - 1)){
            //cout << "*** " << ptA[j] << " " << (ptA[j].length() - 2) << "\n";
            ptA[j] = ptA[j].substr(0, (ptA[j].length() - 1));
            //cout << "&&& " << ptA[j] << "\n";
          }
          else{
            //cout << "**** " << ptA[j] << " " << k+1 << " " << (ptA[j].length() - (k+1)) << "\n";
            ptA[i] = ptA[j].substr(k+1, (ptA[j].length() - (k+1)));
            i++;
            ptA[j] = ptA[j].substr(0, k);
            //cout << "&&&& " << ptA[j] << " " << i << "\n";
          }
        }
        else{
          regex e ("([a-zA-Z][\\.]){2,}");
          smatch m;
          regex_search (ptA[j],m,e);

          if(m.empty()){
            if (k == 0){
              ptA[j] = ptA[j].substr(1, (ptA[j].length() - 1));
              j--;
            }
            else if (k == (ptA[j].length() - 1)){
              ptA[j] = ptA[j].substr(0, (ptA[j].length() - 1));
            }
            else{
              ptA[i] = ptA[j].substr(k+1, (ptA[j].length() - (k+1)));
              i++;
              ptA[j] = ptA[j].substr(0, k);
            }
          }
          else{
            //cout << "*** " << ptA[j] << " " << m.length(0) << " " << m.position(0) << "\n";
            for(int l = m.length(0); l > m.position(0); l--){
              ptA[j].erase(l-1, 1);
              //cout << "&&& " << ptA[j] << "\n";
              l--;
            }
            //cout << "&&& " << ptA[j] << "\n";
            j--;
          }
        }
      }
   }
   for(int j = 0; j < 1000; j++){
      for(unsigned int k = 0; k < ptA[j].length(); k++){
        //if(isalpha(ptA[j][k])){
          ptA[j][k] = tolower(ptA[j][k]);
        //}
      }
   }
   for(int j = 0; j < 1000; j++){
      for(int k = 0; k < 419; k++){
        if(ptA[j].compare(sWords[k]) == 0){
          ptA[j] = "";
        }
      }
    }

    for(int j = 0; j < 1000; j++){

      if(ptA[j].length() > 4 && ptA[j][ptA[j].length()-1] == 's' && ptA[j][ptA[j].length()-2] == 'e' && ptA[j][ptA[j].length()-3] == 's' && ptA[j][ptA[j].length()-4] == 's'){
        ptA[j].erase(ptA[j].length()-2, 2);
      }
      else if(ptA[j].length() > 1 && ptA[j][ptA[j].length()-1] == 's' && !isVowel(ptA[j][ptA[j].length()-2])){
        ptA[j].erase(ptA[j].length()-1);
      }
      else if(ptA[j].length() > 3 && (ptA[j][ptA[j].length()-1] == 's' || ptA[j][ptA[j].length()-1] == 'd') && ptA[j][ptA[j].length()-2] == 'e' && ptA[j][ptA[j].length()-3] == 'i'){
        ptA[j].erase(ptA[j].length()-2, 2);
        if (ptA[j].length() <= 2){
          ptA[j] += 'e';
        }
      }
      if(ptA[j].length() > 4 && ptA[j][ptA[j].length()-1] == 'd' && ptA[j][ptA[j].length()-2] == 'e' && ptA[j][ptA[j].length()-3] == 'e'){
        ptA[j].erase(ptA[j].length()-1);
      }
      else if(ptA[j].length() > 7 && ptA[j][ptA[j].length()-1] == 'y' && ptA[j][ptA[j].length()-2] == 'l' && ptA[j][ptA[j].length()-3] == 'd' && ptA[j][ptA[j].length()-4] == 'e' && ptA[j][ptA[j].length()-5] == 'e'){
        ptA[j].erase(ptA[j].length()-3,3);
      }
      else if(ptA[j].length() > 2 && ptA[j][ptA[j].length()-1] == 'd' && ptA[j][ptA[j].length()-2] == 'e'){
        bool vowel = false;
        for (unsigned int l = 0; l < (ptA[j].length()-2); l++){
          if(isVowel(ptA[j][l])){
            vowel = true;
          }
        }
        if (vowel){
          ptA[j].erase(ptA[j].length()-2, 2);
        
          if((ptA[j][ptA[j].length()-1] == 't' && ptA[j][ptA[j].length()-2] == 'e') || (ptA[j][ptA[j].length()-1] == 'l' && ptA[j][ptA[j].length()-2] == 'b') || (ptA[j][ptA[j].length()-1] == 'z' && ptA[j][ptA[j].length()-2] == 'i')){
            ptA[j] += 'e';
          }
          else if(ptA[j][ptA[j].length()-1] == ptA[j][ptA[j].length()-2] && (ptA[j][ptA[j].length()-1] != 'l' && ptA[j][ptA[j].length()-1] != 's' && ptA[j][ptA[j].length()-1] != 'z')){
            ptA[j].erase(ptA[j].length()-1);
          }
          else if(ptA[j].length() >= 3){
            ptA[j] += 'e';
          }
          
        }
      }

    }

    ofstream outputFileA("tokenized.txt");

    for(int j = 0; j < 1000; j++){
      if(ptA[j].length() > 0){
        outputFileA << ptA[j] << "\n";
      }
    }
    outputFileA.close();



   Node* ptB = new Node[500000];
  i = 0;
  while(partB >> data){
    ptB[i].word = data;
    i++;
   }


for(int j = 0; j < 500000; j++){
      unsigned int k;
      for(k = 0; k < ptB[j].word.length(); k++){
        if (!isalnum(ptB[j].word[k]))
          break;
      }
      
      //if(ptB[j].word != "")
      //  cout << ptB[j].word << " " << k << "\n";
      
      if(k != ptB[j].word.length()){
        if(ptB[j].word[k] != '.'){
          if (k == 0){
            ptB[j].word = ptB[j].word.substr(1, (ptB[j].word.length() - 1));
            j--;
          }
          else if (k == (ptB[j].word.length() - 1)){
            //cout << "*** " << ptB[j].word << " " << (ptB[j].word.length() - 2) << "\n";
            ptB[j].word = ptB[j].word.substr(0, (ptB[j].word.length() - 1));
            //cout << "&&& " << ptB[j].word << "\n";
          }
          else{
            //cout << "**** " << ptB[j].word << " " << k+1 << " " << (ptB[j].word.length() - (k+1)) << "\n";
            ptB[i].word = ptB[j].word.substr(k+1, (ptB[j].word.length() - (k+1)));
            i++;
            ptB[j].word = ptB[j].word.substr(0, k);
            //cout << "&&&& " << ptB[j].word << " " << i << "\n";
          }
        }
        else{
          regex e ("([a-zA-Z][\\.]){2,}");
          smatch m;
          regex_search (ptB[j].word,m,e);

          if(m.empty()){
            if (k == 0){
              ptB[j].word = ptB[j].word.substr(1, (ptB[j].word.length() - 1));
              j--;
            }
            else if (k == (ptB[j].word.length() - 1)){
              ptB[j].word = ptB[j].word.substr(0, (ptB[j].word.length() - 1));
            }
            else{
              ptB[i].word = ptB[j].word.substr(k+1, (ptB[j].word.length() - (k+1)));
              i++;
              ptB[j].word = ptB[j].word.substr(0, k);
            }
          }
          else{
            //cout << "*** " << ptB[j].word << " " << m.length(0) << " " << m.position(0) << "\n";
            for(int l = m.length(0); l > m.position(0); l--){
              ptB[j].word.erase(l-1, 1);
              //cout << "&&& " << ptB[j].word << "\n";
              l--;
            }
            //cout << "&&& " << ptB[j].word << "\n";
            j--;
          }
        }
      }
   }
   for(int j = 0; j < 500000; j++){
      for(unsigned int k = 0; k < ptB[j].word.length(); k++){
        //if(isalpha(ptB[j].word[k])){
          ptB[j].word[k] = tolower(ptB[j].word[k]);
        //}
      }
   }

   for(int j = 0; j < 500000; j++){
      for(int k = 0; k < 419; k++){
        if(ptB[j].word.compare(sWords[k]) == 0){
          ptB[j].word = "";
        }
      }
    }

    for(int j = 0; j < 500000; j++){

      if(ptB[j].word.length() > 4 && ptB[j].word[ptB[j].word.length()-1] == 's' && ptB[j].word[ptB[j].word.length()-2] == 'e' && ptB[j].word[ptB[j].word.length()-3] == 's' && ptB[j].word[ptB[j].word.length()-4] == 's'){
        ptB[j].word.erase(ptB[j].word.length()-2, 2);
      }
      else if(ptB[j].word.length() > 1 && ptB[j].word[ptB[j].word.length()-1] == 's' && !isVowel(ptB[j].word[ptB[j].word.length()-2])){
        ptB[j].word.erase(ptB[j].word.length()-1);
      }
      else if(ptB[j].word.length() > 3 && (ptB[j].word[ptB[j].word.length()-1] == 's' || ptB[j].word[ptB[j].word.length()-1] == 'd') && ptB[j].word[ptB[j].word.length()-2] == 'e' && ptB[j].word[ptB[j].word.length()-3] == 'i'){
        ptB[j].word.erase(ptB[j].word.length()-2, 2);
        if (ptB[j].word.length() <= 2){
          ptB[j].word += 'e';
        }
      }
      if(ptB[j].word.length() > 4 && ptB[j].word[ptB[j].word.length()-1] == 'd' && ptB[j].word[ptB[j].word.length()-2] == 'e' && ptB[j].word[ptB[j].word.length()-3] == 'e'){
        ptB[j].word.erase(ptB[j].word.length()-1);
      }
      else if(ptB[j].word.length() > 7 && ptB[j].word[ptB[j].word.length()-1] == 'y' && ptB[j].word[ptB[j].word.length()-2] == 'l' && ptB[j].word[ptB[j].word.length()-3] == 'd' && ptB[j].word[ptB[j].word.length()-4] == 'e' && ptB[j].word[ptB[j].word.length()-5] == 'e'){
        ptB[j].word.erase(ptB[j].word.length()-3,3);
      }
      else if(ptB[j].word.length() > 2 && ptB[j].word[ptB[j].word.length()-1] == 'd' && ptB[j].word[ptB[j].word.length()-2] == 'e'){
        bool vowel = false;
        for (unsigned int l = 0; l < (ptB[j].word.length()-2); l++){
          if(isVowel(ptB[j].word[l])){
            vowel = true;
          }
        }
        if (vowel){
          ptB[j].word.erase(ptB[j].word.length()-2, 2);
        
          if((ptB[j].word[ptB[j].word.length()-1] == 't' && ptB[j].word[ptB[j].word.length()-2] == 'e') || (ptB[j].word[ptB[j].word.length()-1] == 'l' && ptB[j].word[ptB[j].word.length()-2] == 'b') || (ptB[j].word[ptB[j].word.length()-1] == 'z' && ptB[j].word[ptB[j].word.length()-2] == 'i')){
            ptB[j].word += 'e';
          }
          else if(ptB[j].word[ptB[j].word.length()-1] == ptB[j].word[ptB[j].word.length()-2] && (ptB[j].word[ptB[j].word.length()-1] != 'l' && ptB[j].word[ptB[j].word.length()-1] != 's' && ptB[j].word[ptB[j].word.length()-1] != 'z')){
            ptB[j].word.erase(ptB[j].word.length()-1);
          }
          else if(ptB[j].word.length() >= 3){
            ptB[j].word += 'e';
          }
          
        }
      }

    }

    for(int j = 0; j < 500000; j++){
      if (ptB[j].word != ""){
        ptB[j].freq = 1;
        for(int k = (j+1); k < 500000; k++){
          if (ptB[j].word.compare(ptB[k].word) == 0){
            ptB[j].freq++;
            ptB[k].word = "";
          }
        }
      }
    }

   bool swap =  true;
    while(swap){
      swap = false;
      for(int j = 0; j < 500000; j++){
        if(ptB[j+1].freq > ptB[j].freq){
          swap = true;
          int tempfreq = ptB[j].freq;
          string tempword = ptB[j].word;
          ptB[j].freq = ptB[j+1].freq;
          ptB[j].word = ptB[j+1].word;
          ptB[j+1].freq = tempfreq;
          ptB[j+1].word = tempword;
        }
      }
    }

    ofstream outputFileB("terms.txt");

    for(int j = 0; j < 200; j++){
      outputFileB << ptB[j].word << " " << ptB[j].freq << "\n";
    }
    outputFileB.close();


	partA.close();//close file
  partB.close();

	return 0;
}

bool isVowel(char c) {
    return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
}