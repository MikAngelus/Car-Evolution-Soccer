#include "ofApp.h"
#include "level.h"
#include "gui.h"
#include "car.h"
#include "arena.h"
#include <iostream>  
#include <fstream>  
#include <string>  

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
	ofLoadImage(textureWheels, "wheels.png");
	ofLoadImage(textureWall, "enclosure.jpg");
	//textureGround.bind(); 
	//textureGround.unbind();

	/*GUI*/

	resetBallButton.addListener(this, &ofApp::resetBall);
	resetCarButton.addListener(this, &ofApp::resetCar);
	playGame.addListener(this, &ofApp::play);
	restartGame.addListener(this, &ofApp::restartPlay);
	levelButton.addListener(this, &ofApp::settingLevel);
	rules.addListener(this, &ofApp::readRules);
	buttonHistory.addListener(this, &ofApp::readHistory);
	


	drawInitialGui();
	drawGuiGame();
	drawGuiSetting();
	drawFirstGui();
	



	//SETUP CAR
	createCar();
	eur_deg = wheel1.getOrientationEulerDeg();


	//CREATE NEW ARENA
	createArena();


	//CREATE OBSTACLE
	createObstacle();
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

	//load font
	title.loadFont("ea.ttf", 100);
	subtitle.loadFont("ea.ttf", 75);
	label.loadFont("ea.ttf", 15);
	ofxGuiSetFont("ea.ttf", 12);

}


//--------------------------------------------------------------
void ofApp::update() {
	world.update();

}


void ofApp::insertNick() {

	nickname = ofSystemTextBoxDialog("Insert your Nickname", nickname);

}



void ofApp::effectGol() {

	//MUSIC WHEN SCORE
	soundGol.setVolume(volume-0.05);
	soundGol.play();
	voiceGol.setVolume(volume+0.3);
	voiceGol.play();

}

void ofApp::readHistory() {

	activeHistory = true;
	linesOfTheFile.clear();

	ofBuffer buffer = ofBufferFromFile("history.txt");
	for (auto line : buffer.getLines()) {
		linesOfTheFile.push_back(line);
	}
}

void ofApp::readRules() {

	activeRules = true;
	linesOfTheFile.clear();

	ofBuffer buffer = ofBufferFromFile("rules.txt");
	for (auto line : buffer.getLines()) {
		linesOfTheFile.push_back(line);
	}

}

