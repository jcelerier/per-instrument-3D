#pragma once
#include "Shape.h"
#include "ofMain.h"
#include "Vector.h"

class SphericShape: public Shape
{
    public:
        SphericShape()
        {
            m_sphere.setRadius(0.01);

        }
        virtual ~SphericShape();

        void draw()
        {
            ofFill();
            ofSetColor(255);

            m_sphere.draw();
        }

        void update()
        {

        }

        void position(Vector p)
        {
            m_sphere.setPosition(p.x, p.y, p.z);
        }

        void size(Vector p)
        {

        }

        void enter()
        {

        }

        ofSpherePrimitive m_sphere;

};
