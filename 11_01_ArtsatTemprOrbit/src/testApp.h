#pragma once

#include "ofMain.h"
#include "ofxiPhone.h"
#include "ofxiPhoneExtras.h"
#include "ofxPrismSAT.h"
#include "ofxSgp.h"
#include "ofxSphere.h"

class testApp : public ofxiPhoneApp, public ofxPrismSAT::Notifier {
   
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
    
    ofxPrismSAT* prism;    // PRISM衛星のAPIをインスタンス化
    ofxSATTime beginTime; //起源の時刻
    ofxSATTime currentTime; // 現在の時刻を格納
    float timeScale; //タイムスケール    
    vector<ofxSATTime> availableTime; // データが取得できた日時の配列
    bool dataLoaded; // データの読み込みが完了したか否か
    int counter; // カウンター
    vector<float> sensorValues; // 取得したセンサーの値の配列
    
    ofxSgp sgp; // ofxSgpをインスタンス化
    ofVec3f currentSatPos; // 現在の衛星の座標を格納
    ofCamera cam; //カメラ
    ofLight light;//
    ofMesh orbitMesh; //衛星軌道を描くためのメッシュ
    ofImage texture; // 地球のテクスチャ
    ofQuaternion curRot; // 現在の地球の回転のクォータニオン
    ofVec2f lastMouse;  // 前回のマウスの位置
	float dampen;    // 地球の回転スピード
    float heading; // 世界全体のY軸を中心にした回転
    float pitch; // 世界全体のX軸を中心にした回転

private:
    virtual void onNotifyTLE(ofxSAT::TLERec const& tle, ofxSATTime const& time);
    virtual void onNotifyData(ofxSATTime const& time);
    virtual void onNotifyFinish(ofxSATError error);
    
};


