//
//  boatRect.cpp
//  ships
//
//  Created by me on 8/28/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "boatRect.h"


void BoatRect::killOrthogonalVelocity()
{
    b2Vec2 localPoint(0.0,0.0);
    b2Vec2 vel = body->GetLinearVelocityFromLocalPoint(localPoint);
    b2Vec2 sidewaysAxis = b2Vec2(body->GetTransform().R.col1);
    sidewaysAxis *= b2Dot(vel,sidewaysAxis);
    body->SetLinearVelocity(sidewaysAxis);
}

ofVec2f BoatRect::getDirection()
{
    b2Vec2 dir = body->GetWorldVector(b2Vec2(-1,0));
    return ofVec2f(dir.x,dir.y);
}


