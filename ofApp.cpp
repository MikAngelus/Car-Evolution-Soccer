#include "ofApp.h"
#include "level.h"
#include "gui.h"
#include "car.h"
#include "arena.h"
//Includiamo le librerie per la gestione dei file e delle stringhe
#include <iostream>  
#include <fstream>  
#include <string>  

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60); //Settiamo il framerate a 60

	//Background
	background.load("background.jpg");

	//Caricamento delle musiche di gioco
	initSound.load("intro.mp3");
	initSound.play();
	initSound.setVolume(volume);
	soundGol.load("goal.mp3");
	voiceGol.load("goal_voice.ogg");
	soundCountdown.load("countdown.mp3");
	generalSound.load("general.mp3");
	whistle.load("whistle.mp3");

	// Caricamento delle TEXTURE
	ofDisableArbTex(); //Permettere il corretto caricamento delle immagini come texture
	ofLoadImage(textureBall, "ball.jpg");
	ofLoadImage(textureGround, "field.jpg");
	ofLoadImage(textureWheels, "wheels.png");
	ofLoadImage(textureWall, "wall.png");
	ofLoadImage(textureWall, "wall.png");
	ofLoadImage(textureObstacle, "obstacle.jpg");
	ofLoadImage(textureBody, "red_carbon.jpg");

	// Setting dei pulsanti alle relative funzioni void
	resetBallButton.addListener(this, &ofApp::resetBall);
	resetCarButton.addListener(this, &ofApp::resetCar);
	playGame.addListener(this, &ofApp::play);
	restartGame.addListener(this, &ofApp::restartPlay);
	rules.addListener(this, &ofApp::readRules);
	buttonHistory.addListener(this, &ofApp::readHistory);
	
	// Inizializzo le GUI
	drawGuiGame();
	drawGuiStatistics();
	drawGuiSetting();
	drawGuiFirst();
	
	//Setup Car
	createCar();

	//Setup Arena
	createArena();

	//Setup Ostacoli
	createObstacle();

	//Inizializzo una nuova istanza del pallone
	sphere = new ofxBulletSphere();
	sphere->create(world.world, ofVec3f(50, 50, 50), 0.000001, ball_radius);

	ofEnableDepthTest(); //Abilitiamo GL Rendering in modalità Depth Test
	ofSetVerticalSync(true); // Setting del V-sync
	cam.setPosition(ofVec3f(60, 30, 160)); //Setting posizione inziale camera
	cam.disableMouseInput(); //Disabilitato gli input del mouse della camera
	ofDisableDepthTest(); //Disabilitiamo GL Rendering in modalità Depth Test

	//Caricamento FONT
	title.loadFont("ea.ttf", 100);
	subtitle.loadFont("ea.ttf", 75);
	label.loadFont("ea.ttf", 15);
	ofxGuiSetFont("ea.ttf", 12);

}

//--------------------------------------------------------------
void ofApp::update() {
	world.update(); //Aggiornamento della variale
}

void ofApp::insertNick() {

	nickname = ofSystemTextBoxDialog("Insert your Nickname", nickname); // Dialog Box che permettere di inserire e salvare il Nickname

}

void ofApp::effectGol() {

	//MUSIC WHEN SCORE
	soundGol.setVolume(volume-0.05);
	soundGol.play();
	voiceGol.setVolume(volume+0.3);
	voiceGol.play();

}

void ofApp::readHistory() { //Funzione legge la cronologia 

	activeHistory = true;
	linesOfTheFile.clear(); //Pulisce l'array che contiene le righe del file

	ofBuffer buffer = ofBufferFromFile("history.txt"); //Prende il file in input
	for (auto line : buffer.getLines()) {
		linesOfTheFile.push_back(line); //Inserisce le righe lette nel file
	}
}

void ofApp::readRules() {// Funzione legge le rgole

	activeRules = true;
	linesOfTheFile.clear();

	ofBuffer buffer = ofBufferFromFile("rules.txt"); //Prende il file in input
	for (auto line : buffer.getLines()) {
		linesOfTheFile.push_back(line);  //Inserisce le righe lette nel file
	}

}

