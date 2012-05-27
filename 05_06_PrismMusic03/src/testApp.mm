#include "testApp.h"

const int DAY_LENGTH = 14; //取得する日数

//--------------------------------------------------------------
void testApp::setup(){	
    
    // iPhone初期設定
    ofRegisterTouchEvents(this);
    ofxAccelerometer.setup();
    ofxiPhoneAlerts.addListener(this);
    iPhoneSetOrientation(OFXIPHONE_ORIENTATION_LANDSCAPE_RIGHT);
    
    // サウンドプレーヤーに音を読み込み
    for (int i =0; i < 6; i++) {
        player[i].loadSound("sounds/glockenspiel.caf");
        player[i].setVolume(0.2);
        player[i].setPan(i / 6.0);
    }
    
    //音階を生成
    pitchRatio[0]= 1.0;
    pitchRatio[1]= 9.0/8.0;
    pitchRatio[2]= 5.0/4.0;
    pitchRatio[3]= 4.0/3.0;
    pitchRatio[4]= 3.0/2.0;
    pitchRatio[5]= 5.0/3.0;
    pitchRatio[6]= 15.0/8.0;
    
    playTime = 0;
    
    // 描画関連の初期設定
    ofEnableSmoothing();
    ofSetFrameRate(60);
    ofBackground(0, 0, 0);
    ofDisableSmoothing();
        
    // 現在時間を最新としておく
    latest = ofxSATTime::CurrentTime();  
    
    // まず始めに指定した日数分の最新データをダウンロード
    loadDataByDays(latest, DAY_LENGTH);       
    
    // 新規にデータを取得した日時を配列に保存
    ofxSATTime temp;
    temp = latest.SubDay(DAY_LENGTH);
    for (int i = 0; i < available.size(); i++) {
        if (available[i] >= temp) {
            downloadedTime.push_back(available[i]);
        }
    }
    
    // 取得した日時だけデータを取得
    for (int i = 0; i < downloadedTime.size(); i++) {
        ofxSATError error;
        double value;
        string log;
        ofVec3f temprM, temprP;
        
        //データ取得
        error = prism.GetSensorTemperatureOutsideMX(downloadedTime[i], &value);
        temprM.x = value;
        error = prism.GetSensorTemperatureOutsideMY(downloadedTime[i], &value);
        temprM.y = value;
        error = prism.GetSensorTemperatureOutsideMZ(downloadedTime[i], &value);
        temprM.z = value;
        error = prism.GetSensorTemperatureOutsidePX(downloadedTime[i], &value);
        temprP.x = value;
        error = prism.GetSensorTemperatureOutsidePY(downloadedTime[i], &value);
        temprP.y = value;
        error = prism.GetSensorTemperatureOutsidePZ(downloadedTime[i], &value);
        temprP.z = value;
        
        TemperatureOutsideM.push_back(temprM);
        TemperatureOutsideP.push_back(temprP);
    }
    
    // 取得したデータの期間(差分)
    diffTime = downloadedTime[downloadedTime.size()-1].Difference(downloadedTime[0]);
}

//--------------------------------------------------------------
void testApp::update(){
    // 演奏タイミングを更新
    playTime += 0.1;
    // 画面の始まできたら最初から
    if (playTime > ofGetWidth()) {
        playTime = 0;
    }
}

