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
    ofNoFill();
    glEnable(GL_DEPTH_TEST);
    
    // ひとまず、現在時間を最新としておく
    latest = ofxSATTime::CurrentTime();  
    // 初回は確実にダウンロードさせたいので、前回の更新時刻を時間の原点(紀元)にしておく
    updateTime = ofxSATTime::EpochTime();
    
    //ライトON
    light.enable();
    
    // まず始めに最新データをダウンロード
    downloadData();

}

//--------------------------------------------------------------
void testApp::update(){
    // 定期的にダウンロードを試みる
    downloadData();
}

//--------------------------------------------------------------
void testApp::draw(){
    // 色指定
    ofSetHexColor(0xffffff);
    
    // 回転スピードをBoxで視覚化
    ofPushMatrix();
    ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
    
    // 取得した角速度でBoxを回転
    ofRotateX(rotationSpeed.x * ofGetElapsedTimef());
    ofRotateY(rotationSpeed.y * ofGetElapsedTimef());
    ofRotateZ(rotationSpeed.z * ofGetElapsedTimef());
    ofBox(0, 0, 0, 150);
    
    ofPopMatrix();
    
    // データをテキストで表示
    ofDrawBitmapString(latest.Format("%YYYY/%MM/%DD %hh:%mm:%ss"), 10, 15);
    ofDrawBitmapString("Gyro X = " + ofToString(rotationSpeed.x, 4) , 10, 15 * 2);
    ofDrawBitmapString("Gyro Y = " + ofToString(rotationSpeed.y, 4) , 10, 15 * 3);
    ofDrawBitmapString("Gyro Z = " + ofToString(rotationSpeed.z, 4) , 10, 15 * 4);
    
}

//--------------------------------------------------------------
// downloadData()
// PRISMの最新のデータを取得するための関数
// 30秒おきにデータを取得する
//--------------------------------------------------------------
void testApp::downloadData(){
    ofxSATTime current;
    
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
        
        // -----------------------------------------------------------------------------
        // ジャイロ情報が最後に取得された日時のデータを取得
        double value;
        ofxSATError error;
        // データを取得した日時を後ろから走査
        for (int i = available.size()-1; i > 0; i--) {
            error = prism.GetSensorGyroX(available[i], &value);
            rotationSpeed.x = value;
            error = prism.GetSensorGyroY(available[i], &value);
            rotationSpeed.y = value;
            error = prism.GetSensorGyroZ(available[i], &value);
            rotationSpeed.z = value;
            
            //もし全てのデータが0でなかったら(つまりデータがあったら)、そのデータを採用
            if (rotationSpeed.x != 0 && rotationSpeed.y != 0 && rotationSpeed.z != 0) {
                latest = available[i];
                break;
            }
        }
        // -----------------------------------------------------------------------------
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

