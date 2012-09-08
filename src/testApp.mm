#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){	
	
	iPhoneSetOrientation(OFXIPHONE_ORIENTATION_LANDSCAPE_LEFT);
	ofRegisterTouchEvents(this);
	ofBackground(127,127,127);
    ofSetFrameRate(30);
    
    box2d.init();
    //box2d.registerGrabbing();
    //box2d.enableGrabbing();
    box2d.setGravity(0,0);
    box2d.setFPS(60);
    //box2d.createBounds();
    //box2d.setIterations(1, 1);
    
    level.setup(box2d);
    chain.setup(box2d);
    
    //cout<<"test:"<<&box2d<<" == "<<chain.box2d<<endl;
}

//--------------------------------------------------------------
void testApp::update(){
    
    
    chain.update();    
    
    box2d.update();
    
    camera.set(-chain.getFrontPos());
    camera += ofPoint(ofGetScreenWidth()/2.0,ofGetScreenHeight()/2.0);
    
}

//--------------------------------------------------------------
void testApp::draw(){
 
    ofPushMatrix();
    ofTranslate(camera);
    level.draw();
    chain.draw();
    
    ofSetHexColor(0x00ff00);
    ofCircle(0,0,4);
    
    ofPopMatrix();
    
    ofPushMatrix();
    ofSetHexColor(0x008800);
    ofScale(0.05, 0.05);
    level.drawDebug();
    ofSetHexColor(0x00ff00);
    chain.drawDebug();
    ofPopMatrix();
    
    string info = "";
	info += "FPS: "+ofToString(ofGetFrameRate(), 1)+"\n";
    info += "camera: "+ofToString(camera.x)+", "+ofToString(camera.y)+"\n";
	ofSetHexColor(0x444342);
	ofDrawBitmapString(info, 230, 30);
    
    
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
   chain.updateAngle(touch.x-camera.x,touch.y-camera.y);
    
}

//--------------------------------------------------------------
void testApp::touchUp(ofTouchEventArgs & touch){
    
}

//--------------------------------------------------------------
void testApp::touchDoubleTap(ofTouchEventArgs & touch){

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

