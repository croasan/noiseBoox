//
//  midiSaver.cpp
//  Ambient
//
//  Created by Raúl Ibarra Díez on 12/08/14.
//
//

#include "midiSaver.h"
typedef unsigned char uchar;

void midiSaver::saveMidiFile(string fileName, vector<Figure> melodicFigures, vector<Figure> harmonicFigures) {
    MidiFile outputfile;        // create an empty MIDI file with one track
	outputfile.absoluteTime();  // time information stored as absolute time
	// (will be coverted to delta time when written)
	outputfile.addTrack(2);     // Add another two tracks to the MIDI file
	Array<uchar> midievent, midievent2;     // temporary storage for MIDI events
	midievent.setSize(3);       // set the size of the array to 3 bytes
    midievent2.setSize(3);
	int tpq = 60;              // default value in MIDI file is 48
	outputfile.setTicksPerQuarterNote(tpq);
	
	int actiontime = 0;      // temporary storage for MIDI event time
	midievent[2] = 64;
    midievent2[2] = 64;
    
    for(int i = 0; i < melodicFigures.size(); i++){
		
		if(melodicFigures[i].getMidiNumber() != -1){
			
			midievent[0] = 0x90;     // store a note on command (MIDI channel 1)
			midievent[1] = melodicFigures[i].getMidiNumber();
			outputfile.addEvent(1, actiontime, midievent);
			actiontime += melodicFigures[i].getDuration();
			midievent[0] = 0x80;     // store a note off command (MIDI channel 1)
			outputfile.addEvent(1, actiontime, midievent);
			
			cout << i << " - NOTE -  Action time: " << actiontime << endl;
		}
		else {
			actiontime += melodicFigures[i].getDuration();
			cout << i << " - SILENCE -  Action time: " << actiontime << endl;
		}
        
		//actiontime += tpq * mrhythm[i];
        
	}
    
    actiontime = 0;
    
    for(int i = 0; i < harmonicFigures.size(); i++){
		
			midievent[0] = 0x90;     // store a note on command (MIDI channel 1)
			midievent[1] = harmonicFigures[i].getMidiNumber();
			outputfile.addEvent(2, actiontime, midievent);
        
            midievent2[0] = 0x90;     // store a note on command (MIDI channel 1)
            midievent2[1] = harmonicFigures[i].getMidiNumberInterval();
            outputfile.addEvent(2, actiontime, midievent2);
        
			actiontime += harmonicFigures[i].getDuration();
			midievent[0] = 0x80;     // store a note off command (MIDI channel 1)
			outputfile.addEvent(2, actiontime, midievent);
        
            midievent2[0] = 0x80;     // store a note off command (MIDI channel 1)
            outputfile.addEvent(2, actiontime, midievent2);
			
			cout << i << " - NOTE -  Action time: " << actiontime << endl;
        
		//actiontime += tpq * mrhythm[i];
        
	}
    
    
    std::size_t found = fileName.find(".mid");
	if (found == std::string::npos)
		fileName += ".mid";
	
	outputfile.write(fileName.c_str());
}