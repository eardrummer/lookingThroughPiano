#ifndef _CONTENT
#define _CONTENT

#include "ofMain.h"

class contentObj {

	public:

		int mode;

		ofVideoPlayer video;
		ofSoundPlayer audio;

		ofImage image1, image2, image3;
		ofVec2f videoPos, image1Pos, image2Pos, image3Pos, textPos, centerPos;
		ofVec2f videoSize, image1Size, image2Size, image3Size;
		int image1State, image2State, image3State; // 1,2,3 - represent the different movements of image.

		string description;
		int alpha;

		int hasVideo;

		contentObj(string, int);
		contentObj();

		void draw();
		void update();
		void rePosition(int, int);
		void playVideo();
		void stopVideo();
		void fadeSustain();
};

#endif