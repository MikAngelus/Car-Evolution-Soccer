
//--------------------------------------------------------------
void ofApp::resetBall() { //Funzione che crea un nuovo pallone eliminando la precedente istanza

	sphere->remove(); //Rimozione del pallone
	sphere = new ofxBulletSphere(); //Nuova instanza
	sphere->create(world.world, ofVec3f(50, 50, 50), 0.000001, ball_radius); //Posizione iniziale pallone; Massa del pallone --> 0.00001 (molto leggera)
	sphere->add(); //Aggiunto il pallone al world
	sphere->setRestitution(ball_restitution); 

}

//--------------------------------------------------------------
void ofApp::resetCar() {

	//Richiamo la funzione crea macchina e la inizializzo
	createCar();
	wheel_deg = speed + 1;
	theta = 0;
}

void ofApp::resetTarget() { //Funzione che aggiora la grandezza della porta dove segnare

	target.remove(); //Rimozione porta

	//Creazione di una nuova porta con l'overflow --> riduzione dimensioni porta e traslazione porta
	target.create(world.world, ofVec3f(xGround / 2, (yBack1 - overflow_target) / 2 + yTarget / 2, 0), 0, xTarget, yTarget + overflow_target, zTarget);
	target.setProperties(.25, .95);
	target.add();

}

//--------------------------------------------------------------
void ofApp::play() { // Funzione richiama quando si preme Start Game
	initialMenu = false; //Disabilito il menù iniziale
	//Richiamo le funzioni che creano la macchina e il pallone
	resetBall();
	resetCar();
	levels = 1; //Livello iniziale --> 1

	//Punteggio
	//ofSetColor(255, 255, 255);
	score = 0; 
	num_match++;

	//COUNTDOWN
	start_countdown = ofGetSystemTimeMillis();
	end_countdown = start_countdown + time_countdown;

	//MUSIC
	soundCountdown.play();
	soundCountdown.setVolume(volume);


}

void ofApp::restartPlay() { // Funzione richiama quando si preme Restart Game

	//Richiamo le funzioni che creano la macchina e il pallone
	resetBall();
	resetCar();

	completed = false; //La partita non sarà più dichiarata come completata
	savedHistory = false; //La partita non sarà più dichiarata come salvata
	levels = 1;

	//Punteggio
	score = 0;
	num_match++;

	//TIMER MATCH
	start_timer = ofGetSystemTimeMillis();
	end_timer = start_timer + time_game;
	
}

void ofApp::settingLevel() { // Gestione dei livell di gioco //

	if (levels == 1) { //Grandezza porta standard
		overflow_target = 0; 
		resetTarget();
	}

	if (levels == 2) { //Grandezza porta ridotta di 15
		overflow_target = 15;
		resetTarget();
	}

	if (levels == 3) { //Grandezza porta ridotta di 20
		overflow_target = 20;
		resetTarget();
	}

	if (levels == 4) {
		level4();
	}

	if (levels == 5) {
		level5();
	
	}

	if (levels > 5) {  // Grandezza porta ridotta di 15

		overflow_target = 15; 
		resetTarget();
	}


	if (levels == 6) {
		level6();
	}

	if (levels == 7) {

		level7();
	}

	if (levels == 8) {
		level8();
	}

	if (levels == 9) {
		level9();
	}

	if (levels == 10) {

		level10();
	}

}

void ofApp::level4() {

		//Aggiornamento porta-->rimozione e creazione secondo un overflow_target
		target.remove();
		target.create(world.world, ofVec3f(xGround / 2, (yBack1 - overflow_target) / 2 + yTarget / 2, 0), 0, xTarget, yTarget + overflow_target, zTarget);
		target.setProperties(.25, .95);
		target.add();
		//SCORRIMENTO VERSO GIU'
		if (overflow_target <= 30 && !reverseLevel4) {	 //Se l'overflow è <=30 e l'andamento è verso giù
			overflow_target = (overflow_target + 0.5); //Aggiorna l'overflow riducendo la porta
			if (overflow_target > 30) { //Se dopo l'aggiornamento supera 30 --> INVERSIONE
				reverseLevel4 = !reverseLevel4;
			}
	
		}
		//SCORRIMETNO VERSO SOPRA
		else if (reverseLevel4) {
			overflow_target = (overflow_target - 0.5);	 //Aggiorna l'overflow ingrandendo la porta
			if (overflow_target < 0) { //Se dopo l'aggiornamento è minore di zero --> INVERSIONE

				reverseLevel4 = !reverseLevel4;

			}
		}


}


