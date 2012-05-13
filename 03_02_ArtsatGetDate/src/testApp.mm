#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){	

	// iPhone初期設定
	ofRegisterTouchEvents(this);
	ofxAccelerometer.setup();
	ofxiPhoneAlerts.addListener(this);
	// iPhoneSetOrientation(OFXIPHONE_ORIENTATION_LANDSCAPE_RIGHT);

	// 描画関連の初期設定
    ofSetFrameRate(60);
	ofBackground(0, 0, 0);
	
	// 利用可能なデータの中で最新のものを取得
	vector<ofxSATTime> available;
	prism.GetAvailableTime(&available);
	lastAvailable = available[available.size()-1];
}

//--------------------------------------------------------------
void testApp::update(){

}

//--------------------------------------------------------------
void testApp::draw(){

	// 取得した日時を画面に表示
	ofSetHexColor(0xffffff);
	ofDrawBitmapString("Year = " + ofToString(lastAvailable.GetYear(), 0), 10, 20);
	ofDrawBitmapString("Month = " + ofToString(lastAvailable.GetMonth(), 0), 10, 20*2);
	ofDrawBitmapString("Day = " + ofToString(lastAvailable.GetDay(), 0), 10, 20*3);
	ofDrawBitmapString("Hour = " + ofToString(lastAvailable.GetHour(), 0), 10, 20*4);
	ofDrawBitmapString("Minute = " + ofToString(lastAvailable.GetMinute(), 0), 10, 20*5);
	ofDrawBitmapString("Second = " + ofToString(lastAvailable.GetSecond(), 0), 10, 20*6);
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

