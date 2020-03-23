
void ofApp::createCar() {

	wheel1.setPosition(50, yGround, 50); // pos iniziale
	wheel1.set(0.01, 4, 4);
	wheel1.setOrientation(ofVec3f(0, 0, 0));

	wheel2.setPosition(50 + distance, yGround, 50); // pos iniziale
	wheel2.set(0.01, 4, 4);
	wheel2.setOrientation(ofVec3f(0, 0, 0));

	wheel3.setPosition(50, yGround, 50 + distance * 2); // pos iniziale
	wheel3.set(0.01, 4, 4);
	wheel3.setOrientation(ofVec3f(0, 0, 0));

	wheel4.setPosition(50 + distance, yGround, 50 + distance * 2); // pos iniziale
	wheel4.set(0.01, 4, 4);
	wheel4.setOrientation(ofVec3f(0,0,0));

	
	point_center.set(distance-1, 3, distance*2); //carrozzeria
	point_center.setPosition(wheel1.getPosition().x + distance / 2, wheel1.getPosition().y+point_center.getSize().y/2, wheel1.getPosition().z + distance); // pos iniziale
	point_center.setOrientation(ofVec3f(0,0,0));

	resetLeftRightPoint();
}



void ofApp::resetLeftRightPoint() {


	point_left.setPosition(point_center.getPosition().x - distance * 3, point_center.getPosition().y, point_center.getPosition().z); // pos iniziale
	point_left.set(0.0001); //grandezza
	point_left.setOrientation(ofVec3f(0, 0, 0));
	point_right.setPosition(point_center.getPosition().x + distance * 3, point_center.getPosition().y, point_center.getPosition().z); // pos iniziale
	point_right.set(0.0001); //grandezza
	point_right.setOrientation(ofVec3f(0, 0, 0));

}


void ofApp::moveW() {

	float deg = wheel_deg;


	if (rotation_left) {

		moveA(deg);

	}

	else if (rotation_right) {

		moveD(deg);
	}

	else if (!rotation_left && !rotation_right) {

		wheel1.setPosition(wheel1.getPosition().x - speed * sin(theta / 360 * 2 * PI), wheel1.getPosition().y, wheel1.getPosition().z - speed * cos(theta / 360 * 2 * PI));
		wheel2.setPosition(wheel2.getPosition().x - speed * sin(theta / 360 * 2 * PI), wheel2.getPosition().y, wheel2.getPosition().z - speed * cos(theta / 360 * 2 * PI));
		wheel3.setPosition(wheel3.getPosition().x - speed * sin(theta / 360 * 2 * PI), wheel3.getPosition().y, wheel3.getPosition().z - speed * cos(theta / 360 * 2 * PI));
		wheel4.setPosition(wheel4.getPosition().x - speed * sin(theta / 360 * 2 * PI), wheel4.getPosition().y, wheel4.getPosition().z - speed * cos(theta / 360 * 2 * PI));

		point_left.setPosition(point_left.getPosition().x - speed * sin(theta / 360 * 2 * PI), point_left.getPosition().y, point_left.getPosition().z - speed * cos(theta / 360 * 2 * PI));
		point_center.setPosition(point_center.getPosition().x - speed * sin(theta / 360 * 2 * PI), point_center.getPosition().y, point_center.getPosition().z - speed * cos(theta / 360 * 2 * PI));
		point_right.setPosition(point_right.getPosition().x - speed * sin(theta / 360 * 2 * PI), point_right.getPosition().y, point_right.getPosition().z - speed * cos(theta / 360 * 2 * PI));
	}


}

void ofApp::moveD(int deg0) {

	float deg = deg0;

	wheel1.rotateAroundDeg(deg, ofVec3f(0, -1, 0), ofVec3f(point_right.getPosition().x, point_right.getPosition().y, point_right.getPosition().z));
	wheel2.rotateAroundDeg(deg, ofVec3f(0, -1, 0), ofVec3f(point_right.getPosition().x, point_right.getPosition().y, point_right.getPosition().z));
	wheel3.rotateAroundDeg(deg, ofVec3f(0, -1, 0), ofVec3f(point_right.getPosition().x, point_right.getPosition().y, point_right.getPosition().z));
	wheel4.rotateAroundDeg(deg, ofVec3f(0, -1, 0), ofVec3f(point_right.getPosition().x, point_right.getPosition().y, point_right.getPosition().z));

	point_center.rotateAroundDeg(deg, ofVec3f(0, -1, 0), ofVec3f(point_right.getPosition().x, point_right.getPosition().y, point_right.getPosition().z));
	point_left.rotateAroundDeg(deg, ofVec3f(0, -1, 0), ofVec3f(point_right.getPosition().x, point_right.getPosition().y, point_right.getPosition().z));

	wheel1.rotateDeg(-deg, ofVec3f(0, 1, 0));
	wheel2.rotateDeg(-deg, ofVec3f(0, 1, 0));
	wheel3.rotateDeg(-deg, ofVec3f(0, 1, 0));
	wheel4.rotateDeg(-deg, ofVec3f(0, 1, 0));

	point_center.rotateDeg(-deg, ofVec3f(0, 1, 0));
	theta = theta - deg;

}

