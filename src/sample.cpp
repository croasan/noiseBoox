//
//  sample.cpp
//  Ambient
//
//  Created by Raúl Ibarra Díez on 11/07/14.
//
//

#include "sample.h"
#include "emotionState.h"
#include <string>
#include <sstream>


sample::sample() {
    antVolume = 1;
    trigger = true;
    
    Iplaying = false;
    IIplaying = false;
    Ivolume = 0;
    IIvolume = 0;
    
}

void sample::load(string path, int firstNote, int lastNote) {
    fNote = firstNote; lNote = lastNote;
    for (int i = firstNote; i <= lastNote; i++) {
        std::ostringstream file;
        file << path << i << ".wav";
        string pathFinal = file.str();
        
        samples[i] = new ofSoundPlayer();
        samples[i]->loadSound(pathFinal);
        samples[i]->setMultiPlay(true);
    }
}

void sample::playNoteMidi(int midiNumber, float volume) {
    samples[midiNumber]->setVolume(volume);
    samples[midiNumber]->play();
}

void sample::playNoteMidiHarmonic(int midiNumber, float volume) {
    
    if (!Iplaying) {
        IIplaying = false;
        Iplaying = true;

        I = *samples[midiNumber];
        Ia = *samples[midiNumber + emotionState::Instance()->getInterval()];

        I.setVolume(volume);
        Ia.setVolume(volume);
        
        I.play();
        Ia.play();
        
        
    }
    else if (!IIplaying) {
        Iplaying = false;
        IIplaying = true;

        II = *samples[midiNumber];
        IIa = *samples[midiNumber + emotionState::Instance()->getInterval()];
        
        II.setVolume(volume);
        IIa.setVolume(volume);
        
        II.play();
        IIa.play();
        
        
        
    }   
    
}


void sample::ADSR() {
    if (!Iplaying && I.getVolume() > 0.05) {
        I.setVolume(I.getVolume() - 0.01);
        Ia.setVolume(Ia.getVolume() - 0.01);
        //cout<<"volumen I bajando "<<I.getVolume()<<endl;
    }
    else if(!Iplaying) {
        I.setVolume(0);
        Ia.setVolume(0);
        I.stop();
        Ia.stop();
        //cout<<"para I"<<endl;

    }
    
    
    if (!IIplaying && II.getVolume() > 0.05) {
        II.setVolume(II.getVolume() - 0.01);
        IIa.setVolume(IIa.getVolume() - 0.01);
        //cout<<"volumen II bajando "<<II.getVolume()<<endl;

    }
    else if(!IIplaying) {
        II.setVolume(0);
        IIa.setVolume(0);
        II.stop();
        IIa.stop();
        //cout<<"para II"<<endl;

    }
}

void sample::setTrigger(bool set) {
    //if (Iplaying) Iplaying = set;
    //if (IIplaying) IIplaying = set;
}

void sample::stopSounds() {
    for (int i = fNote; i < lNote; i++) {
        samples[i]->stop();
    }
}
