#include <iostream>
#include <vector>
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

void Polyomino::addCube(int x, int y, int z) {
  Position k = Position(x, y, z);

  if (x < minCornerCube.x) minCornerCube.x = x;
  if (y < minCornerCube.y) minCornerCube.y = y;
  if (z < minCornerCube.z) minCornerCube.z = z;

  if (x > maxCornerCube.x) maxCornerCube.x = x;
  if (y > maxCornerCube.y) maxCornerCube.y = y;
  if (z > maxCornerCube.z) maxCornerCube.z = z;

  cubes.push_back(k);
  cubeCount++;

  recomputeDims();
}

bool Polyomino::cubeTouching(int x, int y, int z) {
  return (isCubeAt(x + 1, y, z) || isCubeAt(x - 1, y, z) ||
    isCubeAt(x, y + 1, z) || isCubeAt(x, y - 1, z) ||
    isCubeAt(x, y, z+1) || isCubeAt(x, y, z-1));
}

Polyomino& Polyomino::rotate(Rotation dir) {
  switch (dir)  {
    case X90: {
      int temp;
      for (int i = 0; i < cubeCount; i++) {
        temp = cubes[i].y;
        cubes[i].y = -cubes[i].z;
        cubes[i].z = temp;
      }
      break;
    }
    case X180: {
      for (int i = 0; i < cubeCount; i++) {
        cubes[i].z = -cubes[i].z;
        cubes[i].y = -cubes[i].y;
      }
      break;
    }
    case X270: {
      int temp;
      for (int i = 0; i < cubeCount; i++) {
        temp = cubes[i].y;
        cubes[i].y = cubes[i].z;
        cubes[i].z = -temp;
      }
    }
    case Y90: {
      int temp;
      for (int i = 0; i < cubeCount; i++) {
        temp = cubes[i].x;
        cubes[i].x = cubes[i].z;
        cubes[i].z = -temp;
      }
      break;
    }
    case Y180: {
      for (int i = 0; i < cubeCount; i++) {
        cubes[i].x = -cubes[i].x;
        cubes[i].z = -cubes[i].z;
      }
      break;
    }
    case Y270: {
      int temp;
      for (int i = 0; i < cubeCount; i++) {
        temp = cubes[i].x;
        cubes[i].x = -cubes[i].z;
        cubes[i].z = temp;
      }
      break;
    }
    case Z90: {
      int temp;
      for (int i = 0; i < cubeCount; i++) {
        temp = cubes[i].x;
        cubes[i].x = -cubes[i].y;
        cubes[i].y = temp;
      }
      break;
    }
    case Z180: {
      for (int i = 0; i < cubeCount; i++) {
        cubes[i].y = -cubes[i].y;
        cubes[i].x = -cubes[i].x;
      }
      break;
    }
    case Z270: {
      int temp;
      for (int i = 0; i < cubeCount; i++) {
        temp = cubes[i].x;
        cubes[i].x = cubes[i].y;
        cubes[i].y = -temp;
      }
      break;
    }
  }

  recomputeBounding();

  return *this;
}

Polyomino& Polyomino::translate(int x, int y, int z) {
  for (int i = 0; i < cubeCount; i++) {
    cubes[i].x += x;
    cubes[i].y += y;
    cubes[i].z += z;
  }

  minCornerCube.x += x;
  minCornerCube.y += y;
  minCornerCube.z += z;

  maxCornerCube.x += x;
  maxCornerCube.y += y;
  maxCornerCube.z += z;

  return *this;
}

Polyomino& Polyomino::moveToOrigin() {
  translate(-minCornerCube.x, -minCornerCube.y, -minCornerCube.z);
  return *this;
}

Position Polyomino::getCube(int index) {
  return cubes.at(index);
}

const std::string Polyomino::toString(int sz = 2) {
  // TODO: Set up udderly display in isometric

  std::string output = "";
  for (int i = 0; i < cubeCount; i++) {
    output = output + "x: " + std::to_string(cubes[i].x)
      + ", y: " + std::to_string(cubes[i].y)
      + ", z: " + std::to_string(cubes[i].z) + "\n";
  }

  return output;
}

std::ostream& operator<< (std::ostream& os, Polyomino& p) {
  os << p.toString();
  return os;
}

bool Polyomino::isCubeAt(int x, int y, int z) {
  Position* q;
  for (int i = 0; i < cubeCount; i++) {
    q = &cubes[index];
    if (q->x == x && q->y == y && q->z == z) {
      return true;
    }
  }
  return false;
}

void Polyomino::recomputeBounding() {
  recomputeCorners();
  recomputeDims();
}

Polyomino& Polyomino::copy() {
  Polyomino* k = new Polyomino();
  Position* w;

  for (int i = 0; i < cubeCount; i++) {
    w = &cubes[i];
    k->addCube(w->x, w->y, w->z);
  }

  return *k;
}

void Polyomino::recomputeCorners() {
  minCornerCube.x = 1e9;
  minCornerCube.y = 1e9;
  minCornerCube.z = 1e9;

  maxCornerCube.x = -1e9;
  maxCornerCube.y = -1e9;
  maxCornerCube.z = -1e9;

  for (int i = 0; i < cubeCount; i++) {
    if (minCornerCube.x > cubes[cubeCount].x) minCornerCube.x = cubes[cubeCount].x;
    if (minCornerCube.y > cubes[cubeCount].y) minCornerCube.y = cubes[cubeCount].y;
    if (minCornerCube.z > cubes[cubeCount].z) minCornerCube.z = cubes[cubeCount].z;

    if (maxCornerCube.x < cubes[cubeCount].x) minCornerCube.x = cubes[cubeCount].x;
    if (maxCornerCube.y < cubes[cubeCount].y) minCornerCube.y = cubes[cubeCount].y;
    if (maxCornerCube.z < cubes[cubeCount].z) minCornerCube.z = cubes[cubeCount].z;
  }
}

void Polyomino::recomputeDims() {
  width = maxCornerCube.x - minCornerCube.x;
  depth = maxCornerCube.y - minCornerCube.y;
  height = maxCornerCube.z - minCornerCube.z;
}

void Polyomino::reorient() {
  moveToOrigin();

}
