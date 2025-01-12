#pragma once

#include <vector>
#include <Monopoly/Players/Player.h>
#include <Monopoly/Interactions/PlayerPropertyInteraction.h>
#include <nlohmann/json.hpp>

#include <Monopoly/Game/GameSetup.h>
#include <Monopoly/Game/GameStatus.h>

using json = nlohmann::json;

class Game {
public:
	Game(GameSetup& setup);

	void Start();
	bool Turn(int verbose = 0);
	bool PlayerTurn(Player& p, Report& r);

private:
	void Init(GameSetup& setup);
	void PlayerSummary(Player p);
	std::vector<Slot*> GetPropertiesOf(PlayerStamp p) const;
	GameStatus* status;
	std::vector<Report> gameInteractions = {};

	PlayerPropertyInteraction ppInteraction = PlayerPropertyInteraction(this->status);
};
