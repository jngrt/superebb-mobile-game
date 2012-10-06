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
    
    //chain.front().addImpulseForce(ofVec2f(1.0,1.0), 1.0);
    chain.front().addImpulseForce(ofVec2f(0.1,0.1), 1.0);
    desiredAngle = 90 * DEG_TO_RAD;
    
    tugImg.loadImage("tug_30.png");
    boatImg.loadImage("cargoboat1_23.png");
    tugImg.setAnchorPercent(0.5, 0.5);
    boatImg.setAnchorPercent(0.5, 0.5);
    
    length = 0;
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
    }else if( vel.Length() < 8.0){
        b2Vec2 force = linVelVec;
        force *= 5.0;
        chain.front().body->ApplyForce(force, chain.front().body->GetWorldCenter());
        //chain.front().addForce(ofVec2f(force.x,force.y), 1.0);
    }
    
    
    for(int i=0;i<chain.size();i++)
       chain[i].killOrthogonalVelocity();
    
    //cout<<"dir:"<<chain.front().getDirection().x<<" x "<<chain.front().getDirection().y<<endl;
}

void BoatChain::updateAngle(float inputX, float inputY)
{
    lastPoint.set(inputX,inputY);
    ofVec2f toTarget = lastPoint - chain.front().getPosition();
    desiredAngle = atan2f(-toTarget.x,toTarget.y);

}

