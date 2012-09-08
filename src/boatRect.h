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

class BoatRect : public ofxBox2dRect
{
public:
    void killOrthogonalVelocity();
};

#endif
