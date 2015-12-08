#pragma once

#include "ofMain.h"
#include "ofxTrueTypeFontUC.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
		void keyPressed(int key);
    
    void getInfo();
    
    ofVideoGrabber cam;
    
    float happy,sad,confused,surprised,calm,angry;
    
    ofxTrueTypeFontUC font;
    
    ofImage img;
    
    vector<ofPoint> biu;
    
    float x,y;
    
    string sadEmo[2], happyEmo[2], confusedEmo[2],calmEmo[1],angryEmo[2], surprisedEmo[2];
};
