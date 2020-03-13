
//--------------------------------------------------------------
void ofApp::resetBall() {

	sphere->remove();
	sphere = new ofxBulletSphere();
	sphere->create(world.world, ofVec3f(50, 50, 50), 0.000001, ball_radius);
	sphere->add();
	sphere->setRestitution(ball_restitution);

}

//--------------------------------------------------------------
void ofApp::resetCar() {

	/*car->remove();
	car = new ofxBulletBox();
	car->create(world.world, ofVec3f(80, 30, 80), 1, 5, 4, 9);
	car->add();
	car->setRestitution(0);*/



	createCar();


}

void ofApp::resetTarget() {

	target.remove();

	if (levels == 5) {

		//Riduzione dimensioni porta e traslazione porta
		target.create(world.world, ofVec3f(xGround / 2, (yBack1) / 2  - overflow_target + yTarget / 2, 0), 0, xTarget, yTarget + overflow_target, zTarget);
	}
	else {
		//Riduzione dimensioni porta
		target.create(world.world, ofVec3f(xGround / 2, (yBack1 - overflow_target) / 2 + yTarget / 2, 0), 0, xTarget, yTarget + overflow_target, zTarget);
	}
	target.setProperties(.25, .95);
	target.add();


	
}

//--------------------------------------------------------------
void ofApp::play() {
	initialMenu = false;
	resetBall();
	resetCar();

	//Punteggio
	ofSetColor(255, 255, 255);
	score = 0;
	num_partita++;
	//car->activate();
	//COUNTDOWN
	start_countdown = ofGetSystemTimeMillis();
	end_countdown = start_countdown + time_countdown;

	//MUSIC
	soundCountdown.play();


}

void ofApp::restartPlay() {

	resetBall();
	resetCar();
	num_partita++;
	//Punteggio
	ofSetColor(255, 255, 255);
	score = 0;
	//car->activate();
	//TIMER
	start_timer = ofGetSystemTimeMillis();
	end_timer = start_timer + time_game;

}

void ofApp::settingLevel() {

	if (levels == 1) {
		overflow_target = 0;
		resetTarget();
	}

	if (levels == 2) {
		overflow_target = 15;
		resetTarget();
	}

	if (levels == 3) {
		overflow_target = 20;
		resetTarget();
	}

	if (levels == 4 && !checkLevel4) {
		level4();
	}

	if (levels == 5) {
		overflow_target = yBack;
		resetTarget();
	}

	if (levels > 5) {

		overflow_target = 15;
		resetTarget();
	}


	//TO DO: RESETTARE OVERFLOW AD OGNI LIVELLO

	if (levels == 6 && !checkLevel6) {
		level6();
	}

	if (levels == 7 && !checkLevel7) {
		level7();
	}

	if (levels == 8 &&  !checkLevel6 && !checkLevel7) {
		level8();
	}

	if (levels == 9 && !checkLevel9) {
		level9();
	}

	if (levels == 10) {

		//IL PALLONE NON DEVE TOCCARE TERRA
	}





	
}

void ofApp::level4() {


	if (!checkLevel4) {

		
		target.remove();
		//Riduzione dimensioni porta
		target.create(world.world, ofVec3f(xGround / 2, (yBack1 - overflow_target) / 2 + yTarget / 2, 0), 0, xTarget, yTarget + overflow_target, zTarget);
		target.setProperties(.25, .95);
		target.add();

		//Riduzione dimensioni porta e traslazione porta
		//target.create(world.world, ofVec3f(xGround / 2, (yBack1) / 2  - overflow + yTarget / 2, 0), 0, xTarget, yTarget + overflow, zTarget);

		
		if (overflow_target <= 30 && !reverseLevel4) {
			
			overflow_target = (overflow_target + 0.5);
			cout << overflow_target << endl;

			if (overflow_target > 30) {

				reverseLevel4 = !reverseLevel4;
				cout << reverseLevel4 << endl;
			}
	
		}

		else if (reverseLevel4) {

			overflow_target = (overflow_target - 0.5);
			cout << overflow_target << endl;
			
			if (overflow_target < 0) {

				reverseLevel4 = !reverseLevel4;

			}
		}

		//checkLevel1 = !checkLevel1;
		
	}
}

