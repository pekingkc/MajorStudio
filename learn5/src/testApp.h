#pragma once

/*
 This example demonstrates how to create a flat plane from triangles,
 and then oscillate its vertices to obtain a dynamic surface.
 
 It's the example 06-OscillatingPlane from the book
 "Mastering openFrameworks: Creative Coding Demystified",
 Chapter 7 - Drawing in 3D
 */

#include "ofMain.h"

class testApp : public ofBaseApp{
public:
    void setup();
    void update();
    void draw();
    
    ofMesh mesh;		//Mesh
    ofLight light;		//Light
    ofEasyCam easyCam;
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y);
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    //**********************************************
    //**********************************************
    //the audio stuff
    void audioIn(float * input, int bufferSize, int nChannels);
    
    float curVol;
    vector <float> left;
    vector <float> right;
    vector <float> volHistory;
    
    int 	bufferCounter;
    int 	drawCounter;
    
    float smoothedVol;
    float scaledVol;
    
    ofSoundStream soundStream;
    //**********************************************
    //**********************************************
};

//Universal function which sets normals
//for the triangle mesh
void setNormals( ofMesh &mesh );

