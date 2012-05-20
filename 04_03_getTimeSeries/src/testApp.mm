#include "testApp.h"

const int DAY_LENGTH = 6;

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
    ofNoFill();
    
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
}

//--------------------------------------------------------------
void testApp::update(){

}

//--------------------------------------------------------------
void testApp::draw(){
    // 取得した日時だけデータを取得、画面に表示
    ofSetHexColor(0xffffff);
    for (int i = 0; i < downloadedTime.size(); i++) {
        ofxSATError error;
        double value;
        string log;

        //データ取得
        error = prism.GetSensorTemperatureMainOBC(downloadedTime[i], &value);
        
        //画面に文字で表示
        log = downloadedTime[i].Format("[%MM/%DD %hh:%mm]") 
        + "TemperMainOBC = " + ofToString(value, 2);
        
        ofDrawBitmapString(log, 10, 15*(i+1));
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

