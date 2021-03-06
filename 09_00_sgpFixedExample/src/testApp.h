#pragma once

#include "ofMain.h"
#include "ofxiPhone.h"
#include "ofxiPhoneExtras.h"
#include "ofxPrismSAT.h"
#include "ofxSgp.h"
#include "ofxSphere.h"

class testApp : public ofxiPhoneApp, public ofxPrismSAT::Notifier {
private:
    ofxPrismSAT* _prism;    
    ofxSgp sgp;             // ofxSgpをインスタンス化
    ofxSATTime currentTime; // 現在の時刻を格納
    ofVec3f currentSatPos;  // 現在の衛星の座標を格納
    ofCamera cam;           //カメラ
    ofMesh orbitMesh;       //衛星軌道を描くためのメッシュ
    float timeScale;        //タイムスケール
    ofImage texture;        // 地球のテクスチャ
    ofQuaternion curRot;    // 現在の全体の回転角度
    ofVec2f lastMouse;      // 最後にタッチした場所
	float dampen;           // 全体の回転スピード
    
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
    
    void onNotifyTLE(ofxPrismSAT::TLERec const& tle, ofxSATTime const& time);

};


