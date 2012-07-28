#include "testApp.h"

const int DAY_LENGTH = 14;

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
}

//--------------------------------------------------------------
void testApp::update(){

}

//--------------------------------------------------------------
void testApp::draw(){
    float dx, dy;
    dx = (float)ofGetWidth()/6.0;
    dy = (float)ofGetHeight()/(float)TemperatureOutsideMX.size();
    
    int hue; //色相, 彩度
	ofColor c; //面を塗る色
    for (int i = 0; i < TemperatureOutsideMX.size(); i++) {
        //MX
        hue = ofMap(TemperatureOutsideMX[i], -40.0, 60, 180, 0);
		c = ofColor::fromHsb(hue, 255, 255);
		ofSetColor(c);
        ofRect(0, dy * i, dx, dy);
        //MY
        hue = ofMap(TemperatureOutsideMY[i], -40.0, 60, 180, 0);
		c = ofColor::fromHsb(hue, 200, 255);
		ofSetColor(c);
        ofRect(dx, dy * i, dx, dy);
        //MZ
        hue = ofMap(TemperatureOutsideMZ[i], -40.0, 60, 180, 0);
		c = ofColor::fromHsb(hue, 200, 255);
		ofSetColor(c);
        ofRect(dx*2, dy * i, dx, dy);
        //PX
        hue = ofMap(TemperatureOutsidePX[i], -40.0, 60, 180, 0);
		c = ofColor::fromHsb(hue, 200, 255);
		ofSetColor(c);
        ofRect(dx*3, dy * i, dx, dy);
        //PY
        hue = ofMap(TemperatureOutsidePY[i], -40.0, 60, 180, 0);
		c = ofColor::fromHsb(hue, 200, 255);
		ofSetColor(c);
        ofRect(dx*4, dy * i, dx, dy);
        //PZ
        hue = ofMap(TemperatureOutsidePZ[i], -40.0, 60, 180, 0);
		c = ofColor::fromHsb(hue, 200, 255);
		ofSetColor(c);
        ofRect(dx*5, dy * i, dx, dy);
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
    
    // 取得した日時だけデータを取得
    for (int i = 0; i < available.size(); i++) {
        ofxSATError error;
        double value;
        string log;
        
        //データ取得
        error = prism->getSensorTemperatureOutsideMX(available[i], &value);
        if (error == SATERROR_OK) {
            TemperatureOutsideMX.push_back(value);
        }
        
        error = prism->getSensorTemperatureOutsideMY(available[i], &value);
        if (error == SATERROR_OK) {
            TemperatureOutsideMY.push_back(value);
        }
        
        error = prism->getSensorTemperatureOutsideMZ(available[i], &value);
        if (error == SATERROR_OK) {
            TemperatureOutsideMZ.push_back(value);
        }
        
        error = prism->getSensorTemperatureOutsidePX(available[i], &value);
        if (error == SATERROR_OK) {
            TemperatureOutsidePX.push_back(value);
        }
        
        error = prism->getSensorTemperatureOutsidePY(available[i], &value);
        if (error == SATERROR_OK) {
            TemperatureOutsidePY.push_back(value);
        }
        
        error = prism->getSensorTemperatureOutsidePZ(available[i], &value);
        if (error == SATERROR_OK) {
            TemperatureOutsidePZ.push_back(value);
        }
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

