#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){	
    // iPhone基本設定
    ofRegisterTouchEvents(this);
    ofxAccelerometer.setup();
    ofxiPhoneAlerts.addListener(this);
    ofEnableAlphaBlending();
    ofEnableSmoothing();
    glEnable(GL_DEPTH_TEST);
    ofBackground(0,0,0);
    ofSetFrameRate(60);
    
    // データ取得
    currentTime = ofxSATTime::currentTime();
    currentTime.subMonth(1);
    _prism.update(ofxSATTime(currentTime).subDay(3));
    
    // 時間のスケール(60倍速)
    timeScale = 600;
    
    // イベント通知
    _prism.setNotifier(this);
    _prism.setup();
    
    // カメラ
    cam.setFarClip(40000);
    cam.setNearClip(100);
    cam.setFov(80);
    cam.setPosition(0, 0, 16000);
    
    // ライト
    // light.enable();
    
    // 衛星軌道メッシュの初期化
    orbitMesh.setMode(OF_PRIMITIVE_LINE_STRIP); 
    
    // テクスチャ読みこみ
    texture.loadImage("earth2.jpeg");
    
    // 回転の抵抗値
    dampen = .4;
}

//--------------------------------------------------------------
void testApp::update(){
    
    // 軌道推定の時間を更新
    currentTime = ofxSATTime::currentTime().subDay(30).addSecond(ofGetElapsedTimef() * timeScale);
    sgp.update(&currentTime);
    
    // 衛星の3D座標を算出
    currentSatPos = sgp.getPos();
    
    // 衛星の軌跡を描く
    orbitMesh.addVertex(currentSatPos);
    orbitMesh.addColor(ofFloatColor(1.0, 1.0, 0.0, 0.5));
    
}

//--------------------------------------------------------------
void testApp::draw(){
    
    // カメラ開始
    cam.begin();
    ofPushMatrix();
    
    // 世界全体の回転
    ofVec3f axis;  
    float angle;  
    curRot.getRotate(angle, axis);  
    ofRotate(angle, axis.x, axis.y, axis.z);
    
    // 地球の自転角度の計算
    float sec = currentTime.getHour() * 3600 + currentTime.getMinute() * 60 + currentTime.getSecond();
    float rot = sec / 86400.0 * 360.0; // 地球が1回転する時間 = 86400(秒)
        
    // 地球の描画
    texture.bind();
    ofPushMatrix();
    ofRotateY(-rot);
    ofFill();
    ofSetColor(255, 255, 255);
    ofxSphere(0, 0, 0, 6378);
    ofPopMatrix();
    texture.unbind();
    
    // 衛星
    ofFill();
    ofSetHexColor(0xffffff);
    ofBox(currentSatPos.x, currentSatPos.y, currentSatPos.z, 250);
    
    // 衛星の軌道を描く
    orbitMesh.draw();
    
    ofPopMatrix();
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
void testApp::exit(){
    
}

//--------------------------------------------------------------
void testApp::touchDown(ofTouchEventArgs &touch){
    
    // 最後にタッチした場所を記録
    lastMouse = ofVec2f(touch.x, touch.y);
    
}

//--------------------------------------------------------------
void testApp::touchMoved(ofTouchEventArgs &touch){
    
    // クォータニオン(四元数)を用いて回転を計算
    ofVec2f mouse(touch.x, touch.y);  
    ofQuaternion yRot((touch.x-lastMouse.x)*dampen, ofVec3f(0,1,0));  
    ofQuaternion xRot((touch.y-lastMouse.y)*dampen, ofVec3f(1,0,0));  
    curRot *= yRot*xRot;  
    lastMouse = mouse;  
    
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

