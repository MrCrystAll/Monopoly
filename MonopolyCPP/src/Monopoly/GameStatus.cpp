#include <Monopoly/GameStatus.h>

GameStatus::GameStatus(std::vector<Player*> players, Board* board): finished(false), players(players), board(board)
{
	this->turnStatus = new TurnStatus();
	this->turnStatus->playerTurnsStatus = {};

	for (const Player* p : players) {
		this->turnStatus->playerTurnsStatus[p->GetStamp()] = PlayerTurnStatus();
	}
}

bool GameStatus::IsFinished() const
{
	return this->finished;
}

std::vector<Player*> GameStatus::GetPlayers() const
{
	return this->players;
}

Board* GameStatus::GetBoard() const
{
	return this->board;
}

void GameStatus::Update()
{
	for (Player* p : this->players) {

		if (p->IsOut()) {
			this->dead[p] = this->nTurns;
			this->players.erase(std::remove(this->players.begin(), this->players.end(), p), this->players.end());
		}
	}
	if (this->players.size() == 1) {
		this->finished = true;
	}
	this->nTurns++;
}

int GameStatus::GetTurn() const
{
	return this->nTurns;
}

std::map<Player*, int> GameStatus::GetDeadPlayers() const
{
	return this->dead;
}

TurnStatus* GameStatus::GetTurnStatus() const
{
	return this->turnStatus;
}

bool GameStatus::GetRunInteractions() const
{
	return this->runInteractions;
}

void GameStatus::SetRunInteractions(bool runInteractions)
{
	this->runInteractions = runInteractions;
}

GameSetup::GameSetup(int nPlayers, std::vector<Player*> players, bool runInteractions): nPlayers(nPlayers), players(players), runInteractions(runInteractions)
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
