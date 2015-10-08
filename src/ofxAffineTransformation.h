#pragma once

#include "ofMain.h"
#include "Eigenvalue.h"

using namespace std;

class ofxAffineTransformation {
public:
	ofxAffineTransformation();
	~ofxAffineTransformation();

	Eigenvalue EV;

	void setCross(int m);
	void setCross(int m, int _w, int _h);
	void setCross(int m, int _x, int _y, int _w, int _h);
	void drawCross();
	void checkCross();
	void updateCross();
	void releaseCross();
	void changeDrawFlag();
	float getFx();
	float getFy();
	void calAffineTransform(bool debug);
	void applyAffineTransformation(int _x, int _y);

private:
	int index;
	int h;
	int areaX, areaY, areaW, areaH;
	float fx;
	float fy;
	float fz;
	float *T;
	ofVec2f *pts;
	ofVec2f *npts;
	bool bDrawFlag;
};


