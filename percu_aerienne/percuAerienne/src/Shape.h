#pragma once

class Shape
{
    public:
        Shape();
        virtual ~Shape();
        virtual void draw() = 0;
        virtual void update() = 0;
};
