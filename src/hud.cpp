//
//  hud.cpp
//  ships2
//
//  Created by me on 10/6/12.
//
//

#include "hud.h"

void Hud::setup(int levelStart,int levelEnd)
{
    scoreFont.loadFont("NothingYouCouldDo.ttf", 24);
    this->levelStart = levelStart;
    this->levelEnd  = levelEnd;
    levelLength = levelStart-levelEnd;
    
}

void Hud::draw(int score, int boat, int tide)
{
    ofSetHexColor(0xeeeeee);
    ofRect(0,290,480,30);
    
    ofSetHexColor(0xdddddd);
    ofRect(0,290,80,30);
    ofSetHexColor(0x555555);
    
    scoreFont.drawStringCenteredHorizontally(ofToString(score), 40, 315);
    
    
    int barLength = 200;
    ofSetHexColor(0x5bc0dc);
    ofRect(100,300,barLength,10);
    
    ofSetHexColor(0xdad5bf);
    
    float boatPerc = (boat-levelEnd) / levelLength;
    boatPerc = fmax(0.0,boatPerc);
    float tidePerc = (tide-levelEnd) / levelLength;
    tidePerc = fmax(0.0,tidePerc);
    float tideStart = tidePerc * barLength;
    
    ofRect(100+tideStart, 300, barLength-tideStart, 10);
    
    ofSetHexColor(0x444444);
    ofCircle(boatPerc*barLength + 100, 305, 5);
}

