//
//  melodicDistribution.h
//  Ambient
//
//  Created by Raúl Ibarra Díez on 04/07/14.
//
//

#ifndef __Ambient__melodicDistribution__
#define __Ambient__melodicDistribution__

#include <iostream>

class melodicDistribution {
    public:
        melodicDistribution();
        int getNote();
        int getTempoFPS();
        void printScale();
    private:
        int antNote;
        int silenceProbability;
    
};

#endif /* defined(__Ambient__melodicDistribution__) */