void ofApp::level5() {

		target.remove();
		//Riduzione dimensioni porta
		target.create(world.world, ofVec3f(xGround / 2, (yBack1 - overflow_target) / 2 + yTarget / 2, 0), 0, xTarget, yTarget + overflow_target, zTarget);
		target.setProperties(.25, .95);
		target.add();
		
		//SCORRIMENTO VERSO GIU'
		if (overflow_target <= 30 && !reverseLevel5) { //Se l'overflow è <=30 e l'andamento è verso giù
			overflow_target = (overflow_target + 1.5); //Aggiorna l'overflow riducendo la porta
			if (overflow_target > 30) { //Se dopo l'aggiornamento supera 30 --> INVERSIONE
				reverseLevel5 = !reverseLevel5;
			}

		}

		//SCORRIMETNO VERSO SOPRA
		else if (reverseLevel5) {
			overflow_target = (overflow_target - 1.5); //Aggiorna l'overflow ingrandendo la porta
			if (overflow_target < 0) { //Se dopo l'aggiornamento è minore di zero --> INVERSIONE
				reverseLevel5 = !reverseLevel5;
			}
		}


}

void ofApp::level6() {

		if (obs6 != nullptr) { //Verifico che ha già dei puntamenti --> se presente lo elimino

			delete obs6;
			obs6 = nullptr;

		}

		//Creazione ostacolo in base all'overflow
		obs6 = new ofxBulletBox();
		obs6->create(world.world, ofVec3f(xGround - overflow, yOst6 / 2, zGround / 2 ), 0, xOst6, yOst6, zOst6);
		obs6->setProperties(.25, .95);
		obs6->add();

		//Scorrimento verso sinistra
		if (overflow <= xGround && !reverseLevel6) {
			overflow = (overflow + 1);
			if (overflow > xGround) {
				reverseLevel6 = !reverseLevel6;
			}

		}

		// Scorrimento verso destra
		else if (reverseLevel6) {
			overflow = (overflow - 1);
			if (overflow < 0) {
				reverseLevel6 = !reverseLevel6;
			}
		}


}




void ofApp::level7() {

	/*RIMUOVE I PRECEDENTI OSTACOLI*/
	
	if (obs6 != nullptr) {
		delete obs6;
		obs6 = nullptr;

	}

	//Vengono creati lo stesso ma posizionati fuori l'arena e non mostrati a video 
	obs6 = new ofxBulletBox();
	obs6->create(world.world, ofVec3f((xGround - overflow)*-10, yBack1 / 2, -50), 0, xOst6, yOst6, zOst6);
	obs6->setProperties(.25, .95);
	obs6->add();


	if (obs7 != nullptr) { //Verifico che ha già dei puntamenti --> se presente lo elimino

		delete obs7;
		obs7 = nullptr;

	}

	//Creazione ostacolo in base all'overflow
		obs7 = new ofxBulletBox();
		obs7->create(world.world, ofVec3f(xGround/2 , yOst7 / 2 + overflow, zGround / 4), 0, xOst7, yOst7, zOst7);
		obs7->setProperties(.25, .95);
		obs7->add();

		//Scorrimento verso sopra
		if (overflow <= yBack1 && !reverseLevel7) {
			overflow = (overflow + 1);
			if (overflow > yBack1) {
				reverseLevel7 = !reverseLevel7;
			}
		}
		//Scorrimento verso sotto
		else if (reverseLevel7) {
			overflow = (overflow - 1);
			if (overflow < 0) {
				reverseLevel7 = !reverseLevel7;
			}
		}


}


