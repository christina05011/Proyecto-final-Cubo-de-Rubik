#ifndef CUBE_H
#define CUBE_H

#include <iostream>

class Cube {

  public: 
      int cubies[9][6];
      std::string mov = "";
  
      Cube();

      std::string printSequence(std::string);
      bool xd = false;
      void moves(std::string);
      void output();
      void R(int);
      void L(int);
      void U(int);
      void D(int);
      void F(int);
      void B(int);
};
#endif
