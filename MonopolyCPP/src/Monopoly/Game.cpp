#include <Monopoly/Game.h>
#include <iostream>
#include <fstream>

Game::Game(int nPlayers)
{
	std::vector<Player*> players = std::vector<Player*>();
	for (uint8_t i = 0; i < nPlayers; i++) {
		players.push_back(new Player(i));
	}
	Board* board = new Board(39);
	std::ofstream json_result;
	LOG("Write board to json...");
	json_result.open("board.json");

	json j = *board;

	json_result << j.dump(4);
	json_result.close();
	LOG("Json saved!");


	this->status = new GameStatus(players, board);

	this->ppInteraction = PlayerPropertyInteraction(this->status);
}

void Game::Start()
{
	while (not this->status->IsFinished()) {
		LOG("================ Turn " << this->status->GetTurn() << " =====================");
		Turn();
	}

	Player* winner = this->status->GetPlayers()[0];
	LOG("Game is finished, player " << winner->GetStamp() << " won");
	this->PlayerSummary(*winner);

	std::map<Player*, int> deadPlayers = this->status->GetDeadPlayers();

	for (const auto& [player, deadTurn] : deadPlayers) {
		LOG("Player " << player->GetStamp() << " died on turn " << deadTurn);
	}
	json j = this->gameInteractions;

	std::ofstream json_result;
	LOG("Saving to json...");
	json_result.open("results.json");
	json_result << j.dump(4);
	json_result.close();
	LOG("Json saved!");

}

bool Game::Turn()
{

	Report report = {};

	//Display turn
	for (const Player* p : this->status->GetPlayers()) {
		if (p->IsOut()) continue;
		this->PlayerSummary(*p);
	}

	//Oooooo, the turn is heeeeeeeeeeeeeeeeeeeere

	int nDead = 0;
	for (Player* p : this->status->GetPlayers()) {
		if (!PlayerTurn(*p, report)) {
			//Fuck outta here
			continue;
		}
	}

	report.turn = this->status->GetTurn();
	std::vector<Player> playerCopies = {};
	std::map<PlayerStamp, std::vector<Slot*>> slotsPerPlayer = {};

	for (Player* p : this->status->GetPlayers()) {
		playerCopies.push_back(*p);
		slotsPerPlayer[p->GetStamp()] = this->GetPropertiesOf(p->GetStamp());
	}
	report.players = playerCopies;
	report.slotsPerPlayer = slotsPerPlayer;

	this->status->Update();
	this->gameInteractions.push_back(report);

	return true;
}

bool Game::PlayerTurn(Player& p, Report& r)
{
	int oldPosition = p.GetPosition();

	bool isDouble = true;

	Slot* currentSlot = nullptr;

	while (isDouble) {
		DiceResult diceResult = p.Roll();

		this->status->GetTurnStatus()->playerTurnsStatus[p.GetStamp()].diceResult = diceResult;

		isDouble = diceResult.isDouble;

		int newPosition = (p.GetPosition() + diceResult.sum) % this->status->GetBoard()->GetBoardLength();
		p.SetPosition(newPosition);

		currentSlot = this->status->GetBoard()->GetSlotAt(p.GetPosition());
		Group* g = this->status->GetBoard()->GetGroupOf(currentSlot);

		this->ppInteraction.Interact(p, currentSlot, g, r);

		if (p.IsOut()) return false;

		//TODO: Interact with the board
	}

	//LOG("Player " << (int)p.GetStamp() << ": " << oldPosition << " -> " << p.GetPosition() << ". Current slot: " << currentSlot->GetName() << " | Money: " << p.GetMoney());

	return true;
}

void Game::PlayerSummary(Player p)
{
	LOG("Player " << p.GetStamp() << ":");
	LOG("\tMoney: " << p.GetMoney());

	const Slot* slot = this->status->GetBoard()->GetSlotAt(p.GetPosition());
	LOG("\tPosition: " << p.GetPosition() << " (" << slot->GetName() << ")");
	std::vector<Slot*> slots = this->GetPropertiesOf(p.GetStamp());

	if (slots.size() == 0) LOG("\tNo property");
	else {
		LOG("\tProperties:");
		for (const Slot* s : slots) {
			std::string houses = s->CanBuild() ? "Number of houses: " + std::to_string(s->GetNHouses()) : "";
			LOG("\t\t" << s->GetName() << " (" << houses << ")");
		}
	}
}

std::vector<Slot*> Game::GetPropertiesOf(PlayerStamp p) const
{
	return this->status->GetBoard()->GetPropertiesOf(p);
}
