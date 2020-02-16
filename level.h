
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

	car->remove();
	car = new ofxBulletBox();
	car->create(world.world, ofVec3f(80, 30, 80), 1, 5, 4, 9);
	car->add();
	car->setRestitution(0);

}

void ofApp::resetTarget() {

	target.remove();
	//Riduzione dimensioni porta
	target.create(world.world, ofVec3f(xGround / 2, (yBack1 - overflow) / 2 + yTarget / 2, 0), 0, xTarget, yTarget + overflow, zTarget);
	target.setProperties(.25, .95);
	target.add();

	//Riduzione dimensioni porta e traslazione porta
	//target.create(world.world, ofVec3f(xGround / 2, (yBack1) / 2  - overflow + yTarget / 2, 0), 0, xTarget, yTarget + overflow, zTarget);
}

//--------------------------------------------------------------
void ofApp::play() {
	SplashScreen = false;
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
		overflow = 0;
		resetTarget();
	}

	if (levels == 2) {
		overflow = 15;
		resetTarget();
	}

	if (levels == 3) {
		overflow = 20;
		resetTarget();
	}

	if (levels == 4 && !checkLevel4) {
		level4();
	}
	
}

void ofApp::level4() {


	if (!checkLevel4) {

		
		target.remove();
		//Riduzione dimensioni porta
		target.create(world.world, ofVec3f(xGround / 2, (yBack1 - overflow) / 2 + yTarget / 2, 0), 0, xTarget, yTarget + overflow, zTarget);
		target.setProperties(.25, .95);
		target.add();

		//Riduzione dimensioni porta e traslazione porta
		//target.create(world.world, ofVec3f(xGround / 2, (yBack1) / 2  - overflow + yTarget / 2, 0), 0, xTarget, yTarget + overflow, zTarget);

		
		if (overflow <= 30 && !reverseLevel4) {
			
			overflow = (overflow + 0.5);
			cout << overflow << endl;

			if (overflow > 30) {

				reverseLevel4 = !reverseLevel4;
				cout << reverseLevel4 << endl;
			}
	
		}

		else if (reverseLevel4) {

			overflow = (overflow - 0.5);
			cout << overflow << endl;
			
			if (overflow < 0) {

				reverseLevel4 = !reverseLevel4;

			}
		}

		//checkLevel1 = !checkLevel1;
		
	}
}
