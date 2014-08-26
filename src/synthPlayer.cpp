//
//  synthPlayer.cpp
//  Ambient
//
//  Created by Raúl Ibarra Díez on 20/06/14.
//
//

#include "synthPlayer.h"
#include "ofApp.h"
#include "scales.h"
#include <time.h>

float semitono = 1.0/12.0;
synthPlayer::synthPlayer() {
    DistributionM = new melodicDistribution();
    DistributionH = new harmonicDistribution();
    harmonicSound = false;
    melodicSound = false;
    i = 1;
    melodicSample = new sample();
    melodicSample->load("samples/piano/", 22, 80);
    harmonicSample = new sample();
    harmonicSample2 = new sample();
    harmonicSample->load("samples/LiquidFingers/", 36, 71);
    harmonicSample2->load("samples/SmartStrings/", 36, 80);
    
    /************DRUMS EXAMPLE***************/
    drums = new ofSoundPlayer();
    drums->loadSound("samples/drums/2.wav"); //Example of sample drums
    drums->setLoop(true);
    drums->setVolume(0.1);
    drumsSound = false;
    /****************************************/
    srand (time(NULL));
    
    
}

void synthPlayer::update(int f, int framesPerSecond) {
    frame = f;
    fps = framesPerSecond;
    emotionState::Instance()->updateEmotion();
    checkSounds();
    
    
    if (!harmonicSound) {
        composeNote(0);
        harmonicSound = true;
    }
    if (!melodicSound) {
        composeNote(1);
        melodicSound = true;
    }
    
    //cout<<"arousal:"<<emotionState::Instance()->getArousal()<<endl;
}


void synthPlayer::checkSounds() {
    beatHarmonic--;
    beatMelodic--;
    
    
    if (beatHarmonic <= 0) {
        harmonicSound = false;
        harmonicSample->setTrigger(false);
    }
    if (beatMelodic <= 0) {
        melodicSound = false;
    }
    harmonicSample->ADSR();
    harmonicSample2->ADSR();
    
}

void synthPlayer::composeNote(int i) {
    Figure *f = new Figure();
    
    
    if (i == 0) { //HARMONIC NOTE
        
        beatHarmonic = DistributionH->getTempoFPS(); //Duration in fps
        int note = DistributionH->getNote();
        
        if (note != -1) {
            ofApp::setParameter("triggerHarmonic", 1);
            ofApp::setParameter("midiNumberHarmonic", note);
            ofApp::setParameter("midiNumberHarmonicInterval", note + emotionState::Instance()->getInterval()); //Interval note may be out of range of the scale

            if(emotionState::Instance()->getValence() >= 0) {
                harmonicSample2->stopSounds();
                harmonicSample->playNoteMidiHarmonic(note, 0.6);
            }
            else {
                harmonicSample->stopSounds();
                harmonicSample2->playNoteMidiHarmonic(note, 0.3);
            }
            
        }
        else {  //SILENCE
            ofApp::setParameter("triggerHarmonic", 0);
        }
        
        f->setDuration(beatHarmonic);
        f->setMidiNumber(note);
        f->setMidiNumberInterval(note + emotionState::Instance()->getInterval());
        emotionState::Instance()->addFigureHarmonic(*f);
        
        //cout<<"Note duration: "<<beatHarmonic<<" midiNumber"<<note<<endl;
    }
    else if (i == 1) { //MELODIC NOTE
        cout<<"M"<<endl;
        beatMelodic = DistributionM->getTempoFPS(); //Duration in fps
        int note = DistributionM->getNote();
        if (note != -1) {
            ofApp::setParameter("triggerMelodic", 1);
            ofApp::setParameter("midiNumberMelodic", note);
            melodicSample->playNoteMidi(note, 1.0);
            
        }
        else {  //SILENCE
            ofApp::setParameter("triggerMelodic", 0);
        }
        
        f->setDuration(beatMelodic);
        f->setMidiNumber(note);
        
        emotionState::Instance()->addFigureMelodic(*f);
    }
    
    /****************DRUMS******************/
    if (emotionState::Instance()->getArousal() > 1 && !drumsSound) {
        cout<<"vamos a reproducir percusion"<<endl;
        drums->play();
        drumsSound = true;
    }
    else if (emotionState::Instance()->getArousal() <= 1 && drumsSound) { drums->stop();}
}