//
//  anim.h
//  ships2
//
//  Created by me on 10/6/12.
//
//

#ifndef ships2_anim_h
#define ships2_anim_h

#include "ofMain.h"
#include "ofxCenteredTrueTypeFont.h"

class Anim
{
public:
    int start;
    int lastUpdate;
    float yspeed;
    float y;
    float x;
    float alpha;
    float alphaSpeed;
    string text;
    int duration;
    
    void setup(float x, float y, string text)
    {
        this->text = text;
        this->x = x;
        this->y = y;
        alpha = 255;
        yspeed = -50.0;

        duration = 2500;
        alphaSpeed = -255.0 / (duration/1000.0);
        
        start = ofGetElapsedTimeMillis();
        lastUpdate = start;
    }
    void update()
    {
        float delta = (ofGetElapsedTimeMillis() - lastUpdate);
        delta /= 1000.0;
        
        y += delta * yspeed;
        alpha += delta * alphaSpeed;
        
        lastUpdate = ofGetElapsedTimeMillis();
    }
    bool isDone()
    {
        return ofGetElapsedTimeMillis() > start + duration;
    }
    void draw(ofxCenteredTrueTypeFont & font)
    {
        ofSetColor(0,0,0,alpha);
        font.drawStringCenteredHorizontally(text,x,y);
    }
};

#endif
