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
    
    introImage.loadImage("zoom0-intro-uitleg.jpg");
    infoImage.loadImage("credits.jpg");
    zoom1Image.loadImage("zoom1.png");
    zoom2Image.loadImage("zoom2.png");
    zoom3Image.loadImage("zoom3.png");
    menuImage.loadImage("menu.jpg");
    winImage.loadImage("winscreen.jpg");
    loseImage.loadImage("gameoverscreen.jpg");
    
    scoreFont.loadFont("GloriaHallelujah.ttf", 26);
    dataFont.loadFont("GloriaHallelujah.ttf",12);
    stateStartMs = ofGetElapsedTimeMillis();
    stateDelay = 1000;
    
    zoomStepMs = 700;
    curZoom = 1;
}

//--------------------------------------------------------------
void testApp::update(){
    if(gameState == ZOOM)
    {
        if( ofGetElapsedTimeMillis() > stateStartMs + zoomStepMs)
        {
            stateStartMs = ofGetElapsedTimeMillis();
            if(++curZoom > 3){
                gameState = GAME;
                tideLine.reset();
            }
        }
    }
    else if(gameState == GAME)
    {
        
        if( ! chain.checkTide(tideLine.x) )
        {
            gameState = LOSE;
            stateStartMs = ofGetElapsedTimeMillis();
            loseSound.play();
            return;
        }
        
        if( level.checkFinish(chain.getFrontPos()))
        {
            cout<<"yay, win"<<endl;
            winSound.play();
            stateStartMs = ofGetElapsedTimeMillis();
            gameState = WIN;
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
    
}

//--------------------------------------------------------------
void testApp::draw(){
    ofSetHexColor(0xffffffff);
    
    if(gameState == INTRO)
    {
        introImage.draw(0,0);
    }
    else if(gameState == INFO)
    {
        infoImage.draw(0,0);
    }
    else if(gameState == MENU)
    {
        menuImage.draw(0,0);
        //ofSetHexColor(0x000000);
        string info = "Scheeps-data ververst:\n"+waitingShips.refreshDate+" GMT";
        dataFont.drawString(info, 10, 22);
        //ofSetHexColor(0xfffffffff);
    }
    else if(gameState == ZOOM)
    {
        if(curZoom==1)zoom1Image.draw(0,0);
        else if(curZoom==2)zoom2Image.draw(0,0);
        else if(curZoom==3)zoom3Image.draw(0,0);
    }
    else if( gameState == LOSE && ofGetElapsedTimeMillis() > stateStartMs + stateDelay )
    {
        loseImage.draw(0,0);
    }
    else if( gameState == WIN && ofGetElapsedTimeMillis() > stateStartMs + stateDelay)
    {
        winImage.draw(0,0);
        scoreFont.drawStringCenteredHorizontally(ofToString(chain.getLength()), 210, 288);
    }
    else
    {
        ofPushMatrix();
        ofTranslate(camera);
        ofSetHexColor(0xffffff);
        
        tideLine.draw(camera);
        level.draw(camera,drawDebug);
        ofSetHexColor(0xffffff);
        chain.draw();
        waitingShips.draw(camera, drawDebug);
        
        waitingShips.drawAnim(camera);
        chain.drawAnim();
        
        
        ofPopMatrix();
        
        hud.draw(chain.getLength(),chain.getFrontPos().x, tideLine.x);
        /*
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
        }*/

      
    }
    ofSetHexColor(0xffffffff);
    
    string info = "";
    info += "FPS: "+ofToString(ofGetFrameRate(), 1);//"\n";
    //info += "camera: "+ofToString(camera.x)+", "+ofToString(camera.y)+"\n";
    ofSetHexColor(0x444342);
    ofDrawBitmapString(info, 390, -20);
    
    
}

void testApp::resetGame()
{
    gameState = MENU;
    
    level.reset();
    chain.reset();
    waitingShips.reset();
    tideLine.reset();
    
    score = 0;
    curZoom = 1;
    stateStartMs = ofGetElapsedTimeMillis();
    
}

//--------------------------------------------------------------
void testApp::exit(){

}

//--------------------------------------------------------------
void testApp::touchDown(ofTouchEventArgs & touch){
    //level.checkInside(ofVec2f(touch.x-camera.x,touch.y-camera.y));
    cout<<"x:"<<touch.x<<" y:"<<touch.y<<endl;
    if(gameState == INTRO)
    {
        
        if( ofGetElapsedTimeMillis() > stateStartMs + stateDelay)
        {
            gameState = MENU;
            stateStartMs = ofGetElapsedTimeMillis();
        }
    }
    else if(gameState == INFO)
    {
        if( ofGetElapsedTimeMillis() > stateStartMs + stateDelay)
        {
            gameState = MENU;
            stateStartMs = ofGetElapsedTimeMillis();
        }
    }
    else if( gameState == MENU)
    {
        
        if( ofGetElapsedTimeMillis() > stateStartMs + stateDelay)
        {
            if( touch.x > 430 && touch.y < 50 )
                gameState = INFO;
            else
                gameState = ZOOM;
            
            stateStartMs = ofGetElapsedTimeMillis();
        }
    }
    else if( gameState == GAME)
    {
        touchMoved(touch);
    }
    else if( gameState == WIN || gameState == LOSE)
    {
        if( ofGetElapsedTimeMillis() > stateStartMs + stateDelay)
            resetGame();
    }
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

