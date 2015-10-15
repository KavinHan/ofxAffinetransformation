#pragma once

#include "ofMain.h"
#include "Eigenvalue.h"

using namespace std;

class ofxAffineTransformation {
public:
	ofxAffineTransformation();
	~ofxAffineTransformation();

	Eigenvalue EV;

	void  setCross(int m);
	void  setCross(int m, int _w, int _h);
	void  setCross(int m, int _x, int _y, int _w, int _h);
	void  setCross(vector<ofVec2f> _pnts);
	void  drawCross();
	void  checkCross();
	void  updateCross();
	void  releaseCross();
	float getFx();
	float getFy();
	void  calAffineTransform(bool debug);
	void  applyAffineTransformation(int _x, int _y);
	bool  checkInside(int _x, int _y);

private:
	int     index;		// corner index
	int     h;			// check corner distance area
	int     areaX,		// the area position.x when auto set initial corner
		    areaY,		// the area position.y when auto set initial corner
		    areaW,		// the area width when auto set initial corner
		    areaH;		// the area height when auto set initial corner
	float   fx;			// the normal x when finish calibration
	float   fy;			// the normal y when finish calibration
	float   fz;			// the normal z when finish calibration
	float   *T;			// the eigen vector when finish calibration
	ofVec2f *pts;		// four corner position
	ofVec2f *npts;		// the order of corner unit coordinate
};


