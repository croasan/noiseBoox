#pragma once

#include "ofMain.h"
#include "ofxUI.h"
#include "ofxTonic.h"
#include "synthPlayer.h"

#include "UDPReceiver.h"
using namespace Tonic;

class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    void audioRequested (float * output, int bufferSize, int nChannels);
    void setUI();
    void guiEvent(ofxUIEventArgs &e);
    void updateUI();
    static void setParameter(string parameter, int data);
    static void setChord(int midiNote1, int midiNote2);
    float mapPAD(float x, float in_min, float in_max, float out_min, int out_max);
    void checkDots();
    void exit();
private:
    static ofxTonicSynth synth;
    ofImage *background;
    UDPReceiver *UDPConnection;
    ofxUICanvas *UI;
    ofxUICanvas *back;
    ofxUICanvas *data;
    ofColor backgroundColor;
	float red, green, blue;
    ofxUI2DPad* emotionPAD;
    synthPlayer* player;
    ControlGenerator noteFreqH;
    ControlGenerator noteFreqM;
    ControlGenerator noteFreqHInterval;
    int frame;
    int fps;
    ofSoundPlayer soundEngine;
    ofSoundPlayer sound2;
    int i;
    float speed;
    
    //UI data
    ofxUILabel *tempoLabel;
    ofxUILabel *scaleLabel;
    ofxUILabel *melodicNote;
    ofxUILabel *harmonicNote1;
    ofxUILabel *harmonicNote2;
    ofxUILabel *melodicGrade;
    ofxUILabel *harmonicGrade;
    ofxUILabel *interval;
    ofxUILabel *numSemitones;
    
    ofImage *keyH1;
    ofImage *keyH2;
    ofImage *keyH3;
    ofImage *keyH4;
    
    ofImage *keyH1a;
    ofImage *keyH2a;
    ofImage *keyH3a;
    ofImage *keyH4a;
    
    ofImage *keyM1;
    ofImage *keyM2;
    ofImage *keyM3;
    ofImage *keyM4;
    
};
