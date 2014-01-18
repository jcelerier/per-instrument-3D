#include "testApp.h"
#include <CubicShape.h>
#include <sstream>
#include <string>
#include <iostream>
//--------------------------------------------------------------
void testApp::setup()
{
    ofSetWindowShape(2 * screenwidth, screenheight);
    ofSetVerticalSync(true);
    ofBackground(0);


    readSetupFile();
    initDrumsticks();

    // Lumière
    ofSetSmoothLighting(true);
    pointLight.setDiffuseColor(ofFloatColor(.85, .85, .55));
    pointLight.setSpecularColor(ofFloatColor(1.f, 1.f, 1.f));

    light.setAmbientColor(ofFloatColor(0.5, 0.5, 0.5));

    // Caméra
    updateCam();

    // FBOs
    left.allocate(screenwidth, screenheight, GL_RGBA, 16);
    right.allocate(screenwidth, screenheight, GL_RGBA, 16);

    // OSC
    osc.startThread(true, false);
}

void testApp::updateCam()
{
    double viewpoint = 1.6; // 1.6 pour FRONT; -1 pour BACK.
    double stereoAmplitude = 0.0;
    // Caméra
    camL.setNearClip(0.1);
    camL.setFarClip(50);
    camL.setPosition(ofVec3f(viewpoint, stereoAmplitude, -stereoAmplitude));
    camL.lookAt(ofVec3f(0,0,-stereoFactor),ofVec3f(0, 1, 0));
    camL.rotate(-90, ofVec3f(1, 0, 0));

    camR.setNearClip(0.1);
    camR.setFarClip(50);
    camR.setPosition(ofVec3f(viewpoint, -stereoAmplitude, stereoAmplitude));
    camR.lookAt(ofVec3f(0,0,stereoFactor),ofVec3f(0, 1, 0));
    camR.rotate(-90, ofVec3f(1, 0, 0));

}

void testApp::initDrumsticks()
{
    ds1 = new SphericShape();
    ds2 = new SphericShape();

    shapes.push_back(ds1);
    shapes.push_back(ds2);
}

double theta = 0;
//--------------------------------------------------------------
void testApp::update()
{
    pointLight.setPosition((ofGetWidth()*.5), ofGetHeight()/2, 500);
    //cam.setPosition(ofVec3f(cos(theta), 0, 2 * sin(theta)));
   //cam.rotate(theta, ofVec3f(1, 0 , 0));
    theta += 0.1;

    for(std::vector<Shape*>::iterator i = shapes.begin(); i != shapes.end(); ++i)
    {
        (*i)->update();
    }
}

void testApp::drawOneSide()
{
    ofEnableDepthTest();
    // Pour avoir de l'éclairage qui fasse 3D
    ofEnableLighting();
    pointLight.enable();
    light.enable();

    // Fond noir : on dessine une grosse sphère qui englobe tout

    ofDrawSphere(ofGetWidth()/2, ofGetHeight()/2, ofGetWidth());


    for(std::vector<Shape*>::iterator i = shapes.begin(); i != shapes.end(); ++i)
    {
        (*i)->draw();
    }

    ofDisableLighting();
    ofDisableDepthTest();

    ofFill();
}
//--------------------------------------------------------------
void testApp::draw()
{
    // Dessin dans les FBO
    left.begin();
    ofClear(255,255,255, 0);
    camL.begin();
    drawOneSide();
    camL.end();
    left.end();

    right.begin();
    ofClear(255,255,255, 0);
    camR.begin();
    drawOneSide();
    camR.end();
    right.end();

    // Affichage des FBO à l'écran
    left.draw(0,0);
    right.draw(screenwidth, 0);
}

void testApp::executeAction(Action a)
{

    if(a.action == Action::Type::ENTER)
    {
        for(Shape* s : shapes)
        {
            if(s->id == a.bird)
            {
                s->enter();
            }
        }
    }
    if(a.action == Action::Type::RECORD)
    {
        Vector pos(a.delta_x, a.delta_y, a.delta_z);
        switch(a.instrument)
        {
        case 1:
            ds1->position(pos);
            break;
        case 2:
            ds2->position(pos);
            break;
        default:
            break;
        }

    }
}

void testApp::keyPressed(int key)
{
    //     357
    // 356 359 358

    switch(key)
    {

    case 357:
        stereoFactor += 0.005;
        break;
    case 359:
        stereoFactor -= 0.005;
        break;
    default:
        break;
    }

    updateCam();
}

// Désolé c'est le code le plus dégueu que j'ai écrit de ma vie - jm
void testApp::readSetupFile()
{
    struct fileData
    {
        int shape;
        int id;
        int a;
        int b1, b2;
        double posx, posy, posz;
        double sizex, sizey, sizez;
        double e1, e2, e3, e4, e5, e6, e7, e8;
        double f1, f2, f3;
    };

    fileData* f;


    std::ifstream infile( "hybridrum.txt" );

    std::string line;
    std::getline(infile, line); // première ligne
    int i = 0;

    while (std::getline(infile, line))
    {
        int mod = i++ % 8;
        switch(mod)
        {
        case 0:
            break;
        case 1:
            {
                f = new fileData;
                    f->shape = 1;
                    f->id = std::stoi(line.substr(line.size() - 1, 1));
                break;
            }
        case 2:
            {
                std::istringstream iss(line);
                iss >> f->a;
                break;
            }
        case 3:
            {
                std::istringstream iss(line);
                iss >> f->b1 >> f->b2;
                break;
            }
        case 4:
            {
                std::istringstream iss(line);
                iss >> f->posx >> f->posy >> f->posz;
                break;
            }
        case 5:
            {
                std::istringstream iss(line);
                iss >> f->sizex >> f->sizey >> f->sizez;
                break;
            }
        case 6:
            {
                std::istringstream iss(line);
                iss >> f->e1 >> f->e2 >> f->e3 >> f->e4 >> f->e5 >> f->e6 >> f->e7 >> f->e8;
                break;
            }
        case 7:
            {
                std::istringstream iss(line);
                iss >> f->f1 >> f->f2 >> f->f3;

                // A la fin on ajoute
                if(f->shape == 1)
                {
                    CubicShape* c = new CubicShape;
                    c->id = f->id;
                    c->position(Vector(f->posx, f->posy, f->posz));
                    c->size(Vector(f->sizex * 1, f->sizey * 1, f->sizez * 1));
                    shapes.push_back(c);
                }
                break;
            }
        }
    }

}
