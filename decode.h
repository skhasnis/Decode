#ifndef _DECODE_H_
#define _DECODE_H_

class  Decode {
  std::string password;
 public: 
  int seed;
  int codeLength; 
  int guessLimit;
  Decode();
 ~Decode();
  void playGame();
  std::string getPassword(); 
  void findWhiteBlackPegs(std::string input); 
};

#endif
