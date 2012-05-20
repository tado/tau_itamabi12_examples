#include "testApp.h"

const int DAY_LENGTH = 20; //取得する日数

//--------------------------------------------------------------
void testApp::setup(){	
    
    // iPhone初期設定
    ofRegisterTouchEvents(this);
    ofxAccelerometer.setup();
    ofxiPhoneAlerts.addListener(this);
    //iPhoneSetOrientation(OFXIPHONE_ORIENTATION_LANDSCAPE_RIGHT);
    
    // 描画関連の初期設定
    ofEnableSmoothing();
    ofSetFrameRate(60);
    ofBackground(0, 0, 0);
    
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
    dx = (float)ofGetWidth()/6.0;
    dy = (float)ofGetHeight()/(float)lengthInHour;
    
    // 取得した温度の記録を色で表現
    ofxSATTime tempTime;
    tempTime = downloadedTime[0];
    int num = 0;
    int hue; //色相
    ofColor c; //面を塗る色
    float temprMin = -30, temprMax = 60;
    
    for (int i = 0; i < lengthInHour; i++) {
        //MX
        hue = ofMap(TemperatureOutsideM[num].x, temprMin, temprMax, 180, 0);
        c = ofColor::fromHsb(hue, 200, 255);
        ofSetColor(c);
        ofRect(0, dy * i, dx, dy);
        //MY
        hue = ofMap(TemperatureOutsideM[num].y, temprMin, temprMax, 180, 0);
        c = ofColor::fromHsb(hue, 200, 255);
        ofSetColor(c);
        ofRect(dx, dy * i, dx, dy);
        //MZ
        hue = ofMap(TemperatureOutsideM[num].z, temprMin, temprMax, 180, 0);
        c = ofColor::fromHsb(hue, 200, 255);
        ofSetColor(c);
        ofRect(dx*2, dy * i, dx, dy);
        //PX
        hue = ofMap(TemperatureOutsideP[num].x, temprMin, temprMax, 180, 0);
        c = ofColor::fromHsb(hue, 200, 255);
        ofSetColor(c);
        ofRect(dx*3, dy * i, dx, dy);
        //PY
        hue = ofMap(TemperatureOutsideP[num].y, temprMin, temprMax, 180, 0);
        c = ofColor::fromHsb(hue, 200, 255);
        ofSetColor(c);
        ofRect(dx*4, dy * i, dx, dy);
        //PZ
        hue = ofMap(TemperatureOutsideP[num].z, temprMin, temprMax, 180, 0);
        c = ofColor::fromHsb(hue, 200, 255);
        ofSetColor(c);
        ofRect(dx*5, dy * i, dx, dy);
        
        tempTime.AddHour(1); //1時間増加
        if (tempTime > downloadedTime[num]) {
            num++;
        }
    }  
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

