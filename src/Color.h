#ifndef COLOR_H_INCLUDED
#define COLOR_H_INCLUDED

using namespace std;
class Color{
    private:
        float red;
        float green;
        float blue;
    public:
        Color(float, float, float );
        float getRed();
        float getGreen();
        float getBlue();
};

#endif // COLOR_H_INCLUDED
