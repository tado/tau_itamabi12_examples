#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){	
	// register touch events
	ofRegisterTouchEvents(this);
	
	// initialize the accelerometer
	ofxAccelerometer.setup();
	
	//iPhoneAlerts will be sent to this.
	ofxiPhoneAlerts.addListener(this);
	
	//If you want a landscape oreintation 
	//iPhoneSetOrientation(OFXIPHONE_ORIENTATION_LANDSCAPE_RIGHT);
	
	ofSetFrameRate(30);
	ofBackground(127,127,127);
	
	//連番がふられた画像を順番に読み込み
	for (int i = 0; i < FRAMENUM; i++) {
		//ファイル名を一時的に格納する文字列
		char char1[32];
		//連番のファイル名を生成
		sprintf(char1, "images/myAnim%04d.png", i+1);
		//画像をofImageのインスタンスの配列に読み込み
		myImage[i].loadImage(char1);
	}
	//再生フレームを0から始める
	currentFrame = 0;
}

//--------------------------------------------------------------
void testApp::update(){
	
}

//--------------------------------------------------------------
void testApp::draw(){
	//現在のフレームの画像を表示
	myImage[currentFrame].draw(0, 0);
	
	//フレーム数をひとつ進める
	currentFrame++;
	//もし指定した枚数よりフレーム数が大きくなったら
	//フレーム数をリセット
	if (currentFrame > FRAMENUM - 1) {
		currentFrame = 0;
	}
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

