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

    // 時間のスケール(10倍速)
    timeScale = 60.0;

    // イベント通知
    _prism.setNotifier(this);
    _prism.setup();
    _prism.update();
    
    // ヒット数初期化
    bulletHit = false;
    hitCount = 0;
    
    // カメラ
    cam.setFarClip(40000);
    cam.setFov(80);
    cam.setNearClip(0.1);
   
    // 衛星軌道メッシュの初期化
    orbitMesh.setMode(OF_PRIMITIVE_LINE_STRIP); 
    
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
    orbitMesh.addVertex(currentSatPos);
    orbitMesh.addColor(ofFloatColor(1.0, 1.0, 0.0));
    
    // 弾の位置を計算
    for (int i = 0; i < bulletDist.size(); i++) {
        bulletDist[i] -= 100;

        // 衛星との衝突判定
        float dist = bulletsPos[i].distance(currentSatPos);
        if (dist < 100) {
            bulletHit = true;
        }
    }
    
    // 圏外の弾を消去
    if (bulletsPos.size() > 1000) {
        bulletsPos.pop_front();
        //camPitch.pop_front();
        //camHeading.pop_front();
        camRot.pop_front();
        bulletDist.pop_front();
    }
}

//--------------------------------------------------------------
void testApp::draw(){

    // カメラ開始
    cam.begin();
    ofPushMatrix();
    {
        //ofRotateY(camPan);
        //ofRotateX(camTilt);
        // 世界全体の回転
        ofVec3f axis;  
        float angle; 
        curRot.getRotate(angle, axis);  
        ofRotate(angle, axis.x, axis.y, axis.z);
        
        // 地球
        ofNoFill();
        ofSetColor(255, 255, 255);
        ofxSphere(0, 0, 0, 6378);
        
        // 衛星の軌道を描く
        ofSetLineWidth(1);
        orbitMesh.draw();
        
        // 衛星
        ofFill();
        if (bulletHit) {
            // 衛星に弾が当たったら、赤くする
            ofSetColor(255, 127, 127);
            // ヒットカウント増加
            hitCount++;
        } else {
            ofSetColor(255, 255, 255);
        }
        bulletHit = false;
        ofBox(currentSatPos.x, currentSatPos.y, currentSatPos.z, 200);

    
        // 弾 
        for (int i = 0; i < bulletDist.size(); i++) {
            
            // 弾の軌道を計算
            ofVec3f worldPoint = camRot[i].inverse() * ofVec3f(0, 0, bulletDist[i]);

            ofPushMatrix();
            {
                ofTranslate(worldPoint.x, worldPoint.y, worldPoint.z);       
                ofSetColor(127, 255, 255);
                ofFill();
                ofPushMatrix();
                {
                    ofRotate(-angle, axis.x, axis.y, axis.z);
                    ofEllipse(100, 0, 20, 20);
                    ofEllipse(-100, 0, 20, 20);
                }
                ofPopMatrix();
            }
            ofPopMatrix();
            bulletsPos[i] = worldPoint;
        }
    }
    ofPopMatrix();
    
    // カメラ終了
    cam.end();
    
    // ログ表示
    ofSetHexColor(0xffffff);
    string curretTimeStr = "time scale: " + ofToString(timeScale,1) + "\n" + currentTime.format("%YYYY/%MM/%DD %hh:%mm:%ss");
    ofDrawBitmapString(curretTimeStr, 10, 15);
    ofDrawBitmapString("x = " + ofToString(currentSatPos.x, 4) + "\n"
                       + "y = " + ofToString(currentSatPos.y, 4) + "\n"
                       + "z = " + ofToString(currentSatPos.z, 4), 10, 50);
    ofDrawBitmapString("Hit Count = " + ofToString(hitCount, 0), 10, 100);
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
    ofQuaternion yRot((lastMouse.x - touch.x)*dampen, ofVec3f(0,1,0));  
    ofQuaternion xRot((lastMouse.y - touch.y)*dampen, ofVec3f(1,0,0));
    curRot *= yRot*xRot;  
    lastMouse = mouse;
    
}

//--------------------------------------------------------------
void testApp::touchUp(ofTouchEventArgs &touch){
    
    bulletDist.push_back(0.0);
    bulletsPos.push_back(ofVec3f(0, 0, 0));
    camRot.push_back(curRot);
    
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

