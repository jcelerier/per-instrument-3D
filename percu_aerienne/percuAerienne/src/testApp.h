#pragma once

#include "ofMain.h"
#include "OscThread.h"
#include "Action.h"
#include <vector>
#include <Shape.h>

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

    void executeAction(Action a);

    std::vector<Shape*> shapes;
    ofLight pointLight;
    ofCamera cam;

    OscThread osc;
};
