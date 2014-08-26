//
//  melodicDistribution.cpp
//  Ambient
//
//  Created by Raúl Ibarra Díez on 04/07/14.
//
//

#include "melodicDistribution.h"
#include "emotionState.h"
#include "scales.h"

melodicDistribution::melodicDistribution() {
    antNote = -1; //Firt time never happens
    silenceProbability = 1;
}

int melodicDistribution::getNote() {
    int pitch;
    int tone;
    
    int silence = rand() % 100 + 1;  //Random between 1 - 100
    silenceProbability++; //Augment of silence probability
    
    if (silence > silenceProbability) { //*****************NOTE
        int random = rand() % 70; // random between 0 - 6

        if (random <= 50) { // 6/7 probability  ->  I - III - IV - V
            if (random < 15) tone = 0; // I
            else if (random < 30) tone  = 2; // III
            else if (random < 45) tone  = 3; // IV
            else tone = 4; // V
        }
        else { // 1/7 probability  ->  II - VI - VII
            if (random < 64) tone = 1; // II
            else if (random < 67) tone = 5; // VI
            else tone = 6; // VII
        }
        
        //printScale();

        int octave = emotionState::Instance()->getOctave();
        
        
        if (tone < octaveChange[emotionState::Instance()->getScale()]) octave--;
        
     
        pitch = 10*(octave + 2) + ListOfScales[emotionState::Instance()->getScale()][tone] + (2*octave + 4) ;
        
        emotionState::Instance()->setMelodicNote(pitch);
        return pitch;
    }
    else { //*****************SILENCE
        silenceProbability = 1;
        return -1;
    }
}

int melodicDistribution::getTempoFPS() {
    int tempo = emotionState::Instance()->getTempo();
    int fps = 60;
    
    float framesPerNote = 10* fps / tempo;
    
    int random = (rand() % 4 + 1);
    
    int fpsDuration = (random * framesPerNote) * 4;
    
    
    
    return fpsDuration;
}

void melodicDistribution::printScale() {
    cout<<"estamos en la escala:"<<emotionState::Instance()->getScale()<<" y contiene: [";
    for (int i = 0 ; i < 7; i++) {
        cout<<ListOfScales[emotionState::Instance()->getScale()][i]<<",";
    }
    cout<<"]"<<endl;
    
    for (int i = 0 ; i < 7; i++) {
        int octave = emotionState::Instance()->getOctave();
        
        if (i < octaveChange[emotionState::Instance()->getScale()]) octave--;
        
        int pitch = 10*(octave + 2) + ListOfScales[emotionState::Instance()->getScale()][i] + (2*octave + 4) ;
        cout<<pitch<<", ";
    }
    cout<<endl;
}