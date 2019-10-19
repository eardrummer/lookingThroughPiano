#pragma once

#include "ofMain.h"
#include "ofxMidi.h"
#include "strokeShape.h"

class ofApp : public ofBaseApp, public ofxMidiListener {

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

		void newMidiMessage(ofxMidiMessage& eventArgs);
		void updateActiveMidiNotes();
		void printMidiMessages();
		void drawStrokes();
		string toVerticalText(string originString);

		ofxMidiIn midiIn;
		std::vector<ofxMidiMessage> midiMessages;
		std::size_t maxMessages = 10; //< max number of messages to keep track of

		std::vector<ofxMidiMessage> midiMessageMemory;
		std::size_t maxMemory = 10;

		//int lowestMidi = 48, highestMidi = 72;
		int lowestMidi = 21, highestMidi = 108;
		int leftX, rightX;
		int singleUnit;

		//Visualizing strokes stuff:
		std::vector<strokeShape> strokes;
		ofTrueTypeFont myfont, wordFont;
		
		// TODO: Fill all names across piano keys. Repeat names for keys with content for same project
		std::string projectNames[12] = {"Brain Opera", "Brain Opera", "Brain Opera","Bug Mudra", "Flora", "Flora","Hypercello", "Hypercello", "Meteroite", "Resurrection", "Valis", "Valis" };

		ofImage pianoInside;
};
