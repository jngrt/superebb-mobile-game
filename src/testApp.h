#pragma once

#include "ofMain.h"
#include "ofxiPhone.h"
#include "ofxiPhoneExtras.h"
#include "ofxBox2d.h"
#include "level.h"
#include "boatChain.h"
#include "waitingShips.h"
#include "tideLine.h"

class testApp : public ofxiPhoneApp{
	
public:
    void setup();
    void update();
    void draw();
    void exit();

    void touchDown(ofTouchEventArgs & touch);
    void touchMoved(ofTouchEventArgs & touch);
    void touchUp(ofTouchEventArgs & touch);
    void touchDoubleTap(ofTouchEventArgs & touch);
    void touchCancelled(ofTouchEventArgs & touch);

    void lostFocus();
    void gotFocus();
    void gotMemoryWarning();
    void deviceOrientationChanged(int newOrientation);
    
    void resetGame();
    
    WaitingShips waitingShips;
    ofxBox2d box2d;
    //ofAppiPhoneWindow * window;
    Level level;
    vector <ofxBox2dPolygon> polyLines;
    BoatChain chain;
    ofPoint camera;
    ofVec2f lastTouch;
    TideLine tideLine;
    float desiredAngle;
    float time;
    int score;
    
    bool drawDebug;
    
    enum {INTRO,GAME,END}gameState;

};