//--------------------------------------------------------------
void ofApp::draw() {

	if (initialMenu == true) { //Se si è dentro il menù iniziale
		ofSetColor(255, 255, 255);
		background.draw(0, 0); //Sfondo
		gui_first.draw();
		title.drawString("CAR SOCCER EVOLUTION", 250, 120); //Titolo del gioco

		
		if (nickname.empty()) { //Verifico se il nickname è valorizzato --> se no chiamo la funzione

			insertNick();
		}
		
		subtitle.drawString("Welcome " + nickname, ofGetWidth() / 2 - ofGetWidth() / 4 +75, 300); 

	
		if (activeRules || activeHistory) { //Se attivo le regole o la cronologia

			int padding = 18;
			ofSetColor(255, 255, 255);
			ofDrawRectRounded(ofGetWidth() / 2 + 125, ofGetHeight() / 2 , 500, 250, 10); //Riquadro che contiene le righe		
			ofSetColor(0, 0, 0);
			for (int j = 0; j < linesOfTheFile.size(); j++) {
				label.drawString(linesOfTheFile[j], ofGetWidth() / 2 + 125 + padding, ofGetHeight() / 2 + padding*2 +j*20); //Stampo a video le righe
			}

		}

		completed = false;
		levels = 0;
	}

	else { //Non si è nel menù iniziale

		initSound.stop(); //Stop la musica iniziale
		
		if (!started) { //Se la partita non è iniziata eseguo il countdown		

			if (ofGetSystemTimeMillis() < end_countdown) {
				ofSetColor(255, 255, 255);
				background.draw(0, 0);
				countdown = end_countdown - ofGetSystemTimeMillis();
				countdown = countdown / 1000;			
				title.drawString(ofToString(countdown+1), ofGetWidth()/2, ofGetHeight()/2); //Stampo a video il countdown		
			}

			else { //Se il countdown è terminato			
				generalSound.play(); //Play della musica di gioco
				generalSound.setLoop(true);
				generalSound.setVolume(volume);

				//Imposto il timer di gioco
				start_timer = ofGetSystemTimeMillis();
				end_timer = start_timer + time_game;
				started = !started;
			}
		}
		else { //Se la partita è iniziata	
			ofEnableAlphaBlending();	
			ofBackground(176, 224, 230);

			cam.begin(); //Setto la camera
			
			/*TEXTURE GROUND*/
			ofSetColor(255, 255, 255, 200);
			textureGround.bind();
			ground.draw();
			textureGround.unbind();


			/*TEXTURE WALLS*/
			ofEnableDepthTest();
			textureWall.bind();
			ofSetColor(255, 255, 255, 200);
			back1.draw();
			back2.draw();	
			textureWall.unbind();
			ofDisableDepthTest();

			// LIVELLI //
			settingLevel();
			if (levels == 6) {
				ofEnableDepthTest();
				textureObstacle.bind();
				ofSetColor(255, 255, 255);
				obs6->draw();
				textureObstacle.unbind();
				ofDisableDepthTest();
			}

			if (levels == 7) {
				ofEnableDepthTest();
				textureObstacle.bind();
				ofSetColor(255, 255, 255);
				obs7->draw();
				textureObstacle.unbind();
				ofDisableDepthTest();
			}

			if (levels == 8) {
				ofEnableDepthTest();
				textureObstacle.bind();
				ofSetColor(255, 255, 255);
				obs6->draw();
				obs7->draw();
				textureObstacle.unbind();
				ofDisableDepthTest();
			}

			if (levels == 9) {
				ofEnableDepthTest();
				textureObstacle.bind();
				ofSetColor(255, 255, 255);
				obs9->draw();
				textureObstacle.unbind();
				ofDisableDepthTest();
			}

			if (levels == 10) {

				ofEnableDepthTest();
				textureObstacle.bind();
				ofSetColor(255, 255, 255);
				obs9->draw();
				textureObstacle.unbind();
				ofDisableDepthTest();
			}

			ofEnableDepthTest();
			textureWall.bind();
			ofSetColor(255,255,255,200);
			target.draw();
			right.draw();
			left.draw();
			textureWall.unbind();
			ofDisableDepthTest();
			
			//TETTO E MURO FRONTALI NO TEXTURE //
			ofNoFill();
			ceiling.draw();
			front.draw();
			ofFill();

			if (sphere->checkCreate() == true ) { //Verifica pallone presente --> se presente lo mostro a video con texture
				ofEnableDepthTest();
				ofSetColor(255, 255, 255);
				textureBall.bind(); 
				sphere->draw();
				textureBall.unbind();
				ofDisableDepthTest();
				ofNoFill();
				ofSetColor(250, 250, 100);

				if (sphere->getPosition().z + sphere->getRadius() < 0) { //Controllo per vedere se è gol 

					resetBall(); //Resetto il pallone

					if (ofGetSystemTimeMillis() < end_timer) {
						score++;
						//Setto la durata dell'effect e richiamo la funzione
						effectGol();
						start_effect = ofGetSystemTimeMillis();
						end_effect = start_effect + time_effect;
						
						if (levels < 11) {  //La variabile livelli dopo il 10 rimane fissa
							levels = levels + 1; //Passo al livello superiore
						}	
						overflow = 0; //resettare il movimento degli ostacoli
					}
				}
			}

			/*Movimento CAR*/
			drawCar();
		
			//Controllo per verificare se la macchina ha colpito il pallone
			if (point_center.getPosition().x > sphere->getPosition().x - distance && point_center.getPosition().x < sphere->getPosition().x + distance) { //Asse X
				if (point_center.getPosition().y + distance > sphere->getPosition().y - ball_radius && point_center.getPosition().y + distance < sphere->getPosition().y + ball_radius) { //Asse Y
					if (point_center.getPosition().z > sphere->getPosition().z - distance && point_center.getPosition().z < sphere->getPosition().z + distance) { //Asse Z

						//Pallone colpito dalla macchina
						//Se la macchina si muove --> la palla subisce una forza proporzionata e di segno uguale all'angolo e velocità della macchina
						if (marcia) {
							sphere->applyCentralForce(ofVec3f(-(speed * sin(theta / 360 * 2 * PI) / 300), 0, -(speed * cos(theta / 360 * 2 * PI) / 300)));
						}
						else if (retromarcia) {
							sphere->applyCentralForce(ofVec3f((speed * sin(theta / 360 * 2 * PI) / 300), 0, (speed * cos(theta / 360 * 2 * PI) / 300)));
						}
					}
				}
			}
				
			cam.end();

			if (!completed) { //Se si è ancora in gioco ed i livelli non sono stati completati --> stampo il livello attuale ed i secondi rimanenti
				ofSetColor(0,0,0);
				subtitle.drawString("Level " + ofToString(readLevel), ofGetWidth() / 2 - 150, 100);
				label.drawString("Second remaining " + ofToString(timer), ofGetWidth() / 2 - 75, 150);
			}

			//glDisable(GL_DEPTH_TEST);
			ofSetColor(34, 169, 0);

			if (levels > 10 && !completed) { //Se si è in gioco e si supera il 10 livello la partita si dichiara completata

				completed = true;
				timer = end_timer - ofGetSystemTimeMillis();
				timer = timer / 1000;
				timeCompleted = (time_game/1000) - timer; //Tempo di completamento gioco
				readLevel = levels;

			}

			//Stampa a video una stringa quando si effettua gol
			if (ofGetSystemTimeMillis() < end_effect) {
				if (levels < 10) {
					subtitle.drawString("GOOOOOL", ofGetWidth() / 2 - 150, ofGetHeight() / 2);
				}
			}

			//Verifica timer se la partita è conclusa
			if (num_match > 0) {
				if (ofGetSystemTimeMillis() < end_timer) { //PARTITA IN CORSO

					timer = end_timer - ofGetSystemTimeMillis();
					timer = timer / 1000;	
					readLevel = levels;

				}

				else if (ofGetSystemTimeMillis() > end_timer) { //PARTITA CONCLUSA 

					completed = true;
					timeCompleted = time_game / 1000;
				}


				if (completed) { // Se match concluso stampa a video le stringe
				
					if (levels > 10) {

						subtitle.drawString("YOU WIN!\nLevel completed: " + ofToString(readLevel - 1) + "\nTime: " + ofToString(timeCompleted) + " seconds", ofGetWidth() / 2 - ofGetWidth() / 4, ofGetHeight() / 2 - 75);

					}
					else {
						subtitle.drawString("Game over!\nLevel completed: " + ofToString(readLevel - 1) + "\nTime: " + ofToString(timeCompleted) + " seconds", ofGetWidth() / 2 - ofGetWidth() / 4, ofGetHeight() / 2 - 75);
					}
			
					if (!savedHistory) { //Se non è stato salvata la partita nella cronologia

						//Salvataggio punteggio
						ofstream fileOUT("data/history.txt", ios::app); // open history.txt in append mode
						fileOUT << nickname << " - level " << (readLevel-1) << " - " << timeCompleted << " seconds" << endl; // append text to the end of the file
						fileOUT.close(); // close the file
						savedHistory = true;

						//Fischio finale
						whistle.play();
						whistle.setVolume(volume);
						whistle.setLoop(false);
					}
				}

			}

			generalSound.setVolume(volume);

			/***** RENDER GUI *****/
			ofDisableDepthTest();
			gui_game.draw();		
			gui_stats.draw();

			if (setting) { //Se il toogle option e setting è attivo
				gui_setting.draw();
			}

			if (num_match > 0) {
				gui_stats.clear();
				drawGuiStatistics();
				gui_stats.draw();
			}

			if (lockCamera) { //Se il toogle blocca camera è attivo
				cam.disableMouseInput();
			}

			else
			{
				cam.enableMouseInput();
			}

		}
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {

	if (key == 'w') { 

		if (controlArena()) { //Verifica se la macchina è dentro l'arena
			if (speed <= 0) {
				marcia = true;
			}
			else if (!marcia) { //Rallenta la vettura se si sta muovendo nella direzione opposta
				speed = speed / 2.5;
			}
		}
		else if (!controlArena()) { //Macchina bloccata
			if (point_center.getPosition().x - distance + max_speed  > 0 || point_center.getPosition().x + distance - max_speed > left.getPosition().x ||
				point_center.getPosition().z - distance + max_speed > 0 || point_center.getPosition().z + distance - max_speed > front.getPosition().z ) {

				//Non può andare avanti, solo indietro
				if (speed <= 0) {
					retromarcia = true;
				}
				else if (!retromarcia) { 
					speed = speed / 2.5;
				}
				//Aggiorno la velocità
				speed = speed + 0.005;
				wheel_deg = wheel_deg + 0.01;
				moveW(); //Richiamo la funzione 
			}

		}
	}

	if (key == 's') {
		if (controlArena()) { //Verifica se la macchina è dentro l'arena
			if (speed <= 0) {
				retromarcia = true;
			}
			else if (!retromarcia) { //Rallenta la vettura se si sta muovendo nella direzione opposta
				speed = speed / 2.5;
			}
		}

		else if (!controlArena()) { //Macchina bloccata
			if (point_center.getPosition().x - distance + max_speed > 0 || point_center.getPosition().x + distance - max_speed > left.getPosition().x ||
				point_center.getPosition().z - distance + max_speed > 0 || point_center.getPosition().z + distance - max_speed > front.getPosition().z) {
				if (speed <= 0) {
					retromarcia = true;
				}
				else if (!retromarcia) {
					speed = speed / 2.5;
				}
				//Aggiorno la velocità
				speed = speed + 0.005;
				wheel_deg = wheel_deg + 0.01;
				cout << speed << endl;
				moveS(); //Richiamo la funzione 
			}

		}
	}

	if (key == 'a') {
		if (controlArena()) {
			if (!rotation_left) { //Le ruote davanti simulano la sterzata
				wheel1.rotateDeg(45, ofVec3f(0, 1, 0));
				wheel2.rotateDeg(45, ofVec3f(0, 1, 0));
				rotation_left = true; //Rotazione a sinistra attiva

			}
		}

	}

	if (key == 'd') {
		if (controlArena()) {
			if (!rotation_right) { //Le ruote davanti simulano la sterzata
				wheel1.rotateDeg(-45, ofVec3f(0, 1, 0));
				wheel2.rotateDeg(-45, ofVec3f(0, 1, 0));
				rotation_right = true;
			}
		}
	}

	/*if (key == 'e') {
		activeRules=false;
		activeHistory = false;
	}*/
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {

	if (key == 'a') {
		if (rotation_left) { //Rotazione disattivata
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
		if (marcia) { 
			marcia = false; //Disattivata la marcia in avanti
			rallentamento_marcia = true; //Attivo il rallentamento marcia in avanti
		}

	}

	if (key == 's') {
		if (retromarcia) { 
			retromarcia = false; //Disattivata la marcia indietro
			rallentamento_marcia = false; //Disattivo il rallentamento marcia in avanti
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