void ofApp::moveA(int deg0) {

	float deg = deg0;

	/*ROTAZIONE RUOTE*/
	wheel1.rotateAroundDeg(deg, ofVec3f(0, 1, 0), ofVec3f(point_left.getPosition().x, point_left.getPosition().y, point_left.getPosition().z));
	wheel2.rotateAroundDeg(deg, ofVec3f(0, 1, 0), ofVec3f(point_left.getPosition().x, point_left.getPosition().y, point_left.getPosition().z));
	wheel3.rotateAroundDeg(deg, ofVec3f(0, 1, 0), ofVec3f(point_left.getPosition().x, point_left.getPosition().y, point_left.getPosition().z));
	wheel4.rotateAroundDeg(deg, ofVec3f(0, 1, 0), ofVec3f(point_left.getPosition().x, point_left.getPosition().y, point_left.getPosition().z));

	/*ROTAZIONE PUNTI DI GUIDA*/
	point_center.rotateAroundDeg(deg, ofVec3f(0, 1, 0), ofVec3f(point_left.getPosition().x, point_left.getPosition().y, point_left.getPosition().z));
	point_right.rotateAroundDeg(deg, ofVec3f(0, 1, 0), ofVec3f(point_left.getPosition().x, point_left.getPosition().y, point_left.getPosition().z));

	wheel1.rotateDeg(deg, ofVec3f(0, 1, 0));
	wheel2.rotateDeg(deg, ofVec3f(0, 1, 0));
	wheel3.rotateDeg(deg, ofVec3f(0, 1, 0));
	wheel4.rotateDeg(deg, ofVec3f(0, 1, 0));

	point_center.rotateDeg(deg, ofVec3f(0, 1, 0));
	theta = theta + deg;

}

void ofApp::moveS() {

	float deg = -1 * wheel_deg;

	if (rotation_left) {

		moveA(deg);

	}

	else if (rotation_right) {

		moveD(deg);

	}

	else if (!rotation_left && !rotation_right) {

		wheel1.setPosition(wheel1.getPosition().x + speed * sin(theta / 360 * 2 * PI), wheel1.getPosition().y, wheel1.getPosition().z + speed * cos(theta / 360 * 2 * PI));
		wheel2.setPosition(wheel2.getPosition().x + speed * sin(theta / 360 * 2 * PI), wheel2.getPosition().y, wheel2.getPosition().z + speed * cos(theta / 360 * 2 * PI));
		wheel3.setPosition(wheel3.getPosition().x + speed * sin(theta / 360 * 2 * PI), wheel3.getPosition().y, wheel3.getPosition().z + speed * cos(theta / 360 * 2 * PI));
		wheel4.setPosition(wheel4.getPosition().x + speed * sin(theta / 360 * 2 * PI), wheel4.getPosition().y, wheel4.getPosition().z + speed * cos(theta / 360 * 2 * PI));

		point_left.setPosition(point_left.getPosition().x + speed * sin(theta / 360 * 2 * PI), point_left.getPosition().y, point_left.getPosition().z + speed * cos(theta / 360 * 2 * PI));
		point_center.setPosition(point_center.getPosition().x + speed * sin(theta / 360 * 2 * PI), point_center.getPosition().y, point_center.getPosition().z + speed * cos(theta / 360 * 2 * PI));
		point_right.setPosition(point_right.getPosition().x + speed * sin(theta / 360 * 2 * PI), point_right.getPosition().y, point_right.getPosition().z + speed * cos(theta / 360 * 2 * PI));

	}

}

void ofApp::drawCar() {

	ofSetColor(255);
	ofFill();
//	cout << "COORDINATE:" << wheel1.getMesh() << endl;
	//textureWheels.enableMipmap();

	//uv.set(1, 4);

	
	//wheel1.draw();


	point_left.draw();
	point_right.draw();
	
	ofEnableDepthTest();
	textureWheels.bind();
	ofSetColor(255);
	wheel1.draw();
	wheel2.draw();
	wheel3.draw();
	wheel4.draw();
	textureWheels.unbind();
	ofDisableDepthTest();


	ofEnableDepthTest();
	//textureBody.bind();
	ofSetColor(0,0,0);
	point_center.drawWireframe();
	//textureBody.unbind();
	ofDisableDepthTest();

	if (controlArena()) {

			if (marcia) {

				if (speed >= max_speed) {

					cout << speed << endl;
					moveW();

				}
				else{

					speed = speed + 0.005;
					wheel_deg = wheel_deg + 0.01;
					cout << speed << endl;
					moveW();
				}

			}

			else if (retromarcia) {

				if (speed >= max_speed / 2) {

					cout << speed << endl;
					moveS();

				}
				else {

					speed = speed + 0.005;
					wheel_deg = wheel_deg + 0.01;
					cout << speed << endl;
					moveS();
				}
			}

			else if (speed > 0 && !marcia) {

				speed = speed - 0.005;
				wheel_deg = wheel_deg - 0.01;

				if (rallentamento_marcia) {
					moveW();
					//cout << "Rallentamento in marcia" << endl;
				}
				else {

					moveS();
					//cout << "Rallentamento in retromarcia" << endl;
				}
				}

				if (speed <= 0) {

					wheel_deg = 1;
				}

	}

}


bool ofApp::controlArena() {

	//CONTROLLO ARENA X
	if (point_center.getPosition().x - distance < xRight/2  || point_center.getPosition().x + distance > left.getPosition().x - xLeft/2 ) {

		//cout << "SEI FUORI ARENA" << endl;
		return false;

	}

	//CONTROLLO Z
	else if (point_center.getPosition().z - distance < zBack1/2 || point_center.getPosition().z + distance > front.getPosition().z - zFront/2) {

		//cout << "SEI FUORI ARENA" << endl;
		return false;

	}

	else return true;



}