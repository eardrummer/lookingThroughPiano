#pragma once

#include "ofMain.h"
#include "ofxMidi.h"
#include "content.h"

class ofApp : public ofBaseApp, public ofxMidiListener{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		void ofApp::exit();
		

		void newMidiMessage(ofxMidiMessage& eventArgs);
		void updateActiveMidiNotes();
		void printMidiMessages();
		int countMidiMessages();

		ofxMidiIn midiIn;
		std::vector<ofxMidiMessage> midiMessages;
		std::size_t maxMessages = 10; //< max number of messages to keep track of

		std::vector<string> contentArrayNames;
		std::map<std::string, contentObj> allContent;

		//int lowestMidi = 48, highestMidi = 72;
		int lowestMidi = 21, highestMidi = 108;

		int previousCount = 0, currentCount = 0;
		ofImage tod;
		ofVec2f todSize;
};