#include "Coordinate.h"

Coordinate::Coordinate(float c1, float c2, float c3): x(c1), y(c2), z(c3){ }

float Coordinate::getX(){
    return x;
}

float Coordinate::getY(){
    return y;
}

float Coordinate::getZ(){
    return z;
}
