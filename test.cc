#include <iostream>
#include "polyomino.h"

int main() {
  Polyomino p;

  p.addCube(0,0,0);

  std::cout << p.getCubeCount() << std::endl;
  p.addCube(0,0,1);
  std::cout << p.getCubeCount() << std::endl;
  p.addCube(0,1,1);
  p.addCube(0,1,2);

  p.rotate(X90).rotate(Y90).translate(5,0,0);

  std::cout << p << std::endl;

  return 0;
}
