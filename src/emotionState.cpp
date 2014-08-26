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
    
    //Default values
    valence = -7;
    arousal = 7;
    minTempo = 80; //60?
    maxTempo = 280; //180?
    scale = 3;
    tempo = 120;
    octave = 3;
    interval = 12;
}

emotionState* emotionState::pinstance = 0;

emotionState* emotionState::Instance() {
    if (pinstance == 0) {
        pinstance = new emotionState;
    }
    return pinstance;
}

void emotionState::addArousal(float a) {
    
    arousal = arousal + a;
    
    if (arousal > 10)
        arousal = 10;
    else if (arousal < -10)
        arousal = -10;
    
}

void emotionState::addValence(float v) {
    
    valence = valence + v;
    
    if (valence > 10)
        valence = 10;
    else if (valence < -10)
        valence = -10;
    
}

void emotionState::updateEmotion() {
    mapTempo();
    mapScale();
    
    
    //cout<<"tempo: "<<tempo<<endl;
    //cout<<"arousal:"<<arousal<<endl;
    //cout<<"intervalo :"<<interval<<endl;
    //cout<<"scale: "<<scale<<endl;
    //cout<<"arousal/valence: "<<arousal<<" / "<<valence<<endl;
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

void emotionState::mapScale() { //Set the scale according to emotion and interval****************************With Arousal/Valence
    scale = 12;
    interval = 12;
    
    
    //******************************SCALES************************************
         if (valence > -10  && valence < -3.5 && arousal > 7   && arousal < 10) scale = 21;//Sibm
    else if ((valence > -10 && valence < -6.5 && arousal > 5   && arousal < 7) || (valence > -8 && valence < -6.5 && arousal > 3.5 && arousal < 5)) scale = 15;//Solm
    else if (valence > -6.5 && valence < -4.5 && arousal > 3.5 && arousal < 7) scale = 16;//LabM
    else if (valence > -3.5 && valence < 0    && arousal > 7.5 && arousal < 10) scale = 2;//RebM
    else if (valence > -4.5 && valence < 0    && arousal > 5.5 && arousal < 7.5) scale = 20;//SibM
    else if (valence > -4.5 && valence < 0    && arousal > 3.5 && arousal < 5.5) scale = 6;//Mibm
    else if (valence > -10  && valence < -8   && arousal > 0   && arousal < 5) scale = 3;//Do#m
    else if (valence > -8   && valence < -5   && arousal > 0   && arousal < 3.5) scale = 17;//Sol#m
    else if ((valence > -5  && valence < -2   && arousal > 0   && arousal < 3.5) || (valence > -2 && valence < 0 && arousal > 2.5 && arousal < 3.5)) scale = 13;//Fa#m
    else if (valence > 0    && valence < 3.5  && arousal > 6.5 && arousal < 10) scale = 4;//ReM
    else if (valence > 0    && valence < 3.5  && arousal > 2.5 && arousal < 6.5) scale = 7;//MibM
    else if (valence > 3.5  && valence < 5.5  && arousal > 2.5 && arousal < 10) scale = 8;//MiM
    else if ((valence > 5.5 && valence < 7.5  && arousal > 0   && arousal < 10) || (valence > 3.5 && valence < 5.5 && arousal > 0 && arousal < 2.5)) scale = 18;//LaM
    else if (valence > 7.5  && valence < 10   && arousal > 0   && arousal < 10) scale = 0;// DoM
    else if ((valence > -10 && valence < 0    && arousal > -4  && arousal < 0) || (valence > -3.5 && valence < 0 && arousal > -6 && arousal < -4) || (valence > -2 && valence < 0 && arousal > 0 && arousal < 2.5)) scale = 1;//Dom
    else if (valence > -10  && valence < -5   && arousal > -10 && arousal < -4 ) scale = 11;//Fam
    else if ((valence > -5  && valence < -3.5 && arousal > -10 && arousal < -4) || (valence > -3.5 && valence < 0 && arousal > -8 && arousal < -6)) scale = 5;//Rem
    else if (valence > 0    && valence < 5    && arousal > -7  && arousal < 0) scale = scale = 12;//SolbM
    else if ((valence > -3.5 && valence < 5   && arousal > -10 && arousal < -8) || (valence > 0 && valence < 5 && arousal > -8 && arousal < -7)) scale = 23;//Sim
    else if (valence > 5    && valence < 7.5  && arousal > -7  && arousal < 0) scale = 10;//FaM
    else if (valence > 7.5  && valence < 10   && arousal > -7  && arousal < 0) scale = 19;//Lam
    else if (valence > 5    && valence < 10   && arousal > -10 && arousal < -7) scale = 14;//SolM
    
    //******************************INTERVALS*********************************
         if (valence >= -10   && valence < -3.5 && arousal > 4.5 && arousal <= 10) interval = 6; //IV augmented - 3 tones
    else if ((valence > -3.5 && valence < 3    && arousal > 8   && arousal <= 10) || (valence > 0 && valence < 3 && arousal > 6.5 && arousal < 9)) interval = 9;//VI
    else if ((valence > -3.5  && valence < 0    && arousal > 4.5 && arousal < 8) || (valence > -10 && valence < -2 && arousal > -4 && arousal < -2) || (valence >= -10 && valence < -3.4 && arousal > -6 && arousal < -4)) interval = 2;//II
    else if (valence > -6    && valence < -1.5 && arousal > 2.5 && arousal < 4.5) interval = 5;//IV justa
    else if ((valence >= -10  && valence < -6   && arousal > 0.5 && arousal < 4.5) || (valence > -6 && valence < -2 && arousal > 0.5 && arousal < 2.5)) interval = 1;//ii
    else if ((valence > -1.5 && valence < 3    && arousal > 2.5 && arousal < 4.5) || (valence > 0 && valence < 3 && arousal > 4.5 && arousal < 6.5)) interval = 10;//vii
    else if (valence > 3     && valence < 6    && arousal > 2.5 && arousal <= 10) interval = 4;//III
    else if (valence > 6     && valence < 10   && arousal > 2.5 && arousal <= 10) interval = 7;//V
    else if (valence >= -10   && valence < -2   && arousal > -2  && arousal < 0.5) interval = 11;//VII
    else if (valence >= -10   && valence < -3.5 && arousal >= -10 && arousal < -6) interval = 3;//iii
    else if ((valence > -2   && valence <= 10   && arousal > -4  && arousal < 2.5) || (valence > -3.5 && valence <= 10 && arousal >= -10 && arousal < -4)) interval = 12;//VIII
    
    //cout<<"Scale: "<<scale<<" interval:"<<interval<<endl;
}

string emotionState::getNameInterval() {
    
    
    if (interval == 1)  return "minor second";
    else if(interval == 2) return "major second";
    else if(interval == 3) return "minor third";
    else if(interval == 4) return "major third";
    else if(interval == 5) return "perfect fourth";
    else if(interval == 6) return "augmented fourth";
    else if(interval == 7) return "perfect fifth";
    else if(interval == 9) return "major sixth";
    else if(interval == 10) return "minor seventh";
    else if(interval == 11) return "major seventh";
    else if(interval == 12) return "octave";
    
    
}


