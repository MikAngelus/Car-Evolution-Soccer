
void ofApp::createCar() { //Funzione creazione macchina

	// RUOTA 1 --> IN ALTO A SX
	wheel1.setPosition(50, yGround, 50); // pos iniziale
	wheel1.set(0.01, 4, 4); //Grandezza
	wheel1.setOrientation(ofVec3f(0, 0, 0)); //Orientamento angolo macchina

	// RUOTA 2 --> IN ALTO A DX
	wheel2.setPosition(50 + distance, yGround, 50); // pos iniziale
	wheel2.set(0.01, 4, 4);
	wheel2.setOrientation(ofVec3f(0, 0, 0));

	// RUOTA 3 --> IN BASSO A SX
	wheel3.setPosition(50, yGround, 50 + distance * 2); // pos iniziale
	wheel3.set(0.01, 4, 4);
	wheel3.setOrientation(ofVec3f(0, 0, 0));

	// RUOTA 4  --> IN BASSO A DX
	wheel4.setPosition(50 + distance, yGround, 50 + distance * 2); // pos iniziale
	wheel4.set(0.01, 4, 4);
	wheel4.setOrientation(ofVec3f(0,0,0));

	// BARICENTRO --> utilizzata come carrozzeria
	point_center.setPosition(wheel1.getPosition().x + distance / 2, wheel1.getPosition().y+point_center.getSize().y/2, wheel1.getPosition().z + distance); // pos iniziale
	point_center.set(distance - 1, 3, distance * 2); //Grandezza
	point_center.setOrientation(ofVec3f(0,0,0));

	resetLeftRightPoint(); 
}



void ofApp::resetLeftRightPoint() { // Funzione che imposta i punti rotazione

	//Punto rotazione sinistra 
	point_left.setPosition(point_center.getPosition().x - distance * 3, point_center.getPosition().y, point_center.getPosition().z); // pos iniziale
	point_left.set(0.0001); //grandezza
	point_left.setOrientation(ofVec3f(0, 0, 0));

	//Punto rotazione destra
	point_right.setPosition(point_center.getPosition().x + distance * 3, point_center.getPosition().y, point_center.getPosition().z); // pos iniziale
	point_right.set(0.0001); //grandezza
	point_right.setOrientation(ofVec3f(0, 0, 0));

}


void ofApp::moveW() { //Funzioni muovi macchina in avanti

	float deg = wheel_deg; //Setto l'angolo da passare in input in base all'attuale angolo delle ruote


	if (rotation_left) { 

		moveA(deg); //Se premuto A eseguito una rotazione in avanti a sinistra

	}

	else if (rotation_right) {

		moveD(deg); //Se premuto D eseguito una rotazione in avanti a destra
	}

	else if (!rotation_left && !rotation_right) { //Se non è premuto A e D --> marcia in avanti

		//Traslazione della posizione dei punti
		// L'Origine tra il back e il left wall: quindi le ruote vanno in avanti per un movimento NEGATIVO negli assi X e Z dato dalla formula:
		// Asse x --> -speed + sin (theta/360 *2PI) --> theta non si ferma a 360 quindi bisogna dividerlo
		// Asse x --> -speed + cos (theta/360 *2PI) 

		// RUOTE //
		wheel1.setPosition(wheel1.getPosition().x - speed * sin(theta / 360 * 2 * PI), wheel1.getPosition().y, wheel1.getPosition().z - speed * cos(theta / 360 * 2 * PI));
		wheel2.setPosition(wheel2.getPosition().x - speed * sin(theta / 360 * 2 * PI), wheel2.getPosition().y, wheel2.getPosition().z - speed * cos(theta / 360 * 2 * PI));
		wheel3.setPosition(wheel3.getPosition().x - speed * sin(theta / 360 * 2 * PI), wheel3.getPosition().y, wheel3.getPosition().z - speed * cos(theta / 360 * 2 * PI));
		wheel4.setPosition(wheel4.getPosition().x - speed * sin(theta / 360 * 2 * PI), wheel4.getPosition().y, wheel4.getPosition().z - speed * cos(theta / 360 * 2 * PI));

		// PUNTI //
		point_left.setPosition(point_left.getPosition().x - speed * sin(theta / 360 * 2 * PI), point_left.getPosition().y, point_left.getPosition().z - speed * cos(theta / 360 * 2 * PI));
		point_center.setPosition(point_center.getPosition().x - speed * sin(theta / 360 * 2 * PI), point_center.getPosition().y, point_center.getPosition().z - speed * cos(theta / 360 * 2 * PI));
		point_right.setPosition(point_right.getPosition().x - speed * sin(theta / 360 * 2 * PI), point_right.getPosition().y, point_right.getPosition().z - speed * cos(theta / 360 * 2 * PI));
	}


}

