#include "ofApp.h"
#include "emotionState.h"
#include <math.h>
#include "midiSaver.h"

ofxTonicSynth ofApp::synth = ofxTonicSynth();

//--------------------------------------------------------------
void ofApp::setup(){
     ofSoundStreamSetup(2, 0, this, 44100, 256, 4);
     UDPConnection = new UDPReceiver();
     player = new synthPlayer();
     fps = 60;
     ofSetFrameRate(fps);
     frame = 0;
     setUI();
    
     //SineWave tone = SineWave();

    
     //*************PARAMETERS*******************
    
    //HARMONIC
     ControlParameter triggerH = synth.addParameter("triggerHarmonic", 1);
     ControlGenerator midiNoteHarmonic = synth.addParameter("midiNumberHarmonic");
     noteFreqH = ControlMidiToFreq().input(midiNoteHarmonic);
    
    ControlGenerator midiNoteHarmonicInterval = synth.addParameter("midiNumberHarmonicInterval");
    noteFreqHInterval = ControlMidiToFreq().input(midiNoteHarmonicInterval);
    

    //MELODIC
    ControlParameter triggerM = synth.addParameter("triggerMelodic", 0);
    ControlGenerator midiNoteMelodic = synth.addParameter("midiNumberMelodic");
    noteFreqM = ControlMidiToFreq().input(midiNoteMelodic);
    
     //***************WAVES**********************
     Generator harmonicTone = SawtoothWave().freq(noteFreqH);
     Generator harmonicInterval = SawtoothWave().freq(noteFreqHInterval);
     Generator melodicTone = TriangleWave().freq(noteFreqM);
    
        //***************Partials**********************
        Generator firstPartial = SineWave().freq(noteFreqH * 2);
        Generator secondPartial = SineWave().freq(noteFreqH * 3);
    
    
     //****************FILTERS*******************
    
    //HARMONIC
     ADSR envH = ADSR(3.4f, 0.8f, 1.5f, 4.4f).trigger(triggerH);
    harmonicTone = LPF12().input(harmonicTone).Q(10).cutoff((noteFreqH) + SineWave().freq(0.6) * 0.5 * noteFreqH);
        
    
    //MELODIC
     ADSR envM = ADSR(1.3f, 0.8f, 1.5f, 1.4f).trigger(triggerM);
     
    
     synth.setParameter("midiNumberHarmonic",60);
     synth.setParameter("midiNumberMelodic", 64);
     //synth.setOutputGen(harmonicTone*envH*0.05 + harmonicInterval*envH*0.05 + melodicTone*envM);
    
    
    //***********TESTING NOISE*****************
    /*Generator noise = PinkNoise();
    Generator tonee = SineWave().freq(400);
    noise = HPF24().cutoff(900).input(noise).Q(50);
    ADSR Adsr = ADSR(0.4f, 0.0f, 0.5f, 0.4f).trigger(triggerH);
    Generator reverb = Reverb().input(noise).density(1).dryLevel(0).wetLevel(0.2).decayTime(1);
    synth.setOutputGen(noise + reverb + harmonicTone);*/
    
    
}

//--------------------------------------------------------------
void ofApp::update(){
    updateUI();
    
    
    if (frame > 60) {
        frame = 0;
    }

    
    
    
    UDPConnection->getMessage();
    player->update(frame, fps);
    frame++;
}

