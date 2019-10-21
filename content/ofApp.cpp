#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	tod.load("tod.jpg");
	todSize = ofVec2f(ofGetWidth(), ofGetHeight());

	// print input ports to console
	midiIn.listInPorts();

	midiIn.openPort(0);
	midiIn.addListener(this);

	// print received messages to console
	midiIn.setVerbose(true);

	// TODO: Load all assets and content

	
	string names[88] = { "0.10","0.11","0.12","1.1","1.2","1.3","1.4","1.5","1.6","1.7","1.8","1.9","1.10","1.11","1.12",
		"2.1","2.2","2.3","2.4","2.5","2.6","2.7","2.8","2.9", "2.10","2.11","2.12",
		"3.1","3.2","3.3","3.4","3.5","3.6","3.7","3.8","3.9", "3.10","3.11","3.12",
		"4.1","4.2","4.3","4.4","4.5","4.6","4.7","4.8","4.9", "4.10","4.11","4.12",
		"5.1","5.2","5.3","5.4","5.5","5.6","5.7","5.8","5.9", "5.10","5.11","5.12",
		"6.1","6.2","6.3","6.4","6.5","6.6","6.7","6.8","6.9", "6.10","6.11","6.12",
		"7.1","7.2","7.3","7.4","7.5","7.6","7.7","7.8","7.9", "7.10","7.11","7.12",
		"8.1"};

	//string names[15] = { "0.10","0.11","0.12","1.1","1.2","1.3","1.4","1.5","1.6","1.7","1.8","1.9","1.10","1.11","1.12" };
		

	string noVideo[24] = { "0.10","1.11", "1.12", "3.6","4.1","4.2","4.3","4.5","4.10","4.11","5.1","5.3","5.5","6.2","6.3",
						  "6.7", "6.11","6.12","7.1","7.4","7.8","7.9","7.11","7.12"}; // TODO: for the ones without video load audio instead. Change constructor

	for (int i = 0; i < 88; i++) {
		int flag = 0;
		for (int j = 0; j < 24; j++) {
			if (names[i] == noVideo[j]) {
				flag = 1;
				break;
			}
		}

		if (flag == 0) {
			contentObj c(names[i], 1);
			allContent[names[i]] = c;
		}
		else {
			std::cout << "no video :";
			contentObj c(names[i], 0);
			allContent[names[i]] = c;
		}
	}

	csvFile.load("Content_List.csv");

	for (int i = 1; i < 89; i++) {
		string id = csvFile.getRow(i).getString(0);

		titles[id] = csvFile.getRow(i).getString(1);
		dates[id] = csvFile.getRow(i).getString(2);
		descriptions[id] = csvFile.getRow(i).getString(5);

		for (int j = 0; j < descriptions[id].length(); j++) {
			if (j % 100 == 0) {

				for (int k = j; k > 0; k--) {
					if (descriptions[id][k] == ' ') {
						descriptions[id].insert(k+1, "\n");
						break;
					}
				}
				
			}
		}
	}

	font.load("Bebas-Regular.otf", 40);
	fontDescription.load("Bebas-Regular.otf", 18);
}

