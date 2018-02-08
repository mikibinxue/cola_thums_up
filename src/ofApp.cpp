#include "ofApp.h"

float shrinkScale = 1.0;
float pulseScale = 1.0;

int stage = 1;

float starting_y;
bool pouring = false;
bool startLerp = false;
float rotation_inc = 0.0;

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);

	shrink.reset(shrinkScale);
	shrink.setCurve(LINEAR);
	shrink.setDuration(5.0);

	pulse.reset(pulseScale);
	pulse.setRepeatType(LOOP_BACK_AND_FORTH);
	pulse.setCurve(EASE_OUT);
	pulse.setDuration(0.25f);
	pulse.animateTo(1.25);

	int ind_positions[11][2] = {
		{ 765,740 },
		{ 770,1178 },
		{ 765,272 },
		{ 835,1275 },
		{ 760,1363 },
		{ 690,1339 },
		{ 803,196 },
		{ 790,750 },
		{ 870,895 },
		{ 685,863 },
		{ 760,1344 },
	};

	int us_positions[8][2] = {
		{ 755,752 },
		{ 764,1187 },
		{ 755,1260 },
		{ 792,980 },
		{ 787,1028 },
		{ 661,985 },
		{ 777,435 },
		{ 765,468 }
	};

	int us_mass[8] = { 1,10,15,20,15,10,13,25 };

	int ind_mass[11] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};

	for (int i = 0; i < 11; i++) {
		string s = "images/in_";
		string ext = ".png";
		string newStr = s + std::to_string(i+1) + ext;
		ofVec3f pos(ind_positions[i][0], ind_positions[i][1], 0);
		Image temp;
		temp.setup(newStr, i, pos, ind_mass[i]);
		temp.resize();
		ind_images.push_back(temp);
	}

	for (int i = 0; i < 8; i++) {
		string s = "images/us_";
		string ext = ".png";
		string newStr = s + std::to_string(i) + ext;
		ofVec3f pos(us_positions[i][0], us_positions[i][1], 0);
		Image temp;
		temp.setup(newStr, i, pos, us_mass[i]);
		temp.resize();
		us_images.push_back(temp);
	}

	cokeMusic.load("coke.mp3");
	cokeMusic.play();

	indiaMusic.load("india.mp3");
    indiaMusic.setVolume(0.35);
    
    myFont.load("fonts/AppleChancery.ttf", 70);
}

//--------------------------------------------------------------
void ofApp::update() {

	float dt = 1.0f / 60.0f;

	shrink.update(dt);
	pulse.update(dt);

	if (stage < 3) {
		ofBackground(255);
	}
	else {
		float background_red = ofMap(pulse.val(), 1, 1.25, 0, 255);
		ofBackground(background_red, 0, 255);
	}

	if (startLerp) {
		shrink.animateTo(0.25f);
		startLerp = false;
	}

}

//--------------------------------------------------------------
void ofApp::draw() {

	// US 
	if (stage == 1) {

        
        
		if (pouring) {
			for (int i = 0; i < us_images.size(); i++) {
				if (i > 0) {
					ofVec3f imagePos = us_images[i].position;
					ofVec3f attractorPos(ofGetWidth() / 2, -500);

					ofVec3f force = attractorPos - imagePos;
					force.normalize();
					force *= 0.5;

					us_images[i].applyForce(force);
					us_images[i].setScale(shrink.val());
				}
				if (us_images[3].position.y <-100) {
					stage = 2;
				}
			}

		}
		for (int i = 0; i < us_images.size(); i++) {
			us_images[i].update();
			us_images[i].draw();
		}
	}

	// US BOTTLE SPINNING
	else if (stage == 2) {
        us_images[0].setRotation(us_images[0].rotation + rotation_inc);
		us_images[0].update();
		us_images[0].draw();
		if (rotation_inc < 30) {
			rotation_inc += 0.05;
		}
		else {
			stage = 3;
			indiaMusic.play();
			indiaMusic.setPositionMS(18250);
			cokeMusic.stop();
		}
	}

	// INDIA BOTTLE
	else if (stage == 3) {
       
		for (int i = 0; i < ind_images.size(); i++) {
			ind_images[i].update();
			ind_images[i].draw();

			if (i > 0) {
				ind_images[i].setScale(pulse.val() + i * 0.01);
			}
		}
        
        ofPushMatrix();
            ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);
            ofRotate(sin(ofGetFrameNum()*0.3)*10);
            ofTranslate(-ofGetWidth() / 2, -ofGetHeight() / 2);
            myFont.drawString("Feel the Thunder", 50, 700);
        ofPopMatrix();

	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {
	
	float dy = y - starting_y;
	
	if (dy > 0) {

		float rotation_ang = ofMap(dy, 0, ofGetHeight(), 0,180);
		for (int i = 0; i < us_images.size();i++) {
			us_images[i].setRotation(rotation_ang);
			// everything but bottle
			if (rotation_ang > 90) {
				pouring = true;
			}
			else {
				pouring = false;
			}
		}
		if (rotation_ang > 90) {
			startLerp = true;
		}
		
	}
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {

	starting_y = y;

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {

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
