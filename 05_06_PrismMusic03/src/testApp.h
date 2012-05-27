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

    // 指定した日数のデータをサーバからダウンロード
    void loadDataByDays(ofxSATTime const& time, int dateLength);

    // 衛星APIのofxPrismSATクラスへのインスタンス
    ofxPrismSAT prism;
    
    // ダウンロード済みの最新のデータの日付
    ofxSATTime latest;
    
    // 前回ダウンロードを試みた時刻
    ofxSATTime updateTime;
    
    // データが取得できた日時の配列
    vector<ofxSATTime> available;

    // 新規に取得した日時の配列
    vector<ofxSATTime> downloadedTime;

    // パネルそれぞれの面の温度を格納する配列
    vector<ofVec3f> TemperatureOutsideM;
    vector<ofVec3f> TemperatureOutsideP;
    
    // ひとつ前に演奏した温度の値を格納
    ofVec3f preTemperatureOutsideM;
    ofVec3f preTemperatureOutsideP;
    
    // 取得した時間の開始と最新時間の差分
    ofxSATTimeDiff diffTime;
    
    // サウンドプレーヤーを6つぶん
    ofSoundPlayer player[6];
    
    // 演奏する時間
    float playTime;
    
    //音階を生成するための比率
    float pitchRatio[7];

};


