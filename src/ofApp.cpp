#include "ofApp.h"
#include<math.h>
int target = 0;


//--------------------------------------------------------------
void ofApp::setup(){
    ofEnableSmoothing();
    Dataset data = Dataset(1);
    for(int i=0;i<NUM_OUTPUT;i++){
        data.target = i;
        data.makeData();
        //data.makeNoise();
        datas.push_back(data);
        datas[i].disp();
    }
    
    
    net = NeuralNetwork(NUM_INPUT,NUM_INTERM,NUM_OUTPUT,datas[0]);
    
    net.dataset = datas[4];
    net.setup();
    
    //glBlendFunc(GL_SRC_ALPHA,GL_ONE);
    img.loadImage("jotaro_tiny.png");
    
    
                

    /////////////////////
    //GUISETUP
    gui.setup();
    gui.add(ita_slider.setup("eta",0.03,0.03,1.0));
    gui.add(speed_slider.setup("speed",1,1,100));
    gui.add(hi_slider.setup("noise",0.03,0.03,1.0));
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofShowCursor();
    
    
    glEnable(GL_DEPTH_TEST);
    float margin = 40.0f;
    ofBackground(119,41,83);
    ofSetColor(255);
    img.draw(10, 10, 100, 100);
    ofDrawBitmapString("3-layer Neural Network Visualizer", 120,10);
    ofDrawBitmapString("itaration count = "+ofToString(net_count) ,240,20);
    ofPushMatrix();{
        ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
        cam.begin();
        ///input layer 100
        sphere.set(5,10);
        ofPushMatrix();
        ofTranslate(0, 200);
        for(int i=0;i<sqrt(NUM_INPUT);i++){
            for(int j=0; j<sqrt(NUM_INPUT);j++){
                ofSetColor(MIN(245*(net.dataset.data[i*sqrt(NUM_INPUT)+j])+10,255));
                sphere.setPosition((float)(i-5)*margin,0 ,(float)(j-5)*margin);
                sphere.draw();
            }
        }ofPopMatrix();
        
        //interm layer 49
        ofPushMatrix();
        ofTranslate(0, 0);
        for(int i=0;i<sqrt(NUM_INTERM);i++){
            for(int j=0; j<sqrt(NUM_INTERM);j++){
                ofSetColor(MIN(255,245*net.interm_layer[i*sqrt(NUM_INTERM)+j].y));
                sphere.setPosition((float)(i-3)*margin,0 ,(float)(j-3)*margin);
                sphere.draw();
            }
        }ofPopMatrix();
        
        //output layer 10
        ofPushMatrix();
        ofTranslate(0, -200);
        for(int i=0;i<NUM_OUTPUT;i++){
            //for(int j=0; j<7;j++){
                ofSetColor(MIN(255,255*net.output_layer[i].y));
                sphere.setPosition((float)(i-3)*margin,0,0);
                sphere.draw();
            //}
        }ofPopMatrix();
        ///
        
        
        ofPushMatrix();
        ofTranslate(0, 200);
        ofSetLineWidth(1);
        
        for(int i=0;i<sqrt(NUM_INPUT);i+=res){
            for(int j=0; j<sqrt(NUM_INPUT);j+=res){
                for(int k=0;k<sqrt(NUM_INTERM);k+=res){
                    for(int l=0;l<sqrt(NUM_INTERM);l+=res){
                        ofSetColor(MIN(255,255 * net.interm_layer[k*sqrt(NUM_INTERM)+l].w[i*sqrt(NUM_INPUT)+j]));
                        ofDrawLine((i-5)*margin,0,(j-5)*margin,(k-3)*margin,-200,(l-3)*margin);
                    }
                }
            }
        }ofPopMatrix();
        
        ofPushMatrix();
        ofTranslate(0, 0);
        ofSetLineWidth(2);
        for(int i=0;i<sqrt(NUM_INTERM);i++){
            for(int j=0; j<sqrt(NUM_INTERM);j++){
                for(int k=0;k<NUM_OUTPUT;k++){
                    //for(int l=0;l<7;l+=2){
                    //net.output_layer[k].disp();
                        ofSetColor(MIN(255,255 * net.output_layer[k].w[i*sqrt(NUM_INTERM)+j]));
                        ofDrawLine((i-3)*margin,0,(j-3)*margin,(k-3)*margin,-200,0);
                    //}
                }
            }
        }ofPopMatrix();
        cam.end();
    }ofPopMatrix();
    glDisable(GL_DEPTH_TEST);
    
    
    ofPushMatrix();{
        gui.setTextColor(ofColor(255,255,255));
        gui.setPosition(20, 150);
        gui.draw();
    }ofPopMatrix();

    ofShowCursor();

    ofPushMatrix();{
        ofTranslate(500,10);
        for(int l=0; l<datas.size();l++){
            for(int i=0; i<sqrt(NUM_INPUT);i++){
                for(int k=0;k<sqrt(NUM_INPUT);k++){
                    ofPushMatrix();{
                        ofTranslate(i*3 + l*40, k*3);
                        ofSetColor(MIN(235,175*(input_log[l][i+k*(int)sqrt(NUM_INPUT)])));
                        ofDrawRectangle(0, 0, 3, 3);
                        
                        
                    }ofPopMatrix();
                }
            }
        }
        for(int l=0; l<NUM_OUTPUT;l++){
            for(int i=0; i<sqrt(NUM_INTERM);i++){
                for(int k=0;k<sqrt(NUM_INTERM);k++){
                    ofPushMatrix();{
                        ofTranslate(i*3 + l*40, k*3+50);
                        ofSetColor(MIN(255,255*(interm_log[l][i+k*(int)sqrt(NUM_INTERM)])));
                        ofDrawRectangle(0, 0, 3, 3);
                        
                        
                    }ofPopMatrix();
                }
            }
        }
        
        
    }ofPopMatrix();
    
}


//--------------------------------------------------------------
void ofApp::drawGUI(){
    gui.draw();
}



//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    net.ita = ita_slider;
    if(key == OF_KEY_UP){
        net.dataset = datas[0];
        net.setup();
    }
    else if(key == OF_KEY_DOWN){
        net.dataset = datas[1];
        net.setup();
    }
    else if(key == OF_KEY_SHIFT){
        res = (res == 1)?3:1;
    }
    else{
        for(int i=0; i < speed_slider; i++){
                net_count++;
                net.dataset = datas[target];
            for(int k=0;k<NUM_INTERM;k++){
                interm_log[target][k]=net.interm_layer[k].y;
            }
            for(int k=0;k<NUM_INPUT;k++){
                input_log[target][k]=net.input_layer[k].y;
            }
                net.update_bp(target);
                target = (target<NUM_OUTPUT-1)?target+1:0;
        }
    }
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
