#include "ofApp.h"
#include "level.h"
#include "gui.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);

	//Background
	background.load("background.jpg");

	//SCOREBOARD
	scoreboard.load("scoreboard.png");


	//MUSIC
	initSound.load("intro.mp3");
	initSound.play();
	initSound.setVolume(volume);
	soundGol.load("goal.mp3");
	soundBall.load("bounce.mp3");
	voiceGol.load("goal_voice.ogg");
	soundCountdown.load("countdown.mp3");
	generalSound.load("general.mp3");
	soundAcc.load("acceleration.ogg");
	whistle.load("whistle.mp3");

	/*light.enable();
	light.setPosition(ofVec3f(100, 100, 200));
	light.lookAt(ofVec3f(0, 0, 0));*/

	/*TEXTURE*/
	ofDisableArbTex();
	ofLoadImage(textureBall, "texture_ball.png");
	ofLoadImage(textureGround, "field.jpg");
	ofLoadImage(textureCar, "car_texture.jpg");
	//ofLoadImage(textureWall, "enclosure.jpg");
	//textureGround.bind(); 
	//textureGround.unbind();

	/*GUI*/

	resetBallButton.addListener(this, &ofApp::resetBall);
	resetCarButton.addListener(this, &ofApp::resetCar);
	playGame.addListener(this, &ofApp::play);
	restartGame.addListener(this, &ofApp::restartPlay);
	levelButton.addListener(this, &ofApp::settingLevel);

	gui_init.setup("GAME", "GAME", ofGetWidth()/2, ofGetHeight()/2);
	gui_init.add(playGame.setup("Start Game"));

	gui_music.setup("MUSIC", "MUSIC", ofGetWidth() - 125, 25);
	gui_music.add(volume.setup("Volume", 0.0,0.0,1.0));

	//gui_ball.add(ball_radius.setup("Raggio Pallone", 4, 0, 30));
	gui_level.setup("TARGET", "TARGET", ofGetWidth() / 2, 150);
	gui_level.add(levels.setup("Level", 0, 0, 10));
	gui_level.add(levelButton.setup("Apply"));
	//gui_ball.add(resetBallButton.setup("Reset Ball"));


	drawGuiGame();
	drawGuiBall();
	drawInitialGui();

	world.setup();
	world.setGravity(ofVec3f(0, -9.8, 0)); // Di default la gravit� 0,9.8,0 verso l'asse Y+
	world.enableGrabbing();
	world.enableDebugDraw();
	world.setCamera(&cam);

	
	ground.create(world.world, ofVec3f(xGround / 2, yGround / 2, zGround / 2), 0, xGround, yGround+overflow, zGround);
	ground.setProperties(.25, .95);
	ground.add();


	ceiling.create(world.world, ofVec3f(xGround / 2, yBack1, zGround / 2), 0, xGround, yGround, zGround);
	ceiling.setProperties(.25, .95);
	ceiling.add();

	/*back.create(world.world, ofVec3f(0, yBack/2, -xGround/2), 0, xBack, yBack, zBack);
	back.setProperties(.25, .95);
	back.add();*/


	back1.create(world.world, ofVec3f(xBack1 / 2, yBack1 / 2, 0), 0, xBack1, yBack1, zBack1);
	back1.setProperties(.25, .95);
	back1.add();


	target.create(world.world, ofVec3f(xGround / 2, yBack1 / 2 + yTarget / 2, 0), 0, xTarget, yTarget + overflow, zTarget);
	target.setProperties(.25, .95);
	target.add();


	back2.create(world.world, ofVec3f(xGround / 2 + xBack1, yBack1 / 2, 0), 0, xBack1, yBack1, zBack1);
	back2.setProperties(.25, .95);
	back2.add();


	right.create(world.world, ofVec3f(0, yBack1 / 2, zGround / 2), 0, xRight, yRight, zRight);
	right.setProperties(.25, .95);
	right.add();

	front.create(world.world, ofVec3f(xGround / 2, yBack1 / 2, zGround), 0, xFront, yFront, zFront);
	front.setProperties(.25, .95);
	front.add();

	left.create(world.world, ofVec3f(xGround, yBack1 / 2, zGround / 2), 0, xLeft, yLeft, zLeft);
	left.setProperties(.25, .95);
	left.add();


	//play();

	sphere = new ofxBulletSphere();
	sphere->create(world.world, ofVec3f(50, 50, 50), 0.000001, ball_radius);
	//sphere->add();
	//sphere->setRestitution(3);

	car = new ofxBulletBox();
	car->create(world.world, ofVec3f(100, 10, 100), 1, 7, 4, 10);
	//car->add();
	//car->setRestitution(0);

	ofEnableDepthTest();
	ofSetVerticalSync(true);

	cam.setPosition(ofVec3f(60, 30, 160)); //Posizione inziale camera
	cam.disableMouseInput();
	//cam.setDistance(100);

	box.setPosition(0, 0, 0); // asse all'origine
	box.set(0.001);



	//LOADING 3D CAR

	octaneModel.loadModel("Octane.obj",20);
	cout << octaneModel.getNumMeshes() << endl;
	
	

	octaneModel.setScale(0.01, 0.01, 0.01);
	octaneModel.setPosition(20, 20, 20);
	octaneModel.setRotation(2,180.f, 1,0,0);


	ofVec3f scale(1, 1, 1);

	ofQuaternion startRot = ofQuaternion(1., 0., 0., PI);
	

	ofDisableDepthTest();
}


