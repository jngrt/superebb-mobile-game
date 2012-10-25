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
    
    //tileImage1.loadImage("tile1b.png");
    //tileImage2.loadImage("tile2b.png");
    //tileImage3.loadImage("tile3.png");
    
    tileImage1.loadImage("tile1_nw2_hi.png");
    tileImage2.loadImage("tile2_nw2_hi.png");
    tileImage3.loadImage("tile3_nw2_hi.png");
    
}
void Level::reset()
{
    
}

void Level::draw(const ofPoint & camera, bool drawPolys)
{
    ofSetHexColor(0xffffff);
    if(-camera.x < 2048)
    {
        tileImage1.draw(0,0);
        if(drawPolys)drawPoly(0);
    }
    if(-camera.x > 2048-windowWidth &&
       -camera.x < 4096)
    {
        tileImage2.draw(2048,1024);
        if(drawPolys)drawPoly(1);
    }
    if(-camera.x > 4096-windowWidth &&
       -camera.x < 6144)
    {
        tileImage3.draw(4096,1024);
        if(drawPolys)drawPoly(2);
    }
       
}
void Level::drawPoly(int tileIndex)
{
    vector<ofxBox2dPolygon> * polys = ((tileIndex==0)? &tileLines1:(tileIndex==1)? &tileLines2:&tileLines3);
    for(int i=0;i<polys->size();i++)
    {
        //ofSetColor( i*50,0,0);
        (*polys)[i].draw();
    }
}

void Level::drawDebug()
{
    for(int i=0;i<3;i++)
        drawPoly(i);
}

void Level::parseLevel()
{
    ofxXmlSettings data;
    data.loadFile("level-sketch2.tmx");
    data.pushTag("map");
    
    int numGroups = data.getNumTags("objectgroup");
    
    for(int i=0;i<numGroups;i++)
    {
        string objName = data.getAttribute("objectgroup", "name", " ",i);
        if(ofIsStringInString(objName, "boundariesTile"))
        {                    
            data.pushTag("objectgroup",i);
            
            int numTags = data.getNumTags("object");
            for(int j=0;j<numTags;j++)
            {
                int baseX = data.getAttribute("object","x",0,j);
                int baseY = data.getAttribute("object","y",0,j);
                //cout<<"base:"<<baseX<<" x "<<baseY<<endl;
                data.pushTag("object",j);
                string vertexData = data.getAttribute("polyline","points","");
                //cout<<"data:"<<vertexData<<endl;
                parsePoly(baseX, baseY, vertexData);
                data.popTag();
            }
            data.popTag();
        }else if( ofIsStringInString(objName, "finishArea"))
        {
            data.pushTag("objectgroup",i);
            int baseX = data.getAttribute("object","x",0);
            int baseY = data.getAttribute("object","y",0);
            
            data.pushTag("object");
            string vertexData = data.getAttribute("polygon","points","");
            //cout<<"finish data:"<<vertexData<<endl;
            parseFinish(baseX, baseY, vertexData);
            data.popTag();
            data.popTag();
        }
    }
    
    
}
void Level::parseFinish(int baseX,int baseY,string vertexData)
{
    //cout<<"parseFinish:"<<baseX<<" , "<<baseY<<endl;
    vector<string> vertices = ofSplitString(vertexData, " ");
    finishRight = 0;
    //finish.resize(vertices.size());
    for(int i=0;i<vertices.size();i++)
    {
        vector<string> vertex = ofSplitString(vertices[i], ",");
        //finish.addVertex((ofToInt(vertex[0])+baseX)*scale , (ofToInt(vertex[1])+baseY)*scale);
        //finish.push_back(ofVec2f((ofToInt(vertex[0])+baseX)*scale , (ofToInt(vertex[1])+baseY)*scale));
        //total += (ofToInt(vertex[0])+baseX)*scale;
        
        //finish[i] = ofVec2f((ofToInt(vertex[0])+baseX)*scale , (ofToInt(vertex[1])+baseY)*scale);
        int x = (ofToInt(vertex[0])+baseX)*scale;
        int y = (ofToInt(vertex[1])+baseY)*scale;
        finishArea.addVertex(x,y);
        
        if(x > finishRight )
            finishRight = x;
    }
    //finish.set
    //finish.create(box2d.getWorld());
}
bool Level::checkFinish(ofVec2f point)
{
    if(point.x < finishRight + 100){
        
        bool check = insidePolygon(point, finishArea);
        //cout<<point.x<<" x "<<point.y<<"close to finish, finished?:"<<check<<endl;
        return check;
    }
    return false;
}
                    

bool Level::checkInside(ofVec2f point)
{
    //cout<<"Check polys. inside:";
    for( int i=0;i<tileLines1.size();i++)
        if( insidePolygon(point, tileLines1[i]) )
            return true;

    for( int i=0;i<tileLines2.size();i++)
        if( insidePolygon(point, tileLines2[i]) )
            return true;

    for( int i=0;i<tileLines3.size();i++)
        if( insidePolygon(point, tileLines3[i]) )
            return true;

    return false;
}

void Level::filterShips(vector<ShipData>& data)
{
    //cout<<"filterShips, invalid ships:";
    for(int i=0;i<data.size();i++)
    {
        if( checkInside(data[i].location)){
            data[i].invalidLocation = true;
            //cout<<i<<",";
        }
            
    }
    //cout<<endl;
}

void Level::parsePoly(int baseX, int baseY, string vertexData)
{
    //cout<<"parsePoly:"<<baseX<<" , "<<baseY<<endl;
    vector<string> vertices = ofSplitString(vertexData, " ");
    ofxBox2dPolygon poly;
    float total=0;
    for(int i=0;i<vertices.size();i++)
    {
        vector<string> vertex = ofSplitString(vertices[i], ",");
        poly.addVertex((ofToInt(vertex[0])+baseX)*scale , (ofToInt(vertex[1])+baseY)*scale);
        total += (ofToInt(vertex[0])+baseX)*scale;
    }
    poly.alive = false;
    poly.create(box2d.getWorld());
    
    float average = total / vertices.size();
    int tileNr = average / 2048;
   
    if(tileNr==0) tileLines1.push_back(poly);
    else if( tileNr==1) tileLines2.push_back(poly);
    else tileLines3.push_back(poly);
    
}