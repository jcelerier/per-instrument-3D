#pragma once

class Shape
{
    public:
        Shape();
        virtual ~Shape();
        virtual void draw() = 0;
        virtual void update() = 0;

        virtual void enter() = 0;
        virtual void leave() = 0;

        int id = 0;
};
