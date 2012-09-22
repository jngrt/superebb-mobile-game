//
//  level.cpp
//  ships2
//
//  Created by me on 9/7/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "level.h"


void Level::setup(ofxBox2d& box2d, int windowWidth)
{
    this->box2d = box2d;
    this->windowWidth = windowWidth;
    
    scale = 1.0;
    
    parseLevel();
    
    /*ofxBox2dPolygon poly;
    poly.addVertex(10,50);
    poly.addVertex(20, 40);
    poly.addVertex(30,50);
    poly.addVertex(40,40);
    poly.create(box2d.getWorld());
    polyLines.push_back(poly);*/
    
    tileImage1.loadImage("tile1.png");
    tileImage2.loadImage("tile2.png");
    tileImage3.loadImage("tile3.png");
    
}

void Level::draw(const ofPoint & camera)
{
    ofSetHexColor(0xffffff);
    if(-camera.x < 2048)
        tileImage1.draw(0,0);
    if(-camera.x > 2048-windowWidth &&
       -camera.x < 4096)
        tileImage2.draw(2048,1024);
    if(-camera.x > 4096-windowWidth &&
       -camera.x < 6144)
        tileImage3.draw(4096,1024);
    
    ofSetHexColor(0xff0000);
    for(int i=0;i<polyLines.size();i++)
    {
        //ofSetColor( i*50,0,0);
        polyLines[i].draw();
    }
}

void Level::drawDebug()
{
    
    for(int i=0;i<polyLines.size();i++)
    {
        //ofSetColor( i*50,0,0);
        polyLines[i].draw();
    } 
}

void Level::parseLevel()
{
    ofxXmlSettings data;
    data.loadFile("level2.tmx");
    data.pushTag("map");
    data.pushTag("objectgroup");
    
    int numTags = data.getNumTags("object");
    for(int i=0;i<numTags;i++)
    {
        int baseX = data.getAttribute("object","x",0,i);
        int baseY = data.getAttribute("object","y",0,i);
        data.pushTag("object",i);
        string vertexData = data.getAttribute("polyline","points","");
        parsePoly(baseX, baseY, vertexData);
        data.popTag();
    }
}


bool Level::checkInside(ofVec2f point)
{
    //cout<<"Check polys. inside:";
    for( int i=0;i<polyLines.size();i++)
        if( insidePolygon(point, polyLines[i]) )
        {
            //cout<<i<<endl;
            return true;
        }
    //cout<<" none"<<endl;
    return false;
}

void Level::filterShips(vector<ShipData>& data)
{
    cout<<"filterShips, invalid ships:";
    for(int i=0;i<data.size();i++)
    {
        if( checkInside(data[i].location)){
            data[i].invalidLocation = true;
            cout<<i<<",";
        }
            
    }
    cout<<endl;
}

void Level::parsePoly(int baseX, int baseY, string vertexData)
{
    cout<<"parsePoly:"<<baseX<<" , "<<baseY<<endl;
    vector<string> vertices = ofSplitString(vertexData, " ");
    ofxBox2dPolygon poly;
    for(int i=0;i<vertices.size();i++)
    {
        vector<string> vertex = ofSplitString(vertices[i], ",");
        poly.addVertex((ofToInt(vertex[0])+baseX)*scale , (ofToInt(vertex[1])+baseY)*scale);
    }
    //poly.close();
    //poly.setPosition(-baseX*scale, -baseY*scale);
    poly.create(box2d.getWorld());
    
    polyLines.push_back(poly);
}