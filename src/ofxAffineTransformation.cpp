#include "ofxAffineTransformation.h"

ofxAffineTransformation::ofxAffineTransformation() {
	index     = -1;
	h         = 8;
	fx        = 0.;
	fy        = 0.;
	fz        = 0.;
	T         = new float[9];
	pts       = new ofVec2f[4];
	npts      = new ofVec2f[4];
	bDrawFlag = true;
}

ofxAffineTransformation::~ofxAffineTransformation() {
	
}

// set cross
//--------------------------------------------------------------
void ofxAffineTransformation::setCross(int m) {
	pts[0].set(m, m);
	pts[1].set(ofGetWidth() - m, m);
	pts[2].set(ofGetWidth() - m, ofGetHeight() - m);
	pts[3].set(m, ofGetHeight() - m);
	npts[0].set(0, 0);
	npts[1].set(1, 0);
	npts[2].set(1, 1);
	npts[3].set(0, 1);

}

// say hello
//--------------------------------------------------------------
void ofxAffineTransformation::checkCross() {
	int i, j = -1;
	for (i = 0; i<4; i++)
		if (abs(pts[i].x - ofGetMouseX()) + abs(pts[i].y - ofGetMouseY())<h) j = i;
	index = j;
}

// say hello
//--------------------------------------------------------------
void ofxAffineTransformation::updateCross() {
	if (index >= 0 && index<4)
		pts[index].set(ofGetMouseX(), ofGetMouseY());
}

// say hello
//--------------------------------------------------------------
void ofxAffineTransformation::releaseCross() {
	index = -1;
}

// say hello
//--------------------------------------------------------------
void ofxAffineTransformation::changeDrawFlag() {
	bDrawFlag = !bDrawFlag;
}

// say hello
//--------------------------------------------------------------
void ofxAffineTransformation::drawCross() {
	if (!bDrawFlag) return;
	ofNoFill();
	if (index != -1) {
		ofSetLineWidth(6);
		ofSetColor(198, 32, 32);
		ofEllipse(pts[index].x, pts[index].y, h, h);
	}

	ofSetLineWidth(2);
	ofSetColor(32, 198, 32);
	for (int i = 0; i<4; i++)
		ofEllipse(pts[i].x, pts[i].y, h, h);

	ofSetLineWidth(1);
	ofSetColor(255, 0, 0);
	ofBeginShape();
	for (int i = 0; i<4; i++)
		ofVertex(pts[i].x, pts[i].y);
	ofEndShape(true);
}

// say hello
//--------------------------------------------------------------
float ofxAffineTransformation::getFx() {
	return fx;
}

// say hello
//--------------------------------------------------------------
float ofxAffineTransformation::getFy() {
	return fy;
}
void ofxAffineTransformation::applyAffineTransformation(int _x, int _y) {
	fx = T[0] * _x + T[1] * _y + T[2];
	fy = T[3] * _x + T[4] * _y + T[5];
	fz = T[6] * _x + T[7] * _y + T[8];
	fx /= fz;
	fy /= fz;
}
// say hello
//--------------------------------------------------------------
void ofxAffineTransformation::calAffineTransform(bool debug) {

	float A[8][9];

	for (int i = 0; i<4; i++) {
		A[2 * i][0] = pts[i].x;
		A[2 * i][1] = pts[i].y;
		A[2 * i][2] = 1;
		A[2 * i][3] = 0;
		A[2 * i][4] = 0;
		A[2 * i][5] = 0;
		A[2 * i][6] = -pts[i].x*npts[i].x;
		A[2 * i][7] = -pts[i].y*npts[i].x;
		A[2 * i][8] = -npts[i].x;

		A[2 * i + 1][0] = 0;
		A[2 * i + 1][1] = 0;
		A[2 * i + 1][2] = 0;
		A[2 * i + 1][3] = pts[i].x;
		A[2 * i + 1][4] = pts[i].y;
		A[2 * i + 1][5] = 1;
		A[2 * i + 1][6] = -pts[i].x*npts[i].y;
		A[2 * i + 1][7] = -pts[i].y*npts[i].y;
		A[2 * i + 1][8] = -npts[i].y;
	}
	

	float At[9][8];
	// At = A.transpose()
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 9; j++) {
			At[j][i] = A[i][j];
		}
	}

	float AtA[9][9];
	// AtA = At * A
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			AtA[i][j] = 0;
			for (int k = 0; k < 8; k++) {
				AtA[i][j] += At[i][k] * A[k][j];
			}
		}
	}
	// EV.A = AtA
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			EV.A[i][j] = AtA[i][j];
		}
	}

	// calculate eigenvalue, eigenvector
	EV.calculate();

	// calculate T
	for (int i = 0; i<9; i++) T[i] = EV.V[i][0] / EV.V[8][0];

	// print debug
	if (debug) {
		cout << "A:\n" << endl;
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 9; j++) {
				cout << A[i][j] << "\t";
			}
			cout << "\n" << endl;
		}

		cout << "At:\n" << endl;
		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 8; j++) {
				cout << At[i][j] << "\t";
			}
			cout << "\n" << endl;
		}

		cout << "AtA:\n" << endl;
		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 9; j++) {
				cout << AtA[i][j] << "\t";
			}
			cout << "\n" << endl;
		}

		cout << "EV.A:\n" << endl;
		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 9; j++) {
				cout << EV.A[i][j] << "\t";
			}
			cout << "\n" << endl;
		}

		cout << "T:\n" << endl;
		for (int i = 0; i < 9; i++) cout << T[i] << "\t";
	}
}