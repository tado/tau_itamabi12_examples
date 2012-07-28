#include "testApp.h"

const int DAY_LENGTH = 6;

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
    ofEnableSmoothing();
    ofSetFrameRate(60);
    ofBackground(0, 0, 0);
    ofNoFill();
}

//--------------------------------------------------------------
void testApp::update(){

}

//--------------------------------------------------------------
void testApp::draw(){
    // 取得した日時だけデータを取得、画面に表示
    for (int i = 0; i < available.size(); i++) {
        ofxSATError error;
        double value;
        string log;

        //データ取得
        error = prism->getSensorTemperatureMainOBC(available[i], &value);
        
        //画面に文字で表示
        log = available[i].format("%MM/%DD,%hh:%mm") + ", TemperMainOBC = " + ofToString(value, 2);
        ofSetHexColor(0xffffff);
        ofDrawBitmapString(log, 10, 15*(i+1));
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

