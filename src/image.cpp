//
//  image.cpp
//  thums_up_sketch1
//
//  Created by Miki Bin on 2/7/18.
//

#include <stdio.h>
#include "image.h"

Image::Image() {
}

void Image::setup(string fp, int _id, ofVec3f _position, int _mass) {
	img.load(fp);
	_id = _id;
	position = _position * (min(ofGetWidth(), ofGetHeight()) / 1500.0);
	mass = _mass;
}

void Image::setRotation(float _rotation) {
	rotation = _rotation;
}

void Image::setScale(float _scale) {
	scale = _scale;
}

void Image::applyForce(ofVec3f _f) {
	_f /= mass;
	acc += _f;
}

void Image::update() {
	vel += acc;
	position += vel;
	vel *= 0.995;
	acc *= 0;
}

void Image::draw() {
    ofSetRectMode(OF_RECTMODE_CENTER);
	ofPushMatrix();

	ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);
	ofRotate(rotation);
	ofTranslate(-ofGetWidth() / 2, -ofGetHeight() / 2);

	ofTranslate(position.x, position.y);
	ofScale(scale, scale);
	img.draw(0, 0);

	ofPopMatrix();
}

void Image::drawAt(ofVec3f pos) {
	ofSetRectMode(OF_RECTMODE_CENTER);
	img.draw(pos.x, pos.y);
	ofDisableAlphaBlending();
	ofPopMatrix();
}

void Image::resize() {
	
	float factor = (min(ofGetWidth(), ofGetHeight()) / 1500.0);
	img.resize(img.getWidth() * factor, img.getHeight() * factor);
}

void Image::resize(float _factor) {
	img.resize(img.getWidth() * _factor, img.getHeight() * _factor);
}