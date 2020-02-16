
void ofApp::drawInitialGui() {

	gui_game.setup("GAME", "GAME", 25, 25);
	gui_game.add(restartGame.setup("Restart Game"));
	gui_game.add(lockCamera.setup("Lock camera", true)); //MOMENTANEAMENTE

}





void ofApp::drawGuiGame() {

	gui_stats.setup("STATISTICS", "STATISTICS", 25, gui_init.getHeight() + 50);
	//gui_game.add(labelGame.setup("Game Statistics", ""));
	gui_stats.add(labelPoint.setup("Score", ofToString(score)));
	gui_stats.add(labelNumMatch.setup("Match nr", ofToString(num_partita)));
	gui_stats.add(labelSeconds.setup("Seconds Remaining", ofToString(timer)));

	if (num_partita > 0 && ofGetSystemTimeMillis() > end_timer) {
		gui_stats.add(labelMatch.setup("State Match", "finished"));
	}

	else if (num_partita > 0 && ofGetSystemTimeMillis() <= end_timer) {
		gui_stats.add(labelMatch.setup("State Match", "in progress"));
	}

	else {
		gui_stats.add(labelMatch.setup("State Match", "to start"));
	}



}

void ofApp::drawGuiBall() {

	gui_ball.setup("BALLS", "BALLS", 25, ofGetHeight() / 2);
	gui_ball.add(ball_radius.setup("Raggio Pallone", 4, 0, 10));
	gui_ball.add(ball_restitution.setup("Forza Rimbalzo", 3, 1, 5));
	gui_ball.add(resetBallButton.setup("Reset Ball"));
	gui_ball.add(resetCarButton.setup("Reset Car"));


}
