//
//  boatRect.h
//  ships
//
//  Created by me on 8/28/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef ships_boatRect_h
#define ships_boatRect_h

#include "ofxBox2dRect.h"
#include "b2Math.h"
#include "b2Body.h"
#include "shipData.h"

class BoatRect : public ofxBox2dRect
{
public:
    int multiplier;
    ShipData data;
    b2RevoluteJoint * joint;
    void killOrthogonalVelocity();
    ofVec2f getDirection();
};

#endif
