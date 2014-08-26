//
//  UDPReceiver.cpp
//  AmbientGenerator
//
//  Created by Raúl Ibarra Díez on 18/06/14.
//
//

#include "UDPReceiver.h"
#include "emotionState.h"
using namespace std;

UDPReceiver::UDPReceiver() {
    //create the socket and bind to port 8051
	udpConnection.Create();
	udpConnection.Bind(8051);
	udpConnection.SetNonBlocking(true);
}

bool UDPReceiver::getMessage() {
    char udpMessage[100000];
	udpConnection.Receive(udpMessage,100000);
	string message=udpMessage;
    
    
	if(message!=""){
        if (message.substr(0, 1) == "A") {
            float arousal = atof(message.substr(2,message.length()).c_str());
            emotionState::Instance()->addArousal(arousal);
        }
        else {
            float valence = atof(message.substr(2,message.length()).c_str());
            emotionState::Instance()->addValence(valence);
        }
        
        return true;
    }
    else {
        return false;
    }
}