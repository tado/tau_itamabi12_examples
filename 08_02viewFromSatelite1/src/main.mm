#include "ofMain.h"
#include "testApp.h"

int main(){
	//ofSetupOpenGL(1024,768, OF_FULLSCREEN);			// <-------- setup the GL context
	//ofRunApp(new testApp);
	
	ofAppiPhoneWindow * window = new ofAppiPhoneWindow();  
    // window->enableAntiAliasing(4);    
	window->enableDepthBuffer();
    ofSetupOpenGL(window, 1024,768, OF_FULLSCREEN);   
    ofRunApp(new testApp);
}