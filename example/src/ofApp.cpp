#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
    aT.setCross(128);
    aT.calAffineTransform(false);
    bDrawAT = true;
}

//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {

    ofSetColor(255);
    if (bDrawAT)
        aT.drawCross();

    ofSetColor(0, 0, 255);
    string str = "mouse [" + ofToString(ofGetMouseX()) + "," + ofToString(ofGetMouseX()) + "]->[" + ofToString(aT.getFx()) + "," + ofToString(aT.getFy()) + "]";
    ofDrawBitmapString(ofToString(str), 180, 180);
    ofDrawBitmapString(ofToString("key c => caliabration"), 180, 200);
    ofDrawBitmapString(ofToString("key h => show/hide control pints"), 180, 220);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
    if (key == 'h')
        bDrawAT = !bDrawAT;
    else if (key == 'c')
        aT.calAffineTransform(false);
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {
    aT.checkCross();
    aT.applyAffineTransformation(x, y);
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {
    if (button == OF_MOUSE_BUTTON_LEFT)
        aT.updateCross();
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {
    aT.releaseCross();
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}
