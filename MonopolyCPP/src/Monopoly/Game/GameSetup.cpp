#include <Monopoly/Game/GameSetup.h>

GameSetup::GameSetup(int nPlayers, std::vector<Player*> players, bool runInteractions) : nPlayers(nPlayers), players(players), runInteractions(runInteractions)
{
	this->PostInit();
}

bool GameSetup::GetRunInteractions() const
{
	return this->runInteractions;
}

void GameSetup::SetRunInteractions(bool runInteractions)
{
	this->runInteractions = runInteractions;
}

int GameSetup::GetNPlayers() const
{
	return this->nPlayers;
}

std::vector<Player*> GameSetup::GetPlayers() const
{
	return this->players;
}

void GameSetup::PostInit()
{
	if (this->nPlayers > this->players.size()) {
		int diff = this->nPlayers - this->players.size();

		for (int i = 0; i < diff; i++) {
			this->players.push_back(new Player(this->players.size()));
		}
	}
	else if (this->nPlayers < this->players.size()) {
		this->nPlayers = this->players.size();
	}
}

