//
//  level.cpp
//  ships2
//
//  Created by me on 9/7/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "level.h"


void Level::setup(ofxBox2d& box2d)
{
    this->box2d = box2d;
    
    scale = 1.0;
    
    parseLevel();
    
    /*ofxBox2dPolygon poly;
    poly.addVertex(10,50);
    poly.addVertex(20, 40);
    poly.addVertex(30,50);
    poly.addVertex(40,40);
    poly.create(box2d.getWorld());
    polyLines.push_back(poly);*/
    
    tileImage.loadImage("tile1.png");
    
}

void Level::draw()
{
    ofSetHexColor(0xffffff);
    tileImage.draw(0,0);
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
    for(int i=0;i<data.size();i++)
    {
        if( checkInside(data[i].location)){
            data[i].invalidLocation = true;
            cout<<"invalid location:"<<i<<endl;
        }
            
    }
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