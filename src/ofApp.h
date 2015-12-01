#pragma once

#include "ofMain.h"
#include "NeuralNetwork.h"
#include "ofxGui.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
        void drawGUI();
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    ofEasyCam cam;
    ofSpherePrimitive sphere;
    NeuralNetwork net;
    vector<Dataset>datas;
    ofImage img;

    ofxPanel gui;
    
    ofxFloatSlider ita_slider;
    ofxIntSlider speed_slider;
    ofxFloatSlider hi_slider;
    ofxFloatSlider lo_slider;
    int m_x,m_y;
    //display resolution
    int res = 3;
    
    //neural network count
    int net_count=0;
};
