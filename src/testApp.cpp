#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup() {
	
		
//	leftHandImg.loadImage("images/pizza.png");
//	rightHandImg.loadImage("images/chicken.png");
	
	target.x = 200;
	target.y = 200;
	target.z = 0;
	hasHit = false;
	targetHitImg.loadImage("images/splat.png");
	
//	isThrowing = false;
	myBall.init();
    
//	ofEnablerightBlendMode(ofBlendMode ADD); // this affects png
    ofSetLogLevel(OF_LOG_VERBOSE);

    openNIDevice.setup();
    openNIDevice.addImageGenerator();
    openNIDevice.addDepthGenerator();
    openNIDevice.setRegister(true);
    openNIDevice.setMirror(true);
    openNIDevice.addUserGenerator();
    openNIDevice.setMaxNumUsers(2);
    openNIDevice.start();
    
    // set properties for all user masks and point clouds
    //openNIDevice.setUseMaskPixelsAllUsers(true); // if you just want pixels, use this set to true
    openNIDevice.setUseMaskTextureAllUsers(true); // this turns on mask pixels internally AND creates mask textures efficiently
    openNIDevice.setUsePointCloudsAllUsers(true);
    openNIDevice.setPointCloudDrawSizeAllUsers(2); // size of each 'point' in the point cloud
    openNIDevice.setPointCloudResolutionAllUsers(2); // resolution of the mesh created for the point cloud eg., this will use every second depth pixel
    
    // you can alternatively create a 'base' user class
//    ofxOpenNIUser user;
//    user.setUseMaskTexture(true);
//    user.setUsePointCloud(true);
//    user.setPointCloudDrawSize(2);
//    user.setPointCloudResolution(2);
//    openNIDevice.setBaseUserClass(user);
      
    verdana.loadFont(ofToDataPath("verdana.ttf"), 96);
	
}

//--------------------------------------------------------------
void testApp::update(){
    openNIDevice.update();
	
	if(hasHit){
		score += 1;
		
		target.x = ofRandom(600);
		target.y = ofRandom(400);
		hasHit = false;
	}
}

//--------------------------------------------------------------
void testApp::draw(){
	ofSetColor(255);
    
    ofPushMatrix();
	ofScale(ofGetWidth()/640, ofGetHeight()/480);
		// draw debug (ie., image, depth, skeleton)
		openNIDevice.drawDebug();
	
    // use a blend mode so we can see 'through' the mask(s)
    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
    
    // get number of current users
    int numUsers = openNIDevice.getNumTrackedUsers();
    
    // iterate through users
    for (int i = 0; i < numUsers; i++){
        
        // get a reference to this user
        ofxOpenNIUser & user = openNIDevice.getTrackedUser(i);
		
		rightHand = user.getJoint(JOINT_RIGHT_HAND).getProjectivePosition();
		leftHand = user.getJoint(JOINT_LEFT_HAND).getProjectivePosition();
		//rightShoulder = user.getJoint(JOINT_RIGHT_SHOULDER).getProjectivePosition();
		
		vel_right = rightHand - prev_rightHand;
		vel_left = leftHand - prev_leftHand;
		
//		if (vel.length() > 50 && rightHand.z < prev_rightHand.z) {
//			isThrowing = true;
//
//		}else if (vel.length() < 10) {
//			isThrowing = false;
//		}
			
		
        // draw the silhouette
        user.drawMask();
        
		if (vel_left.length() > vel_right.length()) {
			vel = vel_left;
			hand = leftHand;
			prevHand = prev_leftHand;
		} else {
			vel = vel_right;
			hand = rightHand;
			prevHand = prev_rightHand;
		}
		
		myBall.update(hand, prevHand, vel);						
		
		if ((target.x - 40) < myBall.pos.x && myBall.pos.x < (target.x + 40) &&
			(target.y - 40) < myBall.pos.y && myBall.pos.y < target.y + 40) {
			
			hasHit = true;
			now = ofGetElapsedTimef();
			lastTarget.x = target.x;
			lastTarget.y = target.y;
				cout << "wtf" << endl;
		
		}
		
		ofNoFill();		
		ofSetColor(ofColor::white);		
		ofSetLineWidth(5);
		ofCircle(target.x, target.y, 50);
		
		ofFill();

		drawSplat();
		prev_rightHand = rightHand;
		prev_leftHand = leftHand;
    }

	myBall.draw(hand);	
   
    ofDisableBlendMode();
    ofPopMatrix();
    
    // draw some info regarding frame counts etc
//	ofSetColor(0, 255, 0);
	//string msg = " MILLIS: " + ofToString(ofGetElapsedTimeMillis()) + " FPS: " + ofToString(ofGetFrameRate()) + " Device FPS: " + ofToString(openNIDevice.getFrameRate());
//    
//	verdana.drawString(msg, 20, openNIDevice.getNumDevices() * 480 - 20);
		
	//cout << vel.length() << endl;
	//draw svg file
	//svg.draw();
	
	
	ofSetColor(255);
	verdana.loadFont(ofToDataPath("verdana.ttf"), 96);
	ofDrawBitmapString("current score: "+ofToString(score), (WIDTH/2), 50);
	

}

//--------------------------------------------------------------
void testApp::userEvent(ofxOpenNIUserEvent & event){
    // show user event messages in the console
    ofLogNotice() << getUserStatusAsString(event.userStatus) << "for user" << event.id << "from device" << event.deviceID;
}

//--------------------------------------------------------------
void testApp::exit(){
    openNIDevice.stop();
}

//--------------------------------------------------------------
void testApp::drawSplat(){
	if (now - ofGetElapsedTimef() > -0.75 && now - ofGetElapsedTimef()<0) {
		targetHitImg.draw((target.x-45), (target.y-35), 90, 70);
		cout << ofToString( now - ofGetElapsedTimef() )<< endl;
	}
}


