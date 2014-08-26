//
//  emotionState.h
//  Ambient
//
//  Created by Raúl Ibarra Díez on 19/06/14.
//
//

#ifndef __Ambient__emotionState__
#define __Ambient__emotionState__

#include <iostream>
#include "scales.h"
#include "Figure.h"
#include <vector>



class emotionState {
    public:
        emotionState();
        static emotionState* Instance();
        void addArousal(float a);
        void addValence(float v);
        float getArousal() { return arousal; }
        float getValence() { return valence; }
        int getTempo() { return tempo; }
        void mapTempo();
        int getOctave() { return octave; }
        int getScale() { return scale; }
        int getInterval() { return interval; } //Return number of semitones since tonic
        void mapScale();
        float map(float x, float in_min, float in_max, float out_min, int out_max);
        void updateEmotion();
        void setMelodicNote(int note){ melodicNote = note;}
        int getMelodicNote(){return melodicNote; }
        void setHarmonicNote(int note){ harmonicNote = note; }
        int getHarmonicNote() { return harmonicNote; }
        void addFigureMelodic(Figure f) { if (f.getDuration() > 0) { compositionMelodic.push_back(f); cout<<"NotaM:"<<f.getMidiNumber()<<" duracion:"<<f.getDuration()<<endl; }}
        void addFigureHarmonic(Figure f) {if (f.getDuration() > 0) { compositionHarmonic.push_back(f); cout<<"NotaH-:"<<f.getMidiNumber()<<" duracion:"<<f.getDuration()<<endl; }}

        int numberOfFigures() { return compositionMelodic.size(); }
        string getNameInterval();
        vector<Figure> getFiguresMelodic() { return compositionMelodic; }
        vector<Figure> getFiguresHarmonic() { return compositionHarmonic; }
    
    private:
        static emotionState* pinstance;
        float arousal; //intensity (-10, 10)
        float valence; //mood (-10, 10)
        int maxTempo;
        int minTempo;
        int tempo;
        int octave;
        int scale;
        int interval;
        int melodicNote;
        int harmonicNote;
    
        vector<Figure> compositionMelodic;
        vector<Figure> compositionHarmonic;
    
};

#endif /* defined(__Ambient__emotionState__) */
