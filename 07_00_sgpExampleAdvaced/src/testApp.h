#pragma once

#include "ofMain.h"
#include "ofxiPhone.h"
#include "ofxiPhoneExtras.h"
#include "ofxPrismSAT.h"
#include "ofxSgp.h"
#include "of3dPrimitives.h"

class testApp : public ofxiPhoneApp, public ofxPrismSAT::Notifier {
private:
    ofxPrismSAT _prism; // PRISM衛星のAPIをインスタンス化
    ofxSgp sgp; // ofxSgpをインスタンス化
    ofxSATTime currentTime; // 現在の時刻を格納
    ofVec3f currentSatPos; // 現在の衛星の座標を格納
    ofCamera cam; //カメラ
    ofLight light;//
    ofMesh orbitMesh; //衛星軌道を描くためのメッシュ
    float timeScale; //タイムスケール
    ofImage texture; // 地球のテクスチャ
    ofQuaternion curRot; //current state of the rotation 
    ofVec2f lastMouse;  //a place to store the mouse position so we can measure incremental change
	float dampen;    //slows down the rotation 1 = 1 degree per pixel
    float heading; // 世界全体のY軸を中心にした回転
    float pitch; // 世界全体のX軸を中心にした回転
    
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
private:
    void drawMatrix(void);
    void drawWeekly(ofxSATTime const& time);
    virtual void onNotifyTLE(void);
    virtual void onNotifyData(ofxSATTime const& param);
    virtual void onNotifyFinish(ofxSATError error);
};


