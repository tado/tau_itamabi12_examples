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
    ofEasyCam cam; //カメラ
    ofMesh orbitMesh; //衛星軌道を描くためのメッシュ
    float timeScale; //タイムスケール
    
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


