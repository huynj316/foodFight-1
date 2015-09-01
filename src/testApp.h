#pragma once
#ifndef _TEST_APP
#define _TEST_APP

#include "ofxOpenNI.h"
#include "ofMain.h"
#include "ball.h"
#include "Splat.h"

class testApp : public ofBaseApp{
	
public:
    
	void setup();
	void update();
	void draw();
    void exit();
    void drawSplat();
	void playSplatSound();
	
    void userEvent(ofxOpenNIUserEvent & event);
    
	ofxOpenNI openNIDevice;
	
	ofSoundPlayer  splatSound;
    
    ofTrueTypeFont verdana;
	
	// body
	ofVec2f head;
	ofVec3f rightShoulder;
	ofVec2f	leftShoulder;
	ofVec2f	rightElbow;
	ofVec2f leftElbow;
	ofVec2f rightHip;
	ofVec2f leftHip;
	ofVec2f rightKnee;
	ofVec2f leftKnee;
	ofVec2f rightFoot;
	ofVec2f leftFoot;
	ofVec2f torsoJoint;
	
	//Throw Tracking
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
	
	ofImage splat[7];
	int currentSplat;
	
	ball myBall;
	
	ofImage bg; // bg img
	
	//	ofImage leftHandImg;
	//	ofImage rightHandImg;
	
	int requiredScore;
	int score;
	float now;
	
	int gameStatus; // 0 = start screen
	// 1 = playing
	// 2 = game over
	bool handTouching;
	
	
	vector<Splat> splatList;
	
	int min; // length of time for levels
	
	
    
};

#endif
