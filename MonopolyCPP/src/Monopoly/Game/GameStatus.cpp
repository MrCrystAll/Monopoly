#include <Monopoly/Game/GameStatus.h>

GameStatus::GameStatus(GameSetup& setup, Board* board): finished(false), setup(setup), board(board)
{
	this->turnStatus = new TurnStatus();
	this->turnStatus->playerTurnsStatus = {};

	for (const Player* p : setup.GetPlayers()) {
		this->turnStatus->playerTurnsStatus[p->GetStamp()] = PlayerTurnStatus();
	}
}

bool GameStatus::IsFinished() const
{
	return this->finished;
}

std::vector<Player*> GameStatus::GetPlayers() const
{
	return this->setup.GetPlayers();
}

Board* GameStatus::GetBoard() const
{
	return this->board;
}

void GameStatus::Update()
{
	for (Player* p : this->GetPlayers()) {

		if (p->IsOut()) {
			this->dead[p] = this->nTurns;
			this->GetPlayers().erase(std::remove(this->GetPlayers().begin(), this->GetPlayers().end(), p), this->GetPlayers().end());
		}
	}
	if (this->GetPlayers().size() == 1) {
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
	return this->setup.GetRunInteractions();
}

void GameStatus::SetRunInteractions(bool runInteractions)
{
	this->setup.SetRunInteractions(runInteractions);
}

int GameStatus::GetVerbose() const
{
	return this->setup.GetVerbose();
}

void GameStatus::SetVerbose(int verbose)
{
	this->setup.SetVerbose(verbose);
}
