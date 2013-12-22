#include "testApp.h"
#include <CubicShape.h>
#include <sstream>
#include <string>

//--------------------------------------------------------------
void testApp::setup(){

    ofSetVerticalSync(true);
    ofBackground(20);

    ofSetSmoothLighting(true);
    pointLight.setDiffuseColor( ofFloatColor(.85, .85, .55) );
    pointLight.setSpecularColor( ofFloatColor(1.f, 1.f, 1.f));

/*
    CubicShape* cube = new CubicShape;
    cube->position(Vector(400.2, 200.3, -600));
    cube->rotationX(45);
    cube->rotationY(128);
    shapes.push_back(cube);
*/
    readSetupFile();
    cam.setNearClip(1);
    cam.setFarClip(50);
    cam.setPosition(ofVec3f(2, 0, 0));

    cam.lookAt(ofVec3f(0,0,0),ofVec3f(0, 1, 0));
    cam.rotate(-90, ofVec3f(1, 0, 0));
    //setupCam();
    //cam.setPosition(0,0,-1); // where are we?

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

//--------------------------------------------------------------
void testApp::draw()
{
    cam.begin();
    ofEnableDepthTest();
    // Pour avoir de l'éclairage qui fasse 3D
    ofEnableLighting();
    pointLight.enable();

    // Fond noir : on dessine une grosse sphère qui englobe tout

    ofDrawSphere(ofGetWidth()/2, ofGetHeight()/2, ofGetWidth());


    for(std::vector<Shape*>::iterator i = shapes.begin(); i != shapes.end(); ++i)
    {
        (*i)->draw();
    }

    ofDisableLighting();


    ofDisableDepthTest();

    ofFill();
    cam.end();
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
           //     if(line.substr(0,2) == "Box")
                    f->shape = 1;
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
                    c->position(Vector(f->posx, f->posy, f->posz));
                    c->size(Vector(f->sizex * 1, f->sizey * 1, f->sizez * 1));
                    shapes.push_back(c);
                }
                break;
            }
        }
    }

}
