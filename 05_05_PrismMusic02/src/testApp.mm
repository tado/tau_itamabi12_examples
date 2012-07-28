#include "testApp.h"

const int DAY_LENGTH = 14; //取得する日数

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
    
    // サウンドプレーヤーに音を読み込み
    for (int i =0; i < 6; i++) {
        player[i].loadSound("sounds/glockenspiel.caf");
        player[i].setVolume(0.2);
    }
    
    playTime = 0;
    
    // 描画関連の初期設定
    ofEnableSmoothing();
    ofSetFrameRate(60);
    ofBackground(0, 0, 0);
    ofDisableSmoothing();
}

//--------------------------------------------------------------
void testApp::update(){
    // もし日付データがダウンロードされていたら
    if(available.size() > 0) {
        // 演奏タイミングを更新
        playTime += 0.1;
        // 画面の始まできたら最初から
        if (playTime > ofGetWidth()) {
            playTime = 0;
        }
    }
}

//--------------------------------------------------------------
void testApp::draw(){
    // 取得したデータの長さの総時間(hour)を求める
    int day, hour, minute, second;
    diffTime.get(&day, &hour, &minute, &second);
    int lengthInHour = day * 24 + hour;
    int num = 0;
    
    // 取得した温度の記録を色で表現
    ofxSATTime tempTime;
    
    // グリッドのサイズを算出
    float dx, dy;
    dx = (float)ofGetWidth()/6.0;
    dy = (float)ofGetHeight()/(float)lengthInHour;
    
    int hue; //色相
    ofColor c; //面を塗る色
    
    // もし日付データがダウンロードされていたら
    if(available.size() > 0) {
        tempTime = available[0];
        float temprMin = -30, temprMax = 60;
        int hueMin = 180, hueMax = 0;
        
        for (int i = 0; i < lengthInHour; i++) {
            //MX
            hue = ofMap(TemperatureOutsideM[num].x, temprMin, temprMax, hueMin, hueMax);
            c = ofColor::fromHsb(hue, 200, 255);
            ofSetColor(c);
            ofRect(0, dy * i, dx, dy);
            //MY
            hue = ofMap(TemperatureOutsideM[num].y, temprMin, temprMax, hueMin, hueMax);
            c = ofColor::fromHsb(hue, 200, 255);
            ofSetColor(c);
            ofRect(dx, dy * i, dx, dy);
            //MZ
            hue = ofMap(TemperatureOutsideM[num].z, temprMin, temprMax, hueMin, hueMax);
            c = ofColor::fromHsb(hue, 200, 255);
            ofSetColor(c);
            ofRect(dx*2, dy * i, dx, dy);
            //PX
            hue = ofMap(TemperatureOutsideP[num].x, temprMin, temprMax, hueMin, hueMax);
            c = ofColor::fromHsb(hue, 200, 255);
            ofSetColor(c);
            ofRect(dx*3, dy * i, dx, dy);
            //PY
            hue = ofMap(TemperatureOutsideP[num].y, temprMin, temprMax, hueMin, hueMax);
            c = ofColor::fromHsb(hue, 200, 255);
            ofSetColor(c);
            ofRect(dx*4, dy * i, dx, dy);
            //PZ
            hue = ofMap(TemperatureOutsideP[num].z, temprMin, temprMax, hueMin, hueMax);
            c = ofColor::fromHsb(hue, 200, 255);
            ofSetColor(c);
            ofRect(dx*5, dy * i, dx, dy);
            
            tempTime.addHour(1); //1時間増加
            if (tempTime > available[num]) {
                num++;
            }
        }
        
        ofSetHexColor(0x000000);
        
        ofxSATTime scanTime;
        tempTime = available[0];
        //scanTime = tempTime.addHour(mouseY / dy);
        scanTime = tempTime.addHour(playTime);
        for (int i = 0; i < available.size(); i++) {
            if (scanTime <= available[i]) {
                num = i;
                break;
            }
        }
        
        // 現在タッチしている場所の情報を表示
        ofLine(0, playTime, ofGetWidth(), playTime);
        
        
        ofDrawBitmapString(available[num].format("%YYYY/%MM/%DD %hh:%mm:%ss"), 10, mouseY - 10);
        string log;
        log = "MX : " + ofToString(TemperatureOutsideM[num].x, 2) + "\n"
        + "MY : " + ofToString(TemperatureOutsideM[num].y, 2) + "\n"
        + "MZ : " + ofToString(TemperatureOutsideM[num].z, 2) + "\n"
        + "PY : " + ofToString(TemperatureOutsideP[num].x, 2) + "\n"
        + "PY : " + ofToString(TemperatureOutsideP[num].y, 2) + "\n"
        + "PZ : " + ofToString(TemperatureOutsideP[num].z, 2);
        ofDrawBitmapString(log, 10, mouseY + 20);
        
        // ---------------------------------------------------------------------
        // ここから音に関係する部分!!
        // 以前と温度の値の変化があった場合、音を鳴らす
        // ---------------------------------------------------------------------
        //MX
        if (preTemperatureOutsideM.x != TemperatureOutsideM[num].x) {
            float speed = ofMap(TemperatureOutsideM[num].x, -50, 50, 0.0, 1.0);
            player[0].setSpeed(speed);
            player[0].play();
        }
        //MY
        if (preTemperatureOutsideM.y != TemperatureOutsideM[num].y) {
            float speed = ofMap(TemperatureOutsideM[num].y, -50, 50, 0.0, 1.0);
            player[1].setSpeed(speed);
            player[1].play();
        }
        //MZ
        if (preTemperatureOutsideM.z != TemperatureOutsideM[num].z) {
            float speed = ofMap(TemperatureOutsideM[num].z, -50, 50, 0.0, 1.0);
            player[2].setSpeed(speed);
            player[2].play();
        }
        //PX
        if (preTemperatureOutsideP.x != TemperatureOutsideP[num].x) {
            float speed = ofMap(TemperatureOutsideP[num].x, -50, 50, 0.0, 1.0);
            player[3].setSpeed(speed / 2.0);
            player[3].play();
        }
        //PY
        if (preTemperatureOutsideP.y != TemperatureOutsideP[num].y) {
            float speed = ofMap(TemperatureOutsideP[num].y, -50, 50, 0.0, 1.0);
            player[4].setSpeed(speed / 2.0);
            player[4].play();
        }
        //PZ
        if (preTemperatureOutsideP.z != TemperatureOutsideP[num].z) {
            float speed = ofMap(TemperatureOutsideP[num].z, -50, 50, 0.0, 1.0);
            player[5].setSpeed(speed / 2.0);
            player[5].play();
        }
        
        // 現在の温度を記録
        preTemperatureOutsideM = TemperatureOutsideM[num];
        preTemperatureOutsideP = TemperatureOutsideP[num];
        
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
    
    // 取得された日付全てをコンソールに出力
    for (int i = 0; i < available.size(); i++) {
        cout << "Available Time[" << i << "] : " << available[i].format("%YYYY/%MM/%DD %hh:%mm:%ss") << endl;
    }
    
    // 取得した日時だけデータを取得
    for (int i = 0; i < available.size(); i++) {
        ofxSATError error;
        double value;
        string log;
        ofVec3f temprM, temprP;
        
        //データ取得
        error = prism->getSensorTemperatureOutsideMX(available[i], &value);
        temprM.x = value;
        error = prism->getSensorTemperatureOutsideMY(available[i], &value);
        temprM.y = value;
        error = prism->getSensorTemperatureOutsideMZ(available[i], &value);
        temprM.z = value;
        error = prism->getSensorTemperatureOutsidePX(available[i], &value);
        temprP.x = value;
        error = prism->getSensorTemperatureOutsidePY(available[i], &value);
        temprP.y = value;
        error = prism->getSensorTemperatureOutsidePZ(available[i], &value);
        temprP.z = value;
        
        TemperatureOutsideM.push_back(temprM);
        TemperatureOutsideP.push_back(temprP);
    }
    
    // 取得したデータの期間(差分)
    diffTime = available[available.size()-1].difference(available[0]);
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

