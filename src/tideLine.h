//
//  tideLine.h
//  ships2
//
//  Created by me on 9/30/12.
//
//

#ifndef ships2_tideLine_h
#define ships2_tideLine_h

#include "ofMain.h"


class TideLine
{
public:
    int x;
    float speed;
    int lastUpdateMs;
    void setup();
    void reset();
    void update();
    void draw(ofPoint camera);
    void drawDebug(ofPoint camera);
    
};

#endif
