#pragma once

#include <vector>
#include <map>
#include <Monopoly/Players/Player.h>
#include <Monopoly/Models/TurnStatus.h>
#include <Monopoly/Board/Board.h>
#include <Monopoly/Game/GameSetup.h>

class GameStatus {
public:
	GameStatus(GameSetup& setup, Board* board);

	bool IsFinished() const;
	std::vector<Player*> GetPlayers() const;
	Board* GetBoard() const;
	void Update();
	int GetTurn() const;
	std::map<Player*, int> GetDeadPlayers() const;
	TurnStatus* GetTurnStatus() const;

	bool GetRunInteractions() const;
	void SetRunInteractions(bool runInteractions);

	int GetVerbose() const;
	void SetVerbose(int verbose);

private:

	bool finished = false;
	std::map<Player*, int> dead = {};
	TurnStatus* turnStatus;
	GameSetup& setup;
	Board* board;
	int nTurns = 0;
};