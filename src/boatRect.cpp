//
//  boatRect.cpp
//  ships
//
//  Created by me on 8/28/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "boatRect.h"


/*
b2Vec2 BoatRect::getLateralVelocity() {
    b2Vec2 currentRightNormal = body->GetWorldVector( b2Vec2(1,0) );
    return b2Dot( currentRightNormal, body->GetLinearVelocity() ) * currentRightNormal;
}

void BoatRect::updateFriction(){
    //b2Vec2 impulse = body->GetMass() * -getLateralVelocity();
    //body->ApplyLinearImpulse( impulse, body->GetWorldCenter() );
}
*/
void BoatRect::killOrthogonalVelocity()
{
    //b2Body& b = body;
    b2Vec2 localPoint(0.0,0.0);
    b2Vec2 vel = body->GetLinearVelocityFromLocalPoint(localPoint);
    b2Vec2 sidewaysAxis = b2Vec2(body->GetTransform().R.col2);
    sidewaysAxis *= b2Dot(vel,sidewaysAxis);
    //(vel.x * sidewaysAxis.x +
                    // vel.y * sidewaysAxis.y);
    body->SetLinearVelocity(sidewaysAxis);
}

/*ofVec2f BoatRect::getDragPoint()
{
    //b2Vec2 localPoint(0.0,-0.3);
    b2Vec2 pnt = body->GetWorldPoint(b2Vec2(0.0,-0.3));
    return ofVec2f(pnt.x,pnt.y);
}

void BoatRect::setupFriction()
{
    //b2FrictionJointDef jd;
    //jd.
}*/