void ofApp::level8() { //Livello 6 + Livello 7

	/*RIMUOVE I PRECEDENTI OSTACOLI*/
	if (obs6 != nullptr) {

		delete obs6;
		obs6 = nullptr;

	}

	if (obs7 != nullptr) {

		delete obs7;
		obs7 = nullptr;

	}

	// Level 6 //
		obs6 = new ofxBulletBox();
		obs6->create(world.world, ofVec3f(xGround - overflow, yOst6 / 2, zGround / 2), 0, xOst6, yOst6, zOst6);
		obs6->setProperties(.25, .95);
		obs6->add();

		if (overflow <= xGround && !reverseLevel6) {
			overflow = (overflow + 1);
			if (overflow > xGround) {
				reverseLevel6 = !reverseLevel6;
			}
		}
		else if (reverseLevel6) {
			overflow = (overflow - 1);
			if (overflow < 0) {
				reverseLevel6 = !reverseLevel6;
			}
		}
		// Level 7 //

		obs7 = new ofxBulletBox();
		obs7->create(world.world, ofVec3f(xGround / 2, yOst7 / 2 + overflow, zGround / 4), 0, xOst7, yOst7, zOst7);
		obs7->setProperties(.25, .95);
		obs7->add();

		if (overflow <= xGround && !reverseLevel7) {
			overflow = (overflow + 1);
			if (overflow > xGround) {
				reverseLevel7 = !reverseLevel7;
			}
		}

		else if (reverseLevel7) {
			overflow = (overflow - 1);
			if (overflow < 0) {
				reverseLevel7 = !reverseLevel7;
			}
		}		
}


void ofApp::level9() {

	/*RIMUOVE I PRECEDENTI OSTACOLI*/

	if (obs6 != nullptr) {

		delete obs6;
		obs6 = nullptr;

	}

	//Vengono creati lo stesso ma posizionati fuori l'arena e non mostrati a video 
	obs6 = new ofxBulletBox();
	obs6->create(world.world, ofVec3f((xGround - overflow)*-10, 0, -50), 0, xOst6, yOst6, zOst6);
	obs6->setProperties(.25, .95);
	obs6->add();

	if (obs7 != nullptr) {

		delete obs7;
		obs7 = nullptr;

	}

	obs7 = new ofxBulletBox();
	obs7->create(world.world, ofVec3f((xGround - overflow)*-10, 0, -50), 0, xOst6, yOst6, zOst6);
	obs7->setProperties(.25, .95);
	obs7->add();



		obs9 = new ofxBulletBox();
		obs9->create(world.world, ofVec3f(xBack1 + overflow, yOst9/2, 0), 0, xOst9, yOst9, zOst9);
		obs9->setProperties(.25, .95);
		obs9->add();
		//Scorrimento verso destra
		if (overflow <= xTarget && !reverseLevel9) {
			overflow = (overflow + 1.25);
			if (overflow > xTarget) {
				reverseLevel9 = !reverseLevel9;
			}

		}
		//Scorrimento verso sinistra
		else if (reverseLevel9) {
			overflow = (overflow - 1.25);
			if (overflow < 0) {
				reverseLevel9 = !reverseLevel9;
			}
		}
}

void ofApp::level10() { //Uguale al 10 ma overflow maggiore e quindi movimento più veloce
		obs9 = new ofxBulletBox();
		obs9->create(world.world, ofVec3f(xBack1 + overflow, yOst9 / 2, 0), 0, xOst9, yOst9, zOst9);
		obs9->setProperties(.25, .95);
		obs9->add();

		if (overflow <= xTarget && !reverseLevel10) {
			overflow = (overflow + 2.25);
			if (overflow > xTarget) {
				reverseLevel10 = !reverseLevel10;		
			}
		}

		else if (reverseLevel10) {
			overflow = (overflow - 2.25);
			if (overflow < 0) {

				reverseLevel10 = !reverseLevel10;
			}
		}
}
