//
//  boatChain.cpp
//  ships2
//
//  Created by me on 9/7/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>

#include "boatChain.h"

void BoatChain::setup(ofxBox2d& box2d)
//void BoatChain::setup()
{
    this->box2d = box2d;
    
    //makeFront(box2d);
    makeFront();
    
    chain.front().addImpulseForce(ofVec2f(1.0,1.0), 1.0);
    desiredAngle = 90 * DEG_TO_RAD;
    for(int i=0;i<10;i++)
        addBoat();
}
void BoatChain::update()
{
    /*
    *First orient the 
    //http://www.iforce2d.net/b2dtut/rotate-to-angle
    */
    float bodyAngle = chain.front().body->GetAngle()+ 90.0*DEG_TO_RAD;
    
    float nextAngle = bodyAngle + chain.front().body->GetAngularVelocity() / 3.0;
    float totalRotation = desiredAngle - nextAngle;//use angle in next time step
    while ( totalRotation < -180 * DEG_TO_RAD ) totalRotation += 360 * DEG_TO_RAD;
    while ( totalRotation >  180 * DEG_TO_RAD ) totalRotation -= 360 * DEG_TO_RAD;    
    if(fabs(totalRotation)>2.0*DEG_TO_RAD)
        chain.front().body->ApplyTorque( totalRotation < 0 ? -2 : 2 );
    
    
    
    //http://www.cocos2d-iphone.org/forum/topic/16767
    b2Vec2 vel = chain.front().body->GetLinearVelocity();
    b2Vec2 linVelVec = vel;
    linVelVec.Normalize();
    //if you use col1/col2, don't forget to also change killOrthogonalVel function
    b2Vec2 facingVec = chain.front().body->GetTransform().R.col1;
    facingVec.Normalize();
    float dot = b2Dot(linVelVec, facingVec);
    if(dot>0.0)
    {
        b2Vec2 force = linVelVec;
        force *= -10.0;
        chain.front().body->ApplyForce(force, chain.front().body->GetWorldCenter());
    }else if( vel.Length() < 1.0){
        b2Vec2 force = linVelVec;
        force *= 5.0;
        chain.front().body->ApplyForce(force, chain.front().body->GetWorldCenter());
        //chain.front().addForce(ofVec2f(force.x,force.y), 1.0);
    }
    
    
    for(int i=0;i<chain.size();i++)
       chain[i].killOrthogonalVelocity();
}

void BoatChain::updateAngle(float inputX, float inputY)
{
    lastPoint.set(inputX,inputY);
    ofVec2f toTarget = lastPoint - chain.front().getPosition();
    desiredAngle = atan2f(-toTarget.x,toTarget.y);

}
void BoatChain::draw()
{
    for(int i=0;i<chain.size();i++)
        chain[i].draw();
    
    ofSetHexColor(0x0000ff);
    ofCircle(lastPoint.x, lastPoint.y, 2);
}
void BoatChain::drawDebug()
{
    ofCircle(chain.front().getPosition(),20);
}
ofVec2f BoatChain::getFrontPos()
{
    return chain.front().getPosition();
}

void BoatChain::makeFront()
{
    BoatRect front;
    front.setPhysics(10.0, 0.1, 0.1);
    front.setDamping(0.2);
    front.setRotationFriction(0.3);
	front.setup(box2d.getWorld(), 1024, 800, 10, 4);
    chain.push_back(front);
}

void BoatChain::addBoat()
{
    BoatRect boat;
    boat.setPhysics(0.001, 0.0, 0.8);
    boat.setDamping(0.95);
    boat.setRotationFriction(0.95);
	boat.setup(box2d.getWorld(), chain.back().getPosition().x+22, chain.back().getPosition().y, 10, 4);
    
    b2RevoluteJointDef rjd;
    rjd.Initialize(chain.back().body,boat.body,chain.back().body->GetPosition()+b2Vec2(0.2,0));
    rjd.collideConnected = false;
    rjd.lowerAngle = -0.25f*b2_pi;
    rjd.upperAngle = 0.25f*b2_pi;
    rjd.enableLimit = true;
    box2d.getWorld()->CreateJoint(&rjd);
    
    chain.push_back(boat);
                   
}

