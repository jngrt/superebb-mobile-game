//
//  tideLine.cpp
//  ships2
//
//  Created by me on 9/30/12.
//
//

#include "tideLine.h"

void TideLine::setup()
{
    startSpeed = 20.0;
    endSpeed = 45.0;
    speed = 20.0;
    lastUpdateMs = ofGetElapsedTimeMillis();
    x = 2048*3 - 200;
    accelSec = 2.0;
    firstTime = true;
}
void TideLine::reset()
{
    speed = startSpeed;
    x = 2048*3 - 200;
    lastUpdateMs = ofGetElapsedTimeMillis();
}

void TideLine::update()
{
    if(firstTime){
        firstTime = false;
        lastUpdateMs = ofGetElapsedTimeMillis();
    }
    int deltaTime = ofGetElapsedTimeMillis() - lastUpdateMs;
    if( speed < endSpeed)
        speed += deltaTime * (accelSec/1000.0);
    x -= deltaTime * (speed/1000.0);
    if( x < 200 ) x = 200;
    lastUpdateMs = ofGetElapsedTimeMillis();
}

void TideLine::draw(ofPoint camera)
{
    ofSetHexColor(0x5bc0dc);
    ofRect(-camera.x,-camera.y,x,-camera.y+320);
    ofSetHexColor(0xdad5bf);
    ofRect(x,-camera.y,-camera.x+480,-camera.y+320);
    
    /*
    ofSetLineWidth(4);
    ofSetHexColor(0xff0000);
    ofLine(x, -1*camera.y, x, -1*camera.y + 320);
    ofSetLineWidth(1);
     */
}
void TideLine::drawDebug(ofPoint camera)
{
    ofSetHexColor(0xff0000);
    ofLine(x, 0, x, 2048);
}