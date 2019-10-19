#include "strokeShape.h"

strokeShape::strokeShape() {
	// constructor
	this->alpha = 0;
	this->posX1 = 0;
	this->posX2 = 0;
	this->posY1 = 0;
	this->posY2 = 0;
}

void strokeShape::create(int x1, int y1, int x2, int y2, int a, string projectName) {
	//create
	this->posX1 = x1;
	this->posY1 = y1;

	this->posX2 = x2;
	this->posY2 = y2;

	this->alpha = a;

	// For when the same key is pressed multiple times.
	this->selfRadius = 10 + ofRandom(20);

	this->projectName = projectName;
	this->namePosX = ofRandom(0.8*ofGetWidth()) + 20;
	this->namePosY = ofRandom(0.8*ofGetHeight()) + 20;

}

void strokeShape::draw() {
	//draw
	//setColor(this.color, this.alpha);
	ofColor c(200, 0, 0, this->alpha);
	ofSetColor(c);

	ofDrawCircle(this->posX1, this->posY1, 3);
	ofDrawCircle(this->posX2, this->posY2, 3);


	if (this->posX1 == this->posX2) {
		ofPath path;

		path.moveTo(this->posX1, this->posY1);
		path.arc(this->posX1, this->posY1 - this->selfRadius, this->selfRadius, this->selfRadius, 90, 450);
		path.setStrokeColor(c);
		path.setStrokeWidth(5);
		path.setFilled(false);
		path.draw();

	}
	else {
		ofPath path;

		path.moveTo(this->posX2, this->posY2);
		path.arc((this->posX2 - this->posX1) / 2 + this->posX1, this->posY1, (this->posX2 - this->posX1) / 2, (this->posX2 - this->posX1) / 2, 0, 180);
		//path.close();

		path.setStrokeColor(c);
		path.setStrokeWidth(5);
		path.setFilled(false);

		path.draw();
	}
	

}

void strokeShape::update() {
	//update

	this->alpha -= 1;
}