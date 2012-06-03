#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){	
    // iPhone基本設定
    ofRegisterTouchEvents(this);
    ofxAccelerometer.setup();
    ofxiPhoneAlerts.addListener(this);
    ofBackground(0,0,0);
    ofSetFrameRate(60);
}

//--------------------------------------------------------------
void testApp::update(){

}

//--------------------------------------------------------------
void testApp::draw(){  

}

//--------------------------------------------------------------
//
// ARTSAT API イベント通知関連
//
//--------------------------------------------------------------
void testApp::onNotifyTLE(void){
    ofxPrismSAT::TLERec tle;
    ofstream file;
    
    if (_prism.getTLE(&tle) == SATERROR_OK) {
        file.open(ofToDataPath("tle.txt").c_str(), ios::out);
        if (file.is_open()) {
            file << "PRISM" << endl;
            file << tle.line[0] << endl;
            file << tle.line[1] << endl;
            file.close();
            
            sgp.setup(ofToDataPath("tle.txt").c_str());
        }
    }
    return;
}

//--------------------------------------------------------------
void testApp::onNotifyData(ofxSATTime const& time){
    cout << "notify data = " << time.format("%YYYY/%MM/%DD %hh:%mm:%ss") << endl;
    return;
}

//--------------------------------------------------------------
void testApp::onNotifyFinish(ofxSATError error){
    cout << "notify error = " << error << endl;
    return;
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

