#include <iostream>
#include "polyomino.h"


int Polyomino::getWidth() {
  return width;
}

int Polyomino::getHeight() {
  return height;
}

int Polyomino::getDepth() {
  return depth;
}

int Polyomino::boundingVolume() {
  return width * height * depth;
}

int Polyomino::getCubeCount() {
  return cubeCount;
}

void Polyomino::addCube() {
  cubeCount++;
}
