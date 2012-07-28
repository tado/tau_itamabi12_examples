#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){	
    
    // iPhone初期設定
    ofRegisterTouchEvents(this);
    ofxAccelerometer.setup();
    ofxiPhoneAlerts.addListener(this);
    //iPhoneSetOrientation(OFXIPHONE_ORIENTATION_LANDSCAPE_RIGHT);
    
    
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
    glEnable(GL_DEPTH_TEST);
    
    //ライトON
    light.enable();
}

//--------------------------------------------------------------
void testApp::update(){
    
    // もし日付データがダウンロードされていたら
    if(available.size() > 0) {    
        double value;
        ofxSATError error;
        // データを取得した日時を後ろから走査
        error = prism->getSensorGyroX(latest, &value);
        rotationSpeed.x = value;
        error = prism->getSensorGyroY(latest, &value);
        rotationSpeed.y = value;
        error = prism->getSensorGyroZ(latest, &value);
        rotationSpeed.z = value;
    }
}

//--------------------------------------------------------------
void testApp::draw(){
    // 色指定
    ofSetHexColor(0xffffff);
    
    // もし日付データがダウンロードされていたら
    if(available.size() > 0) {
        // 回転スピードをBoxで視覚化
        ofPushMatrix();
        ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
        
        // 取得した角速度でBoxを回転
        ofRotateX(rotationSpeed.x * ofGetElapsedTimef());
        ofRotateY(rotationSpeed.y * ofGetElapsedTimef());
        ofRotateZ(rotationSpeed.z * ofGetElapsedTimef());
        ofBox(0, 0, 0, 150);
        
        ofPopMatrix();
        
        // データをテキストで表示
        ofDrawBitmapString(latest.format("%YYYY/%MM/%DD %hh:%mm:%ss"), 10, 15);
        ofDrawBitmapString("Gyro X = " + ofToString(rotationSpeed.x, 4) , 10, 15 * 2);
        ofDrawBitmapString("Gyro Y = " + ofToString(rotationSpeed.y, 4) , 10, 15 * 3);
        ofDrawBitmapString("Gyro Z = " + ofToString(rotationSpeed.z, 4) , 10, 15 * 4);
    } else {
        // そうでなければ、ローディング表示
        ofSetHexColor(0xffffff);
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
	latest = available[available.size()-1];
    
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

