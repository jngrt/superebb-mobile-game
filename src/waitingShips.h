//
//  waitingShips.h
//  ships2
//
//  Created by me on 9/9/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef ships2_waitingShips_h
#define ships2_waitingShips_h

#include "ofMain.h"
#include "ofxJansson.h"

class WaitingShips
{
public:
    void setup();
    void draw();
    
private:
    void parseData();
};


#endif
