#pragma once

#include <vector>
#include <map>
#include <Monopoly/Players/Player.h>
#include <Monopoly/Board.h>

#include <Monopoly/Models/TurnStatus.h>

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

private:

	bool finished = false;
	std::vector<Player*> players = {};
	std::map<Player*, int> dead = {};
	TurnStatus* turnStatus;
	Board* board;
	int nTurns = 0;
};
