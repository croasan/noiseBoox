//
//  synthPlayer.h
//  Ambient
//
//  Created by Raúl Ibarra Díez on 20/06/14.
//
//

#ifndef __Ambient__synthPlayer__
#define __Ambient__synthPlayer__

#include <iostream>
#include "ofxTonic.h"
#include "emotionState.h"
#include "melodicDistribution.h"
#include "harmonicDistribution.h"
#include "sample.h"
#include "Figure.h"
#include <math.h>
using namespace Tonic;

class synthPlayer {
    public:
        synthPlayer();
        void update(int f, int fps);
        float getFrequency(float midiNote) { return  (440 * pow(2.0f, ((midiNote - 69)/12))); }
        void checkSounds();
        void composeNote(int i); // i = 0 (HARMONIC)|| i = 1 (MELODIC)
    private:
        melodicDistribution* DistributionM;
        harmonicDistribution* DistributionH;
        int beatHarmonic;
        int beatMelodic;
        int beatDrums;
        int frame;
        int fps;
        bool harmonicSound;
        bool melodicSound;
        int i;
        sample *melodicSample;
        sample *harmonicSample;
        sample *harmonicSample2;
        ofSoundPlayer *drums;
        bool drumsSound;
    
        
    
};

#endif /* defined(__Ambient__synthPlayer__) */
