#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){	
    // iPhone基本設定
    ofRegisterTouchEvents(this);
    ofxAccelerometer.setup();
    ofxiPhoneAlerts.addListener(this);
    ofBackground(0,0,0);
    ofSetFrameRate(60);
    
    // イベント通知
    _prism.setNotifier(this);
    _prism.setup();
    
    // カメラ設定
    cam.setDistance(20000);
    cam.setNearClip(40000);
}

//--------------------------------------------------------------
void testApp::update(){
    // 現在の時刻を取得
    currentTime = ofxSATTime::currentTime();
    
    // SGPに時間を設定
    sgp.update(&currentTime);
    
    // 現在のPRISM衛星の3D座標を算出
    currentSatPos = sgp.getPos();
}

//--------------------------------------------------------------
void testApp::draw(){
    
    //カメラ開始
    cam.begin();
    
    ofSetColor(255, 255, 255);
    ofBox(currentSatPos.x, currentSatPos.y, currentSatPos.z, 200);
    
    //カメラ終了
    cam.end();
    
    
    // 現在の衛星の座標を表示
    ofSetHexColor(0xffffff);
    string curretTimeStr = currentTime.format("%YYYY/%MM/%DD %hh:%mm:%ss");
    ofDrawBitmapString(curretTimeStr, 10, 15);
    ofDrawBitmapString("x = " + ofToString(currentSatPos.x, 4) + "\n"
                       + "y = " + ofToString(currentSatPos.y, 4) + "\n"
                       + "z = " + ofToString(currentSatPos.z, 4), 10, 50);
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

