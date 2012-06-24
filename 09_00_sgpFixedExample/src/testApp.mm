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
    
    if ((_prism = new ofxPrismSAT) != NULL) {
        _prism->setNotifier(this);
        _prism->setup();
        _prism->update();
    }
    
    // 時間のスケール
    timeScale = 100;
    
    // カメラ
    cam.setFarClip(40000);
    cam.setNearClip(100);
    cam.setFov(60);
    cam.setPosition(0, 0, 20000);
    
    // 衛星軌道メッシュの初期化
    orbitMesh.setMode(OF_PRIMITIVE_LINE_STRIP); 
    
    // テクスチャ読みこみ
    texture.loadImage("earth_fixed.jpg");
    
    // 回転の抵抗値
    dampen = .4;
    
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

    // 衛星の高度に地球の半径を足して、地球中心からの距離を算出
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
    ofPushMatrix();
    
    // 世界全体の回転
    ofVec3f axis;  
    float angle;  
    curRot.getRotate(angle, axis);  
    ofRotate(angle, axis.x, axis.y, axis.z);
    
    // 地球の自転角度の計算
    // 現在の時刻を秒に換算
    float curTimeInSec = currentTime.getHour() * 3600 + currentTime.getMinute() * 60 + currentTime.getSecond();
    // 現在の地球の自転角度を計算
    float rot = curTimeInSec / 86400.0 * 360.0;
    ofRotateY(rot);
    
    // 地球の描画
    texture.bind();
    ofFill();
    ofSetColor(255, 255, 255);
    ofxSphere(0, 0, 0, 6378);
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