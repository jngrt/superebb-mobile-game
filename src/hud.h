//
//  hud.h
//  ships2
//
//  Created by me on 10/6/12.
//
//

#ifndef ships2_hud_h
#define ships2_hud_h

#include "ofMain.h"
#include "ofxCenteredTrueTypeFont.h"

class Hud
{
public:
    void setup(int levelStart, int levelEnd);
    void draw(int score, int boat, int tide);
    void update();
    
    ofImage bg;
    //ofTrueTypeFont scoreFont;
    ofxCenteredTrueTypeFont scoreFont;
    
private:
    int levelStart;
    int levelEnd;
    float levelLength;
};

#endif
