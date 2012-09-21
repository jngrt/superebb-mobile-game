//
//  shipData.h
//  ships2
//
//  Created by me on 9/16/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef ships2_shipData_h
#define ships2_shipData_h

#include "ofMain.h"

class ShipData
{
public:
    
    ofVec2f location;
    string title;
    bool pickedUp;
    bool invalidLocation;
    
    void setup(float x,float y,string title)
    {
        this->location.set(x,y);
        this->title = title;
        this->invalidLocation = false;
        this->pickedUp = false;
    }

};


#endif
