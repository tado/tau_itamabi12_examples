#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){	

	// iPhone初期設定
	ofRegisterTouchEvents(this);
	ofxAccelerometer.setup();
	ofxiPhoneAlerts.addListener(this);
	iPhoneSetOrientation(OFXIPHONE_ORIENTATION_LANDSCAPE_RIGHT);

	// 描画関連の初期設定
    ofEnableSmoothing();
    ofEnableAlphaBlending();
    ofSetFrameRate(60);
	ofBackground(0, 0, 0);
	glEnable(GL_DEPTH_TEST);
	ofSetRectMode(OF_RECTMODE_CENTER);
	
	// カメラ初期化
	_cam.setDistance(300);
	
}

//--------------------------------------------------------------
void testApp::update(){

	// 衛星の情報取得に必要な変数
	double value;
	ofxSATError error;
	ofxSATTime lastAvailable;
	
	// 利用可能なデータの中で最新のものを取得
	vector<ofxSATTime> available;
	_prism.GetAvailableTime(&available);
	lastAvailable = available[available.size()-1];
	
	/*
	 * ARTSAT APIを使用して外壁の温度を取得
	 * (+X, -X, +Y, -Y, +Z, -Z) の6つ
	 */
	
	// -X面
	error = _prism.GetSensorTemperatureOutsideMX(lastAvailable, &value);
	_temperatureOutsideMX = value;
	// +X面
	error = _prism.GetSensorTemperatureOutsidePX(lastAvailable, &value);
	_temperatureOutsidePX = value;
	// -Y面
	error = _prism.GetSensorTemperatureOutsideMY(lastAvailable, &value);
	_temperatureOutsideMY = value;
	// +X面
	error = _prism.GetSensorTemperatureOutsidePY(lastAvailable, &value);
	_temperatureOutsidePZ = value;
	// -X面
	error = _prism.GetSensorTemperatureOutsideMZ(lastAvailable, &value);
	_temperatureOutsideMZ = value;
	// +X面
	error = _prism.GetSensorTemperatureOutsidePZ(lastAvailable, &value);
	_temperatureOutsidePZ = value;
	
}

//--------------------------------------------------------------
void testApp::draw(){

	/*
	 * 取得した温度をもとに、立方体の面を塗りわける
	 * カメラを使用してドラッグ操作で視点を移動
	 */
	

	int hue; //色相
	ofColor c; //面を塗る色

	_cam.begin();	// カメラ開始
	{
		// +X面
		hue = ofMap(_temperatureOutsideMX, -10.0, 10, 128, 0);
		c = ofColor::fromHsb(hue, 200, 255);
		ofSetColor(c);
		ofPushMatrix();
		{
			ofTranslate(0, 0, 50);
			ofRect(0, 0, 100, 100);
			ofTranslate(0, 0, 10);
		}
		ofPopMatrix();
		
		// -X面
		hue = ofMap(_temperatureOutsidePX, -10.0, 10, 128, 0);
		c = ofColor::fromHsb(hue, 200, 255);
		ofSetColor(c);
		ofPushMatrix();
		{
			ofTranslate(0, 0, -50);
			ofRect(0, 0, 100, 100);
		}
		ofPopMatrix();
		

		// +Y面
		hue = ofMap(_temperatureOutsideMY, -10.0, 10, 128, 0);
		c = ofColor::fromHsb(hue, 200, 255);
		ofSetColor(c);
		ofPushMatrix();
		{
			ofRotate(90, 0, 1, 0);
			ofTranslate(0, 0, 50);
			ofRect(0, 0, 100, 100);
		}
		ofPopMatrix();
		
		// -Y面
		hue = ofMap(_temperatureOutsidePY, -10.0, 10, 128, 0);
		c = ofColor::fromHsb(hue, 200, 255);
		ofSetColor(c);
		ofPushMatrix();
		{
			ofRotate(90, 0, 1, 0);
			ofTranslate(0, 0, -50);
			ofRect(0, 0, 100, 100);
		}
		ofPopMatrix();
		
		// +Z面
		hue = ofMap(_temperatureOutsideMZ, -10.0, 10, 128, 0);
		c = ofColor::fromHsb(hue, 200, 255);
		ofSetColor(c);
		ofPushMatrix();
		{
			ofRotate(90, 1, 0, 0);
			ofTranslate(0, 0, 50);
			ofRect(0, 0, 100, 100);
		}
		ofPopMatrix();
		
		// -Z面
		hue = ofMap(_temperatureOutsidePZ, -10.0, 10, 128, 0);
		c = ofColor::fromHsb(hue, 200, 255);
		ofSetColor(c);
		ofPushMatrix();
		{
			ofRotate(90, 1, 0, 0);
			ofTranslate(0, 0, -50);
			ofRect(0, 0, 100, 100);
		}
		ofPopMatrix();
	}
	_cam.end();		// カメラ終了
	
	// テキストで表示
	ofSetHexColor(0xffffff);
	int lineHeight = 15;
	ofDrawBitmapString("-X = " + ofToString(_temperatureOutsideMX, 4) + " C", 20, lineHeight*1);
	ofDrawBitmapString("+X = " + ofToString(_temperatureOutsidePX, 4) + " C", 20, lineHeight*2);
	ofDrawBitmapString("-Y = " + ofToString(_temperatureOutsideMY, 4) + " C", 20, lineHeight*3);
	ofDrawBitmapString("+Y = " + ofToString(_temperatureOutsidePY, 4) + " C", 20, lineHeight*4);
	ofDrawBitmapString("-Z = " + ofToString(_temperatureOutsideMZ, 4) + " C", 20, lineHeight*5);
	ofDrawBitmapString("+Z = " + ofToString(_temperatureOutsidePZ, 4) + " C", 20, lineHeight*6);

}

//--------------------------------------------------------------
void testApp::exit(){

}

//--------------------------------------------------------------
void testApp::touchDown(ofTouchEventArgs &touch){

}

//--------------------------------------------------------------
void testApp::touchMoved(ofTouchEventArgs &touch){

}

//--------------------------------------------------------------
void testApp::touchUp(ofTouchEventArgs &touch){

}

//--------------------------------------------------------------
void testApp::touchDoubleTap(ofTouchEventArgs &touch){

}

//--------------------------------------------------------------
void testApp::lostFocus(){

}

//--------------------------------------------------------------
void testApp::gotFocus(){

}

//--------------------------------------------------------------
void testApp::gotMemoryWarning(){

}

//--------------------------------------------------------------
void testApp::deviceOrientationChanged(int newOrientation){

}


//--------------------------------------------------------------
void testApp::touchCancelled(ofTouchEventArgs& args){

}

