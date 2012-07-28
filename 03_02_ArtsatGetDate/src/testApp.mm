#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){	
    
	// iPhone初期設定
	ofRegisterTouchEvents(this);
	ofxAccelerometer.setup();
	ofxiPhoneAlerts.addListener(this);
	
    // 衛星の初期化
    if ((prism = new ofxPrismSAT) != NULL) {
        prism->setNotifier(this); // ローディング完了の通知を設定
        prism->setup();
        prism->update();
    }
    
    
	// 描画関連の初期設定
    ofSetFrameRate(60);
	ofBackground(0, 0, 0);
}

//--------------------------------------------------------------
void testApp::update(){
    
}

//--------------------------------------------------------------
void testApp::draw(){
    
    //もし時刻が取得できたら
    if (available.size() > 0) {
        // 取得した日時を画面に表示
        ofSetHexColor(0xffffff);
        ofDrawBitmapString("Year = " + ofToString(lastAvailable.getYear(), 0), 10, 20);
        ofDrawBitmapString("Month = " + ofToString(lastAvailable.getMonth(), 0), 10, 20*2);
        ofDrawBitmapString("Day = " + ofToString(lastAvailable.getDay(), 0), 10, 20*3);
        ofDrawBitmapString("Hour = " + ofToString(lastAvailable.getHour(), 0), 10, 20*4);
        ofDrawBitmapString("Minute = " + ofToString(lastAvailable.getMinute(), 0), 10, 20*5);
        ofDrawBitmapString("Second = " + ofToString(lastAvailable.getSecond(), 0), 10, 20*6);
    } else {
        // そうでなければ、ローディング表示
        ofDrawBitmapString("Loading data...", 10, 20);
    }
}

//--------------------------------------------------------------
void testApp::exit(){
    
}

void testApp::onNotifyTLE(ofxSAT::TLERec const& tle, ofxSATTime const& time) {
    
}

void testApp::onNotifyData(ofxSATTime const& time) {    
    
}

void testApp::onNotifyFinish(ofxSATError error) {
	// 利用可能なデータの中で最新のものを取得
	prism->getAvailableTime(&available);
	lastAvailable = available[available.size()-1];
    
    // 取得された日付全てをコンソールに出力
    for (int i = 0; i < available.size(); i++) {
        cout << "Available Time[" << i << "] : " << available[i].format("%YYYY/%MM/%DD %hh:%mm:%ss") << endl;
    }
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