void ofApp::moveD(int deg0) { //Funzione movimento macchina rotazione destra

	float deg = deg0; //Salvo l'attuale angolo che ricevo in input da moveW o moveS

	//Per la rotazione della macchina tutte le ruote e i punti devono ruotare rispetto all'asse -Y per un punto --> point_right
	// RUOTE //
	wheel1.rotateAroundDeg(deg, ofVec3f(0, -1, 0), ofVec3f(point_right.getPosition().x, point_right.getPosition().y, point_right.getPosition().z));
	wheel2.rotateAroundDeg(deg, ofVec3f(0, -1, 0), ofVec3f(point_right.getPosition().x, point_right.getPosition().y, point_right.getPosition().z));
	wheel3.rotateAroundDeg(deg, ofVec3f(0, -1, 0), ofVec3f(point_right.getPosition().x, point_right.getPosition().y, point_right.getPosition().z));
	wheel4.rotateAroundDeg(deg, ofVec3f(0, -1, 0), ofVec3f(point_right.getPosition().x, point_right.getPosition().y, point_right.getPosition().z));

	//PUNTI// 
	point_center.rotateAroundDeg(deg, ofVec3f(0, -1, 0), ofVec3f(point_right.getPosition().x, point_right.getPosition().y, point_right.getPosition().z));
	point_left.rotateAroundDeg(deg, ofVec3f(0, -1, 0), ofVec3f(point_right.getPosition().x, point_right.getPosition().y, point_right.getPosition().z));

	// Rotazione degli oggetti in base all'angolo --> mentre ruotano intorno ad un punto gli oggetti devono subire una rotazione
	wheel1.rotateDeg(-deg, ofVec3f(0, 1, 0));
	wheel2.rotateDeg(-deg, ofVec3f(0, 1, 0));
	wheel3.rotateDeg(-deg, ofVec3f(0, 1, 0));
	wheel4.rotateDeg(-deg, ofVec3f(0, 1, 0));
	point_center.rotateDeg(-deg, ofVec3f(0, 1, 0));

	theta = theta - deg; //Aggiorno l'angolo di rotazione delle ruote

}

void ofApp::moveA(int deg0) { //Funzione movimento macchina rotazione sinistra

	float deg = deg0;  //Salvo l'attuale angolo che ricevo in input da moveW o moveS

	//Per la rotazione della macchina tutte le ruote e i punti devono ruotare rispetto all'asse +Y per un punto --> point_left

	//RUOTE//
	wheel1.rotateAroundDeg(deg, ofVec3f(0, 1, 0), ofVec3f(point_left.getPosition().x, point_left.getPosition().y, point_left.getPosition().z));
	wheel2.rotateAroundDeg(deg, ofVec3f(0, 1, 0), ofVec3f(point_left.getPosition().x, point_left.getPosition().y, point_left.getPosition().z));
	wheel3.rotateAroundDeg(deg, ofVec3f(0, 1, 0), ofVec3f(point_left.getPosition().x, point_left.getPosition().y, point_left.getPosition().z));
	wheel4.rotateAroundDeg(deg, ofVec3f(0, 1, 0), ofVec3f(point_left.getPosition().x, point_left.getPosition().y, point_left.getPosition().z));

	//PUNTI //
	point_center.rotateAroundDeg(deg, ofVec3f(0, 1, 0), ofVec3f(point_left.getPosition().x, point_left.getPosition().y, point_left.getPosition().z));
	point_right.rotateAroundDeg(deg, ofVec3f(0, 1, 0), ofVec3f(point_left.getPosition().x, point_left.getPosition().y, point_left.getPosition().z));

	//Rotazione degli oggetti in base all'angolo --> mentre ruotano intorno ad un punto gli oggetti devono subire una rotazione
	wheel1.rotateDeg(deg, ofVec3f(0, 1, 0));
	wheel2.rotateDeg(deg, ofVec3f(0, 1, 0));
	wheel3.rotateDeg(deg, ofVec3f(0, 1, 0));
	wheel4.rotateDeg(deg, ofVec3f(0, 1, 0));
	point_center.rotateDeg(deg, ofVec3f(0, 1, 0));

	theta = theta + deg; //Aggiorno l'angolo di rotazione delle ruote

}

