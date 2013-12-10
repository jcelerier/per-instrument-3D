#pragma once

struct Vector
{
        Vector(double _x, double _y, double _z):
            x(_x),
            y(_y),
            z(_z)
        {
        }
        ~Vector() {}

        double x = 0;
        double y = 0;
        double z = 0;
};
