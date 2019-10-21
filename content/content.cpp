#include "content.h"

contentObj::contentObj() {
	// default constructor
}

contentObj::contentObj(string name, int hasVideo = 1) {

	
	string path = std::to_string(name[0] - '0') + "\\" + name + "\\";
	std::cout << "Loading:" << path << endl;

	if (hasVideo == 1) {
		this->video.load(path + "video.mp4");
	}
	else {
		this->audio.load(path + "audio.mp3");
	}
	
	this->hasVideo = hasVideo;
	this->image1.load(path + "1.jpg");
	this->image2.load(path + "2.jpg");
	this->image3.load(path + "3.jpg");


	this->mode = 0;
	this->alpha = 200;

	this->image1State = 1;
	this->image2State = 2;
	this->image3State = 3;
}


void contentObj::draw() {
	
	ofSetColor(255, 255, 255, this->alpha);

	if (this->mode == 0 || this->mode == 1) {


		// Display IMAGES

		ofPushMatrix();
		ofTranslate(this->image3Pos);
		this->image3.draw(-1 * this->image3Size.x / 2, -1 * this->image3Size.y / 2, this->image3Size.x, this->image3Size.y);
		ofPopMatrix();

		ofPushMatrix();
		ofTranslate(this->image2Pos);
		this->image2.draw(-1 * this->image2Size.x / 2, -1 * this->image2Size.y / 2, this->image2Size.x, this->image2Size.y);
		ofPopMatrix();

		ofPushMatrix();
		ofTranslate(this->image1Pos);
		this->image1.draw(-1 * this->image1Size.x / 2, -1 * this->image1Size.y / 2, this->image1Size.x, this->image1Size.y);
		ofPopMatrix();


		// Display VIDEO
		if (this->hasVideo) {
			ofPushMatrix();
			ofTranslate(this->videoPos);
			this->video.draw(-1 * this->videoSize.x / 2, -1 * this->videoSize.y / 2, this->videoSize.x, this->videoSize.y);
			ofPopMatrix();
		}
		

	}
	else {
		//std::cout << " mode is Tiled(2)" << endl;

		ofPushMatrix();
		ofTranslate(this->image1Pos);
		this->image1.draw(-1 * this->image1Size.x / 2, -1 * this->image1Size.y / 2, this->image1Size.x, this->image1Size.y);
		ofPopMatrix();
	}
}

void contentObj::update() {
	this->video.update();

	int speed = 2;

	if (this->mode == 0) {


		if (this->image1State == 1) {
			image1Pos.x += speed;
			image1Pos.y += speed;

			if (image1Pos.x > 900 || image1Pos.y > 900) {
				image1Pos.x = 900;
				image1Pos.y = 900;
				image1State = 3;
			}
		}
		if (this->image1State == 3) {
			image1Pos.x += speed;
			image1Pos.y -= speed;

			if (image1Pos.x > 1500 || image1Pos.y < 300) {
				image1Pos.x = 1500;
				image1Pos.y = 300;
				image1State = 2;
			}
		}
		if (this->image1State == 2) {
			image1Pos.x -= (speed * 2);

			if (image1Pos.x < 300) {
				image1Pos.x = 300;
				image1Pos.y = 300;
				image1State = 1;
			}
		}

		// For image2 -------------------------------

		if (this->image2State == 1) {
			image2Pos.x += speed;
			image2Pos.y += speed;

			if (image2Pos.x > 900 || image2Pos.y > 900) {
				image2Pos.x = 900;
				image2Pos.y = 900;
				image2State = 3;
			}
		}
		if (this->image2State == 3) {
			image2Pos.x += speed;
			image2Pos.y -= speed;

			if (image2Pos.x > 1500 || image2Pos.y < 300) {
				image2Pos.x = 1500;
				image2Pos.y = 300;
				image2State = 2;
			}
		}
		if (this->image2State == 2) {
			image2Pos.x -= (speed * 2);

			if (image2Pos.x < 300) {
				image2Pos.x = 300;
				image2Pos.y = 300;
				image2State = 1;
			}
		}


		// For image3 -------------------------------
		if (this->image3State == 1) {
			image3Pos.x += speed;
			image3Pos.y += speed;

			if (image3Pos.x > 900 || image3Pos.y > 900) {
				image3Pos.x = 900;
				image3Pos.y = 900;
				image3State = 3;
			}
		}
		if (this->image3State == 3) {
			image3Pos.x += speed;
			image3Pos.y -= speed;

			if (image3Pos.x > 1500 || image3Pos.y < 300) {
				image3Pos.x = 1500;
				image3Pos.y = 300;
				image3State = 2;
			}
		}
		if (this->image3State == 2) {
			image3Pos.x -= (speed * 2);

			if (image3Pos.x < 300) {
				image3Pos.x = 300;
				image3Pos.y = 300;
				image3State = 1;
			}
		}
	
	} // End of Mode  = 0 check condition
	if (this->mode == 1) {

		image1Pos.x += 2;
		image2Pos.x += 2;
		image3Pos.x += 2;
		videoPos.x += 2;
		textPos.x += 2;

		if (image1Pos.x > ofGetWidth() || image2Pos.x > ofGetWidth() || image3Pos.x > ofGetWidth()) {
			videoPos.x = 0;
			
			image1Pos.x = 20;
			textPos.x = image1Pos.x - 180;
			image2Pos.x = 40;
			image3Pos.x = 60;
		}
	}

}

