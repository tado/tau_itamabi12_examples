#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){	
	// iPhone初期設定
	ofRegisterTouchEvents(this);
	ofxAccelerometer.setup();
	ofxiPhoneAlerts.addListener(this);
	
	// 背景色
	ofBackground(0,0,0);
}

//--------------------------------------------------------------
void testApp::update(){
	
}

//--------------------------------------------------------------
void testApp::draw(){
	// 2つの円を描く
	ofEnableAlphaBlending();
	ofSetColor(0, 127, 255, 200);
	ofCircle(130, 240, 50);
	ofSetColor(255, 127, 0, 200);
	ofCircle(190, 240, 50);    
}

//--------------------------------------------------------------
void testApp::exit(){
	
}

//--------------------------------------------------------------
void testApp::touchDown(ofTouchEventArgs &touch){
	
}

//--------------------------------------------------------------
void testApp::touchMoved(ofTouchEventArgs &touch){
	
}

//--------------------------------------------------------------
void testApp::touchUp(ofTouchEventArgs &touch){
	
}

//--------------------------------------------------------------
void testApp::touchDoubleTap(ofTouchEventArgs &touch){
	
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


//--------------------------------------------------------------
void testApp::touchCancelled(ofTouchEventArgs& args){
	
}

