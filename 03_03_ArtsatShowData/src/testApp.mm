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
	
	// 衛星の情報取得に必要な変数
	double value;
	ofxSATError error;
	
	// 現在のメインOBCの温度(C°)をvalueに読込み
	error = prism.GetSensorTemperatureMainOBC(lastAvailable, &value);
	
	// 表示
	ofSetHexColor(0xffffff);
	ofDrawBitmapString("Main OBC Temprature : " + ofToString(value, 4), 10, 20);
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

