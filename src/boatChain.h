//
//  boatChain.h
//  ships2
//
//  Created by me on 9/7/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef ships2_boatChain_h
#define ships2_boatChain_h

#include "ofMain.h"
#include "ofxBox2d.h"
#include "boatRect.h"
#include "scoreAnim.h"


class BoatChain
{
public:
    void setup(ofxBox2d& box2d);
    //void setup();
    void draw();
    void drawDebug();
    void drawAnim();
    void update();
    void updateAnim();
    void reset();
    void updateAngle(float touchX,float touchY);
    void bump(float touchX,float touchY);
    
    void addShips(const vector<ShipData> &shipsToAdd);
    ofVec2f getFrontPos();
    bool checkTide(int x);
    int getLength();
    
    void contactEnd(ofxBox2dContactArgs &e);
    void contactStart(ofxBox2dContactArgs &e);
    
private:
    void calculateLength();
    void makeFront();
    void addShip(ShipData data);
    void collapseBoats(int index);
    void checkBoats();
    void playSound(int id);
    //vector<
    vector<BoatRect> chain;
    float desiredAngle;
    ofVec2f lastPoint;
    
    ofxBox2d box2d;
    
    ofImage tugImg;
    ofImage boatImg;
    int length;
    
    ofxCenteredTrueTypeFont animFont;
    vector<ScoreAnim> anims;
    
    vector<int> frontBumps;
    int lastChainDestroy;
    int destroyIndex;
    
    ofSoundPlayer ping1;
    ofSoundPlayer ping2;
    ofSoundPlayer ping3;
    ofSoundPlayer ping4;
    ofSoundPlayer crash;
    int lastPing;
};


#endif
