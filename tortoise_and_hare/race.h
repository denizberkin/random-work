#pragma once
#include <iostream>
class Race{
public:
  Race();
  void moveTortoise (int *);
  void moveHare (int *);
  int race(int *, int *);
  
private:
  int tortoisePos = 1,
      harePos = 1;
};