void ofApp::moveS() { //Funzioni muovi macchina in dietro

	float deg = -1 * wheel_deg; //Setto l'angolo da passare in input in base all'attuale angolo delle ruote

	if (rotation_left) { //Se premuto A eseguito una rotazione indietro a sinistra

		moveA(deg); //Funzione che passa in input l'angolo

	}

	else if (rotation_right) { //Se premuto D eseguito una rotazione indietro a destra

		moveD(deg);

	}

	else if (!rotation_left && !rotation_right) { //Se non è premuto A e D --> marcia in avanti

		//Traslazione della posizione dei punti
		// L'Origine tra il back e il left wall: quindi le ruote vanno in avanti per un movimento POSITIVO negli assi X e Z dato dalla formula:
		// Asse x --> speed + sin (theta/360 *2PI) --> theta non si ferma a 360 quindi bisogna dividerlo
		// Asse x --> speed + cos (theta/360 *2PI) 

		// RUOTE //
		wheel1.setPosition(wheel1.getPosition().x + speed * sin(theta / 360 * 2 * PI), wheel1.getPosition().y, wheel1.getPosition().z + speed * cos(theta / 360 * 2 * PI));
		wheel2.setPosition(wheel2.getPosition().x + speed * sin(theta / 360 * 2 * PI), wheel2.getPosition().y, wheel2.getPosition().z + speed * cos(theta / 360 * 2 * PI));
		wheel3.setPosition(wheel3.getPosition().x + speed * sin(theta / 360 * 2 * PI), wheel3.getPosition().y, wheel3.getPosition().z + speed * cos(theta / 360 * 2 * PI));
		wheel4.setPosition(wheel4.getPosition().x + speed * sin(theta / 360 * 2 * PI), wheel4.getPosition().y, wheel4.getPosition().z + speed * cos(theta / 360 * 2 * PI));

		// PUNTI //
		point_left.setPosition(point_left.getPosition().x + speed * sin(theta / 360 * 2 * PI), point_left.getPosition().y, point_left.getPosition().z + speed * cos(theta / 360 * 2 * PI));
		point_center.setPosition(point_center.getPosition().x + speed * sin(theta / 360 * 2 * PI), point_center.getPosition().y, point_center.getPosition().z + speed * cos(theta / 360 * 2 * PI));
		point_right.setPosition(point_right.getPosition().x + speed * sin(theta / 360 * 2 * PI), point_right.getPosition().y, point_right.getPosition().z + speed * cos(theta / 360 * 2 * PI));

	}

}

void ofApp::drawCar() { //Funzione richiamata nel draw()

	ofSetColor(255);
	ofFill(); //Impostiamo il riempimento 

	//Draw punti di rotazione
	point_left.draw(); 
	point_right.draw();
	
	//Draw RUOTE con texture
	ofEnableDepthTest();
	textureWheels.bind(); //Lego le texture agli oggetti
	ofSetColor(255);
	wheel1.draw();
	wheel2.draw();
	wheel3.draw();
	wheel4.draw();
	textureWheels.unbind(); //Slego le texture
	ofDisableDepthTest();

	ofEnableDepthTest();
	//textureBody.bind();
	ofSetColor(0,0,0);
	point_center.drawWireframe();
	//textureBody.unbind();
	ofDisableDepthTest();
	
	if (controlArena()) { 	//Richiamo la funzione per verificare se la macchina è all'interno dell'arena

			if (marcia) { //Se si muove in avanti 

				if (speed >= max_speed) { // e la velocità supera quella massima

					//cout << speed << endl;
					moveW(); //Richiamo la funzione che muove in avanti la macchina --> si muoverà per una velocità fissa = speed

				}
				else{ 

					speed = speed + 0.005; //Aumento la velocità di 0.005
					wheel_deg = wheel_deg + 0.01; //Aumento la velocità con cui le ruote girano
					//cout << speed << endl;
					moveW(); //Richiamo la funzione che muove in avanti la macchina
				}

			}

			else if (retromarcia) { //Se si muove indietro

				if (speed >= max_speed / 2) { // e la velocità supera quella massima/2

					//cout << speed << endl;
					moveS(); //Richiamo la funzione che muove in avanti la macchina --> si muoverà per una velocità fissa = speed

				}
				else {

					speed = speed + 0.005; //Aumento la velocità di 0.005
					wheel_deg = wheel_deg + 0.01; //Aumento la velocità con cui le ruote girano
					cout << speed << endl;
					moveS(); //Richiamo la funzione che muove indietro la macchina
				}
			}
			
			// GESTIONE RALLENTAMENTO MACCHINA //
			else if (speed > 0 && !marcia) { //Se siamo in velocità ma non c'è nessun tasto premuto --> nessuna marcia richiesta

				speed = speed - 0.005; //La velocità dimuisce
				wheel_deg = wheel_deg - 0.01; //La velocità angolare delle route dimuisce

				if (rallentamento_marcia) { //Rallentamento dopo un movimento in avanti
					moveW();
					//cout << "Rallentamento in marcia" << endl;
				}
				else { //Rallentamento dopo un movimento in avanti
					moveS();
					//cout << "Rallentamento in retromarcia" << endl;
				}
				}

				if (speed <= 0) { //Se la velocità è < 0 fisso la veloclità minima delle ruote

					wheel_deg = 1; //Angolo minimo di rotazione 1
				}

	}

}

bool ofApp::controlArena() { //funzione per verificare se la macchina è all'interno dell'arena

	//Controllo se macchina supera l'asse X
	if (point_center.getPosition().x - distance < xRight/2  || point_center.getPosition().x + distance > left.getPosition().x - xLeft/2 ) {

		return false;

	}
	//Controllo se macchina supera l'asse X
	else if (point_center.getPosition().z - distance < zBack1/2 || point_center.getPosition().z + distance > front.getPosition().z - zFront/2) {

		return false;
	}

	else return true;

}