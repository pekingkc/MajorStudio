#include "testApp.h"

int W = 200;		//Grid size
int H = 200;

//--------------------------------------------------------------
void testApp::setup(){
    //Set up vertices and colors
    for (int y=0; y<H; y++) {
        for (int x=0; x<W; x++) {
            mesh.addVertex(
                           ofPoint( (x - W/2) * 12, (y - H/2) * 12, 0 ) );
            mesh.addColor( ofColor( 0, 255, 0 ) );
        }
    }
    //Set up triangles' indices
    for (int y=0; y<H-1; y++) {
        for (int x=0; x<W-1; x++) {
            int i1 = x + W * y;
            int i2 = x+1 + W * y;
            int i3 = x + W * (y+1);
            int i4 = x+1 + W * (y+1);
            mesh.addTriangle( i1, i2, i3 );
            mesh.addTriangle( i3, i1, i2 );
        }
    }
    setNormals( mesh );		//Set normals
    light.enable();			//Enable lighting
    
    
    
//**********************************************
//**********************************************
//setup the audio input
    
    soundStream.listDevices();
    
    int bufferSize = 256;
    
    left.assign(bufferSize, 0.0);
    
    volHistory.assign(400, 0.0);
    
    bufferCounter	= 0;
    drawCounter		= 0;
    smoothedVol     = 0.0;
    scaledVol		= 0.0;
    
    soundStream.setup(this, 0, 2, 44100, bufferSize, 4);
    
//**********************************************
//**********************************************
}

//--------------------------------------------------------------
void testApp::update(){
    float time = ofGetElapsedTimef();	//Get time
    //Change vertices
    for (int y=0; y<H; y++) {
        for (int x=0; x<W; x++) {
            int i = x + W * y;			//Vertex index
            ofPoint p = mesh.getVertex( i );
            
            //Get Perlin noise value
            float value =
            ofNoise( x * 0.1, y * 0.1, time * 1 );
            
            //Change z-coordinate of vertex
            p.z = value * 100*smoothedVol*100;
//            p.x = x+100 * smoothedVol;
            mesh.setVertex( i, p );
            
            //Change color of vertex
            mesh.setColor( i,
//                          ofColor( value*255, value * 255, 255 ) );
                          ofColor( 0, 255, 255 ) );
        }
    }
    setNormals( mesh );	//Update the normals
}

//--------------------------------------------------------------
void testApp::draw(){
    ofEnableDepthTest();				//Enable z-buffering
    
    //Set a gradient background from white to gray
    ofBackgroundGradient( ofColor( 255 ), ofColor( 128 ) );
    
    
    easyCam.begin();

    
    ofPushMatrix();						//Store the coordinate system
    
    //Move the coordinate center to screen's center
    ofTranslate( ofGetWidth()/2, ofGetHeight()/2, 0 );
    
    //Calculate the rotation angle
    float time = ofGetElapsedTimef();   //Get time in seconds
    float angle = time * 20;			//Compute angle. We rotate at speed
    //20 degrees per second
//    ofRotate( smoothedVol*PI, 1, 0, 0 );			//Rotate coordinate system
    ofRotate( angle, 0, 0, 1 );
    
    //Draw mesh
    //Here ofSetColor() does not affects the result of drawing,
    //because the mesh has its own vertices' colors
    mesh.draw();
    
    ofPopMatrix();      //Restore the coordinate system
    
    
    easyCam.end();
}

//**********************************************
//**********************************************
//audio input class
void testApp::audioIn(float * input, int bufferSize, int nChannels){
    
    float curVol = 0.0;
    
    // samples are "interleaved"
    int numCounted = 0;
    
    //lets go through each sample and calculate the root mean square which is a rough way to calculate volume
    for (int i = 0; i < bufferSize; i++){
        left[i]		= input[i*2]*0.5;
        //        right[i]	= input[i*2+1]*0.5;
        
        curVol += left[i] * left[i];
        //        curVol += right[i] * right[i];
        numCounted+=2;
    }
    
    //this is how we get the mean of rms :)
    curVol /= (float)numCounted;
    
    // this is how we get the root of rms :)
    curVol = sqrt( curVol );
    
    smoothedVol *= 0.93;
    smoothedVol += 0.07 * curVol;
    
    bufferCounter++;
    
}
//**********************************************
//**********************************************


//--------------------------------------------------------------
//Universal function which sets normals for the triangle mesh
void setNormals( ofMesh &mesh ){
    
    //The number of the vertices
    int nV = mesh.getNumVertices();
    
    //The number of the triangles
    int nT = mesh.getNumIndices() / 3;
    
    vector<ofPoint> norm( nV ); //Array for the normals
    
    //Scan all the triangles. For each triangle add its
    //normal to norm's vectors of triangle's vertices
    for (int t=0; t<nT; t++) {
        
        //Get indices of the triangle t
        int i1 = mesh.getIndex( 3 * t );
        int i2 = mesh.getIndex( 3 * t + 1 );
        int i3 = mesh.getIndex( 3 * t + 2 );
        
        //Get vertices of the triangle
        const ofPoint &v1 = mesh.getVertex( i1 );
        const ofPoint &v2 = mesh.getVertex( i2 );
        const ofPoint &v3 = mesh.getVertex( i3 );
        
        //Compute the triangle's normal
        ofPoint dir = ( (v2 - v1).crossed( v3 - v1 ) ).normalized();
        
        //Accumulate it to norm array for i1, i2, i3
        norm[ i1 ] += dir;
        norm[ i2 ] += dir;
        norm[ i3 ] += dir;
    }
    
    //Normalize the normal's length
    for (int i=0; i<nV; i++) {
        norm[i].normalize();
    }
    
    //Set the normals to mesh
    mesh.clearNormals();
    mesh.addNormals( norm );
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y){
    
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 
    
}