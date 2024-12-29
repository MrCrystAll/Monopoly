#pragma once

#include <vector>
#include <Monopoly/Players/Player.h>
#include <Monopoly/Interactions/PlayerPropertyInteraction.h>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class Game {
public:
	Game(int nPlayers);

	void Start();

private:
	bool Turn();
	bool PlayerTurn(Player& p, Report& r);
	void PlayerSummary(Player p);
	std::vector<Slot*> GetPropertiesOf(PlayerStamp p) const;
	GameStatus* status;
	std::vector<Report> gameInteractions = {};

	PlayerPropertyInteraction ppInteraction = PlayerPropertyInteraction(this->status);
};
