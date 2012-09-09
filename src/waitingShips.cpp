//
//  waitingShips.cpp
//  ships2
//
//  Created by me on 9/9/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "waitingShips.h"


void WaitingShips::setup()
{
    parseData();
}

void WaitingShips::draw()
{
    
}

void WaitingShips::parseData()
{
    json_t* root;
	json_error_t error;
    
    ofBuffer buffer = ofBufferFromFile("ship_data.json");
    //cout<<"test:"<<buffer<<endl;
    
    // load json.
	//root = json_loads(buffer.getText(), &error);
    //root = json_load_file("ship_data.json", &error);
    //char text[buffer.getText().size()];
    //text = buffer.getText().c_str();
    
    char* p = new char[buffer.getText().length()+1];
    memcpy(p, buffer.getText().c_str(), buffer.getText().length());
    root = json_loads(p, &error);

    //ifstream dataFile;
    //dataFile.open("ship_data.json");
    //root = json_loadf(datafile,&error);
    
    if(!root) {
		cout <<  "error: on line:" << error.line << ", " << error.text << endl;
		return;
	}else{
        cout<< "no json error?"<<endl;
    }
}