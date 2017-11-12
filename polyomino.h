#ifndef POLYOMINO_H
#define POLYOMINO_H

class Polyomino {
private:
  int width;
  int height;
  int depth;

  int cubeCount;
public:
  int getWidth();
  int getHeight();
  int getDepth();
  int boundingVolume();
  int getCubeCount();
  void addCube();
};


#endif
