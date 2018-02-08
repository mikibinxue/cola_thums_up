#pragma once

#include "ofMain.h"
#include "image.h"
#include "ofxAnimatableFloat.h"
#include "ofxAnimatableOfPoint.h"
#include "ofxAnimatableOfColor.h"

//#define TIME_SAMPLE
#ifdef TIME_SAMPLE
#include "ofxTimeMeasurements.h"
#endif


class ofApp : public ofBaseApp {

public:
	void setup();
	void update();
	void draw();

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);

	vector<Image> ind_images;
	vector<Image> us_images;

	bool clicked = true;

	ofxAnimatableFloat shrink;
	ofxAnimatableFloat pulse;

	ofSoundPlayer cokeMusic;
	ofSoundPlayer indiaMusic;
    
    ofTrueTypeFont myFont;
};
