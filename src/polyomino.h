#include <vector>
#include "position.h"

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

class Polyomino {
private:
  Position minCornerCube;
  Position maxCornerCube;

  unsigned long hashResult;
  int width;
  int height;
  int depth;
  int cubeCount;
  bool hashComputed;
  bool reoriented;

  std::vector<Position> cubes;

public:

  Polyomino();
  ~Polyomino();

  int getWidth();
  int getHeight();
  int getDepth();
  Position minCorner();
  Position maxCorner();

  int boundingVolume();

  int getCubeCount();
  bool isCubeAt(int,int,int);
  bool cubeTouching(int,int,int);
  Polyomino& addCube(int,int,int);
  Polyomino& reorient();

  void recomputeBounding();
  void recomputeCorners();
  void recomputeDims();

  Position getCube(int);
  Polyomino& translate(int,int,int);
  Polyomino& rotate(int);
  Polyomino& moveToOrigin();
  Polyomino& join(Polyomino&);
  bool equals(Polyomino&);
  bool operator== (Polyomino&);

  hashType hash();

  const std::string toString();
  friend std::ostream& operator<< (std::ostream& os, Polyomino& c);
};

#endif // POLYOMINO_H
