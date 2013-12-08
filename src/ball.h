/*
 *  ball.h
 *  openNiSample007
 *
 *  Created by Julie Huynh on 11/20/13.
 *  Copyright 2013 __MyCompanyName__. All rights reserved.
 *
 */
#pragma once
#include "ofMain.h"
class ball{
public:
	void init();
	void update(ofVec3f hand, ofVec3f prev_hand, ofVec3f vel);
	void draw(ofVec3f hand);
	
	ofVec3f pos;
	ofVec3f vel;
	int movementCount;
	float radius;
	bool isTracking;
	bool isThrowing;
	
	ofImage handImg[7];
	int currentFood;
	
	
//	ofImage rightHandImg;
};

