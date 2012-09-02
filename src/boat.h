//
//  boat.h
//  ships
//
//  Created by me on 9/1/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef ships_boat_h
#define ships_boat_h



#include "ofMain.h"
#include "ofxBox2dRect.h"
#include "ofxBox2dCircle.h"
#include "b2Math.h"
#include "ofxBox2d.h"

class Boat
{
  
public:
    void setup(ofxBox2d box2d, float x, float y, float width, float length);
    
protected:
    float           x;
    float           y;
    float           size;
    ofxBox2dRect    middle;
    ofxBox2dCircle  front;
    ofxBox2dCircle  back;
};



#endif
