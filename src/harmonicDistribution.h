//
//  harmonicDistribution.h
//  Ambient
//
//  Created by Raúl Ibarra Díez on 07/07/14.
//
//

#ifndef __Ambient__harmonicDistribution__
#define __Ambient__harmonicDistribution__

#include <iostream>


class harmonicDistribution {
    public:
        harmonicDistribution();
        int getNote();
        int getTempoFPS();
    private:
        int antRandom;
};

#endif /* defined(__Ambient__harmonicDistribution__) */
