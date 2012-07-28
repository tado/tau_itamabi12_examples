#pragma once

#include "ofMain.h"
#include "ofxiPhone.h"
#include "ofxiPhoneExtras.h"
#include "ofxPrismSAT.h"

class testApp : public ofxiPhoneApp, public ofxPrismSAT::Notifier {
    
private:
	// 衛星APIのofxPrismSATクラスへのインスタンス
    ofxPrismSAT * prism;
    
    // 取得された日時の配列
    vector<ofxSATTime> available;

    // 最後にデータを取得した日時
	ofxSATTime lastAvailable;
	
	// 衛星外面の気温を記録する変数
	double _temperatureOutsideMX; // -X面
	double _temperatureOutsidePX; // +X面
	double _temperatureOutsideMY; // -Y面
	double _temperatureOutsidePY; // +Y面
	double _temperatureOutsideMZ; // -Z面
	double _temperatureOutsidePZ; // +Z面
	
	// カメラ
	ofEasyCam cam;
	
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
    
    virtual void onNotifyTLE(ofxSAT::TLERec const& tle, ofxSATTime const& time);
    virtual void onNotifyData(ofxSATTime const& time);
    virtual void onNotifyFinish(ofxSATError error);
};


