#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){	
	// initialize the accelerometer
	//ofxAccelerometer.setup();
	
	//If you want a landscape oreintation 
	iPhoneSetOrientation(OFXIPHONE_ORIENTATION_LANDSCAPE_RIGHT);
	
	//ofBackground(127,127,127);
    ofRegisterTouchEvents(this);
    ofxiPhoneAlerts.addListener(this);
    ofSetFrameRate(30);
    //ofSetVerticalSync(true);
	ofBackgroundHex(0xfdefc2);
	//ofSetLogLevel(OF_LOG_NOTICE);
    
    cameraX = 0.0;
    worldWidth = 1000.0;
    
	box2d.init();
	box2d.setGravity(0, 0);
	box2d.setFPS(30.0);
	//box2d.registerGrabbing();
	
    //walls
    walls.resize(3);
    //walls[0].setup(box2d.getWorld(),worldWidth/2.0,0,worldWidth/2.0,10);
    walls[1].setup(box2d.getWorld(),0,0,10,ofGetHeight());
   
    
    int objCount = 40;
    objects.resize(objCount);
    for(int i=0;i<objCount;i++)
        objects[i].setup(box2d.getWorld(),
                         i*(worldWidth/objCount),
                         ofRandomHeight(),
                         10.0,
                         10.0+ofRandom(10.0));
    
	//anchor.setup(box2d.getWorld(), 20, ofGetHeight()/2, 4);
    anchor.setPhysics(10.0, 0.1, 0.1);
    anchor.setDamping(0.95);
    anchor.setRotationFriction(0.95);
	anchor.setup(box2d.getWorld(), ofGetWidth()/2, 80, 4, 10);
    
	// first we add just a few circles
	for (int i=0; i<10; i++) {
		BoatRect boat;
		boat.setPhysics(0.0001, 0.0, 0.8);
        boat.setDamping(0.95);
        
        boat.setRotationFriction(0.95);
		boat.setup(box2d.getWorld(), ofGetWidth()/2, 100+(i*20), 4, 12);
		boats.push_back(boat);
	}
    
    
    for (int i=0;i<boats.size();i++){
        b2RevoluteJointDef rjd;   
        if(i==0)
        {
            rjd.Initialize(anchor.body, boats[0].body, anchor.body->GetPosition()+b2Vec2(0,0.2));
        }
        else
        {
            rjd.Initialize(boats[i-1].body, boats[i].body, boats[i-1].body->GetPosition()+b2Vec2(0,0.2));

        }
        rjd.collideConnected = false;
        rjd.lowerAngle = -0.25f * b2_pi;
        rjd.upperAngle = 0.25f * b2_pi;
        rjd.enableLimit = true;
        box2d.getWorld()->CreateJoint(&rjd);
        
    }
    
    waves.loadImage("water2.jpg");
    
}

//--------------------------------------------------------------
void testApp::update(){

    /*
     *First orient the 
     */
    //http://www.iforce2d.net/b2dtut/rotate-to-angle
    float bodyAngle = anchor.body->GetAngle() + 180.0*DEG_TO_RAD;
    
    float nextAngle = bodyAngle + anchor.body->GetAngularVelocity() / 3.0;
    float totalRotation = desiredAngle - nextAngle;//use angle in next time step
    while ( totalRotation < -180 * DEG_TO_RAD ) totalRotation += 360 * DEG_TO_RAD;
    while ( totalRotation >  180 * DEG_TO_RAD ) totalRotation -= 360 * DEG_TO_RAD;    
    if(fabs(totalRotation)>2.0*DEG_TO_RAD)
        anchor.body->ApplyTorque( totalRotation < 0 ? -2 : 2 );

    
    b2Vec2 vel = anchor.body->GetLinearVelocity();
    b2Vec2 linVelVec = vel;
    linVelVec.Normalize();
    b2Vec2 facingVec = anchor.body->GetTransform().R.col2;
    facingVec.Normalize();
    float dot = b2Dot(linVelVec, facingVec);
    if(dot>0.0)
    {
        //cout<<"going backward"<<endl;
        b2Vec2 force = linVelVec;
        force *= -10.0;
        anchor.body->ApplyForce(force, anchor.body->GetWorldCenter());
    }else if( vel.Length() < 1.0){
        b2Vec2 force = linVelVec;
        force*=5.0;
        anchor.body->ApplyForce(force, anchor.body->GetWorldCenter());
    }
    
    //anchor.updateFriction();
    
    box2d.update();
    
    
    anchor.killOrthogonalVelocity();
    for(int i=0;i<boats.size();i++)
        //boats[i].updateFriction();
        boats[i].killOrthogonalVelocity();
    
    //change camera
    //cameraX -= 1.0;
    cameraX = ofGetScreenWidth()/2.0 - anchor.getPosition().x;
    
}