//--------------------------------------------------------------
void ofApp::draw(){

    
    background->draw(0, 0);
    
    
    checkDots();
	
	
}
//--------------------------------------------------------------
void ofApp::checkDots() {
    //******HARMONIC**********
    
    int midiNoteH = emotionState::Instance()->getHarmonicNote() % 12;
    int midiNoteM = emotionState::Instance()->getMelodicNote() % 12;
    int interval = emotionState::Instance()->getInterval() + midiNoteH;
    int start = ListOfScales[emotionState::Instance()->getScale()][0];
    
    
    
    
    if (start >= 5) { //In case of I grade >= A
        if (midiNoteH == 5) keyH1->draw(20, 527, 42, 85);
        else if (midiNoteH == 6) keyH2->draw(20, 484, 64, 42);
        else if (midiNoteH == 7) keyH1->draw(63, 527, 42, 85);
        else if (midiNoteH == 8) keyH3->draw(85, 484, 41, 41);
        else if (midiNoteH == 9) keyH1->draw(106, 527, 42, 85);
        else if (midiNoteH == 10) keyH4->draw(127, 484, 64, 41);
        else if (midiNoteH == 11) keyH1->draw(149, 527, 42, 85);
        else if (midiNoteH == 0) keyH1->draw(193, 527, 42, 85);
        else if (midiNoteH == 1) keyH2->draw(193, 484, 64, 42);
        else if (midiNoteH == 2) keyH1->draw(236, 527, 42, 85);
        else if (midiNoteH == 3) keyH4->draw(258, 484, 64, 41);
        else if (midiNoteH == 4) keyH1->draw(279, 527, 42, 85);
        
        //********INTERVAL*********//
        if(midiNoteH < 5) interval += 7;
        if(midiNoteH >= 5) interval -= 5;
        
        //cout<<"interval:"<<interval<<endl;
        
        if (interval == 0) keyH1a->draw(20, 527, 42, 85);
        else if (interval == 1) keyH2a->draw(20, 484, 64, 42);
        else if (interval == 2) keyH1a->draw(63, 527, 42, 85);
        else if (interval == 3) keyH3a->draw(85, 484, 41, 41);
        else if (interval == 4) keyH1a->draw(106, 527, 42, 85);
        else if (interval == 5) keyH4a->draw(127, 484, 64, 41);
        else if (interval == 6) keyH1a->draw(149, 527, 42, 85);
        else if (interval == 7) keyH1a->draw(193, 527, 42, 85);
        else if (interval == 8) keyH2a->draw(193, 484, 64, 42);
        else if (interval == 9) keyH1a->draw(236, 527, 42, 85);
        else if (interval == 10) keyH4a->draw(258, 484, 64, 41);
        else if (interval == 11) keyH1a->draw(279, 527, 42, 85);
        
        else if (interval == 12) keyH1a->draw(322, 527, 42, 85);
        else if (interval == 13) keyH2a->draw(323, 484, 64, 42);
        else if (interval == 14) keyH1a->draw(366, 527, 42, 85);
        else if (interval == 15) keyH3a->draw(388, 484, 41, 41);
        else if (interval == 16) keyH1a->draw(409, 527, 42, 85);
        else if (interval == 17) keyH4a->draw(430, 484, 64, 41);
        else if (interval == 18) keyH1a->draw(452, 527, 42, 85);
        
        else if (interval == 19) keyH1a->draw(495, 527, 42, 85);
        else if (interval == 20) keyH2a->draw(496, 484, 64, 42);
        else if (interval == 21) keyH1a->draw(538, 527, 42, 85);
        else if (interval == 22) keyH4a->draw(561, 484, 64, 41);
        else if (interval == 23) keyH1a->draw(582, 527, 42, 85);
    }
    else {
        if (midiNoteH == 0) keyH1->draw(193, 527, 42, 85);
        else if (midiNoteH == 1) keyH2->draw(193, 484, 64, 42);
        else if (midiNoteH == 2) keyH1->draw(236, 527, 42, 85);
        else if (midiNoteH == 3) keyH4->draw(258, 484, 64, 41);
        else if (midiNoteH == 4) keyH1->draw(279, 527, 42, 85);
        else if (midiNoteH == 5) keyH1->draw(323, 527, 42, 85);
        else if (midiNoteH == 6) keyH2->draw(323, 484, 64, 42);
        else if (midiNoteH == 7) keyH1->draw(366, 527, 42, 85);
        else if (midiNoteH == 8) keyH3->draw(389, 484, 41, 41);
        else if (midiNoteH == 9) keyH1->draw(409, 527, 42, 85);
        else if (midiNoteH == 10) keyH4->draw(431, 484, 64, 41);
        else if (midiNoteH == 11) keyH1->draw(452, 527, 42, 85);
        
        interval += 7;
        
        //cout<<"interval: "<<interval<<endl;
        
        if (interval == 7) keyH1a->draw(193, 527, 42, 85);
        else if (interval == 8) keyH2a->draw(193, 484, 64, 42);
        else if (interval == 9) keyH1a->draw(236, 527, 42, 85);
        else if (interval == 10) keyH4a->draw(258, 484, 64, 41);
        else if (interval == 11) keyH1a->draw(279, 527, 42, 85);
        
        else if (interval == 12) keyH1a->draw(322, 527, 42, 85);
        else if (interval == 13) keyH2a->draw(323, 484, 64, 42);
        else if (interval == 14) keyH1a->draw(366, 527, 42, 85);
        else if (interval == 15) keyH3a->draw(388, 484, 41, 41);
        else if (interval == 16) keyH1a->draw(409, 527, 42, 85);
        else if (interval == 17) keyH4a->draw(430, 484, 64, 41);
        else if (interval == 18) keyH1a->draw(452, 527, 42, 85);
        
        else if (interval == 19) keyH1a->draw(495, 527, 42, 85);
        else if (interval == 20) keyH2a->draw(496, 484, 64, 42);
        else if (interval == 21) keyH1a->draw(538, 527, 42, 85);
        else if (interval == 22) keyH4a->draw(561, 484, 64, 41);
        else if (interval == 23) keyH1a->draw(582, 527, 42, 85);
    }
    
    
    //*******MELODIC**********
    if (start >= 5) { //In case of I grade >= A
        if (midiNoteM == 5) keyM1->draw(20, 651, 42, 130);
        else if (midiNoteM == 6) keyM4->draw(53, 648, 21, 85);
        else if (midiNoteM == 7) keyM2->draw(64, 651, 41, 130);
        else if (midiNoteM == 8) keyM4->draw(95, 648, 21, 85);
        else if (midiNoteM == 9) keyM2->draw(105, 651, 45, 130);
        else if (midiNoteM == 10) keyM4->draw(139, 648, 21, 85);
        else if (midiNoteM == 11) keyM3->draw(150, 651, 41, 130);
        else if (midiNoteM == 0) keyM1->draw(193, 651 , 42, 130);
        else if (midiNoteM == 1) keyM4->draw(225, 648, 21, 85);
        else if (midiNoteM == 2) keyM2->draw(235, 651, 43, 130);
        else if (midiNoteM == 3) keyM4->draw(268, 648, 21, 85);
        else if (midiNoteM == 4) keyM3->draw(280, 651, 41, 130);
    }
    else {
        if (midiNoteM == 0) keyM1->draw(193, 651, 42, 130);
        else if (midiNoteM == 1) keyM4->draw(225, 648, 21, 85);
        else if (midiNoteM == 2) keyM2->draw(235, 651, 43, 130);
        else if (midiNoteM == 3) keyM4->draw(268, 648, 21, 85);
        else if (midiNoteM == 4) keyM3->draw(280, 651, 41, 130);
        else if (midiNoteM == 5) keyM1->draw(323, 651, 42, 130);
        else if (midiNoteM == 6) keyM4->draw(354, 648, 21, 85);
        else if (midiNoteM == 7) keyM2->draw(364, 651, 45, 130);
        else if (midiNoteM == 8) keyM4->draw(398, 648, 21, 85);
        else if (midiNoteM == 9) keyM2->draw(409, 651, 41, 130);
        else if (midiNoteM == 10) keyM4->draw(441, 648, 21, 85);
        else if (midiNoteM == 11) keyM3->draw(452, 651, 41, 130);
    }
    
}


