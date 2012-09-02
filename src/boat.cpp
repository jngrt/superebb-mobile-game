//
//  boat.cpp
//  ships
//
//  Created by me on 9/1/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>

#include "boat.h"

void Boat::setup(ofxBox2d box2d, float x, float y, float width, float length)
{
    
    middle.setPhysics(10.0, 0.1, 0.1);
    middle.setDamping(0.95);
    middle.setRotationFriction(0.95);
	middle.setup(box2d.getWorld(), x+width, y, length, width);
    
    front.setup(box2d.getWorld(),x,y,width);
    back.setup(box2d.getWorld(),x+length,y,width);
    
}