void contentObj::rePosition(int numberOfAssets = 1, int indexOfAsset = 1) {


	// Setting the initial conditions
	this->alpha = 200;
	if (this->hasVideo) {
		this->video.setVolume(1);
	}
	else {
		this->audio.setVolume(1);
	}
	
	this->image1State = 1;
	this->image2State = 2;
	this->image3State = 3;

	//TODO: changes position of the video and images, and resizes based on mode.

	if (this->mode != 2) {


		if (numberOfAssets == 1) {

			// SOLO: video position for solo mode

			if (this->hasVideo) {
				this->videoPos = ofVec2f(ofGetWidth() / 2, ofGetHeight() / 2);
				this->videoSize = ofVec2f(ofGetWidth()*0.45, ofGetHeight()*0.45);
			}

			this->image1Pos = ofVec2f(300, 300);
			this->image1Size = ofVec2f(ofGetWidth()*0.25, ofGetHeight()*0.25);

			this->image2Pos = ofVec2f(1500, 300);
			this->image2Size = ofVec2f(ofGetWidth()*0.25, ofGetHeight()*0.25);

			this->image3Pos = ofVec2f(900, 900);
			this->image3Size = ofVec2f(ofGetWidth()*0.25, ofGetHeight()*0.25);

		}
		else if (numberOfAssets > 1 && numberOfAssets < 4) {

			switch (indexOfAsset) {
			case 1:

				if (this->hasVideo) {
					this->videoPos = ofVec2f(ofGetWidth() / 2 - 20, ofGetHeight() * 2 / 3);
					this->videoSize = ofVec2f(ofGetWidth()*0.25, ofGetHeight()*0.25);
				}

				this->image1Pos = ofVec2f(ofGetWidth() / 2 - 20 + 20, ofGetHeight() * 2 / 3 - 100);
				this->image1Size = ofVec2f(ofGetWidth()*0.25, ofGetHeight()*0.25);

				this->textPos = ofVec2f(image1Pos.x - 180, image1Pos.y + 300);

				this->image2Pos = ofVec2f(ofGetWidth() / 2 - 20 + 40, ofGetHeight() * 2 / 3 - 200);
				this->image2Size = ofVec2f(ofGetWidth()*0.25, ofGetHeight()*0.25);

				this->image3Pos = ofVec2f(ofGetWidth() / 2 - 20 + 60, ofGetHeight() * 2 / 3 - 300);
				this->image3Size = ofVec2f(ofGetWidth()*0.25, ofGetHeight()*0.25);

				break;
			case 2:

				if (this->hasVideo) {
					this->videoPos = ofVec2f(350, ofGetHeight() * 2 / 3);
					this->videoSize = ofVec2f(ofGetWidth()*0.25, ofGetHeight()*0.25);
				}
				

				this->image1Pos = ofVec2f(350 + 20, ofGetHeight() * 2 / 3 - 100);
				this->image1Size = ofVec2f(ofGetWidth()*0.25, ofGetHeight()*0.25);

				this->textPos = ofVec2f(image1Pos.x - 180, image1Pos.y + 300);

				this->image2Pos = ofVec2f(350 + 40, ofGetHeight() * 2 / 3 - 200);
				this->image2Size = ofVec2f(ofGetWidth()*0.25, ofGetHeight()*0.25);

				this->image3Pos = ofVec2f(350 + 60, ofGetHeight() * 2 / 3 - 300);
				this->image3Size = ofVec2f(ofGetWidth()*0.25, ofGetHeight()*0.25);

				break;
			case 3:

				if (this->hasVideo) {
					this->videoPos = ofVec2f(1500, ofGetHeight() * 2 / 3);
					this->videoSize = ofVec2f(ofGetWidth()*0.25, ofGetHeight()*0.25);
				}
			

				this->image1Pos = ofVec2f(1500 + 20, ofGetHeight() * 2 / 3 - 100);
				this->image1Size = ofVec2f(ofGetWidth()*0.25, ofGetHeight()*0.25);

				this->textPos = ofVec2f(image1Pos.x - 180, image1Pos.y + 300);

				this->image2Pos = ofVec2f(1500 + 40, ofGetHeight() * 2 / 3 - 200);
				this->image2Size = ofVec2f(ofGetWidth()*0.25, ofGetHeight()*0.25);

				this->image3Pos = ofVec2f(1500 + 60, ofGetHeight() * 2 / 3 - 300);
				this->image3Size = ofVec2f(ofGetWidth()*0.25, ofGetHeight()*0.25);
				break;

			default:
				break;
			}
		}
	}  // End of Mode != 2 check condition

	else {
	
		int noPerSide = ceil(sqrt(numberOfAssets));

		int xCount = indexOfAsset % noPerSide;
		int yCount = indexOfAsset / noPerSide;

		this->image1Size = ofVec2f(ofGetWidth()/noPerSide, ofGetHeight()/ floor(sqrt(numberOfAssets)));
		this->image1Pos = ofVec2f(image1Size.x/2 + (xCount * image1Size.x), image1Size.y / 2 + (yCount * image1Size.y));

	}
	
	
}

void contentObj::playVideo() {

	if (this->hasVideo) {

		this->video.play();
		this->video.setVolume(1);
	}
	else {
		this->audio.play();
		this->audio.setLoop(true);
		this->audio.setVolume(1);
	}
	
	this->alpha = 200;
	
}

void contentObj::stopVideo() {
	
	if (this->hasVideo) {
		this->video.stop();
	}
	else {
		this->audio.stop();
	}
	
}

void contentObj::fadeSustain() {
	ofSetColor(255,255,255,this->alpha);
	this->alpha-= 5;

	if (this->hasVideo) {
		this->video.setVolume(alpha / 255.0);
	}
	else {
		this->audio.setVolume(alpha / 255.0);
	}
	
}