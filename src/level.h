//
//  level.h
//  ships2
//
//  Created by me on 9/7/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef ships2_level_h
#define ships2_level_h

#include "ofxBox2d.h"
#include "ofMain.h"
#include "ofxXmlSettings.h"
#include "shipData.h"

class Level{
public:
    void setup(ofxBox2d& box2d);
    void draw();
    void drawDebug();
    bool checkInside(ofVec2f point);
    void filterShips(vector<ShipData>& data);
    
    float scale;
    
private:
    void parseLevel();
    void parsePoly(int baseX, int baseY, string vertexData);
    
    ofxBox2d box2d;
    vector<ofxBox2dPolygon> polyLines;
    ofImage tileImage;
};

#endif
