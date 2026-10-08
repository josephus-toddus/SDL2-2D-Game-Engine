#include <cmath>

#pragma once

namespace cpuEng
{
    struct Position
    {
        float x;
        float y;

        bool operator==(const Position& pos)
        {
            return x == pos.x && y == pos.y;
        }
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
            double mag = std::sqrt(x * x + y * y);

            return {x : x / mag, y : y / mag};
        }
    };

    struct BoundingBox
    {
        float x;
        float y;

        float width;
        float height;
    };
}