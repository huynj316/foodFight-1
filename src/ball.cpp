/*
 *  ball.cpp
 *  openNiSample007
 *
 *  Created by Julie Huynh on 11/20/13.
 *  Copyright 2013 __MyCompanyName__. All rights reserved.
 *
 */

#include "ball.h"
void ball::init(){
	radius = 30;
	isTracking = false;
	isThrowing = false;
	movementCount = 0;
	
	currentFood = floor((ofRandom(7))); //floor will give integer btwn 0-6, select this line for every time you select your food
	for (int i=0; i<7; i++) {
		
		string food = "images/food" + ofToString(i) + ".png";
		handImg[i].loadImage(food);
	}


}
void ball::update(ofVec3f hand, ofVec3f prev_hand, ofVec3f handVel){
	
	
	//Trigger the average tracking
	//80 is the threshold!
	if (handVel.length() > 80 && hand.z < prev_hand.z && movementCount == 0) {
		
		currentFood = floor((ofRandom(7)));
		isTracking = true;
		cout << "threw!" << endl;
	}
	//else if (handVel.length() < 10) {
	else if (movementCount > 60) {
		//Throws!		
		//isTracking = false;
		//vel /= movementCount;
		movementCount = 0;
		pos = ofVec3f (2000, 2000, 0);
		vel.set (0, 0, 0);
	}	

	//Tracks
	if(isTracking){
		pos = hand;
		vel = (handVel/3);
		//movementCount ++;
		movementCount = 1;
		isTracking = false;
	}else if (movementCount > 0){
		pos += vel;
		//movementCount = 1;
		movementCount++;
	}
	
}

void ball::draw(ofVec3f hand){
	
	ofPushMatrix();
	ofTranslate(0, 0, hand.z);
	
		if (isTracking) {
			//ofSetColor(ofColor::red);
		}
		else {
			//ofSetColor(ofColor::aquamarine);		
		}
		//ofCircle(pos.x, pos.y, pos.z * (-1), radius);
	
		if(pos.x > 5 && pos.y > 5){ //only draw if NOT in the corner.
		
			//handImg -> draw(pos.x, pos.y, pos.z*(-1), radius, radius);
			//cout << "draw food" << endl;
			
			handImg[currentFood].draw(pos.x, pos.y, pos.z*(-1), radius, radius);	
		}
	
	ofPopMatrix();	
}