//--------------------------------------------------------------
void ofApp::draw() {

	/*glEnable(GL_DEPTH_TEST);
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	glPushClientAttrib(GL_CLIENT_ALL_ATTRIB_BITS);
	glEnable(GL_NORMALIZE);
	glDisable(GL_CULL_FACE);*/
	

	if (initialMenu == true) {
		ofSetColor(255, 255, 255);
		background.draw(0, 0);
		//drawInitialGui();
		gui_first.draw();
		title.drawString("CAR SOCCER EVOLUTION", 250, 120);

		
		//fontSize++;
		//font.drawString("CIAONE", ofGetWidth() / 2, ofGetHeight() / 2);


		if (nickname.empty()) {

			insertNick();
		}
		
		subtitle.drawString("Welcome " + nickname, ofGetWidth() / 2 - ofGetWidth() / 4 +75, 300);

	
		if (activeRules || activeHistory) {

			int padding = 18;
			ofSetColor(255, 255, 255);
			ofDrawRectRounded(ofGetWidth() / 2 + 125, ofGetHeight() / 2 , 500, 250, 10);
			
			ofSetColor(0, 0, 0);
			for (int j = 0; j < linesOfTheFile.size(); j++) {

				label.drawString(linesOfTheFile[j], ofGetWidth() / 2 + 125 + padding, ofGetHeight() / 2 + padding*2 +j*20);

			}

		}

		completed = false;
		levels = 0;
	}

	else {

		initSound.stop();
		

		
		if (!started) {
			

			if (ofGetSystemTimeMillis() < end_countdown) {

				ofSetColor(255, 255, 255);
				background.draw(0, 0);

				countdown = end_countdown - ofGetSystemTimeMillis();
				countdown = countdown / 1000;
				
				title.drawString(ofToString(countdown+1), ofGetWidth()/2, ofGetHeight()/2);
			
				
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



			//scoreboard.draw(ofGetWidth()/2 -scoreboard.getWidth()/2 , 100);

			if (!completed) {
			subtitle.drawString("Level " + ofToString(readLevel), ofGetWidth() / 2 - 150, 100);
			label.drawString("Second remaining " + ofToString(timer), ofGetWidth() / 2 - 75, 150);	
			}

			cam.begin();
			ofSetColor(255, 255, 255);
			
			
			
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
			
			//ofSetColor(255, 0, 0);
			ofFill();

			/*GROUND*/
			textureGround.bind(); 
			ground.draw();
			textureGround.unbind();
			
	
			settingLevel();
			
			if (levels == 6) {
				
				ostacolo6.draw();
			}
			
			if (levels == 7) {

				ostacolo7.draw();
			}
			
			if (levels == 8) {
				ostacolo6.draw();
				ostacolo7.draw();

			}

			if (levels == 9) {
		
				ostacolo9.draw();
			}

			if (levels == 10) {
		
				ostacolo9.draw();
			}



			ofNoFill();
			ceiling.draw();
			textureWall.bind();
			back1.draw();
			textureWall.unbind();
		

			textureWall.bind();
			back2.draw();
		
			right.draw();
			textureWall.unbind();
			textureWall.bind();
			left.draw();
			textureWall.unbind();
			textureWall.bind();
			front.draw();
			textureWall.unbind();

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

						if (levels < 11) {
							levels = levels + 1;
						}
						
						overflow = 0; //resettare il movimento degli ostacoli

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


			//cout << "Centro Macchina:" << point_center.getPosition() << "Palla:" << sphere->getPosition() << endl;

			/*Movimento CAR*/
			drawCar();
		
			//cout << wheel_deg << endl;
			//cout << speed << endl;

			if (point_center.getPosition().x > sphere->getPosition().x - distance && point_center.getPosition().x < sphere->getPosition().x + distance) {

				if (point_center.getPosition().y + distance > sphere->getPosition().y - ball_radius && point_center.getPosition().y + distance < sphere->getPosition().y + ball_radius) {

					if (point_center.getPosition().z > sphere->getPosition().z - distance && point_center.getPosition().z < sphere->getPosition().z + distance) {

						
						cout << "palla colpita" << endl;
						cout << sphere->getPosition().y << endl;

				
						if (marcia) {

							sphere->applyCentralForce(ofVec3f(-(speed * sin(theta / 360 * 2 * PI) / 300), 0, -(speed * cos(theta / 360 * 2 * PI) / 300)));
						}

						else if (retromarcia) {

							sphere->applyCentralForce(ofVec3f((speed * sin(theta / 360 * 2 * PI) / 300), 0, (speed * cos(theta / 360 * 2 * PI) / 300)));

						}
					}
				}
			}
				

				
	
			/*car->remove();
			car = new ofxBulletBox();
			car->create(world.world, ofVec3f(point_center.getPosition()), 1, 7, 4, 10);
			car->add();
			car->draw();*/

			box.draw();
			//box.drawAxes(1000);

			//Il modello 3D segue l'oggetto CAR (BULLET BOX)
			ofFill();
			//textureCar.bind();
			//octaneModel.drawFaces();
			//octaneModel.setRotation(0, car->getRotationAngle(), car->getRotation().x, car->getRotation().y, car->getRotation().z); NON FUNZIONA LA ROTAZIONE
			//octaneModel.setPosition(car->getPosition().x, car->getPosition().y - 1, car->getPosition().z + 1);
			//textureCar.unbind();
			cam.end();

			glDisable(GL_DEPTH_TEST);
			ofSetColor(0, 0, 255);


			if (levels > 10 && !completed) {

				completed = true;
				timer = end_timer - ofGetSystemTimeMillis();
				timer = timer / 1000;
				timeCompleted = (time_game/1000) - timer;
				readLevel = levels;


			}

			//EFFECT WHEN SCORE
			if (ofGetSystemTimeMillis() < end_effect) {

				if (levels < 10) {
					subtitle.drawString("GOOOOOL", ofGetWidth() / 2 - 150, ofGetHeight() / 2);
					//ofBackground(ofRandom(256), ofRandom(256), ofRandom(256));
				}

			}

			if (num_partita > 0) {


				//if(endsphere->applyCentralForce(ofVec3f(0, 000000000000001, 0));

				if (ofGetSystemTimeMillis() < end_timer) { //PARTITA IN CORSO

					timer = end_timer - ofGetSystemTimeMillis();
					timer = timer / 1000;	
					readLevel = levels;

				}

				else if (ofGetSystemTimeMillis() > end_timer) { //PARTITA CONCLUSA 


					completed = true;
					timeCompleted = time_game / 1000;


				
				}


				if (completed) { // match concluso

					//background.draw(0, 0);
				
					if (levels > 10) {

						subtitle.drawString("YOU WIN!\nLevel completed: " + ofToString(readLevel - 1) + "\nTime: " + ofToString(timeCompleted) + " seconds", ofGetWidth() / 2 - ofGetWidth() / 4, ofGetHeight() / 2 - 75);

					}
					else {
						subtitle.drawString("Game over!\nLevel completed: " + ofToString(readLevel - 1) + "\nTime: " + ofToString(timeCompleted) + " seconds", ofGetWidth() / 2 - ofGetWidth() / 4, ofGetHeight() / 2 - 75);
					}
			
					if (!savedHistory) {

						//Salvataggio punteggio
						ofstream fileOUT("data/history.txt", ios::app); // open history.txt in append mode
						fileOUT << nickname << " - level " << (readLevel-1) << " - " << timeCompleted << " seconds" << endl; // append text to the end of the file
						fileOUT.close(); // close the file
						savedHistory = true;

						//fischio finale
						whistle.play();
						whistle.setVolume(volume);
						whistle.setLoop(false);
						cout << "fischio finale" << endl;

					}
				}


			}

			
			else {
				//ofDrawBitmapString("Premi 'Start Game' per iniziare a giocare!", (ofGetWidth() / 2), 25);

			}

			


			/***** RENDER GUI *****/
			ofDisableDepthTest();


			gui_game.draw();
			
			gui_stats.draw();
	

			if (setting) {
				gui_setting.draw();
			}

			//MUSIC
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
	if (key == 'w') {

		cout << wheel1.getPosition().x << endl;

		if (controlArena()) {

			if (speed <= 0) {
				marcia = true;
			}
			else if (!marcia) {

				speed = speed / 2.5;
			}
		}

		else if (!controlArena()) {

			if (point_center.getPosition().x - distance + max_speed  > 0 || point_center.getPosition().x + distance - max_speed > left.getPosition().x ||
				point_center.getPosition().z - distance + max_speed > 0 || point_center.getPosition().z + distance - max_speed > front.getPosition().z ) {
				cout << "macchina piantata" << endl;

				if (speed <= 0) {
					retromarcia = true;
				}
				else if (!retromarcia) {

					speed = speed / 2.5;
				}

				speed = speed + 0.005;
				wheel_deg = wheel_deg + 0.01;
				cout << speed << endl;
				moveW();
			}





		}

	}


	if (key == 's') {
	


		if (controlArena()) {

			if (speed <= 0) {
				retromarcia = true;
			}
			else if (!retromarcia) {

				speed = speed / 2.5;
			}
		}

		else if (!controlArena()) {
		

			if (point_center.getPosition().x - distance + max_speed > 0 || point_center.getPosition().x + distance - max_speed > left.getPosition().x ||
				point_center.getPosition().z - distance + max_speed > 0 || point_center.getPosition().z + distance - max_speed > front.getPosition().z) {

				if (speed <= 0) {
					retromarcia = true;
				}
				else if (!retromarcia) {

					speed = speed / 2.5;
				}

				speed = speed + 0.005;
				wheel_deg = wheel_deg + 0.01;
				cout << speed << endl;
				moveS();
			}

		}
	}

	if (key == 'a') {

		if (controlArena()) {
			if (!rotation_left) {

				wheel1.rotateDeg(45, ofVec3f(0, 1, 0));
				wheel2.rotateDeg(45, ofVec3f(0, 1, 0));

				rotation_left = true;

			}
		}

	}

	if (key == 'd') {

		if (controlArena()) {
			if (!rotation_right) {

				wheel1.rotateDeg(-45, ofVec3f(0, 1, 0));
				wheel2.rotateDeg(-45, ofVec3f(0, 1, 0));
				rotation_right = true;
			}
		}
	}

	if (key == 'e') {


		activeRules=false;
		activeHistory = false;

	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {

	if (key == 'a') {

		if (rotation_left) {

			wheel1.rotateDeg(-45, ofVec3f(0, 1, 0));
			wheel2.rotateDeg(-45, ofVec3f(0, 1, 0));

			rotation_left = false;

		}

	}

	if (key == 'd') {


		if (rotation_right) {

			wheel1.rotateDeg(45, ofVec3f(0, 1, 0));
			wheel2.rotateDeg(45, ofVec3f(0, 1, 0));
			rotation_right = false;

		}

	}


	if (key == 'w') {

		sphere->applyCentralForce(ofVec3f(0.0000001, 0, 0.0000001));
		if (marcia) {
			marcia = false;
			rallentamento_marcia = true;
		}

	}

	if (key == 's') {

		sphere->applyCentralForce(ofVec3f(0.0000001, 0 , 0.0000001));
		if (retromarcia) {
			retromarcia = false;
			rallentamento_marcia = false;
		}
		

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
