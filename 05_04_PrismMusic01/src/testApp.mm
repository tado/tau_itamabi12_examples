#include "testApp.h"

const int DAY_LENGTH = 20; //取得する日数

//--------------------------------------------------------------
void testApp::setup(){	
    
    // iPhone初期設定
    ofRegisterTouchEvents(this);
    ofxAccelerometer.setup();
    ofxiPhoneAlerts.addListener(this);

    iPhoneSetOrientation(OFXIPHONE_ORIENTATION_LANDSCAPE_RIGHT);
    
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
    ofSetHexColor(0x000000);
    ofLine(mouseX, 0, mouseX, ofGetHeight());
    
    ofxSATTime scanTime;
    tempTime = downloadedTime[0];
    scanTime = tempTime.AddHour(mouseX / dx);
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