//--------------------------------------------------------------
void testApp::draw(){
    float wave = -10 + 10*sin(ofGetElapsedTimeMillis()/1000.0);
    waves.draw(wave,0);
    
    ofPushMatrix();
    ofTranslate(cameraX,0);
  	ofSetHexColor(0xf2ab01);
	
    for(int i=0;i<walls.size();i++)
        walls[i].draw();
    for(int i=0;i<objects.size();i++)
        objects[i].draw();
    
    anchor.draw();
    ofSetHexColor(0xff0000);
   // dragPoint.draw();
	
    ofFill();
    //ofSetHexColor(0x01b1f2);
    ofEnableAlphaBlending();
    ofSetColor(100,100,100,100);
	for(int i=0; i<boats.size(); i++) {
		boats[i].draw();
	}
    ofDisableAlphaBlending();
	
    ofSetHexColor(0x444342);
	for(int i=0; i<joints.size(); i++) {
		joints[i].draw();
	}
	
    ofPopMatrix();
    
    string info = "";
	info += "Double tap to add a new joint\n";
	info += "Press and pull the chain around\n";
	info += "FPS: "+ofToString(ofGetFrameRate(), 1)+"\n";
	ofSetHexColor(0x444342);
	ofDrawBitmapString(info, 30, 30);

}

//--------------------------------------------------------------
void testApp::exit(){
    
}

//--------------------------------------------------------------
void testApp::touchDown(ofTouchEventArgs & touch){
    touchMoved(touch);
}

//--------------------------------------------------------------
void testApp::touchMoved(ofTouchEventArgs & touch){
    lastTouch.x = touch.x - cameraX;
    lastTouch.y = touch.y;
    ofVec2f toTarget = lastTouch - anchor.getPosition();
    desiredAngle = atan2f(-toTarget.x,toTarget.y);
    
}

//--------------------------------------------------------------
void testApp::touchUp(ofTouchEventArgs & touch){
    applyForce = false;
}

//--------------------------------------------------------------
void testApp::touchDoubleTap(ofTouchEventArgs & touch){
//    ofxBox2dCircle c;
//    c.setPhysics(1, 0.4, 0.4);
//    c.setup(box2d.getWorld(), touch.x, touch.y, ofRandom(13, 25));
//    circles.push_back(c);
    
    // add a new circle
    /*
    ofxBox2dCircle circle;
    circle.setPhysics(0.5, 0.02, 0.1);
    circle.setup(box2d.getWorld(), circles.back().getPosition().x+ofRandom(-30, 30), circles.back().getPosition().y-30, 8);
    circles.push_back(circle);
	
    // get this cirlce and the prev cirlce
    int a = (int)circles.size()-2;
    int b = (int)circles.size()-1; 
    
    // now connect the new circle with a joint
    ofxBox2dJoint joint;
    joint.setup(box2d.getWorld(), circles[a].body, circles[b].body);
    joint.setLength(25);
    joints.push_back(joint);
     */
}

//--------------------------------------------------------------
void testApp::touchCancelled(ofTouchEventArgs & touch){
    
}

//--------------------------------------------------------------
void testApp::lostFocus(){

}

//--------------------------------------------------------------
void testApp::gotFocus(){

}

//--------------------------------------------------------------
void testApp::gotMemoryWarning(){

}

//--------------------------------------------------------------
void testApp::deviceOrientationChanged(int newOrientation){

}

