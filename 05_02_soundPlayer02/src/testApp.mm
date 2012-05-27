#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){	
	// iPhone初期設定
	ofRegisterTouchEvents(this);
	ofxAccelerometer.setup();
	ofxiPhoneAlerts.addListener(this);
	
	ofBackgroundHex(0x000000);
	
	// サウンド初期設定
	synth.loadSound("sounds/glockenspiel.caf");
	
	synth.setVolume(0.75f);
	synth.setMultiPlay(true);
	
	//タッチポイントを初期化、画面の外に
    for (int i=0; i<NUM_SYNTH; i++) {
        touchLoc[i].set(-100, -100);
		circleSize[i] = 0;
	}

	//現在タッチされた数
    currentTouch = 0;
}


//--------------------------------------------------------------
void testApp::update(){
	// サウンド再生システムを更新
	ofSoundUpdate();
	
	for (int i=0; i<NUM_SYNTH; i++) {
        //もし円のサイズが0より大きく、画面の高さよりも小さかったら
        if(circleSize[i]>0 && circleSize[i]<ofGetHeight()){
            //円のサイズを増加させる
            circleSize[i]+=1;
        } 
	}
}

//--------------------------------------------------------------
void testApp::draw(){

	//描画設定
	ofSetHexColor(0x3399ff);
	ofNoFill();
	ofSetLineWidth(4);
	ofSetCircleResolution(64);

    //タッチした位置を取得して、円を描く
	for (int i=0; i<NUM_SYNTH; i++) {
        if(circleSize[i]>0 && circleSize[i]<ofGetHeight()){

            //拡大する円のサイズを指定して円を描く
            ofCircle(touchLoc[i].x, touchLoc[i].y, circleSize[i]);
        }
    }
}

//--------------------------------------------------------------
void testApp::exit(){
	ofSoundStopAll();
}

//--------------------------------------------------------------
void testApp::touchDown(ofTouchEventArgs &touch){

	// タッチした場所に応じて、定位、ピッチを決定し、サンプルを再生
	synth.play();
	synth.setSpeed(touch.y / ofGetHeight() * 2.0);
	synth.setPan(touch.x / ofGetWidth());
	
	//タッチした場所に円を生成
	touchLoc[currentTouch].set(touch.x, touch.y);
    circleSize[currentTouch]=1;
	
	//タッチ数更新
	currentTouch = (currentTouch + 1) % NUM_SYNTH;
}

//--------------------------------------------------------------
void testApp::touchMoved(ofTouchEventArgs &touch){
	// タッチした場所に応じて定位ピッチを決定し、現在の音を変更
	synth.setSpeed(touch.y / ofGetHeight() * 2.0);
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

