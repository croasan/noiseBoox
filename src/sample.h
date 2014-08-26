//
//  sample.h
//  Ambient
//
//  Created by Raúl Ibarra Díez on 11/07/14.
//
//

#ifndef __Ambient__sample__
#define __Ambient__sample__

#include <iostream>
#include "ofMain.h"
#include "ofxTonic.h"
using namespace Tonic;

class sample {
public:
    sample();
    void load(string path, int firstNote, int lastNote);
    void playNoteMidi(int midiNumber, float volume);
    void playNoteMidiHarmonic(int midiNumber, float volume);
    void ADSR();
    void setTrigger(bool set);
    void stopSounds();
private:
    ofSoundPlayer *samples[88];
    float antVolume;
    bool trigger;
    int currentTone;
    int fNote;
    int lNote;
    
    
    //ADSR STUFF
    ofSoundPlayer I; //Harmonic note
    ofSoundPlayer II; //Another harmonic note
    ofSoundPlayer Ia; //Harmonic note interval
    ofSoundPlayer IIa; //Another harmonic note interval
    
    bool Iplaying;
    bool IIplaying;
    float Ivolume;
    float IIvolume;

};

#endif /* defined(__Ambient__sample__) */
