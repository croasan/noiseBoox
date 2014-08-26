#include "ofApp.h"
#include "emotionState.h"

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


     //PinkNoise noise = PinkNoise();
    
     //*************PARAMETERS*******************
    
    //HARMONIC
     ControlParameter triggerH = synth.addParameter("triggerHarmonic", 1);
     ControlGenerator midiNoteHarmonic = synth.addParameter("midiNumberHarmonic");
     noteFreqH = ControlMidiToFreq().input(midiNoteHarmonic);
    

    //MELODIC
    ControlParameter triggerM = synth.addParameter("triggerMelodic", 0);
    ControlGenerator midiNoteMelodic = synth.addParameter("midiNumberMelodic");
    noteFreqM = ControlMidiToFreq().input(midiNoteMelodic);
    
     //***************WAVES**********************
     Generator harmonicTone = SawtoothWave().freq(noteFreqH);
     Generator melodicTone = SineWave().freq(noteFreqM);
    
    
    
     //****************FILTERS*******************
    
    //HARMONIC
     ADSR envH = ADSR(0.4f, 0.2f, 0.5f, 0.4f).trigger(triggerH);
    harmonicTone = HPF12().input(harmonicTone).Q(20).cutoff((noteFreqH * 2) + SineWave().freq(3) * 0.5 * noteFreqH);
    
    //MELODIC
     ADSR envM = ADSR(0.4f, 0.2f, 0.5f, 0.4f).trigger(triggerM);
     
    
     synth.setParameter("midiNumberHarmonic",60);
     synth.setParameter("midiNumberMelodic", 64);
     synth.setOutputGen(harmonicTone*envH + melodicTone*envM);
    
}

//--------------------------------------------------------------
void ofApp::update(){
    updateUI();
    if (frame > 60) frame = 0;
    
    
    UDPConnection->getMessage();
    player->update(frame, fps);
    frame++;
}

//--------------------------------------------------------------
void ofApp::draw(){

	
	
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
    UI = new ofxUISuperCanvas("EMOTION STATE");
    UI->addSpacer();
    
    //UI->addLabel("2D PAD");
    emotionPAD = UI->add2DPad("arousal/valence", ofPoint(-10,10), ofPoint(-10,10), ofPoint(0,0), 500, 500);
    
    UI->setPosition(0, 0);
    UI->autoSizeToFitWidgets();
    ofAddListener(UI->newGUIEvent,this,&ofApp::guiEvent);
}

void ofApp::guiEvent(ofxUIEventArgs &e) {
    string name = e.getName();
	int kind = e.getKind();
	cout << "got event from: " << name << endl;
}

void ofApp::updateUI() {
    //Update 2DPad
    emotionPAD->input(emotionState::Instance()->getValence() * 40 + 250, -emotionState::Instance()->getArousal() * 40 + 250);
}

void ofApp::setParameter(string parameter, int data) {
    synth.setParameter(parameter, data);
}