//--------------------------------------------------------------
void testApp::draw(){
    // 取得したデータの長さの総時間(hour)を求める
    int day, hour, minute, second;
    diffTime.Get(&day, &hour, &minute, &second);
    int lengthInHour = day * 24 + hour;
    
    // グリッドのサイズを算出
    float dx, dy;
    dx = (float)ofGetWidth()/(float)lengthInHour;
    dy = (float)ofGetHeight()/6.0;
    
    // 取得した温度の記録を色で表現
    ofxSATTime tempTime;
    int num = 0;
    int hue; //色相
    ofColor c; //面を塗る色
    tempTime = downloadedTime[0];
    float temprMin = -30, temprMax = 60;
    int hueMin = 180, hueMax = 0;
    
    for (int i = 0; i < lengthInHour; i++) {
        //MX
        hue = ofMap(TemperatureOutsideM[num].x, temprMin, temprMax, hueMin, hueMax);
        c = ofColor::fromHsb(hue, 200, 255);
        ofSetColor(c);
        ofRect(dx * i, 0, dx, dy);
        //MY
        hue = ofMap(TemperatureOutsideM[num].y, temprMin, temprMax, hueMin, hueMax);
        c = ofColor::fromHsb(hue, 200, 255);
        ofSetColor(c);
        ofRect(dx * i, dy, dx, dy);
        //MZ
        hue = ofMap(TemperatureOutsideM[num].z, temprMin, temprMax, hueMin, hueMax);
        c = ofColor::fromHsb(hue, 200, 255);
        ofSetColor(c);
        ofRect(dx * i, dy * 2, dx, dy);
        //PX
        hue = ofMap(TemperatureOutsideP[num].x, temprMin, temprMax, hueMin, hueMax);
        c = ofColor::fromHsb(hue, 200, 255);
        ofSetColor(c);
        ofRect(dx * i, dy * 3, dx, dy);
        //PY
        hue = ofMap(TemperatureOutsideP[num].y, temprMin, temprMax, hueMin, hueMax);
        c = ofColor::fromHsb(hue, 200, 255);
        ofSetColor(c);
        ofRect(dx * i, dy * 4, dx, dy);
        //PZ
        hue = ofMap(TemperatureOutsideP[num].z, temprMin, temprMax, hueMin, hueMax);
        c = ofColor::fromHsb(hue, 200, 255);
        ofSetColor(c);
        ofRect(dx * i, dy * 5, dx, dy);
        
        tempTime.AddHour(1); //1時間増加
        if (tempTime > downloadedTime[num]) {
            num++;
        }
    }
        
    // 現在タッチしている場所の情報を表示
    ofSetHexColor(0xffffff);
    ofLine(playTime, 0, playTime, ofGetHeight());
    
    ofxSATTime scanTime;
    tempTime = downloadedTime[0];
    scanTime = tempTime.AddHour(playTime / dx);
    for (int i = 0; i < downloadedTime.size(); i++) {
        if (scanTime <= downloadedTime[i]) {
            num = i;
            break;
        }
    }
    
    ofDrawBitmapString(downloadedTime[num].Format("%YYYY/%MM/%DD %hh:%mm:%ss"), 10, 15);

    string log;
    log = "MX : " + ofToString(TemperatureOutsideM[num].x, 2) + "\n"
    + "MY : " + ofToString(TemperatureOutsideM[num].y, 2) + "\n"
    + "MZ : " + ofToString(TemperatureOutsideM[num].z, 2) + "\n"
    + "PY : " + ofToString(TemperatureOutsideP[num].x, 2) + "\n"
    + "PY : " + ofToString(TemperatureOutsideP[num].y, 2) + "\n"
    + "PZ : " + ofToString(TemperatureOutsideP[num].z, 2);
    
    ofDrawBitmapString(log, 10, 30);
        
    // ---------------------------------------------------------------------
    // ここから音に関係する部分!!
    // 以前と温度の値の変化があった場合、音を鳴らす
    // ---------------------------------------------------------------------
    //MX
    if (preTemperatureOutsideM.x != TemperatureOutsideM[num].x) {
        float volume = ofMap(TemperatureOutsideM[num].x, -30, 50, 0.0, 1.0);
        player[0].setSpeed(pitchRatio[(int)ofRandom(7)] * 0.2);
        player[0].setVolume(volume);
        player[0].play();
    }
    //MY
    if (preTemperatureOutsideM.y != TemperatureOutsideM[num].y) {
        float volume = ofMap(TemperatureOutsideM[num].y, -30, 50, 0.0, 1.0);
        player[1].setSpeed(pitchRatio[(int)ofRandom(7)] * 0.2);
        player[1].setVolume(volume);
        player[1].play();
    }
    //MZ
    if (preTemperatureOutsideM.z != TemperatureOutsideM[num].z) {
        float volume = ofMap(TemperatureOutsideM[num].z, -30, 50, 0.0, 1.0);
        player[2].setSpeed(pitchRatio[(int)ofRandom(7)] * 0.2);
        player[2].setVolume(volume);
        player[2].play();
    }
    //PX
    if (preTemperatureOutsideP.x != TemperatureOutsideP[num].x) {
        float volume = ofMap(TemperatureOutsideP[num].x, -30, 50, 0.0, 1.0);
        player[3].setSpeed(pitchRatio[(int)ofRandom(7)] * 0.4);
        player[3].setVolume(volume);
        player[3].play();
    }
    //PY
    if (preTemperatureOutsideP.y != TemperatureOutsideP[num].y) {
        float volume = ofMap(TemperatureOutsideP[num].y, -30, 50, 0.0, 1.0);
        player[4].setSpeed(pitchRatio[(int)ofRandom(7)] * 0.4);
        player[4].setVolume(volume);
        player[4].play();
    }
    //PZ
    if (preTemperatureOutsideP.z != TemperatureOutsideP[num].z) {
        float volume = ofMap(TemperatureOutsideP[num].z, -30, 50, 0.0, 1.0);
        player[5].setSpeed(pitchRatio[(int)ofRandom(7)] * 0.4);
        player[5].setVolume(volume);
        player[5].play();
    }

    // 現在の温度を記録
    preTemperatureOutsideM = TemperatureOutsideM[num];
    preTemperatureOutsideP = TemperatureOutsideP[num];
}

//--------------------------------------------------------------
// loadDays()
// 指定した日数の最新データを取得
//--------------------------------------------------------------

void testApp::loadDataByDays(ofxSATTime const& time, int dateLength){
    
    ofxSATTime temp;
    int prev;
    int i;
    ofxSATError error;
    
    if ((error = prism.GetAvailableTime(&available)) == SATERROR_OK) {
        temp = time;
        temp.SubDay(dateLength);
        while (temp <= time && error == SATERROR_OK) {
            
            for (i = 0; i < available.size(); ++i) {
                if (temp.EqualsDate(available[i])) {
                    temp.AddDay(1);
                    break;
                }
            }
            if (i >= available.size()) {
                error = prism.GetSensorTimeRTC(temp, NULL, NULL);
                switch (error) {
                    case SATERROR_OK:
                    case SATERROR_NO_RESULT:
                        prev = available.size();
                        if ((error = prism.GetAvailableTime(&available)) == SATERROR_OK) {
                            if (available.size() <= prev) {
                                temp.AddDay(1);
                            }
                        }
                        break;
                    default:
                        break;
                }
            }
        }
    }
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

