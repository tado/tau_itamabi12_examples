#include "testApp.h"

const int DAY_LENGTH = 20; //取得する日数

//--------------------------------------------------------------
void testApp::setup(){	
    // iPhone基本設定
    ofRegisterTouchEvents(this);
    ofxAccelerometer.setup();
    ofxiPhoneAlerts.addListener(this);
    glEnable(GL_DEPTH_TEST);
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    ofBackground(0,0,0);
    ofSetFrameRate(60);
    
    if ((prism = new ofxPrismSAT) != NULL) {
        prism->setNotifier(this);
        prism->setup();
        prism->update();
    }
    
    // 時間のスケール
    timeScale = 40;
    counter = 0;
    
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
    
    // データを取得可能な日時を調べる
    dataLoaded = false;
    prism->getAvailableTime(&availableTime);
    
}

//--------------------------------------------------------------
void testApp::update(){
    
    if (dataLoaded) {//もしデータのダウンロードが完了していたら
        
        // データ取得する時間を決定
        ofxSATTime b = beginTime;
        currentTime = b.addSecond(counter * timeScale);
        counter++;

        // データの最後まできたら、最初に戻る
        if (currentTime > availableTime[availableTime.size()-1]) {
            counter = 0;
        }
        
        // 軌道推定の時間を更新
        sgp.update(&currentTime);
        
        // 衛星の3D座標を算出
        // 緯度・経度・距離から、クオータニオンを使用して座標(ofVec3f)に変換
        ofQuaternion latRot, longRot, spinQuat;
        latRot.makeRotate(-sgp.getSatLatitude(), 1, 0, 0);
        longRot.makeRotate(sgp.getSatLongitude(), 0, 1, 0);
        
        // 衛星の高度に地球の半径を足して、地球中心からの距離を算出
        ofVec3f center = ofVec3f(0,0,sgp.getSatAlt() + 6378);
        currentSatPos = latRot * longRot * center;
        
    }
    
    counter++;
}

//--------------------------------------------------------------
void testApp::draw(){
    
    if (dataLoaded) {//もしデータのダウンロードが完了していたら
        
        // 直近のデータ取得可能時間を調べる
        ofxSATTime sensorPickupTime;
        
        for (int i = 0; i < availableTime.size(); i++) {
            if (availableTime[i] > currentTime) {
                sensorPickupTime = availableTime[i];
                break;
            }
        }
        
        // 衛星の情報取得に必要な変数
        double value;
        ofxSATError e;
        
        // センサーデータ読みこみここから --------------
        int lineHeight = 0;
        ofDrawBitmapString("current time: " + currentTime.format("%YYYY/%MM/%DD %hh:%mm:%ss"), 10, lineHeight+=12);
        ofDrawBitmapString("available time: " + sensorPickupTime.format("%YYYY/%MM/%DD %hh:%mm:%ss"), 10, lineHeight+=12);
        
        ofSetColor(0, 0, 255);
                
        // 各センサーの値を表示
        ofSetColor(255, 255, 255);
        //sensorValues.clear();
        
        // 外壁温度MXを取得 (取得するセンサーの種類を変更すれば、別の色になるはず)
        e = prism->getSensorTemperatureOutsideMX(sensorPickupTime, &value);
        if (value != 0.0f) sensorValues.push_back(value);
        ofDrawBitmapString("TemperatureOutsideMX = " + ofToString(sensorValues[sensorValues.size()-1], 4), 10, lineHeight+=12);
        
        // センサーデータ読みこみここまで --------------
        
        // 衛星軌道描画ここから --------------
        
        // カメラ開始
        cam.begin();
        ofPushMatrix();
        
        // 衛星の軌跡を描く
        orbitMesh.addVertex(currentSatPos);
        float col = ofMap(sensorValues[sensorValues.size()-1], -40, 20, 0.0, 1.0); //値の変換は値によって調整してみる
        orbitMesh.addColor(ofFloatColor(0.0, 1.0 - col, col));
        
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
        
        /* ------------------------
        // 地球の描画
        texture.bind();
        ofFill();
        ofSetColor(255, 255, 255);
        ofxSphere(0, 0, 0, 6378);
        texture.unbind();
        --------------------------- */
        
        // 衛星
        ofFill();
        ofSetHexColor(0xffffff);
        ofBox(currentSatPos.x, currentSatPos.y, currentSatPos.z, 250);
        
        // 衛星の軌道を描く
        orbitMesh.draw();
        
        ofPopMatrix();
        // カメラ終了
        cam.end();
        
        // 衛星軌道描画ここまで --------------
    } else {
        ofDrawBitmapString("loading data...", 10, 24);
    }
}

//--------------------------------------------------------------
void testApp::exit(){
    if (prism != NULL) {
        prism->cleanup();
        delete prism;
    }
    prism = NULL;
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

void testApp::onNotifyData(ofxSATTime const& time) {    
    
}

void testApp::onNotifyFinish(ofxSATError error)
{
    // データロード完了
    dataLoaded = true;
    beginTime = availableTime[0];
    
    for (int i = 0; i < availableTime.size(); i++) {
        cout << "Available Time[" << i << "] : " << availableTime[i].format("%YYYY/%MM/%DD %hh:%mm:%ss") << endl;
    }
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