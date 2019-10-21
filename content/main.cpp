#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){

	int Projector = 1;

	if (Projector) {
		ofAppGLFWWindow window;
		window.listMonitors();

		//window.setMultiDisplayFullscreen(true);
		ofSetupOpenGL(&window, 1920, 1080, OF_FULLSCREEN);
		window.setFullscreen(1);
		ofSetWindowPosition(1920, 0);
		ofRunApp(new ofApp());
		ofRunMainLoop();
	}
	else {

		ofSetupOpenGL(1024,768,OF_WINDOW);			// <-------- setup the GL context

		// this kicks off the running of my app
		// can be OF_WINDOW or OF_FULLSCREEN
		// pass in width and height too:
		ofRunApp(new ofApp());
	}
	



}
