/*
 *  Splat.cpp
 *  openNiSample007
 *
 *  Created by Julie Huynh on 12/9/13.
 *  Copyright 2013 __MyCompanyName__. All rights reserved.
 *
 */

#include "Splat.h"

Splat::Splat( ) {
	
	splatSize = 100;
	
	trans = 255;
	
	rotation = ofRandom(360);
	
}

void Splat::setup( ofImage *_img ) {

	img = _img;
	
}

void Splat::update() {

	trans -= 1.0;
	
}

void Splat::draw() {
	ofPushMatrix();
	ofSetColor( 255, trans );
	ofTranslate( pos );
	//ofRotate( rotation * -3);
	ofScale( 0.25, 0.25, 0.25);
	ofRectMode( OF_RECTMODE_CENTER );
	img->draw( 0, 0 );
	ofPopMatrix();
}