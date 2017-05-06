#include <iostream>
#include "decode.h"
#include <string> 
#include <cstdlib>
#include <utility> 
#include <algorithm>

using namespace std;

void welcomeMessage() {
  cout << "Welcome to Decode the code!" << endl;
  cout << "In this version, the code will be generated by the computer and you will have to decipher it." << endl;
  cout<< "The code is four letters, and can be any of A B C D E F." << endl;
  cout << "To continue, enter start. To quit at any point of the game, type quit." << endl; 
}


void chooseDifficulty(Decode &m) {
  cout << "Choose the difficulty level: easy, medium, hard" << endl;
  string difficult; 
  cin >> difficult;
  if (difficult == "easy") {
    m.guessLimit = 20;
  } else if (difficult == "medium") {
    m.guessLimit = 15;
  } else {
    m.guessLimit = 10;
  }
  cout << "Enter your first guess, four letter code:" << endl; 
} 

Decode::Decode() {
  this->seed = 5; 
  this->codeLength = 4;
  this->guessLimit = 20;
  char x;
  string code; 
  for(int i = 0; i < codeLength; i++) {
    char addA = 'A';
    x = rand() % 6 + addA;
    code += x;
  }
  this->password = code;
}


Decode::~Decode() { } 

string Decode::getPassword() {
  return this->password;
}

int findPair(vector <pair <char, bool> > seenChars, char  input) {
  int index = -1; 
  for(unsigned int i = 0 ; i < seenChars.size() ; i++) {
    if (seenChars[i].first == input && seenChars[i].second == false) {
      index = i; 
    }
  }
  return index; 
}


void Decode::findWhiteBlackPegs(string input){
  int blackPeg = 0;
  int whitePeg = 0;
  vector <pair <char, bool> >  seenChars;  
  string code = this->getPassword(); 
  for(int i = 0 ; i < 4; i++) {
    if (input[i] == code[i]) {
      ++blackPeg;
      seenChars.push_back(make_pair(code[i], true)); 
    } else {
      seenChars.push_back(make_pair(code[i], false)); 
    }
   }
   for(int i = 0 ; i < 4 ; i++) {
     int index = findPair(seenChars, input[i]); 
     if (input[i] != code[i] && index >= 0 ) {
       ++whitePeg;
       seenChars[index].second = true; 
     }
   }
  cout << "You have " << blackPeg << " black peg(s) (correct letter + placement) " << endl;
  cout << "You have " << whitePeg << " white peg(s) (correct letter + incorrect placement)" << endl; 
} 


int main() {
  welcomeMessage();
  string input; 
  cin >> input;

  if (input == "start") { 
  Decode game; 
  chooseDifficulty(game);

  // depending on the level of difficulty break the game 
  game.guessLimit--; 
  while(cin >> input && game.guessLimit) { 
    if (input == "quit") {
      cout << "Thanks for playing! :)" << endl;
      break;
    }
    else if (input == game.getPassword()) {
      cout << "You won! Thanks for playing :)" << endl;
      break; 
    }
    else {
      game.findWhiteBlackPegs(input);
    }
    cout << "You have " << game.guessLimit << " guesses left." << endl; 
    game.guessLimit = game.guessLimit - 1; 
  }
 }
}