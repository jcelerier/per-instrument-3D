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
}

//--------------------------------------------------------------
void testApp::update()
{
    pointLight.setPosition((ofGetWidth()*.5), ofGetHeight()/2, 500);


    for(std::vector<Shape*>::iterator i = shapes.begin(); i != shapes.end(); ++i)
    {
        (*i)->update();
    }
}

//--------------------------------------------------------------
void testApp::draw()
{
    ofEnableDepthTest();
    // Pour avoir de l'éclairage qui fasse 3D
    ofEnableLighting();
    pointLight.enable();

    // Fond noir : on dessine une grosse sphère qui englobe tout
    ofSetColor(0);
    ofDrawSphere(ofGetWidth()/2, ofGetHeight()/2, ofGetWidth());


    for(std::vector<Shape*>::iterator i = shapes.begin(); i != shapes.end(); ++i)
    {
        (*i)->draw();
    }

    ofDisableLighting();


    ofDisableDepthTest();

    ofFill();
}


// Désolé c'est le code le plus dégueu que j'ai écrit de ma vie - jm
void testApp::readSetupFile()
{
    // Structure pour lire les données
    struct fileData
    {
        int shape;
        int id;
        int a;
        int b1, b2;
        double c1, c2, c3;
        double d1, d2, d3;
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
                iss >> f->c1 >> f->c2 >> f->c3;
                break;
            }
        case 5:
            {
                std::istringstream iss(line);
                iss >> f->d1 >> f->d2 >> f->d3;
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
                    c->position(Vector(f->c1 * 500, f->c2 * 500, f->c3 * 100));
                    shapes.push_back(c);
                }
                break;
            }
        }



    }

}
