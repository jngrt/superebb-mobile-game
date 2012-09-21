//
//  waitingShips.cpp
//  ships2
//
//  Created by me on 9/9/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "waitingShips.h"


void WaitingShips::setup()
{
    realStartCoord.set(4.1238f,51.9707f);
    realEndCoord.set(4.4894f, 51.9076f);
    //(1.381 x 0.916 ) * 1024 = (1414,938) 
    //(5.721 x 2.136 ) * 1024 = (5858,2187)
    gameStartCoord.set(1414.0f, 938.0f);
    gameEndCoord.set(5858.0f, 2187.0f);
    realArea = realEndCoord - realStartCoord;
    gameArea = gameEndCoord - gameStartCoord;
    
    parseData();
}

void WaitingShips::draw()
{
    
    for(int i=0;i<ships.size();i++)
    {
        if( ships[i].invalidLocation)
            ofSetHexColor(0xff0000);
        else if(ships[i].pickedUp)
            ofSetHexColor(0x777777);
        else
            ofSetHexColor(0x0000ff);
        //ofSetHexColor( ships[i].invalidLocation?0x880000:0x000088);
        ofCircle(ships[i].location.x,ships[i].location.y,5); 
    }
}

void WaitingShips::drawDebug()
{
    for(int i=0;i<ships.size();i++)
    {
        if( ships[i].invalidLocation)
            ofSetHexColor(0xff0000);
        else if(ships[i].pickedUp)
            ofSetHexColor(0x777777);
        else
            ofSetHexColor(0x0000ff);
        
        ofCircle(ships[i].location.x,ships[i].location.y,5); 
    }
}

void WaitingShips::getShipsNearby(ofVec2f point, vector<ShipData> &shipsNear )
{
    for(int i=0;i<ships.size();i++)
        if( !ships[i].pickedUp && (point - ships[i].location).length()<20.0)
        {
            ships[i].pickedUp = true;
            shipsNear.push_back(ships[i]);
        }
}

void WaitingShips::parseData()
{
    ofxJSONElement data;
    
    if( data.openLocal("data_tanker_only_18092012.json.txt") )
        cout<<"Json parsed items:"<<data.size()<<endl;
    else 
        cout<<"Failed to parse json"<<endl;
    
    ships.resize(data.size());
    
    for(int i=0;i<data.size();i++)
    {
        ofxJSONElement dataItem = data[i];
        float objectY = dataItem[0u].asDouble();
        float objectX = dataItem[1].asDouble();
        float offsetX = (objectX - realStartCoord.x);
        float offsetY = (objectY - realStartCoord.y);
        float relativeX =  offsetX / realArea.x;
        float relativeY =  offsetY / realArea.y;
        
        float x = gameStartCoord.x + relativeX * gameArea.x;
        float y = gameStartCoord.y + relativeY * gameArea.y;
        
        ships[i].setup(x, y, dataItem[2].asString());
        
        //cout<<i<<":--------------"<<endl;
        //cout<<" obj:"<<objectX<<" x "<<objectY<<endl;
        //cout<<" off:"<<offsetX<<" x "<<offsetY<<endl;
        //cout<<" rel:"<<relativeX<<" x "<<relativeY<<endl;
        //cout<<"real:"<<x<<" x "<<y<<endl;
        //cout<<"ship:"<<ships[i].location.x<<" x "<<ships[i].location.y<<endl;
        
    }
    
}