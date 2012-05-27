#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){	
	// register touch events
	ofRegisterTouchEvents(this);
	ofxAccelerometer.setup();
	ofxiPhoneAlerts.addListener(this);
	
	ofBackgroundHex(0x000000);
	
	synth.loadSound("sounds/glockenspiel.caf");
	synth.setVolume(0.75f);
	synth.setMultiPlay(true);
}


//--------------------------------------------------------------
void testApp::update(){
	// サウンド再生システムを更新
	ofSoundUpdate();
}

//--------------------------------------------------------------
void testApp::draw(){
	// マウスの位置に円を描画
	ofSetHexColor(0x3399ff);
	ofCircle(mouseX, mouseY, 20);
}

//--------------------------------------------------------------
void testApp::exit(){

}

//--------------------------------------------------------------
void testApp::touchDown(ofTouchEventArgs &touch){
	// タッチした場所に応じて、定位、ピッチを決定し、サンプルを再生
	synth.play();
	synth.setSpeed(touch.y / ofGetHeight() * 2.0);
	synth.setPan(touch.x / ofGetWidth());
}

//--------------------------------------------------------------
void testApp::touchMoved(ofTouchEventArgs &touch){
	// タッチした場所に応じて定位ピッチを決定し、現在の音を変更
	synth.setSpeed(touch.y / ofGetHeight() * 2.0);
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

