#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){	
    // iPhone基本設定
    ofRegisterTouchEvents(this);
    ofxAccelerometer.setup();
    ofxiPhoneAlerts.addListener(this);
    glEnable(GL_DEPTH_TEST);
    ofBackground(0,0,0);
    ofSetFrameRate(60);
    
    // データ取得
    currentTime = ofxSATTime::currentTime();
    currentTime.subMonth(1);
    _prism.update(ofxSATTime(currentTime).subDay(3));

    // 時間のスケール(60倍速)
    timeScale = 60.0;

    // イベント通知
    _prism.setNotifier(this);
    _prism.setup();
    
    // カメラ
    cam.setDistance(20000);
    cam.setFarClip(40000);
    
    // 衛星軌道メッシュの初期化
    orbitMesh.setMode(OF_PRIMITIVE_LINE_STRIP); 
}

//--------------------------------------------------------------
void testApp::update(){
    // 軌道推定の時間を更新
    currentTime = ofxSATTime::currentTime().subDay(30).addSecond(ofGetElapsedTimef() * timeScale);
    sgp.update(&currentTime);

    // 衛星の3D座標を算出
    currentSatPos = sgp.getPos();
    orbitMesh.addVertex(currentSatPos);
    orbitMesh.addColor(ofFloatColor(1.0, 1.0, 0.0));
}

//--------------------------------------------------------------
void testApp::draw(){

    // カメラ開始
    cam.begin();
    
    // 地球
    ofNoFill();
    ofSetColor(0, 50, 100);
    ofxSphere(0, 0, 0, 6378);

    // 衛星
    ofFill();
    ofSetHexColor(0xffffff);
    ofBox(currentSatPos.x, currentSatPos.y, currentSatPos.z, 250);

    // 衛星の軌道を描く
    orbitMesh.draw();
    
    // カメラ終了
    cam.end();
    
    // ログ表示
    ofSetHexColor(0xffffff);
    string curretTimeStr = currentTime.format("%YYYY/%MM/%DD %hh:%mm:%ss") + "\ntime scale: " + ofToString(timeScale,1);
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
void testApp::onNotifyTLE(void)
{
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
void testApp::onNotifyData(ofxSATTime const& time)
{
    cout << "notify data = " << time.format("%YYYY/%MM/%DD %hh:%mm:%ss") << endl;
    return;
}

//--------------------------------------------------------------
void testApp::onNotifyFinish(ofxSATError error)
{
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

