
void ofApp::drawGuiFirst() { //Pannello menù iniziale
	
	gui_first.setDefaultHeight(25);
	gui_first.setup("GAME", "GAME", ofGetWidth() / 2 - 75, ofGetHeight() / 2);

	if (num_match == 0) {
		gui_first.add(playGame.setup("Start Game"));
	}

	else if (num_match > 0) {
		gui_first.add(restartGame.setup("Restart Game"));
	}
	gui_first.add(buttonHistory.setup("History"));
	gui_first.add(rules.setup("Game rules"));


}

void ofApp::drawGuiGame() { // Pannello di gioco --> in alto a sinistra
	gui_game.setDefaultHeight(25);
	gui_game.setup("GAME", "GAME", 25, 25);
	gui_game.add(restartGame.setup("Restart Game"));
	gui_game.add(lockCamera.setup("Lock camera", true));
	gui_game.add(setting.setup("Option", false));

}

void ofApp::drawGuiStatistics() { //Pannello statistiche --> in alto a destra
	gui_stats.setDefaultHeight(25);
	gui_stats.setup("STATISTICS", "STATISTICS", ofGetWidth() - 250, 25 );
	gui_stats.add(labelPoint.setup("Score", ofToString(score)));
	gui_stats.add(labelNumMatch.setup("Match nr", ofToString(num_match)));
	gui_stats.add(labelSeconds.setup("Seconds Remaining", ofToString(timer)));

	if (num_match > 0 && ofGetSystemTimeMillis() > end_timer) {
		gui_stats.add(labelMatch.setup("State Match", "finished"));
	}

	else if (num_match > 0 && ofGetSystemTimeMillis() <= end_timer) {
		gui_stats.add(labelMatch.setup("State Match", "in progress"));
	}

	else {
		gui_stats.add(labelMatch.setup("State Match", "to start"));
	}

}

void ofApp::drawGuiSetting() { //Pannello dei setting e opzioni
	gui_setting.setDefaultHeight(25); 
	gui_setting.setup("SETTING", "SETTING", 25, (gui_game.getPosition().y + 150));
	gui_setting.add(ball_radius.setup("Raggio Pallone", 4, 4, 10)); //4 il raggio impostato di default
	gui_setting.add(ball_restitution.setup("Forza Rimbalzo", 3, 3, 5)); //default 3
	gui_setting.add(resetBallButton.setup("Reset Ball"));
	gui_setting.add(resetCarButton.setup("Reset Car"));
	gui_setting.add(volume.setup("Volume", 0.3, 0.0, 1.0)); //Default 0.3
	gui_setting.add(levels.setup("Level", 1, 1, 10)); 


}
