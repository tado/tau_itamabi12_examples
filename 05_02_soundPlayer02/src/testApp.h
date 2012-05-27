#pragma once

#include "ofMain.h"
#include "ofxiPhone.h"
#include "ofxiPhoneExtras.h"

#define NUM_SYNTH 20 //最大発音数(20)

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
	
	//サウンドプレーヤー
	ofSoundPlayer  synth;
	//円の大きさ情報の配列
    float circleSize[NUM_SYNTH];
    //タッチした座標情報の配列
    ofPoint touchLoc[NUM_SYNTH];
	//現在タッチした数(0〜20)
    int currentTouch;
};