//--------------------------------------------------------------
void ofApp::update() {
	world.update();

}


void ofApp::effectGol() {
	ofSetColor(0, 0, 0);

	//MUSIC WHEN SCORE
	soundGol.setVolume(0.25);
	soundGol.play();
	voiceGol.setVolume(1);
	voiceGol.play();

}



//--------------------------------------------------------------
void ofApp::draw() {

	/*glEnable(GL_DEPTH_TEST);
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	glPushClientAttrib(GL_CLIENT_ALL_ATTRIB_BITS);
	glEnable(GL_NORMALIZE);
	glDisable(GL_CULL_FACE);*/
	

	if (SplashScreen == true) {

		background.draw(0, 0);
		gui_init.draw();

		//MUSIC
		gui_music.draw();
		initSound.setVolume(volume);

	}

	else {

		initSound.stop();

		if (!started) {
			

			if (ofGetSystemTimeMillis() < end_countdown) {
				countdown = end_countdown - ofGetSystemTimeMillis();
				countdown = countdown / 1000;

				ofDrawBitmapString(countdown+1, ofGetWidth()/2, ofGetHeight()/2);
			
				
			}

			else {
				//MUSIC
				generalSound.play();
				generalSound.setLoop(true);
				generalSound.setVolume(volume);

				//TIMER
				start_timer = ofGetSystemTimeMillis();
				end_timer = start_timer + time_game;

				started = !started;
			}




		}
		else {
			ofEnableAlphaBlending();
			ofSetColor(255, 255, 255);
			scoreboard.draw(ofGetWidth()/2 -scoreboard.getWidth()/2 , 100);
			cam.begin();
			ofSetColor(255, 255, 255);
			
			settingLevel();
			
			//if (scelta == 1 ) {
			//	level1();
		
				textureWall.unbind();
				target.draw();
				textureWall.bind();
			//}
			//else

			//{
			//	resetTarget();
			//	textureWall.unbind();
			//	target.draw();
			//	textureWall.bind();
			//}
			
			
			ofFill();
			/*GROUND*/
			textureGround.bind(); 
			ground.draw();
			textureGround.unbind();

			ofNoFill();
			ceiling.draw();
			textureWall.bind();
			back1.draw();
			textureWall.unbind();
			//fgegege//

			textureWall.bind();
			back2.draw();
		
			right.draw();
			textureWall.unbind();
			textureWall.bind();
			left.draw();
			textureWall.unbind();
			//textureWall.bind();
			front.draw();
			//textureWall.unbind();

			ofFill();

			if (sphere->checkCreate() == true && car->checkCreate() == true) {

				ofSetColor(255, 0, 0);
				//textureBall.bind(); //PROBLEMI DELLA TEXTURE CON OFBULLET
				sphere->draw();
				//textureBall.unbind();
				ofNoFill();
				ofSetColor(250, 250, 100);
				car->draw();

				if (sphere->getPosition().z + sphere->getRadius() < 0) { //CONTROLLO PER VEDERE SE E' GOL

					resetBall();

					if (ofGetSystemTimeMillis() < end_timer) {
						score++;
						effectGol();

						//Setto l'effetto
						start_effect = ofGetSystemTimeMillis();
						end_effect = start_effect + time_effect;
						//effect = end_effect - ofGetSystemTimeMillis();
						//effect = effect / 1000;

					}

				}

				//Controllo per non far andare la macchina dentro la porta
				if (car->getPosition().z + car->getWidth() / 4 < 0) {
					ofVec3f posCar = car->getPosition();
					car->remove();
					car = new ofxBulletBox();
					car->create(world.world, posCar, 1, 5, 4, 9);
					car->add();


				}


				//cout << sphere->getPosition().y << endl;

			}

			//effectGol();

			box.draw();
			//box.drawAxes(1000);

			//Il modello 3D segue l'oggetto CAR (BULLET BOX)
			ofFill();
			textureCar.bind();
			octaneModel.drawFaces();
			//octaneModel.setRotation(0, car->getRotationAngle(), car->getRotation().x, car->getRotation().y, car->getRotation().z); NON FUNZIONA LA ROTAZIONE
			octaneModel.setPosition(car->getPosition().x, car->getPosition().y - 1, car->getPosition().z + 1);
			textureCar.unbind();
			cam.end();

			glDisable(GL_DEPTH_TEST);
			ofSetColor(0, 0, 255);

			//EFFECT WHEN SCORE
			if (ofGetSystemTimeMillis() < end_effect) {

				ofSetColor(0, 0, 0);
				ofDrawBitmapString("GOOOOOL", ofGetWidth() / 2, ofGetHeight() / 2);
				//ofBackground(ofRandom(256), ofRandom(256), ofRandom(256));

			}

			if (num_partita > 0) {

				if (ofGetSystemTimeMillis() < end_timer) { //PARTITA IN CORSO

					timer = end_timer - ofGetSystemTimeMillis();
					timer = timer / 1000;				

				}

				else if (ofGetSystemTimeMillis() > end_timer) { //PARTITA CONCLUSA 
					
					ofDrawBitmapString("PARTITA CONCLUSA", (ofGetWidth() / 2), 25);
					//whistle.play();
					//whistle.setLoop(false);

				}
			}

			else {
				//ofDrawBitmapString("Premi 'Start Game' per iniziare a giocare!", (ofGetWidth() / 2), 25);

			}



			/***** RENDER GUI *****/
			ofDisableDepthTest();


			gui_game.draw();
			gui_ball.draw();
			gui_stats.draw();
			gui_level.draw();

			//MUSIC
			gui_music.draw();
			generalSound.setVolume(volume);


			if (num_partita > 0) {
				gui_stats.clear();
				drawGuiGame();
				gui_stats.draw();
			}

			if (lockCamera) {
				cam.disableMouseInput();
			}

			else
			{
				cam.enableMouseInput();
			}

			//ofEnableDepthTest();

		}
	}
}



