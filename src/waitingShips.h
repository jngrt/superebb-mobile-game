//
//  waitingShips.h
//  ships2
//
//  Created by me on 9/9/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef ships2_waitingShips_h
#define ships2_waitingShips_h

#include "ofMain.h"
//#include "ofxJansson.h"
#include "ofxJSONElement.h"
#include "shipData.h"
#include "anim.h"

class WaitingShips
{
public:
    void setup();
    void reset();
    void update();
    void draw(bool debug=false);
    void drawDebug();
    void drawAnim(ofPoint camera);
    void getShipsNearby(ofVec2f point, vector<ShipData> &shipsNear);    
    vector<ShipData> ships;    
    
private:
    void parseData();
    ofVec2f realStartCoord;
    ofVec2f gameStartCoord;
    ofVec2f realEndCoord;
    ofVec2f gameEndCoord;
    ofVec2f realArea;
    ofVec2f gameArea;
    
    ofImage img;

    vector<Anim> anims;
    
    ofxCenteredTrueTypeFont animFont;
    
};


#endif
