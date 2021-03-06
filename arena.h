void ofApp::createArena(){

	world.setup();
	world.setGravity(ofVec3f(0, -9.8, 0)); // Di default la gravit� 0,9.8,0 verso l'asse Y+
	world.enableGrabbing();
	world.enableDebugDraw();
	world.setCamera(&cam);

	ground.create(world.world, ofVec3f(xGround / 2, yGround / 2, zGround / 2), 0, xGround, yGround, zGround);
	ground.setProperties(.25, .95);
	ground.add();

	ceiling.create(world.world, ofVec3f(xGround / 2, yBack1, zGround / 2), 0, xGround, yGround, zGround);
	ceiling.setProperties(.25, .95);
	ceiling.add();

	back1.create(world.world, ofVec3f(xBack1 / 2, yBack1 / 2, 0), 0, xBack1, yBack1, zBack1);
	back1.setProperties(.25, .95);
	back1.add();

	target.create(world.world, ofVec3f(xGround / 2, yBack1 / 2 + yTarget / 2, 0), 0, xTarget, yTarget, zTarget);
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


}

void ofApp::createObstacle() { //Inizializzo gli ostacoli

	//OSTACOLO livello 6
	obs6 =  new ofxBulletBox();
	obs6->create(world.world, ofVec3f(xGround, 0, zGround / 2), 0, 0, 0, 0);
	obs6->setProperties(.25, .95);
	obs6->add();

	//OSTACOLO livello 7
	obs7 = new ofxBulletBox();
	obs7->create(world.world, ofVec3f(xGround, 0, zGround / 2), 0, 0, 0, 0);
	obs7->setProperties(.25, .95);
	obs7->add();

	//OSTACOLO LIVELLO 9
	obs9 = new ofxBulletBox();
	obs9->create(world.world, ofVec3f(xGround, 0, zGround / 2), 0, 0, 0, 0);
	obs9->setProperties(.25, .95);
	obs9->add();

}