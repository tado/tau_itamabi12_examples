#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){	
    // iPhone基本設定
    ofRegisterTouchEvents(this);
    ofxAccelerometer.setup();
    ofxiPhoneAlerts.addListener(this);
    ofEnableAlphaBlending();
    ofEnableSmoothing();
    ofBackground(0,0,0);
    ofSetFrameRate(60);
    
    iPhoneSetOrientation(OFXIPHONE_ORIENTATION_LANDSCAPE_RIGHT);
    
    if ((_prism = new ofxPrismSAT) != NULL) {
        _prism->setNotifier(this);
        _prism->setup();
        _prism->update();
    }
    
    // 時間のスケール
    timeScale = 100;
    
    // 衛星軌道メッシュの初期化
    orbitMesh.setMode(OF_PRIMITIVE_LINE_STRIP); 
    
    // テクスチャ読みこみ
    texture.loadImage("earth_fixed.jpg");
}

//--------------------------------------------------------------
void testApp::update(){
    // 衛星アップデート
    _prism->update();
    
    // 軌道推定の時間を更新
    currentTime = ofxSATTime::currentTime().addSecond(ofGetElapsedTimef() * timeScale);
    sgp.update(&currentTime);
}

//--------------------------------------------------------------
void testApp::draw(){
    
    texture.draw(ofPoint(0, 0), ofGetWidth(), ofGetHeight());
    
    // 衛星の緯度経度から、地図の座標へマッピング
    // sgp.getSatLatitude(): 衛星の現在の緯度
    // sgp.getSatLongitude(): 衛星の現在の経度
    ofVec2f satMapPos;
    satMapPos.y = ofMap(sgp.getSatLatitude(), 90, -90, 0, ofGetHeight());
    satMapPos.x = ofMap(sgp.getSatLongitude(), 0, 360, 0, ofGetWidth());
    
    ofSetColor(255, 255, 255);
    ofCircle(satMapPos.x, satMapPos.y, 4);
    
    // 衛星の軌跡を描く
    satPath.push_back(satMapPos);
    ofSetColor(255, 255, 0);
    for (int i = 1; i < satPath.size()-1; i++) {
        if (satPath[i].distance(satPath[i+1]) < 10) {
            ofLine(satPath[i].x, satPath[i].y, satPath[i+1].x, satPath[i+1].y);
        }
    }
    
    // ログ表示
    ofSetHexColor(0xffffff);
    string curretTimeStr = currentTime.format("%YYYY/%MM/%DD %hh:%mm:%ss") + "\ntime scale: " + ofToString(timeScale,1);
    ofDrawBitmapString(curretTimeStr, 10, 15);
    ofDrawBitmapString("lat = " + ofToString(sgp.getSatLatitude(), 8) + "\n"
                       + "lon = " + ofToString(sgp.getSatLongitude(), 8) + "\n"
                       + "alt = " + ofToString(sgp.getSatAlt(), 8), 10, 50);
    
}

//--------------------------------------------------------------
void testApp::exit(){
    if (_prism != NULL) {
        _prism->cleanup();
        delete _prism;
    }
    _prism = NULL;
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

void testApp::onNotifyTLE(ofxPrismSAT::TLERec const& tle, ofxSATTime const& time) {

    //TLEデータを書き出すpathを設定
    ofstream file;
    string path;
    path = ofToDataPath("");
    path = ofFilePath::join(ofFilePath::getEnclosingDirectory(path), "Library");
    path = ofFilePath::join(path, "tle.txt");
    
    cout << "TLE data path : " << path << endl;

    // ファイルにTLEを書き込み、SGPを設定
    file.open(path.c_str(), ios::out);
    if (file.is_open()) {
        file << "PRISM" << endl;
        file << tle.line[0] << endl;
        file << tle.line[1] << endl;
        file.close();
        
        sgp.setup(path.c_str());
    }
}