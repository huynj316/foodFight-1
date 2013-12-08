#pragma once
#ifndef _TEST_APP
#define _TEST_APP

#include "ofxOpenNI.h"
#include "ofMain.h"
#include "ball.h"

class testApp : public ofBaseApp{

public:
    
	void setup();
	void update();
	void draw();
    void exit();
    void drawSplat();

    void userEvent(ofxOpenNIUserEvent & event);
    
	ofxOpenNI openNIDevice;
    
    ofTrueTypeFont verdana;
	
	ofVec3f rightHand;
	ofVec3f leftHand;
	ofVec3f hand;
	ofVec3f prev_rightHand;
	ofVec3f prev_leftHand;
	ofVec3f prevHand;
	ofVec3f dist_vect;
	float dist;
	
	bool isThrowing;
	
	ofVec3f vel_right;
	ofVec3f vel_left;
	ofVec3f vel;
	ofVec3f target;	
	ofVec2f lastTarget;
	bool hasHit;
	
	ofImage targetHitImg;
	
	ball myBall;
	
//	ofImage leftHandImg;
//	ofImage rightHandImg;
	
	int score;
	float now;
	

	
    
};

#endif
