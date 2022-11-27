// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here

bool checkValidity(string word);

// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
    std::set<std::string> answers;
    
    std::string word = in;
    int n=0;
    
    //find length of word
    for (int i=0; i<in.length(); i++){
      n++;
    }
    
    //goes until word is filled out
    while (word.find("-") == true){
       for (char c ) 
    }
    
    answers = wordleHelper(word, floating, dict, n, 0);

    return answers;
}

// Define any helper functions here

bool checkValidity(std::string word, std::string floats){
    if (word.find("-") == false){
        for (int i=0; i<floats.length(); i++){
            if (word.find(floats[i]) == false){
                return false;
            }
        }
        return true;
    }
    return false;
}

void wordleHelper(
  const std::string& word,
  const std::string& floating,
  const std::set<std::string>& dict,
  int n, int k);
{
  std::set<std::string> options
  //std::string combination = word

  for (char c = 'a'; c < 'z'; c++){
    if(combination.find('-') == true){
      if(combination[k] == '-'){
        combination[k] = c;
       }
      k++;
       if (k<n){
         wordleHelper(combination, floating, dict, n, k);
       }
    }
    else if (checkValidity(combination, floating) == true){
      options.add(combination);
     }
    //reset last position
     combination[k] = '-';
     k = 0;
  }
} 
