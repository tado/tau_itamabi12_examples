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
    ofMesh orbitMesh; //衛星軌道を描くためのメッシュ
    float timeScale; //タイムスケール
   
    deque<float> bulletDist; //弾の原点からの距離
    deque<ofVec3f> bulletsPos; // 弾の座標
    deque<float> camHeading; // 弾を打ったときのY軸角度
    deque<float> camPitch; //弾を打ったときのZ軸角度
    //deque<ofVec3f> camLookAt;
    deque<ofQuaternion> camRot; //弾を打ったときの回転角度
    
    bool bulletHit; // 弾が当たったか?
    int hitCount; // 弾が当たった回数
    ofQuaternion curRot; // 現在の回転角度
    ofQuaternion yRot;
    ofQuaternion xRot;
    ofVec2f lastMouse;  // 最後にタッチした場所
	float dampen;    // 回転の摩擦力
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


