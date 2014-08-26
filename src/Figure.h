//
//  Figure.h
//  Ambient
//
//  Created by Raúl Ibarra Díez on 11/08/14.
//
//

#ifndef __Ambient__Figure__
#define __Ambient__Figure__

#include <iostream>

class Figure {
public:
    Figure();
    void setType(int t) { type = t; }
    void setDuration(int d) { duration = d; }
    int getType() {return type; }
    int getDuration() {return duration; }
    void setMidiNumber(int m) {midiNumber = m; }
    int getMidiNumber() {return midiNumber; }
    void setMidiNumberInterval (int i){ midiNumberInterval = i; }
    int getMidiNumberInterval() {return midiNumberInterval; }
    
    
private:
    int type; // 1 - 4
    int duration;
    int midiNumber;
    int midiNumberInterval;
    
};

#endif /* defined(__Ambient__Figure__) */