void ofApp::level6() {


	if (!checkLevel6) {

		ostacolo6.remove();
		ostacolo6.create(world.world, ofVec3f(xGround - overflow, 0, zGround / 2 ), 0, xOst6, yOst6, zOst6);
		ostacolo6.setProperties(.25, .95);
		ostacolo6.add();

		if (overflow <= xGround && !reverseLevel6) {

			overflow = (overflow + 1);
			cout << overflow << endl;

			if (overflow > xGround) {

				reverseLevel6 = !reverseLevel6;
				cout << reverseLevel6 << endl;
			}

		}

		else if (reverseLevel6) {

			overflow = (overflow - 1);
			cout << overflow << endl;

			if (overflow < 0) {

				reverseLevel6 = !reverseLevel6;

			}
		}

	}


}




void ofApp::level7() {



	if (!checkLevel7) {

		ostacolo7.remove();
		ostacolo7.create(world.world, ofVec3f(xGround/2 , 0 + overflow, zGround / 4), 0, xOst7, yOst7, zOst7);
		ostacolo7.setProperties(.25, .95);
		ostacolo7.add();

		if (overflow <= yBack && !reverseLevel7) {

			overflow = (overflow + 1);
			cout << overflow << endl;

			if (overflow > yBack) {

				reverseLevel7 = !reverseLevel7;
				cout << reverseLevel7 << endl;
			}

		}

		else if (reverseLevel7) {

			overflow = (overflow - 1);
			cout << overflow << endl;

			if (overflow < 0) {

				reverseLevel7 = !reverseLevel7;

			}
		}

	}


}


void ofApp::level8() {


	if (!checkLevel6) {

		ostacolo6.remove();
		ostacolo6.create(world.world, ofVec3f(xGround - overflow, 0, zGround / 2), 0, xOst6, yOst6, zOst6);
		ostacolo6.setProperties(.25, .95);
		ostacolo6.add();

		if (overflow <= xGround && !reverseLevel6) {

			overflow = (overflow + 1);
			cout << overflow << endl;

			if (overflow > xGround) {

				reverseLevel6 = !reverseLevel6;
				cout << reverseLevel6 << endl;
			}

		}

		else if (reverseLevel6) {

			overflow = (overflow - 1);
			cout << overflow << endl;

			if (overflow < 0) {

				reverseLevel6 = !reverseLevel6;

			}
		}

	}

	if (!checkLevel7) {

		ostacolo7.remove();
		ostacolo7.create(world.world, ofVec3f(xGround / 2, 0 + overflow, zGround / 4), 0, xOst7, yOst7, zOst7);
		ostacolo7.setProperties(.25, .95);
		ostacolo7.add();

		if (overflow <= xGround && !reverseLevel7) {

			overflow = (overflow + 1);
			cout << overflow << endl;

			if (overflow > xGround) {

				reverseLevel7 = !reverseLevel7;
				cout << reverseLevel7 << endl;
			}

		}

		else if (reverseLevel7) {

			overflow = (overflow - 1);
			cout << overflow << endl;

			if (overflow < 0) {

				reverseLevel7 = !reverseLevel7;

			}
		}

	}

}




void ofApp::level9() {


	if (!checkLevel9) {

		ostacolo9.remove();
		ostacolo9.create(world.world, ofVec3f(xBack1 + overflow, yOst9/2, 0), 0, xOst9, yOst9, zOst9);
		ostacolo9.setProperties(.25, .95);
		ostacolo9.add();

		if (overflow <= xTarget && !reverseLevel9) {

			overflow = (overflow + 1.25);
			cout << overflow << endl;

			if (overflow > xTarget) {

				reverseLevel9 = !reverseLevel9;
				cout << reverseLevel6 << endl;
			}

		}

		else if (reverseLevel9) {

			overflow = (overflow - 1.25);
			cout << overflow << endl;

			if (overflow < 0) {

				reverseLevel9 = !reverseLevel9;

			}
		}

	}

}