//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == 'a')
     synth.setParameter("triggerHarmonic", 0);
     if(key == 's')
     synth.setParameter("triggerHarmonic", 1);
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

void ofApp::audioRequested (float * output, int bufferSize, int nChannels){
    synth.fillBufferOfFloats(output, bufferSize, nChannels);
}

void ofApp::setUI() {
    red = 250;     blue = 248;    green = 250;
    backgroundColor = ofColor(red, green, blue);
    ofColor transparent(255,255,255,0);
    
    
    /*****BACKGROUND*****/
    background = new ofImage();
    background->loadImage("bg.png");
    /********************/
    
    /***********PAD2D*********/
    UI = new ofxUICanvas();
    UI->setTheme(0);
    UI->setColorBack(transparent);
    
    UI->setFont("UI/RODUSreg100.otf");
    UI->addLabel("EMOTION STATE");
    UI->addSpacer();
    emotionPAD = UI->add2DPad("valence/arousal", ofPoint(-10,10), ofPoint(-10,10), ofPoint(0,0), 400, 400);

    UI->setPosition(18, 10);
    UI->autoSizeToFitWidgets();
    ofAddListener(UI->newGUIEvent,this,&ofApp::guiEvent);
    /********************/
    
    /**********DATA**********/
    data = new ofxUICanvas();
    data->setTheme(0);
    data->setColorBack(transparent);
    data->setWidth(200);
    
    data->setPosition(425, 10);
    data->setFont("UI/RODUSreg100.otf");
    data->addLabel("MUSIC PARAMETERS");
    data->addSpacer();
    tempoLabel = data->addLabel("");
    scaleLabel = data->addLabel("");
    
    data->addLabel("");
    data->addSpacer();
    data->addLabel("HARMONIC TRACK");
    data->addSpacer();
    harmonicNote1 = data->addLabel("");
    harmonicNote2 = data->addLabel("");
    interval = data->addLabel("");
    numSemitones = data->addLabel("");
    data->addLabel("");
    data->addSpacer();
    data->addLabel("MELODIC TRACK");
    data->addSpacer();
    melodicNote = data->addLabel("");
    
    data->autoSizeToFitWidgets();
    
    
   
    /********************/

    
    /**********DOTS**********/
    keyH1 = new ofImage();
    keyH2 = new ofImage();
    keyH3 = new ofImage();
    keyH4 = new ofImage();

    keyH1->loadImage("UI/keyH1.png");
    keyH2->loadImage("UI/keyH2.png");
    keyH3->loadImage("UI/keyH3.png");
    keyH4->loadImage("UI/keyH4.png");
    
    keyH1a = new ofImage();
    keyH2a = new ofImage();
    keyH3a = new ofImage();
    keyH4a = new ofImage();
    
    keyH1a->loadImage("UI/keyH1a.png");
    keyH2a->loadImage("UI/keyH2a.png");
    keyH3a->loadImage("UI/keyH3a.png");
    keyH4a->loadImage("UI/keyH4a.png");
    
    keyM1 = new ofImage();
    keyM2 = new ofImage();
    keyM3 = new ofImage();
    keyM4 = new ofImage();
    
    keyM1->loadImage("UI/keyM1.png");
    keyM2->loadImage("UI/keyM2.png");
    keyM3->loadImage("UI/keyM3.png");
    keyM4->loadImage("UI/keyM4.png");
    /**********************/
}

