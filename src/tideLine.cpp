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
    speed = 0.5;
    lastUpdateMs = ofGetElapsedTimeMillis();
    x = 2048*3;
}

void TideLine::update()
{
    int deltaTime = ofGetElapsedTimeMillis() - lastUpdateMs;
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