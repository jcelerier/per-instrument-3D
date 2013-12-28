#pragma once
#include "ofMain.h"
#include "ofxOscReceiver.h"

class testApp;

class OscThread : public ofThread
{
    public:
        OscThread(testApp* p);
        virtual ~OscThread();
        virtual void threadedFunction();
        void executeMessage(ofxOscMessage& m);

    private:
        ofxOscReceiver oscIn;
        testApp* parent;
};
