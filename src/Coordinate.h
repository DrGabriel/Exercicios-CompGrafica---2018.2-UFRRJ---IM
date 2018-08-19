#ifndef COORDINATE_H_INCLUDED
#define COORDINATE_H_INCLUDED

using namespace std;
class Coordinate{
    private:
        float x;
        float y;
        float z;
    public:
        Coordinate(float, float, float);
        float getX();
        float getY();
        float getZ();
};

#endif // COORDINATE_H_INCLUDED
