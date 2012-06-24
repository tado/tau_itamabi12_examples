#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){	
    // iPhone基本設定
    ofRegisterTouchEvents(this);
    ofxAccelerometer.setup();
    ofxiPhoneAlerts.addListener(this);
    ofEnableAlphaBlending();
    ofEnableSmoothing();
    iPhoneSetOrientation(OFXIPHONE_ORIENTATION_LANDSCAPE_RIGHT);

    ofBackground(0,0,0);
    ofSetFrameRate(40);
    
    if ((_prism = new ofxPrismSAT) != NULL) {
        _prism->setNotifier(this);
        _prism->setup();
        _prism->update();
    }
    
    // 時間のスケール
    timeScale = 1000;
    
    // カメラ
    cam.setFarClip(100000);
    cam.setNearClip(0);
    cam.setFov(60);
    
    // カメラの位置を、多摩美(八王子)の緯度、経度から計算 
    ofQuaternion latRot, longRot, spinQuat;
    latRot.makeRotate(-35.611946, 1, 0, 0);
    longRot.makeRotate(139.350433, 0, 1, 0);
    ofVec3f center = ofVec3f(0,0,6378);
    ofVec3f look = ofVec3f(0,0,10000);
    camPos = latRot * longRot * center;
    cam.setPosition(camPos.x, camPos.y, camPos.z);
    
    ofVec3f lookat = latRot * longRot * look;
    cam.lookAt(lookat);
    
    // 衛星軌道メッシュの初期化
    orbitMesh.setMode(OF_PRIMITIVE_LINE_STRIP); 
    
    // テクスチャ読みこみ
    texture.loadImage("earth_fixed.jpg");
    
    // 回転の抵抗値
    dampen = .2;
    
}

//--------------------------------------------------------------
void testApp::update(){
    // 衛星アップデート
    _prism->update();
    
    // 軌道推定の時間を更新
    currentTime = ofxSATTime::currentTime().addSecond(ofGetElapsedTimef() * timeScale);
    sgp.update(&currentTime);
    
    // 衛星の3D座標を算出
    // 緯度・経度・距離から、クオータニオンを使用して座標(ofVec3f)に変換
    ofQuaternion latRot, longRot, spinQuat;
    latRot.makeRotate(-sgp.getSatLatitude(), 1, 0, 0);
    longRot.makeRotate(sgp.getSatLongitude(), 0, 1, 0);
    ofVec3f center = ofVec3f(0,0,sgp.getSatAlt() + 6378);

    currentSatPos = latRot * longRot * center;

    // 衛星の軌跡を描く
    orbitMesh.addVertex(currentSatPos);
    orbitMesh.addColor(ofFloatColor(1.0, 1.0, 0.0));
    
}

//--------------------------------------------------------------
void testApp::draw(){
    
    // カメラ開始
    cam.begin();
    
    // 方角を表示
    ofPushMatrix();
    ofTranslate(camPos.x, camPos.y, camPos.z);
    ofRotateY(139 + 45/60.0);
    ofRotateX(-35 + 40./60.0);
    ofNoFill();
    for (int i = 0; i < 36; i++) {
        ofRotateZ(360/36.0);
        ofSetColor(31, 31, 31);
        ofLine(-100000, 0, 10, 100000, 0, 10);
        ofSetColor(255, 255, 255);
    }
    for (int i = 0; i < 12; i++) {
        ofRotateZ(360/12.0);
        ofSetColor(63, 63, 63);
        ofLine(-100000, 0, 10, 100000, 0, 10);
        ofSetColor(255, 255, 255);
    }
    ofPopMatrix();
    
    glEnable(GL_DEPTH_TEST);
    
    // 地球の描画
    texture.bind();
    ofFill();
    ofSetColor(255, 255, 255);
    ofxSphere(0, 0, 0, 6378);
    texture.unbind();
    
    // 衛星
    ofFill();
    ofSetHexColor(0xffffff);
    ofBox(currentSatPos.x, currentSatPos.y, currentSatPos.z, 10);
    
    // 衛星の軌道を描く
    orbitMesh.draw();
    
    // カメラ終了
    cam.end();
    
    glDisable(GL_DEPTH_TEST);
    
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
    
    // 最後にタッチした場所を記録
    lastMouse = ofVec2f(touch.x, touch.y);
    
}

//--------------------------------------------------------------
void testApp::touchMoved(ofTouchEventArgs &touch){

    // カメラの向きを変更
    ofVec2f mouse(touch.x, touch.y);  
    float tilt = (touch.x-lastMouse.x) * dampen;
    float pan = (touch.y-lastMouse.y) * dampen;
    
    cam.pan(pan);
    cam.tilt(-tilt);
    
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