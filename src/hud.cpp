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
    scoreFont.loadFont("GloriaHallelujah.ttf", 20);
    this->levelStart = levelStart;
    this->levelEnd  = levelEnd;
    levelLength = levelStart-levelEnd;
    slider.loadImage("tug_slider.png");
    slider.setAnchorPercent(0.5, 0.5);
    
}

void Hud::draw(int score, int boat, int tide)
{
    ofSetHexColor(0xeeeeee);
    //ofRect(0,290,480,30);
    ofRect(0,0,480,30);
    
    ofSetHexColor(0xdddddd);
    ofRect(0,0,80,30);
    ofSetHexColor(0x555555);
    
    //scoreFont.drawStringCenteredHorizontally(ofToString(score), 40, 315);
    scoreFont.drawStringCenteredHorizontally(ofToString(score), 40, 25);
    
    int barLength = 200;
    ofSetHexColor(0x5bc0dc);
    //ofRect(100,300,barLength,10);
    ofRect(100,10,barLength,10);
    
    //ofSetHexColor(0xdad5bf);
    ofSetHexColor(0xc0b649);
    
    
    float boatPerc = (boat-levelEnd) / levelLength;
    boatPerc = fmax(0.0,boatPerc);
    float tidePerc = (tide-levelEnd) / levelLength;
    tidePerc = fmax(0.0,tidePerc);
    float tideStart = tidePerc * barLength;
    
    //ofRect(100+tideStart, 300, barLength-tideStart, 10);
    ofRect(100+tideStart, 10, barLength-tideStart, 10);
    
    ofSetHexColor(0xffffff);
    //ofCircle(boatPerc*barLength + 100, 305, 5);
    //ofCircle(boatPerc*barLength + 100, 15, 5);
    ofEnableAlphaBlending();
    slider.draw(boatPerc*barLength + 100,15);
    ofDisableAlphaBlending();
}

