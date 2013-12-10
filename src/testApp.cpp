#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup() {
	
	playing = true;
	
	splatSound.loadSound("audio/splatter.mp3");
	
	target.x = 200;
	target.y = 200;
	target.z = 0;
	hasHit = false;
	
	currentSplat = floor((ofRandom(7))); //floor will give integer btwn 0-6, select this line for every time you select your food
	for (int i=0; i<7; i++) {
		
		string splatter = "images/splat" + ofToString(i) + ".png";
		splat[i].loadImage(splatter);
	}
	
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
	
	requiredScore = 10;
	
}

//--------------------------------------------------------------
void testApp::update(){
    openNIDevice.update();
	
	ofSoundUpdate();
	
	long currTime = ofGetElapsedTimeMillis();
	int min = 60000;
	
	//playing = false; //uncomment to see gameover screen
	
	for (int i = 0; i < splatList.size(); i++ ) {
		splatList[i].update();
	}
	
	
	if(hasHit){
		score += 1;
		
		target.x = ofRandom(600);
		target.y = ofRandom(400);
		hasHit = false;
		

		
//		if (currTime > min && currTime < min*2){ //1  -  2 min
//			if (score < 10){
//				playing = false;
//			}
//		}
//		
//		else if (currTime >= min*2 && currTime < min*3){ //2 - 3 min
//			if (score < 20){
//				playing = false;
//			}
//		}
//		
//		else if (currTime >= min*3 && currTime < min*4){ //2 - 3 min
//			if (score < 30){
//				playing = false;
//			}
//		}
		

	}
	
	if ( currTime % min < 15 ) {
		if ( score < requiredScore ) {
			playing = false;
		}
		requiredScore += 10;
		
		cout << requiredScore << endl;
	}
	
}

//--------------------------------------------------------------
void testApp::draw(){
	

		ofSetColor(255);
		
		ofPushMatrix();
		ofScale(ofGetWidth()/640, ofGetHeight()/480);
			// draw debug (ie., image, depth, skeleton)
			// openNIDevice.drawDebug();
		
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
				//cout << "wtf" << endl;
			
			}
			
			ofNoFill();		
			ofSetColor(ofColor::white);		
			ofSetLineWidth(5);
			ofCircle(target.x, target.y, 50);
			
			ofFill();

			drawSplat();
			
			for (int i = 0; i < splatList.size(); i++ ) {
				splatList[i].draw();
			}
			
			prev_rightHand = rightHand;
			prev_leftHand = leftHand;
		}
	
	if (playing){

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
		ofDrawBitmapString("Current Score: "+ofToString(score), (WIDTH/2), 50);
		ofDrawBitmapString("Time (seconds): "+ofToString((ofGetElapsedTimeMillis()/1000)), (WIDTH/4), 50);
	
	} else {
		
	//	ofRect(	//draw rect over background
		
		//restart button
		ofSetColor(ofColor::pink);
		ofCircle(WIDTH/2, HEIGHT/2, 50);
		// (ballX >= ofGetWidth() || ballX <= 0 )
		if ( hand.x >= WIDTH/2 && hand.y <= HEIGHT/2  ) {
			playing;
		}
		
		//quit button
		ofSetColor(ofColor::aquamarine);
		ofCircle(WIDTH/4, HEIGHT/4, 50);
		
		
		string msg = "Final Score:"+ofToString(score);
		verdana.drawString(msg, WIDTH/3, 100);	//final score
		//draw game over screen with final score
	}
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
	if (now - ofGetElapsedTimef() > - .5 && now - ofGetElapsedTimef()<0 ) {
		currentSplat = myBall.currentFood;
		//splat[currentSplat].draw((lastTarget.x-45), (lastTarget.y-35), 90, 70); //fix and declare
		
		Splat s;
		s.setup( &splat[currentSplat] );
		s.pos.set( lastTarget.x - 45, lastTarget.y - 35 );
		splatList.push_back( s );
		
		//cout << ofToString( now - ofGetElapsedTimef() )<< endl;
		playSplatSound();
	}
}

//--------------------------------------------------------------
void testApp::playSplatSound(){
	
	if (splatSound.getIsPlaying() == false){
		//synth.setPan(ofMap(x, 0, widthStep, -1, 1, true));  <-- how to move it between L and R channels	
		splatSound.play();
	}
}


