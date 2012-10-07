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
    
    //window = ofxiPhoneGetOFWindow();
    
    level.setup(box2d,480);
    chain.setup(box2d);
    waitingShips.setup();
    level.filterShips(waitingShips.ships);
    
    tideLine.setup();
    
    levelStart = 2048*3;
    levelEnd = 820;
    
    hud.setup(levelStart,levelEnd);
    
    score = 0;
    
    gameState = INTRO;
    
    drawDebug = false;
    
    loseSound.loadSound("lose_crash.wav");
    winSound.loadSound("victory2.wav");
}

//--------------------------------------------------------------
void testApp::update(){
    if(gameState == INTRO)
    {
        
    }
    else if(gameState == GAME)
    {
        
        if( ! chain.checkTide(tideLine.x) )
        {
            gameState = END;
            loseSound.play();
            return;
        }
        
        if( level.checkFinish(chain.getFrontPos()))
        {
            cout<<"yay, win"<<endl;
            winSound.play();
            gameState = END;
            return;
        }
        
        waitingShips.update();
        
        vector<ShipData> shipsNear;
        waitingShips.getShipsNearby(chain.getFrontPos(), shipsNear);
        
        if(shipsNear.size()>0)
        {
            chain.addShips(shipsNear);
        }
        
        chain.update();
        chain.updateAnim();
        
        tideLine.update();
        
        box2d.update();
        
        camera.set(-chain.getFrontPos());
        camera += ofPoint(240,160);
    }
    else if(gameState == END)
    {
        
    }
    
}

//--------------------------------------------------------------
void testApp::draw(){
 
    if(gameState == INTRO)
    {
        ofSetHexColor(0x000000);
        ofDrawBitmapString("TOUCH TO START", 200, 120);
    }
    else if( gameState == GAME)
    {
        ofPushMatrix();
        ofTranslate(camera);

        tideLine.draw(camera);
        level.draw(camera,drawDebug);
        ofSetHexColor(0xffffff);
        chain.draw();
        waitingShips.draw(drawDebug);
        
        waitingShips.drawAnim(camera);
        chain.drawAnim();
        
        
        ofPopMatrix();
        
        hud.draw(chain.getLength(),chain.getFrontPos().x, tideLine.x);
        
        if(drawDebug)
        {
            ofPushMatrix();
            ofSetHexColor(0x008800);
            ofScale(0.05, 0.05);
            level.drawDebug();
            ofSetHexColor(0x00ff00);
            chain.drawDebug();
            ofSetHexColor(0x880000);
            waitingShips.drawDebug();
            tideLine.drawDebug(camera);
            ofPopMatrix();
        }

      
    }
    else if( gameState == END)
    {
        ofSetHexColor(0x000000);
        ofDrawBitmapString("END OF GAME", 200, 120);
    }
    
    string info = "";
    info += "FPS: "+ofToString(ofGetFrameRate(), 1)+"\n";
    info += "camera: "+ofToString(camera.x)+", "+ofToString(camera.y)+"\n";
    ofSetHexColor(0x444342);
    ofDrawBitmapString(info, 230, 30);
    
}

void testApp::resetGame()
{
    gameState = INTRO;
    
    level.reset();
    chain.reset();
    waitingShips.reset();
    tideLine.reset();
    
    score = 0;
    
}

//--------------------------------------------------------------
void testApp::exit(){

}

//--------------------------------------------------------------
void testApp::touchDown(ofTouchEventArgs & touch){
    //level.checkInside(ofVec2f(touch.x-camera.x,touch.y-camera.y));
    if(gameState == INTRO)
        gameState = GAME;
    else if( gameState == GAME)
        touchMoved(touch);
    else if( gameState == END)
        resetGame();
}

//--------------------------------------------------------------
void testApp::touchMoved(ofTouchEventArgs & touch){
   if(gameState == GAME)
       chain.updateAngle(touch.x-camera.x,touch.y-camera.y);
    
}

//--------------------------------------------------------------
void testApp::touchUp(ofTouchEventArgs & touch){
    
}

//--------------------------------------------------------------
void testApp::touchDoubleTap(ofTouchEventArgs & touch){
    drawDebug = !drawDebug;
    //cout<<"double tap"<<endl;
    //chain.
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

