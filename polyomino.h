#include <vector>

#ifndef POLYOMINO_H
#define POLYOMINO_H

enum Rotation {
  X90,
  X180,
  X270,
  Y90,
  Y180,
  Y270,
  Z90,
  Z180,
  Z270,
};

struct Position {
  int x;
  int y;
  int z;
  Position(int xa = 0, int ya = 0, int za = 0) {
    x = xa;
    y = ya;
    z = za;
  }
};

class Polyomino {
private:
  int width;
  int height;
  int depth;

  Position minCornerCube;
  Position maxCornerCube;

  int cubeCount;
  std::vector<Position> cubes;

public:

  Polyomino() {
    width = 0;
    height = 0;
    depth = 0;

    cubeCount = 0;
  }

  int getWidth();
  int getHeight();
  int getDepth();

  int boundingVolume();

  int getCubeCount();
  bool isCubeAt(int,int,int);
  bool cubeTouching(int,int,int);
  void addCube(int,int,int);
  void reorient();

  void recomputeBounding();
  void recomputeCorners();
  void recomputeDims();

  Position getCube(int);
  Polyomino& translate(int,int,int);
  Polyomino& rotate(Rotation);
  Polyomino& moveToOrigin();
  Polyomino& copy();

  const std::string toString(int);
  friend std::ostream& operator<< (std::ostream& os, Polyomino& c);
};


#endif
