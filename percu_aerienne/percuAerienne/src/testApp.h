#pragma once

#include "ofMain.h"
#include <vector>
#include <Shape.h>
class testApp : public ofBaseApp{

public:
	void setup();
	void update();
	void draw();

	void readSetupFile();

    std::vector<Shape*> shapes;
    ofLight pointLight;

};