void ofApp::guiEvent(ofxUIEventArgs &e) {
    string name = e.getName();
	int kind = e.getKind();
	
    if(name == "THEME"){
		ofxUISlider *slider = (ofxUISlider *) e.getSlider();
        
		UI->setTheme((int)slider->getValue());
		
	}
}

void ofApp::updateUI() {
    //Update 2DPad
    float x = mapPAD(emotionState::Instance()->getValence(), -10.0, 10.0, emotionPAD->getRect()->getX(), emotionPAD->getRect()->getX() + 400.0);
    float y = mapPAD(emotionState::Instance()->getArousal(), -10.0, 10.0, emotionPAD->getRect()->getY() + 400.0, emotionPAD->getRect()->getY());
    
    emotionPAD->input(x, y);
    //cout<<"x:"<<x<<" y:"<<y<<endl;
    
    
    std::ostringstream tempoAux;
    tempoAux << "Tempo: " <<emotionState::Instance()->getTempo();
    string tempo = tempoAux.str();
    
    tempoLabel->setLabel(tempo);
    
    std::ostringstream melodicNoteAux;
    melodicNoteAux << "Note: " <<emotionState::Instance()->getMelodicNote();
    string melodicNoteUI = melodicNoteAux.str();
    
    melodicNote->setLabel(melodicNoteUI);
    
    std::ostringstream scaleAux;
    scaleAux << "Scale: " <<NamesOfScales[emotionState::Instance()->getScale()];
    string scaleUI = scaleAux.str();
    
    scaleLabel->setLabel(scaleUI);
    
    std::ostringstream harmonicNote1Aux;
    harmonicNote1Aux << "Note 1: " <<emotionState::Instance()->getHarmonicNote();
    string harmonicNote1UI = harmonicNote1Aux.str();
    
    harmonicNote1->setLabel(harmonicNote1UI);
    
    std::ostringstream harmonicNote2Aux;
    harmonicNote2Aux << "Note 2: " <<emotionState::Instance()->getHarmonicNote() + emotionState::Instance()->getInterval();
    string harmonicNote2UI = harmonicNote2Aux.str();
    
    harmonicNote2->setLabel(harmonicNote2UI);
    
    std::ostringstream intervalAux;
    intervalAux << "Interval: " <<emotionState::Instance()->getNameInterval();
    string intervalUI = intervalAux.str();
    
    interval->setLabel(intervalUI);
    
    std::ostringstream numSemitonesAux;
    numSemitonesAux << "Semitones: " <<emotionState::Instance()->getInterval();
    string numST = numSemitonesAux.str();
    
    numSemitones->setLabel(numST);
}

void ofApp::setParameter(string parameter, int data) {
    synth.setParameter(parameter, data);
}

float ofApp::mapPAD(float x, float in_min, float in_max, float out_min, int out_max) {
 
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
 

}

void ofApp::exit() {
    midiSaver::saveMidiFile("../../../data/midis/cosica.mid", emotionState::Instance()->getFiguresMelodic(), emotionState::Instance()->getFiguresHarmonic());
}




