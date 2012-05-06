#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){	
	// register touch events
	ofRegisterTouchEvents(this);
	
	// initialize the accelerometer
	ofxAccelerometer.setup();
	
	//iPhoneAlerts will be sent to this.
	ofxiPhoneAlerts.addListener(this);
	
	//If you want a landscape oreintation 
	//iPhoneSetOrientation(OFXIPHONE_ORIENTATION_LANDSCAPE_RIGHT);
	
	ofSetFrameRate(24);
	for (int i = 0; i < FRAMENUM; i++) {
		char char1[32];
		sprintf(char1, "images/myAnim%04d.png", i+1);
		myImage[i].loadImage(char1);
	}
	frameCount = 0;
}

//--------------------------------------------------------------
void testApp::update(){
	
}

//--------------------------------------------------------------
void testApp::draw(){
	myImage[frameCount].draw(0, 0);
	frameCount++;
	if (frameCount > FRAMENUM - 1) {
		frameCount = 0;
	}
}

//--------------------------------------------------------------
void testApp::exit(){
	
}

//--------------------------------------------------------------
void testApp::touchDown(ofTouchEventArgs &touch){
	int frameRate = touch.y / ofGetWidth() * 60;
	ofSetFrameRate(frameRate);
}

//--------------------------------------------------------------
void testApp::touchMoved(ofTouchEventArgs &touch){
	int frameRate = touch.y / ofGetWidth() * 60;
	ofSetFrameRate(frameRate);
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

