#pragma once

#include "ofMain.h"
#include "ofxiPhone.h"
#include "ofxiPhoneExtras.h"
#include "ofxPrismSAT.h"
#include "ofxSgp.h"

class testApp : public ofxiPhoneApp {
private:
	// 衛星APIのofxPrismSATクラスへのインスタンス
    ofxPrismSAT _prism;
	
	// 衛星外面の気温を記録する変数
	double _temperatureOutsideMX; // -X面
	double _temperatureOutsidePX; // +X面
	double _temperatureOutsideMY; // -Y面
	double _temperatureOutsidePY; // +Y面
	double _temperatureOutsideMZ; // -Z面
	double _temperatureOutsidePZ; // +Z面
	
	// カメラ
	ofEasyCam _cam;
	
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
};


