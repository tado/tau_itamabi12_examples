#pragma once

#include "ofMain.h"
#include "ofxiPhone.h"
#include "ofxiPhoneExtras.h"
#include "ofxPrismSAT.h"
#include "ofxSgp.h"

class testApp : public ofxiPhoneApp {
	
public:
	void setup();
	void update();
	void draw();
	void exit();
	
	void touchDown(ofTouchEventArgs &touch);
	void touchMoved(ofTouchEventArgs &touch);
	void touchUp(ofTouchEventArgs &touch);
	void touchDoubleTap(ofTouchEventArgs &touch);
	void touchCancelled(ofTouchEventArgs &touch);

	void lostFocus();
	void gotFocus();
	void gotMemoryWarning();
	void deviceOrientationChanged(int newOrientation);

    // 最新の更新日時をサーバーから取得する関数
    void downloadData();
    
    // 衛星APIのofxPrismSATクラスへのインスタンス
    ofxPrismSAT prism;
    // ダウンロード済みの最新のデータの日付
    ofxSATTime latest;
    // 前回ダウンロードを試みた時刻
    ofxSATTime updateTime;
    // データが取得できた日時の配列
    vector<ofxSATTime> available;
    // PRISMの回転スピード(角速度)を記録
    ofVec3f rotationSpeed;
    // ライト
    ofLight light;
};