//--------------------------------------------------------------
void ofApp::update(){

	// debug = 1 To see the status of the assets being printed in console
	int debug = 0;

	if(debug){
		printMidiMessages();
	}
	
	updateActiveMidiNotes();



	if (currentCount == 0) {

		for (int i = 0; i < contentArrayNames.size(); i++) {
			allContent[contentArrayNames[i]].fadeSustain();
		}

		// No keys pressed, empty display. TODO: Replace with static display when nothing is being pressed
		while (!contentArrayNames.empty()) {

			if (allContent[contentArrayNames.back()].alpha < 20) {
				allContent[contentArrayNames.back()].stopVideo();
				contentArrayNames.pop_back();
			}
			else {
				break;
			}
		}

		if (debug) {
			std::cout << "Play Me" << endl;
		}

	}

	else {

		if (previousCount != currentCount) {
			// Change in midi information detected

			// Refresh contentArray
			while (!contentArrayNames.empty()) {
				allContent[contentArrayNames.back()].stopVideo();
				contentArrayNames.pop_back();
			}

			if (currentCount == 1) {

				// Single display
				int count = 0;
				for (int i = 0; i < midiMessages.size(); i++) {
					if (midiMessages[i].velocity != 0) {

						// TODO: replace with correct octave folder as well
						int octave = midiMessages[i].pitch / 12 - 1;
						string s = std::to_string(octave) + "." + std::to_string(midiMessages[i].pitch % 12 + 1);
						contentArrayNames.push_back(s);

						allContent[contentArrayNames.back()].mode = 0;  // MODE = 0 / Solo
						allContent[contentArrayNames.back()].rePosition(1,1);
						allContent[contentArrayNames.back()].playVideo();

						count++;

						// Only pick out the 1 active midi message to generate content for
						if (count == 1) {
							break;
						}
					}
				}
			}
			else if (currentCount < 4) {

				// Multiple Display

				int count = 0;
				for (int i = 0; i < midiMessages.size(); i++) {
					if (midiMessages[i].velocity != 0) {
						// TODO: replace with correct octave folder as well
						int octave = midiMessages[i].pitch / 12 - 1;
						string s = std::to_string(octave) + "." + std::to_string(midiMessages[i].pitch % 12 + 1);
						contentArrayNames.push_back(s);
						allContent[contentArrayNames.back()].mode = 1;   // MODE = 1 / Multi
						allContent[contentArrayNames.back()].rePosition(currentCount, count+1);
						allContent[contentArrayNames.back()].playVideo();

						count++;

						// Only pick out the 5 active midi message to generate content for
						if (count == 4) {
							break;
						}
					}
				}
			}
			else {

				// Tiled Display
				int count = 0;
				for (int i = 0; i < midiMessages.size(); i++) {
					if (midiMessages[i].velocity != 0) {

						// TODO: replace with correct octave folder as well
						int octave = midiMessages[i].pitch / 12 - 1;
						string s = std::to_string(octave) + "." + std::to_string(midiMessages[i].pitch % 12 + 1);
						contentArrayNames.push_back(s);
						allContent[contentArrayNames.back()].mode = 2;  // MODE = 2 / Tiled
						allContent[contentArrayNames.back()].rePosition(currentCount, count);

						count++;
					}
				}
			}
		}
		else {
			// Continue displaying current content.
			// TODO: Update video, Update position of Images

			if (debug) {
				std::cout << "Continue displaying" << endl;
			}

			for (int i = 0; i < contentArrayNames.size(); i++) {
				allContent[contentArrayNames[i]].update();

				//TODO: If in mode == 1: Change the order of contents at some interval, Perhaps when main video ends.
			}

		}
	}
	

	if (debug) {
		for (int i = 0; i < contentArrayNames.size(); i++) {
			std::cout << contentArrayNames[i] << " " << allContent[contentArrayNames[i]].mode << " ";
		}
		std::cout << endl;
	}
	

	previousCount = countMidiMessages();
}

//--------------------------------------------------------------
void ofApp::draw(){

	ofBackground(0);
	for (int i = 0; i < contentArrayNames.size(); i++) {

		allContent[contentArrayNames[i]].draw();

		if (allContent[contentArrayNames[i]].mode == 0) {
			// Solo mode
			font.drawString(titles[contentArrayNames[i]], 50, 900);
			font.drawString(dates[contentArrayNames[i]], 50, 950);
			fontDescription.drawString(descriptions[contentArrayNames[i]], 50, 1000);
		}
		else if (allContent[contentArrayNames[i]].mode == 1) {
			// Multiple mode
			font.drawString(titles[contentArrayNames[i]], allContent[contentArrayNames[i]].textPos.x, allContent[contentArrayNames[i]].textPos.y);
			font.drawString(dates[contentArrayNames[i]], allContent[contentArrayNames[i]].textPos.x, allContent[contentArrayNames[i]].textPos.y + 50);
		}
	}

	// if they are in tiled mode
	if (contentArrayNames.size() > 0) {
		if (allContent[contentArrayNames[0]].mode == 2) {
			// TODO: Surpriese Tod Appears
			ofPushMatrix();
			ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);
			tod.draw(-1 * this->todSize.x / 2, -1 * this->todSize.y / 2, this->todSize.x, this->todSize.y);
			ofPopMatrix();
		}
	}

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

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
void ofApp::exit() {

	// clean up
	midiIn.closePort();
	midiIn.removeListener(this);
}

//--------------------------------------------------------------
void ofApp::newMidiMessage(ofxMidiMessage& msg) {

	// add the latest message to the message queue
	midiMessages.push_back(msg);

	// remove any old messages if we have too many
	while (midiMessages.size() > maxMessages) {
		midiMessages.erase(midiMessages.begin());
	}

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


	currentCount = countMidiMessages();
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
int ofApp::countMidiMessages() {

	int count = 0;

	for (int i = 0; i < midiMessages.size(); i++) {

		ofxMidiMessage &message = midiMessages[i];
		if (message.velocity != 0) {
			count++;
		}
	}

	return count;
}



