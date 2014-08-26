//
//  UDPReceiver.h
//  AmbientGenerator
//
//  Created by Raúl Ibarra Díez on 18/06/14.
//
//

#include "ofMain.h"
#include "ofxNetwork.h"


#ifndef __AmbientGenerator__UDPReceiver__
#define __AmbientGenerator__UDPReceiver__

#include <iostream>


class UDPReceiver {
    
    public:
        UDPReceiver();
        bool getMessage();
    private:
        ofxUDPManager udpConnection;
    
    
};

#endif /* defined(__AmbientGenerator__UDPReceiver__) */
