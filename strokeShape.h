#ifndef _STROKESHAPE
#define _STROKESHAPE

#include "ofMain.h"

class strokeShape {
public:
	void create(int x1, int y1, int x2, int y2, int a, string projectName);
	void draw();
	void update();

	int posX1, posY1, posX2, posY2, namePosX, namePosY;
	int alpha;

	int selfRadius;
	string projectName;

	strokeShape();
};
#endif