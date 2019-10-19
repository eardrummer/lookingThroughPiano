#include "ofMain.h"
#include "ofApp.h"
#include "ofAppGLFWWindow.h"

//========================================================================
int main( ){

	// For non projector display
	/*
	ofSetupOpenGL(1024, 768, OF_WINDOW);
	ofRunApp(new ofApp());
	*/

	// For projector display
	
	
	ofAppGLFWWindow window;
	window.listMonitors();

	//window.setMultiDisplayFullscreen(true);
	ofSetupOpenGL(&window, 1920, 1080, OF_FULLSCREEN);
	window.setFullscreen(1);
	ofSetWindowPosition(1920, 0);
	ofRunApp(new ofApp());
	ofRunMainLoop();
	
}