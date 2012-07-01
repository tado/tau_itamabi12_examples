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
    ofxSATTime epochTime; //起源の時刻
    ofxSATTime currentTime; // 現在の時刻を格納
    float timeScale; //タイムスケール    
    vector<ofxSATTime> availableTime; // データが取得できた日時の配列
    bool dataLoaded; // データの読み込みが完了したか否か
    int counter; // カウンター

private:
    virtual void onNotifyTLE(ofxSAT::TLERec const& tle, ofxSATTime const& time);
    virtual void onNotifyData(ofxSATTime const& time);
    virtual void onNotifyFinish(ofxSATError error);
    
};


