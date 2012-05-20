#include "testApp.h"

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
    
    // ひとまず、現在時間を最新としておく
    latest = ofxSATTime::CurrentTime();  
    // 初回は確実にダウンロードさせたいので、前回の更新時刻を時間の原点(紀元)にしておく
    updateTime = ofxSATTime::EpochTime();

}

//--------------------------------------------------------------
void testApp::update(){
    // 定期的にダウンロードを試みる
    downloadData();
}

//--------------------------------------------------------------
void testApp::draw(){
    // テキストで表示
    ofSetHexColor(0xffffff);
    ofDrawBitmapString(latest.Format("%YYYY/%MM/%DD %hh:%mm:%ss"), 10, 15);
}

//--------------------------------------------------------------
// downloadData()
// PRISMの最新のデータを取得するための関数
// 30秒おきにデータを取得する
//--------------------------------------------------------------
void testApp::downloadData(){
    ofxSATTime current;
    vector<ofxSATTime> available;
    
    // 現在時刻を取得して
    current = ofxSATTime::CurrentTime();
    // 前回ダウンロードを試みた時刻との差を計算し、
    // 30 秒以上経過していたら次のダウンロードを試みる
    if (current.Difference(updateTime).AsTime_t() >= 30) {
        // 現在時刻を前回のダウンロード時刻として記録する
        updateTime = current;
        
        // まずは既にダウンロード済みのデータの有効な日付を取得し
        // 最新のデータの日付を取得する
        prism.GetAvailableTime(&available);
        if (available.size() > 0) {
            latest = available.back();
        }
        // 最新のデータの日付が今日の日付と一致している場合はダウンロードを試みない
        // 今日の日付のデータが無い場合は、ダウンロードを試みる
        if (!latest.EqualsDate(current)) {
            cout << current.Format("try %YYYY/%MM/%DD %hh:%mm:%ss") << endl;
            cout << "downloading..." << endl;
            
            // 適当なセンサ名で今日のデータのダウンロードを試みる
            prism.GetSensorTimeRTC(current, NULL);
        }
        
        // もう一度、ダウンロード済みのデータの有効な日付を取得し
        // 最新のデータの日付を取得する
        prism.GetAvailableTime(&available);
        if (available.size() > 0) {
            latest = available.back();
        }
        cout << latest.Format("latest = %YYYY/%MM/%DD %hh:%mm:%ss") << endl;
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

