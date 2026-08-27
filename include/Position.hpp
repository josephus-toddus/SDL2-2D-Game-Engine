#include <cmath>
namespace cpuEng{
    struct Position
    {
        double x;
        double y;
    };

    struct Dimensions
    {
        int width;
        int height;

        int area() { return width * height; }
    };

    struct Vector2D
    {
        double x;
        double y;

        Vector2D normalise()
        {
            //say x = 33 y = 100
            // 33/100 = X/Y
            double mag = std::sqrt(x * x + y * y);

            return {x : x / mag, y : y / mag};
        }
    };
}