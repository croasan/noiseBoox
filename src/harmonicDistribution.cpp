//
//  harmonicDistribution.cpp
//  Ambient
//
//  Created by Raúl Ibarra Díez on 07/07/14.
//
//

#include "harmonicDistribution.h"
#include "emotionState.h"
using namespace std;

harmonicDistribution::harmonicDistribution() {
    antRandom = -1;
}

int harmonicDistribution::getNote() {
    int pitch;
    int tone;
    
    int silence = rand() % 10 +1;
    
    if (silence > 0) { //*****************NOTE
        
        
        int random = rand()% 3 + 1;
        
        while (random == antRandom) {
            random = rand()% 3 + 1;
        }
        
        if (random == 1) tone = 0;
        else if (random == 2) tone = 2;
        else tone = 4;
        
        antRandom =random;
        
        
        
            
        int octave = emotionState::Instance()->getOctave();
       
        if (tone < octaveChange[emotionState::Instance()->getScale()]) octave--;
        
        pitch = 10*(octave + 2) + ListOfScales[emotionState::Instance()->getScale()][tone] + (2*octave + 4);
        
        emotionState::Instance()->setHarmonicNote(pitch - 12);
        
        cout<<"eehh que va esto:"<<pitch-12<<" - "<<pitch - 12 + emotionState::Instance()->getInterval()<<endl;
        
        return pitch -12;
    }
    else { //*****************SILENCE
        return -1;
    }
}

int harmonicDistribution::getTempoFPS() {
    int tempo = emotionState::Instance()->getTempo();
    int fps = 60;
    
    float framesPerNote = 10* fps / tempo;
    
    int fpsDuration = ((rand() % 4 + 1) * framesPerNote) * 16;
    
    fpsDuration = 120;
    return fpsDuration;
}
