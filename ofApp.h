#pragma once

#include "ofMain.h"
#include "ofxBullet.h"
#include "ofxGui.h"
#include "ofxAssimpModelLoader.h"


class ofApp : public ofBaseApp {

public:
	void setup();
	void update();
	void draw();

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);

	vector <ofxBulletBox*>		bounds;
	ofxBulletCustomShape*		boundsShape;
	ofMaterial					boundsMat;
	float						boundsWidth;
	ofEasyCam					cam;

	ofxBulletSphere*			sphere;
	ofxBulletBox*				car;
	//ofxBulletCustomShape		octane;



	ofBoxPrimitive box;
	float angle;
	ofLight light;
	bool bOrbit, bRoll;
	float angleH, roll, distance;

	//Punteggio
	int num_partita = 0;
	int	 score = 0;

	//Variabili di movimento
	int forza = 250;
	int frizione = -25;

	/****** ARENA ******/
	ofxBulletWorldRigid			world;
	



	// GROUND //
	int xGround = 120;
	int zGround = 100;
	int yGround = 1;
	ofxBulletBox ground;

	// BACK WALL //
	int xBack = 100;
	int yBack = 50;
	int zBack = 5;
	ofxBulletBox back;


	// BACK WALL LEFT AND RIGHT //
	int xBack1 = 40;
	int yBack1 = 60;
	int zBack1 = 5;
	ofxBulletBox back1;
	ofxBulletBox back2;

	//TARGET//
	int xTarget = 40;
	int yTarget = 30;
	int zTarget = 5;
	ofxBulletBox target;

	//RIGHT WALL//
	int xRight = 5;
	int yRight = 60;
	int zRight = 100;
	ofxBulletBox right;

	//LEFT WALL//
	int xLeft = 5;
	int yLeft = 60;
	int zLeft = 100;
	ofxBulletBox left;

	/*CELING//
	int xCeiling= 120;
	int yCeiling = 100;
	int zCeiling = 0.05;*/
	ofxBulletBox ceiling;

	//FRONT WALL//
	int xFront = 120;
	int yFront = 60;
	int zFront = 5;
	ofxBulletBox front;


	/****** GUI ******/
	ofxPanel gui_game;
	ofxPanel gui_ball;
	ofxPanel gui_init;
	ofxPanel gui_stats;
	void drawInitialGui();
	void drawGuiGame();
	void drawGuiBall();
	ofxFloatSlider ball_radius;
	ofxFloatSlider ball_restitution;
	ofxFloatSlider car_width;
	ofxFloatSlider car_height;
	ofxToggle lockCamera;
	ofxButton resetBallButton;
	ofxButton resetCarButton;
	ofxButton playGame;
	ofxButton restartGame;
	ofxLabel labelGame;
	ofxLabel labelPoint;
	ofxLabel labelSeconds;
	ofxLabel labelNumMatch;
	ofxLabel labelMatch;
	ofxLabel labelBall;
	ofxLabel labelCar;

	/*GUI MUSIC*/
	ofxPanel gui_music;
	ofxFloatSlider volume=0.0; //MUSICA INIZIALE DEL GIOCO E MUSICA BACKGROUND : SONO ESCLUSI GLI EFFETTI

	
	
	void resetTarget();

	void resetBall();
	void resetCar();
	void play();
	void restartPlay();
	bool SplashScreen = false; //mostra menu iniziale

	/***** TIME *****/
	double start_timer;
	double end_timer;
	double time_game = 10000; //300.000 are 5 minutes -- 125.000 are 2 minutes
	int timer = 0;

	bool started = false;
	double start_countdown;
	double end_countdown;
	double time_countdown = 5000; //300.000 are 5 minutes -- 125.000 are 2 minutes
	int countdown = 0;
	int scelta = 0;

	/*LEVELS*/
	ofxPanel gui_level;
	ofxButton levelButton;
	//int selectLevel = 0;


	/*LEVEL 4*/
	void level4();
	bool checkLevel4 = false;
	bool reverseLevel4 = false;



	void settingLevel();
	/*GUI LEVELS*/
	
	float overflow=0;
	ofxIntSlider levels;
	

	//3D OBJECT

	ofxAssimpModelLoader octaneModel;
	vector<ofxBulletCustomShape*>	logos;
	ofVboMesh mesh;
	bool bUsingMesh=true;
	ofNode meshNode;
	//ofxBulletWorldRigid			world;
	ofMaterial						logoMat;


	//background
	ofImage background;


	//SOUNDS
	ofSoundPlayer   soundCountdown;

	//Effect Gol
	//int frame_gol = 10000000;
	void effectGol();
	ofSoundPlayer   soundGol;
	ofSoundPlayer   voiceGol;
	ofSoundPlayer   whistle;

	double start_effect;
	double end_effect;
	double time_effect = 4000; //4000 are 4 second for effet
	int effect = 0;



	//Ball Effect
	
	ofSoundPlayer   soundBall;

	//Sound in Game
	ofSoundPlayer   generalSound;

	//Sound Car
	ofSoundPlayer   soundAcc;


	//StartGame
	ofSoundPlayer initSound;

	/**** TEXTURE ***/
	ofTexture textureBall;
	ofTexture textureGround;
	ofTexture textureCar;
	ofTexture textureWall;

	//SCOREBOARD
	ofImage scoreboard;


};

