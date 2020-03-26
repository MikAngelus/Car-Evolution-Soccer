#pragma once

#include "ofMain.h"
#include "ofxBullet.h"
#include "ofxGui.h"
#include <iostream>  
#include <fstream>  
#include <string>  

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

	ofImage background; //Immagine utilizzata come sfondo nel menù iniziale
	ofEasyCam cam; //Variabile CAMERA
	ofxBulletSphere* sphere; //Variabile Pallone

	/****** ARENA ******/
	ofxBulletWorldRigid	 world; // Variabile che definisce il mondo e che è presente la gravità della libreria ofxbulletWordRigid

	// GROUND //
	int xGround = 120;
	int zGround = 100;
	int yGround = 1;
	ofxBulletBox ground;

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

	//CELING//
	ofxBulletBox ceiling;

	//FRONT WALL//
	int xFront = 120;
	int yFront = 60;
	int zFront = 5;
	ofxBulletBox front;

	void createArena(); // Funzione che creare l'arena di gioco
	void createObstacle(); //Funzione che creare gli ostacoli


	/****** GUI ******/
	ofxPanel gui_game; // Pannello di gioco --> in alto a sinistra
	ofxPanel gui_setting; //Pannello dei setting e opzioni
	ofxPanel gui_first; //Pannello menù iniziale
	ofxPanel gui_stats; //Pannello statistiche --> in alto a destra
	
	//Funzioni DRAW pannelli //
	void drawGuiGame();
	void drawGuiFirst();
	void drawGuiStatistics();
	void drawGuiSetting();


	//Variabili presenti nei pannelli //
	ofxFloatSlider ball_radius; //Variabile raggio pallone
	ofxFloatSlider ball_restitution; //Variabile utilizzata per la libreria ofxbullet che indica la forza di rimbalzo/impatto
	ofxFloatSlider volume = 0.3; //Musica iniziale del gioco
	ofxIntSlider levels = 1; //Setta il livello del gioco

	// TOOGLE AND BUTTON //
	ofxToggle lockCamera; //Toogle blocco camera
	ofxButton resetBallButton; //Pulsante Reset Pallone
	ofxButton resetCarButton; // Pulsante Reset Macchina
	ofxButton playGame; // Pulsante Play game
	ofxButton restartGame; //Pulsante Riavvio gioco
	ofxButton buttonHistory; //Pulsante mostra cronologia
	ofxToggle setting; //Toogle apri setting e option
	ofxButton rules; // Pulsante mostra regole

	// LABEL //
	ofxLabel labelPoint; //Segna i gol segnati
	ofxLabel labelSeconds; //Segna i secondi rimanenti
	ofxLabel labelNumMatch; //Segna le partita giocate
	ofxLabel labelMatch; //Segna lo stato del match

	// Funzioni di gioco //
	void resetTarget(); //Reset e imposta la porta/target
	void resetBall(); //Funzione reset palla
	void resetCar(); //Funzione reset macchina
	void play(); //Funzione Play
	void restartPlay(); //Funzione reset play
	bool initialMenu = true; //Mostra menu iniziale --> true

	/***** TIME *****/
	double start_timer; //Variabile che segna l'inzio del timer gioco
	double end_timer; //Variabile che segna la fine del timer gioco
	double time_game = 300000; //Tempo di gioco: 300 000 are 5 minutes -- 125 000 are 2 minutes
	int timer = 0; //Variabile che indica i ms trascorsi
	double start_countdown; //Variabile che segna l'inzio del timer countdown
	double end_countdown; //Variabile che segna la fine del timer countdown
	double time_countdown = 5000; //Tempo di gioco: 5000 are 5 seconds
	int countdown = 0; //Variabile che indica i ms trascorsi
	int timeCompleted = 0; //Tempo trascorso per completare il gioco
	bool started = false; //Verifica partita iniziata
	bool completed = false; //Verifica partita conclusa

	int num_match = 0; // Variabile numero partita
	int	 score = 0; // Gol segnati

	/***** OSTACOLI ******/

	/*LEVEL 4*/
	void level4(); //Funzione che chiama il livello 4
	bool reverseLevel4 = false; //Variabile che indica quando effettuare l'inversione di marcia dell'ostacolo

	/*LEVEL 5*/
	void level5(); // Funzione che chiama il livello 5
	bool reverseLevel5 = false; //Variabile che indica quando effettuare l'inversione di marcia dell'ostacolo

	/*LEVEL 6*/
	void level6(); // Funzione che chiama il livello 6
	bool reverseLevel6 = false; //Variabile che indica quando effettuare l'inversione di marcia dell'ostacolo

	// OSTACOLO 6//
	int xOst6 = 40;
	int yOst6 = 20;
	int zOst6 = 5;
	ofxBulletBox* obs6;

	/*LEVEL 7*/
	void level7();
	bool reverseLevel7 = false;

	// OSTACOLO 7//
	int xOst7 = xGround;
	int yOst7 = yBack1 / 2;
	int zOst7 = yGround;
	ofxBulletBox* obs7;

	/*LEVEL 8*/
	void level8();
	bool reverseLevel8 = false;

	/*LEVEL 9*/
	void level9();
	bool reverseLevel9 = false;

	// OSTACOLO 9//
	int xOst9 = 15;
	int yOst9 = 15;
	int zOst9 = 15;
	ofxBulletBox* obs9;

	/*LEVEL 10*/
	void level10();
	bool reverseLevel10 = false;

	int readLevel; //Variabile che legge l'attuale livello giocato
	void settingLevel(); //Funzone che gestisce i livelli impostati

	float overflow_target=0; //Variabile che gestisce la dimensione della porta
	float overflow = 0; //Variabile che gestisce lo spostamento degli ostacoli - Utilizzato dal livello 6 in poi

	// Effetti quando si fa gol //
	double start_effect; //Variabile che segna l'inzio del timer effect
	double end_effect; //Variabile che segna la fine del timer effect
	double time_effect = 4000; //Durata funzione effectGol: 4 secondi
	void effectGol(); //Funzione richiamata quando viene fatto gol

	//SOUNDS
	ofSoundPlayer   soundCountdown; //Suono Countdown
	ofSoundPlayer   soundGol; //Suono gol
	ofSoundPlayer   voiceGol; //Voce gol
	ofSoundPlayer   whistle; //Suono fischio finale
	ofSoundPlayer   generalSound; //Sound in game
	ofSoundPlayer   initSound; //Suono avvio gioco
	
	/**** TEXTURE ***/
	ofTexture textureBall;
	ofTexture textureGround;
	ofTexture textureWheels;
	ofTexture textureWall;
	ofTexture textureObstacle;
	ofTexture textureBody;

	/***** CAR *****/
	ofBoxPrimitive wheel1, wheel2, wheel3, wheel4, point_left, point_right, point_center; //Variabili utili per costruire la macchina
	float distance = 5; //Variabile per distanziare gli elementi della macchina

	bool rotation_left = false; //Verifica rotazione sx
	bool rotation_right = false; //Verifica rotazione dx
	bool marcia = false; //Verifica se la macchina si muove in avanti
	bool retromarcia = false; //Verifica se la macchina si muove indietro

	void resetLeftRightPoint(); //Imposta e resetta i punti di rotazione
	void createCar(); //Funzione che creare la macchina
	void drawCar(); //Funzione DRAW macchina

	void moveW(); //Funzione eseguita quando si va in avanti --> Key W
	void moveD(int deg);  //Funzione eseguita quando si va a destra  --> Key D
	void moveA(int deg); //Funzione eseguita quando si va in sinistra --> Key A
	void moveS(); //Funzione eseguita quando si va indietro --> Key S
	bool controlArena(); //Funzione verifica che la macchina sia dentro il perimetro dell'arena
	
	float speed = 0.05; //Velocità macchina
	float max_speed = 1; //Velocità max che può assumere la macchina
	int rallentamento_marcia = true; //rallentamento macchina quando è in velocità e vengono rilasciati i pulsanti

	ofVec3f eur_deg; //Angolo di rotazione macchina
	float theta = 0; //Gradi angolo macchina
	float wheel_deg = speed + 1; //Gradi ruote 

	vector < string > linesOfTheFile; //Variabile lettura stringhe in input da file
	void readRules(); //Funzione leggi regolamento
	bool activeRules = false; //Verifica regole attive
	void readHistory(); //Funzione leggi cronologia
	bool activeHistory = false; //Verifica cronologia attiva
	bool savedHistory = false; //Verifica se il punteggio finale è stato salvato nel file
	string nickname; //Variabile salvataggio nickname
	void insertNick(); //Funzione che richiede l'inserimento del nickname
	
	// FONT //
	ofTrueTypeFont title;
	ofTrueTypeFont subtitle;
	ofTrueTypeFont label;

};

