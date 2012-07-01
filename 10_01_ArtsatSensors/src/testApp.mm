#include "testApp.h"

const int DAY_LENGTH = 20; //取得する日数

//--------------------------------------------------------------
void testApp::setup(){	
    // iPhone基本設定
    ofRegisterTouchEvents(this);
    ofxAccelerometer.setup();
    ofxiPhoneAlerts.addListener(this);
    ofBackground(0,0,0);
    ofSetFrameRate(60);
    
    if ((prism = new ofxPrismSAT) != NULL) {
        prism->setNotifier(this);
        prism->setup();
        prism->update();
    }
    
    // 時間のスケール
    timeScale = 30;
    counter = 0;
    
    // データを取得可能な日時を調べる
    dataLoaded = false;
    prism->getAvailableTime(&availableTime);
    
}

//--------------------------------------------------------------
void testApp::update(){
    
    if (dataLoaded) {//もしデータのダウンロードが完了していたら
        currentTime = epochTime.addSecond(counter * timeScale / ofGetFrameRate());
    }
    
    counter++;
}

//--------------------------------------------------------------
void testApp::draw(){
    
    if (dataLoaded) {//もしデータのダウンロードが完了していたら
        
        
        // 直近のデータ取得可能時間を調べる
        ofxSATTime getTime;
        
        for (int i = 0; i < availableTime.size(); i++) {
            if (availableTime[i] >= currentTime) {
                getTime = availableTime[i];
                break;
            }
            
            if (availableTime[availableTime.size()-1] < currentTime) {
                counter = 0;
            }
        }
        
        // 衛星の情報取得に必要な変数
        double value;
        ofxSATError e;
        
        if (getTime > epochTime) {

            int lineHeight = 0;
            
            ofDrawBitmapString("current time: " + currentTime.format("%YYYY/%MM/%DD %hh:%mm:%ss"), 10, lineHeight+=12);
            ofDrawBitmapString("available time: " + getTime.format("%YYYY/%MM/%DD %hh:%mm:%ss"), 10, lineHeight+=12);
            
            ofSetColor(0, 0, 255);
            
            // 各センサーの値を表示
            ofSetColor(255, 255, 255);
            
            e = prism->getSensorTemperatureBattery1(getTime, &value);
            ofDrawBitmapString("TemperatureBattery1 = " + ofToString(value, 4), 10, lineHeight+=24);
            
            e = prism->getSensorTemperatureBattery2(getTime, &value);
            ofDrawBitmapString("TemperatureBattery2 = " + ofToString(value, 4), 10, lineHeight+=12);
            
            e = prism->getSensorTemperatureMainCamera(getTime, &value);
            ofDrawBitmapString("TemperatureMainCamera = " + ofToString(value, 4), 10, lineHeight+=12);
            
            e = prism->getSensorTemperatureMainOBC(getTime, &value);
            ofDrawBitmapString("TemperatureMainOBC = " + ofToString(value, 4), 10, lineHeight+=12);
            
            e = prism->getSensorTemperatureOutsideMX(getTime, &value);
            ofDrawBitmapString("TemperatureOutsideMX = " + ofToString(value, 4), 10, lineHeight+=12);
            
            e = prism->getSensorTemperatureOutsideMY(getTime, &value);
            ofDrawBitmapString("TemperatureOutsideMY = " + ofToString(value, 4), 10, lineHeight+=12);
            
            e = prism->getSensorTemperatureOutsideMZ(getTime, &value);
            ofDrawBitmapString("TemperatureOutsideMZ = " + ofToString(value, 4), 10, lineHeight+=12);
            
            e = prism->getSensorTemperatureOutsidePX(getTime, &value);
            ofDrawBitmapString("TemperatureOutsidePX = " + ofToString(value, 4), 10, lineHeight+=12);
            
            e = prism->getSensorTemperatureOutsidePY(getTime, &value);
            ofDrawBitmapString("TemperatureOutsidePY = " + ofToString(value, 4), 10, lineHeight+=12);
            
            e = prism->getSensorTemperatureOutsidePZ(getTime, &value);
            ofDrawBitmapString("TemperatureOutsidePZ = " + ofToString(value, 4), 10, lineHeight+=12);
            
            e = prism->getSensorTemperaturePanelMX(getTime, &value);
            ofDrawBitmapString("TemperaturePanelMX = " + ofToString(value, 4), 10, lineHeight+=12);
            
            e = prism->getSensorTemperaturePanelMY(getTime, &value);
            ofDrawBitmapString("TemperaturePanelMY = " + ofToString(value, 4), 10, lineHeight+=12);
            
            e = prism->getSensorTemperaturePanelPX(getTime, &value);
            ofDrawBitmapString("TemperaturePanelPX = " + ofToString(value, 4), 10, lineHeight+=12);
            
            e = prism->getSensorTemperaturePanelPY(getTime, &value);
            ofDrawBitmapString("TemperaturePanelPY = " + ofToString(value, 4), 10, lineHeight+=12);
            
            e = prism->getSensorTemperaturePanelPY(getTime, &value);
            ofDrawBitmapString("TemperaturePanelPY = " + ofToString(value, 4), 10, lineHeight+=12);
            
            e = prism->getSensorVoltageAFSKSender(getTime, &value);
            ofDrawBitmapString("VoltageAFSKSender = " + ofToString(value, 4), 10, lineHeight+=12);
            
            e = prism->getSensorVoltageBattery(getTime, &value);
            ofDrawBitmapString("VoltageBattery = " + ofToString(value, 4), 10, lineHeight+=12);
            
            e = prism->getSensorVoltageExpander(getTime, &value);
            ofDrawBitmapString("VoltageExpander = " + ofToString(value, 4), 10, lineHeight+=12);
            
            e = prism->getSensorVoltageGMSKSender(getTime, &value);
            ofDrawBitmapString("VoltageGMSKSender = " + ofToString(value, 4), 10, lineHeight+=12);
            
            e = prism->getSensorVoltageHeater(getTime, &value);
            ofDrawBitmapString("VoltageHeater = " + ofToString(value, 4), 10, lineHeight+=12);
            
            e = prism->getSensorVoltageMain33V(getTime, &value);
            ofDrawBitmapString("VoltageMain33V = " + ofToString(value, 4), 10, lineHeight+=12);
            
            e = prism->getSensorVoltageMain50V(getTime, &value);
            ofDrawBitmapString("VoltageMain50V = " + ofToString(value, 4), 10, lineHeight+=12);
            
            e = prism->getSensorVoltageMainReceiver(getTime, &value);
            ofDrawBitmapString("VoltageMainReceiver = " + ofToString(value, 4), 10, lineHeight+=12);
            
            e = prism->getSensorVoltageMission33V(getTime, &value);
            ofDrawBitmapString("VoltageMission33V = " + ofToString(value, 4), 10, lineHeight+=12);
            
            e = prism->getSensorVoltageMission50V(getTime, &value);
            ofDrawBitmapString("VoltageMission50V = " + ofToString(value, 4), 10, lineHeight+=12);
            
            e = prism->getSensorVoltageNetwork(getTime, &value);
            ofDrawBitmapString("VoltageNetwork = " + ofToString(value, 4), 10, lineHeight+=12);
            
            e = prism->getSensorVoltagePower(getTime, &value);
            ofDrawBitmapString("VoltagePower = " + ofToString(value, 4), 10, lineHeight+=12);
            
            e = prism->getSensorVoltageSolar(getTime, &value);
            ofDrawBitmapString("VoltageSolar = " + ofToString(value, 4), 10, lineHeight+=12);
              
            e = prism->getSensorGyroX(getTime, &value);
            ofDrawBitmapString("GyroX = " + ofToString(value, 4), 10, lineHeight+=12);
            
            e = prism->getSensorGyroY(getTime, &value);
            ofDrawBitmapString("GyroY = " + ofToString(value, 4), 10, lineHeight+=12);
            
            e = prism->getSensorGyroZ(getTime, &value);
            ofDrawBitmapString("GyroZ = " + ofToString(value, 4), 10, lineHeight+=12);
            
            e = prism->getSensorMagnetometerX(getTime, &value);
            ofDrawBitmapString("getSensorMagnetometerX = " + ofToString(value, 4), 10, lineHeight+=12);
            
            e = prism->getSensorMagnetometerY(getTime, &value);
            ofDrawBitmapString("getSensorMagnetometerY = " + ofToString(value, 4), 10, lineHeight+=12);
            
            e = prism->getSensorMagnetometerZ(getTime, &value);
            ofDrawBitmapString("getSensorMagnetometerZ = " + ofToString(value, 4), 10, lineHeight+=12);
                        
        } 
    } else {
        ofDrawBitmapString("loading data...", 10, 24);
    }
}

//--------------------------------------------------------------
void testApp::exit(){
    if (prism != NULL) {
        prism->cleanup();
        delete prism;
    }
    prism = NULL;
}

void testApp::onNotifyTLE(ofxSAT::TLERec const& tle, ofxSATTime const& time)
{
    
}

void testApp::onNotifyData(ofxSATTime const& time)
{    
    
}

void testApp::onNotifyFinish(ofxSATError error)
{
    // データロード完了
    dataLoaded = true;
    epochTime = availableTime[0];
    
    for (int i = 0; i < availableTime.size(); i++) {
        cout << "Available Time[" << i << "] : " << availableTime[i].format("%YYYY/%MM/%DD %hh:%mm:%ss") << endl;
    }
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