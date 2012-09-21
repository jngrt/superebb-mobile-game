//
//  boatChain.h
//  ships2
//
//  Created by me on 9/7/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef ships2_boatChain_h
#define ships2_boatChain_h

#include "ofMain.h"
#include "ofxBox2d.h"
#include "boatRect.h"


class BoatChain
{
public:
    void setup(ofxBox2d& box2d);
    //void setup();
    void draw();
    void drawDebug();
    void update();
    void updateAngle(float touchX,float touchY);

    void addShips(const vector<ShipData> &shipsToAdd);
    ofVec2f getFrontPos();
    
    
private:
    void makeFront();
    void addShip(ShipData data);
    void collapseBoats(int index);
    void checkBoats();
    //vector<
    vector<BoatRect> chain;
    float desiredAngle;
    ofVec2f lastPoint;
    
    ofxBox2d box2d;
};


#endif
