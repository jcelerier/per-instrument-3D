#pragma once

#include "ofMain.h"
#include "OscThread.h"
#include "Action.h"
#include <vector>
#include <Shape.h>
#include <SphericShape.h>
class testApp : public ofBaseApp{

public:
    testApp():
        osc(this)
    {
    }

    ~testApp()
    {
        osc.stopThread();
    }

	void setup();
	void update();
	void draw();

	void readSetupFile();
	void initDrumsticks();

    void executeAction(Action a);

    std::vector<Shape*> shapes;
    ofLight pointLight;
    ofCamera camL;
    ofCamera camR;

    OscThread osc;

    SphericShape* ds1, *ds2;

    ofFbo left;
    ofFbo right;
};
