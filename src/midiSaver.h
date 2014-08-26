//
//  midiSaver.h
//  Ambient
//
//  Created by Raúl Ibarra Díez on 12/08/14.
//
//

#ifndef __Ambient__midiSaver__
#define __Ambient__midiSaver__

#include <iostream>
#include <string>
#include <vector>
#include "Figure.h"
#include "MIDIFile.h"
using namespace std;

class midiSaver {
    public:
        static void saveMidiFile(string fileName, vector<Figure> melodicFigures, vector<Figure> harmonicFigures);
    
};

#endif /* defined(__Ambient__midiSaver__) */