bool BoatChain::checkTide(int x)
{
    if(chain.begin()->getPosition().x>x)
    {
        return false;
    }
    
    for(int i=1;i<chain.size();i++)
    {
        if(chain[i].getPosition().x > x)
        {
            collapseBoats(i-1);
            calculateLength();
            break;
        }
    }
    return true;
}
int BoatChain::getLength()
{
    return length;
}
void BoatChain::calculateLength()
{
    length = 0;
    for(int i=1;i<chain.size();i++)
        length += pow(5.0, chain[i].multiplier);
}
void BoatChain::draw()
{
    ofColor colors[] = {ofColor(200,200,200),ofColor(80,80,80),ofColor(50,50,255),ofColor(50,255,255)};
    ofEnableAlphaBlending();
    for(int i=0;i<chain.size();i++)
    {
        if(chain[i].multiplier > -1)
            ofSetColor(colors[chain[i].multiplier]);
        
        //chain[i].draw();
        chain[i].drawGraphics();
    }
    ofDisableAlphaBlending();
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
    front.multiplier = -1;
    front.setPhysics(10.0, 0.0, 0.0);
    front.setDamping(0.2);
    front.setRotationFriction(0.3);
	//front.setup(box2d.getWorld(), 4233, 2348, 10, 5);
    front.setup(box2d.getWorld(), 5821, 2155, 10, 5);
    front.setImageData(&tugImg,10,5);
    chain.push_back(front);
}
void BoatChain::addShips(const vector<ShipData> &shipsToAdd)
{
    //cout<<"addShips:"<<shipsToAdd.size()<<"----------"<<endl;
    //cout<<"before:";
    //for(int i=0;i<chain.size();i++)
    //    cout<<chain[i].multiplier<<":";
    //cout<<endl;
    
    for(int i=0;i<shipsToAdd.size();i++)
    {
        addShip(shipsToAdd[i]);
        checkBoats();
    }
    calculateLength();
    //cout<<"after:";
    //for(int i=0;i<chain.size();i++)
    //    cout<<chain[i].multiplier<<":";
    //cout<<endl<<"_________________"<<endl;
    
}
void BoatChain::addShip(ShipData data)
{
    //ofVec2f dir = chain.back().getDirection();
    ofVec2f prevPos = chain.back().getPosition();
    //ofVec2f newPos = prevPos - dir * ((chain.size()==1)?26:29);
    ofVec2f newPos = prevPos;
    
    BoatRect boat;
    boat.multiplier = 0;
    boat.data = data;
    boat.setPhysics(0.01, 0.0, 0.0);
    boat.setDamping(0.1);
    boat.setRotationFriction(0.9);
    boat.setup(box2d.getWorld(),newPos.x,newPos.y,11.5,4.5);
	boat.body->SetTransform(boat.body->GetPosition(), chain.back().body->GetAngle());
    boat.body->SetAngularVelocity(0.0);
    boat.setImageData(&boatImg,15,4.5);
    //boat.setup(box2d.getWorld(), chain.back().getPosition().x+22, chain.back().getPosition().y, 10, 4);
    
    //
    
    /*
    //SIMPLE JOINTS
    ofxBox2dJoint joint;
    joint.setup(box2d.getWorld(),chain.back().body,boat.body,
                chain.back().body->GetWorldPoint(b2Vec2(0.3,0)),
                boat.body->GetWorldPoint(b2Vec2(-0.3,0)), 4.0, 1.0, true);
                //);//,b2Vec2(0.2,0),b2Vec2(-0.2,0));
    joint.setLength(3.0);
    //joint.setDamping(1.0);
    //joint.setFrequency(15.0);
    */
    
    /*
    //REVOLUTE JOINTS
    b2Vec2 jointPos = chain.back().body->GetPosition();
    jointPos += chain.back().body->GetWorldVector(b2Vec2((chain.size()==1)?0.2:0.23,0));
    
    b2RevoluteJointDef rjd;
    //rjd.Initialize(chain.back().body,boat.body,chain.back().body->GetPosition()+b2Vec2(0.2,0));
    //rjd.Initialize(chain.back().body,boat.body,jointPos);
    //rjd.collideConnected = false;
    //rjd.lowerAngle = -0.6f*b2_pi;
    //rjd.upperAngle = 0.6f*b2_pi;
    //rjd.enableLimit = true;
    
    
    rjd.localAnchorA.Set((chain.size()==1)?0.4:0.4, 0);
    rjd.localAnchorB.Set(-0.4, 0);
    rjd.bodyA = chain.back().body;
    rjd.bodyB = boat.body;
    
    boat.body->SetAngularDamping(1.0);
    
    boat.joint = (b2RevoluteJoint *)box2d.getWorld()->CreateJoint(&rjd);
     */
    
    
    
    //REVOLUTE JOINTS WITH MOTOR
    //b2Vec2 jointPos = chain.back().body->GetPosition();
    //jointPos += chain.back().body->GetWorldVector(b2Vec2((chain.size()==1)?0.2:0.23,0));
    
    b2RevoluteJointDef rjd;
    //rjd.Initialize(chain.back().body,boat.body,chain.back().body->GetPosition()+b2Vec2(0.2,0));
    //rjd.Initialize(chain.back().body,boat.body,jointPos);
    rjd.collideConnected = false;
    rjd.lowerAngle = -0.6f*b2_pi;
    rjd.upperAngle = 0.6f*b2_pi;
    rjd.enableLimit = true;
    
    
    rjd.localAnchorA.Set((chain.size()==1)?0.36:0.41, 0);
    rjd.localAnchorB.Set(-0.41, 0);
    rjd.bodyA = chain.back().body;
    rjd.bodyB = boat.body;
    
    //rjd.maxMotorTorque = 0.1f;
    
    //rjd.motorSpeed = 0.0f;
    
    //rjd.enableMotor = true;
    //boat.body->SetAngularDamping(1.0);
    
    boat.joint = (b2RevoluteJoint *)box2d.getWorld()->CreateJoint(&rjd);
    
    chain.push_back(boat);
                
}
void BoatChain::checkBoats()
{
    
    int stackSize = 5;
    int curLevelCount = 0;
    int lastMultiplier = -1;
    
    for(int i = chain.size()-1;i>0;i--)
    {
        
        if(chain[i].multiplier == lastMultiplier)
        {
            if(++curLevelCount >= stackSize )
            {
                chain[i].multiplier++;
                collapseBoats(i);
                checkBoats();
                return;
            }
        }
        else if( chain[i].multiplier != -1)
        {
            curLevelCount = 1;
            lastMultiplier = chain[i].multiplier;
        }
    }
}
void BoatChain::collapseBoats(int index)
{
    for(int i=chain.size()-1;i>index;i--)
    {
        box2d.world->DestroyBody(chain[i].body);
        chain.erase(chain.begin()+i);
    }  

}