//--------------------------------------------------------------
void ofApp::keyPressed(int key) {


	if (key == '6' or key == 'd') { //SPOSTAMENTO A DESTRA
		car->applyCentralForce(ofVec3f(forza, frizione, 0));
	}


	if (key == '9') { //SPOSTAMENTO A DESTRA-AVANTI
		car->applyCentralForce(ofVec3f(forza, frizione, -forza));
	}

	if (key == '8' or key == 'w') { //SPOSTAMENTO AVANTI
		car->applyCentralForce(ofVec3f(0, frizione, -forza));
		
	}

	if (key == '7') { //SPOSTAMENTO A SINISTRA-AVANTI
		car->applyCentralForce(ofVec3f(-forza, frizione, -forza));
	}

	if (key == '4' or key == 'a') { //SPOSTAMENTO A SINISTRA
		car->applyCentralForce(ofVec3f(-forza, frizione, 0));
	}


	if (key == '1') { //SPOSTAMENTO INDIETRO-SINISTRA
		car->applyCentralForce(ofVec3f(-forza, frizione, forza));
	}

	if (key == '2' or key == 's') { //SPOSTAMENTO INDIETRO
		car->applyCentralForce(ofVec3f(0, frizione, forza));
	}

	if (key == '3') { //SPOSTAMENTO INDIETRO - DESTRA
		car->applyCentralForce(ofVec3f(forza, frizione, forza));
	}

	if (key == OF_KEY_TAB) { //SALTO
		car->applyForce(ofVec3f(0, -20, 0), ofVec3f(0, -20, 0));
	}

	if (key == 'r') {
		resetBall();

	}

	if (key == 't') {

		resetCar();
	}

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {

	if (key == '8' or key == 'w') { //SPOSTAMENTO AVANTI
		soundAcc.play();
		soundAcc.setVolume(1);

	}
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}