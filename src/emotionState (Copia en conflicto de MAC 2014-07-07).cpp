//
//  emotionState.cpp
//  Ambient
//
//  Created by Raúl Ibarra Díez on 19/06/14.
//
//

#include "emotionState.h"
using namespace std;

emotionState::emotionState() {
    arousal = 0;
    valence = 0;
    minTempo = 60;
    maxTempo = 180;
    scaleTonic = 40;
    tempo = 120;
}

emotionState* emotionState::pinstance = 0;

emotionState* emotionState::Instance() {
    if (pinstance == 0) {
        pinstance = new emotionState;
    }
    return pinstance;
}

void emotionState::addArousal(float a) {
    if (arousal > 10)
        arousal = 10;
    else if (arousal < -10)
        arousal = -10;
    else
        arousal = arousal + a;
}

void emotionState::addValence(float v) {
    if (valence > 10)
        valence = 10;
    else if (valence < -10)
        valence = -10;
    else
        valence = valence + v;
}

void emotionState::updateEmotion() {
    mapTempo();
    
    //cout<<"tempo: "<<tempo<<endl;
    //cout<<"arousal:"<<arousal<<endl;
}


/*float mapTempo(float x, float in_min, float in_max, float out_min, int out_max) {
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}*/

void emotionState::mapTempo() {
    float x = arousal + 10; // x (0, 20)
    float tempoFloat = (x - 0) * (maxTempo - minTempo) / (20 - 0) + minTempo;
    int auxTempo = tempoFloat/10;
    tempo = auxTempo * 10;
}