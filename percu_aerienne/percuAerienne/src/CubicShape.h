#pragma once
#include <Shape.h>
#include <Vector.h>

#include "ofMain.h"
class CubicShape : public Shape
{
    public:
        CubicShape();
        virtual ~CubicShape();

        void draw()
        {
            ofFill();
            if(inside)
            {
                ofSetColor(250);
            }
            else
            {
                ofSetColor(100);
            }

            m_box.draw();
        }

        void update()
        {
        }

        virtual void enter()
        {
            inside++;
        }
        virtual void leave()
        {
            inside--;
        }
        void position(Vector p)
        {
            m_box.setPosition(p.x, p.y, p.z);
        }

        void size(Vector p)
        {
            m_box.set(p.x, p.y, p.z);
        }

        void rotationX(double deg)
        {
            m_box.rotate(deg, 1, 0, 0);
        }

        void rotationY(double deg)
        {
            m_box.rotate(deg, 0, 1, 0);
        }

        void rotationZ(double deg)
        {
            m_box.rotate(deg, 0, 1, 0);
        }

        ofBoxPrimitive m_box;
    private:
        double count = 0.1;
        int inside = 0;
        bool inside_enable = false;
};
