#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	// print input ports to console
	midiIn.listInPorts();

	midiIn.openPort(0);
	midiIn.addListener(this);

	// print received messages to console
	midiIn.setVerbose(true);

	//Visualizing stroke Stuff:
	myfont.load("AmaticSC-Regular.ttf", 48);
	wordFont.load("DroidSans.ttf", 32);

	//Piano Inside
	pianoInside.load("insidePiano.jpg");
}

//--------------------------------------------------------------
void ofApp::update(){
	updateActiveMidiNotes();
}

//--------------------------------------------------------------
void ofApp::draw(){


	// Initializing constants for displaying timeline
	leftX = ofGetWidth() * 0.1;
	rightX = ofGetWidth() * 0.9;
	singleUnit = (rightX - leftX) / (highestMidi - lowestMidi);

	ofBackground(0);

	ofSetColor(255);
	//pianoInside.draw(0, 0, ofGetWidth(), ofGetHeight());
	ofDrawLine(leftX, 500, rightX, 500);

	myfont.drawString("1986", leftX - 20, 570);
	myfont.drawString("Now", rightX - 20, 570);

	drawStrokes();

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

	if (key == 'f')
		ofToggleFullscreen();
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}  

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

//--------------------------------------------------------------
void ofApp::updateActiveMidiNotes() {


	// Updating midiMessages which stores the active button presses at any instant
	for (int i = 0; i < midiMessages.size(); i++) {

		ofxMidiMessage &message = midiMessages[i];

		if (message.velocity == 0 && midiMessages.size() > 1) {

			for (int j = 0; j < midiMessages.size(); j++) {
				ofxMidiMessage &message1 = midiMessages[j];

				if (message1.pitch == message.pitch && message1.velocity > 0) {

					midiMessages.erase(midiMessages.begin() + j);
					j = 0;
					i = 0;
				}
			}
		}

	}



	for (int i = 0; i < midiMessages.size(); i++) {
		ofxMidiMessage &message = midiMessages[i];

		if (message.velocity == 0) {

			//std::cout << "deleting i " << i << " ";
			midiMessages.erase(midiMessages.begin() + i);

		}
	}


	// Updating the midiMessageMemory which stores the last maxMemory number of button press events.
	for (int i = 0; i < midiMessageMemory.size(); i++) {
		ofxMidiMessage &memory = midiMessageMemory[i];
	}
}

//--------------------------------------------------------------
void ofApp::printMidiMessages() {

	//std::cout << midiMessages.size() << endl;
	for (int i = 0; i < midiMessages.size(); i++) {

		ofxMidiMessage &message = midiMessages[i];

		std::cout << "pitch = " << message.pitch << " velocity = " << message.velocity << " ";
	}
	if (midiMessages.size() > 0) {
		std::cout << endl;
		std::cout << "****************************************************************" << endl;
	}
}

//--------------------------------------------------------------
void ofApp::drawStrokes() {

	// Fade these circles out using update and if alpha value is less than a certain small amount, delete from strokes array
	for (int i = 0; i < strokes.size(); i++) {

		strokes[i].draw();
		strokes[i].update();

		ofSetColor(255, 255, 255, strokes[i].alpha);
		wordFont.drawString(strokes[i].projectName, strokes[i].namePosX, strokes[i].namePosY);

	}


	for (int i = 0; i < strokes.size(); i++) {
		if (strokes[i].alpha < 10) {
			strokes.erase(strokes.begin() + i);
			i -= 1; // After erasing, all elements shift by 1 and i needs to be kept at same position
		}
	}

}

//--------------------------------------------------------------
void ofApp::newMidiMessage(ofxMidiMessage& msg) {

	// add the latest message to the message queue
	midiMessages.push_back(msg);

	// remove any old messages if we have too many
	while (midiMessages.size() > maxMessages) {
		midiMessages.erase(midiMessages.begin());
	}

	// add the latest message to the message queue in memory
	if (msg.velocity != 0) {
		midiMessageMemory.push_back(msg);
	}

	while (midiMessageMemory.size() > maxMemory) {
		midiMessageMemory.erase(midiMessageMemory.begin());
	}


	// Add a stroke for every note on event after the first 2
	if (midiMessageMemory.size() >= 2 && msg.velocity != 0) {

		// Draw shape between i and i+1

		int x1 = leftX + (midiMessageMemory.back().pitch - lowestMidi) * singleUnit;
		int y1 = 500;
		int x2 = leftX + (midiMessageMemory.end()[-2].pitch - lowestMidi) * singleUnit;
		int y2 = 500;

		string t = projectNames[midiMessageMemory.back().pitch % 12];
		if (ofRandomf() > 0.5) {
			t = toVerticalText(t);
		}

		strokeShape s;
		s.create(x1, y1, x2, y2, 255, t);
		strokes.push_back(s);

	}

	// Printing for DEBUGGING every time new Midi message is received.
	/*
	for (int i = 0; i < midiMessageMemory.size(); i++) {
		std::cout << "pitch = " << midiMessageMemory[i].pitch << " velcity = " << midiMessageMemory[i].velocity << endl;
	}

	if (midiMessageMemory.size() > 0) {
		std::cout << " ********************************************* " << endl;
	}
	*/
}

//--------------------------------------------------------------
string ofApp::toVerticalText(string originString) {
	string str = "";
	string returnChar = "\n";
	for (int i = 0; i < originString.size(); i++) {
		str = str + originString[i] + returnChar;
	}
	return str;
}