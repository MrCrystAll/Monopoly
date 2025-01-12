#pragma once

#include <vector>
#include <map>
#include <Monopoly/Players/Player.h>
#include <Monopoly/Models/TurnStatus.h>
#include <Monopoly/Board/Board.h>

class GameStatus {
public:
	GameStatus(std::vector<Player*> players, Board* board);

	bool IsFinished() const;
	std::vector<Player*> GetPlayers() const;
	Board* GetBoard() const;
	void Update();
	int GetTurn() const;
	std::map<Player*, int> GetDeadPlayers() const;
	TurnStatus* GetTurnStatus() const;

	bool GetRunInteractions() const;
	void SetRunInteractions(bool runInteractions);

private:

	bool finished = false;
	bool runInteractions = true;
	std::vector<Player*> players = {};
	std::map<Player*, int> dead = {};
	TurnStatus* turnStatus;
	Board* board;
	int nTurns = 0;
};