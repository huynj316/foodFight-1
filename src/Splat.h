/*
 *  Splat.h
 *  openNiSample007
 *
 *  Created by Julie Huynh on 12/9/13.
 *  Copyright 2013 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once

#include "ofMain.h"

class Splat {

	public:
		Splat( );
		void setup( ofImage *_img );
		void update();
		void draw();
		
		ofVec2f pos;
		
		float splatSize;
		
		float trans;
	
		float rotation;
		
		ofImage  *img;
	
	
};
