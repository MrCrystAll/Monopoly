#pragma once

#include <Monopoly/Players/Player.h>

class GameSetup {
public:
	GameSetup(int nPlayers = 0, std::vector<Player*> players = {}, bool runInteractions = true);

	bool GetRunInteractions() const;
	void SetRunInteractions(bool runInteractions);

	int GetNPlayers() const;

	std::vector<Player*> GetPlayers() const;

private:
	bool runInteractions;
	int nPlayers;
	std::vector<Player*> players;

	void PostInit();
};

