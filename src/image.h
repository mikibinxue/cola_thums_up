#pragma once
#pragma once

//
//  image.h
//  thums_up_sketch1
//
//  Created by Miki Bin on 2/7/18.
//

#ifndef image_h
#define image_h

#include "ofMain.h"

class Image {
public:

	//methods
	void setup(string fp, int _id, ofVec3f position, int mass);
	void update();
	void draw();
	void drawAt(ofVec3f pos);
	void resize();
	void resize(float factor);
	void setScale(float scale);
	void setRotation(float rotation);
	void applyForce(ofVec3f f);

	//variables
	ofImage img;

	int _id;
	float opacity = 1.0;
	float scale = 1.0;
	float rotation = 0.0;
	float mass = 1.0;

	ofVec3f position;
	ofVec3f vel;
	ofVec3f acc;

	Image();

private:
};

#endif /* image_h */

