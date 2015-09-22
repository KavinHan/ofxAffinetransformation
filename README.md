# ofxAffinetransformation
Affine Triansformation addons for openframeworks



**Study from [Prof.LeeByungGook](http://kowon.dongseo.ac.kr/~lbg/)**

Reference:
* [Smarter Presentations: Exploiting Homography in Camera-Projector Systems](http://www.cs.cmu.edu/~rahuls/pub/iccv2001-rahuls.pdf)
* [Affine transformation](https://en.wikipedia.org/wiki/Affine_transformation)

## Requirements
* openFrameworks 0.8.4+

## Test Environments
* Windows 10 + Visual Studio 2015

## Getting Started
Just following under step, you will know how to use ofxAffinetransformation.
For this I'm using openFrameworks 0.8.4+ for window.
1. After downloading or cloning ofxAffinetransformation, place the folder in your openframeworks addons folder.

2. Create a new oF project using the project generator, make sure ofxAffinetransformation is enabled from the list of addons shown.
  * Run openframeworks/projectGenerator/projectGenerator.exe
  * Write name -> Choose path -> Click Addons -> Select ofxAffinetransformation -> Click BACK -> Click GENERATE PROJECT
  * Open the project in Visual Studio
  * Open file ofApp.h and include header file
  like this:
  ```
  #include "ofMain.h
  #include "ofxAffinetransformation.h"
  ```
  * Add initialize code in ofApp.h
  ```
  class ofApp : public ofBaseApp {
    public:
    ...
        ofxAffineTransformation aT;
  }
  ```
  * Open ofApp.cpp file and add setting code
  ```
  void ofApp::setup() {
    aT.setCross(128);
    aT.calAffineTransform(false);
  }
  void ofApp::mouseMoved(int x, int y ){
  	aT.checkCross();
  	aT.applyAffineTransformation(x, y);
  }
  void ofApp::mouseDragged(int x, int y, int button){
  	if (button == OF_MOUSE_BUTTON_LEFT)
  		aT.updateCross();
  }
  void ofApp::mouseReleased(int x, int y, int button){
  	aT.releaseCross();
  }
  ```
