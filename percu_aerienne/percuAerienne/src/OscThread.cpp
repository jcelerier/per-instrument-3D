#include "OscThread.h"
#include "testApp.h"
#include "Action.h"
#include <iostream>
OscThread::OscThread(testApp* p):
    parent(p)
{
    oscIn.setup(9786);
}

void OscThread::threadedFunction()
{
    ofxOscMessage m;
    while(isThreadRunning())
    {
        while(oscIn.getNextMessage(&m))
        {
            executeMessage(m);
        }
    }
}


void OscThread::executeMessage(ofxOscMessage& m)
{
    Action b;

    map<string, Action::Type> actions
    {
        {"/record", Action::Type::RECORD},
        {"/enter",  Action::Type::ENTER},
        {"/bump",  Action::Type::BUMP},
        {"/leave", Action::Type::LEAVE}
    };

    b.action = actions[m.getAddress()];

    unsigned int i = 0;
    b.instrument = m.getArgAsInt32(i++);
    b.bird = m.getArgAsInt32(i++);

    if(b.action == Action::Type::RECORD || b.action == Action::Type::BUMP)
    {
        b.delta_x = m.getArgAsFloat(i++);
        b.delta_y = m.getArgAsFloat(i++);
        b.delta_z = m.getArgAsFloat(i++);
        b.angle_x = m.getArgAsFloat(i++);
        b.angle_y = m.getArgAsFloat(i++);
        b.angle_z = m.getArgAsFloat(i++);

        if(b.action != Action::Type::BUMP)
        {
            b.speed_x = m.getArgAsFloat(i++);
            b.speed_y = m.getArgAsFloat(i++);
            b.speed_z = m.getArgAsFloat(i++);
            b.accel_x = m.getArgAsFloat(i++);
            b.accel_y = m.getArgAsFloat(i++);
            b.accel_z = m.getArgAsFloat(i++);
        }
        else // BUMP
        {
            b.velo_city = m.getArgAsFloat(i++);
        }
    }

    parent->executeAction(b);
}

OscThread::~OscThread()
{
}
