#pragma once


#include "ofMain.h"
#include "ofxiPhone.h"
#include "ofxiPhoneExtras.h"
#include "ofxBox2d.h"
#include "boatRect.h"
#include "b2Math.h"
#include "b2Body.h"
#include "b2WeldJoint.h"
#include "boat.h"

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
    
    ofVec2f getLateralVelocity();
    
    ofxBox2d						box2d;			  //	the box2d world
	//ofxBox2dCircle					anchor;			  //	fixed anchor
	//vector		<ofxBox2dCircle>	circles;		  //	default box2d circles
	BoatRect                        anchor;
    ofVec2f                         anchorPoint;
    ofxBox2dRect                    dragPoint;
    vector      <BoatRect>          boats;
    vector		<ofxBox2dJoint>		joints;			  //	joints
    
    vector      <ofxBox2dRect>      walls;
    vector      <ofxBox2dRect>      objects;
    ofVec2f lastTouch;
    bool applyForce;
    
    float cameraX;
    float worldWidth;
    
    ofImage waves;
    Boat    boat;
    float desiredAngle;
};


