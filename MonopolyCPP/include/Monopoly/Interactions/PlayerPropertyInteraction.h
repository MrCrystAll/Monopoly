#pragma once

#include <string>
#include <Monopoly/Players/Player.h>
#include <Monopoly/Slots/Slot.h>
#include <Monopoly/GameStatus.h>
#include <Monopoly/Logging/Report.h>
#include <Monopoly/Groups/Group.h>

class PlayerPropertyInteraction {
public:
	PlayerPropertyInteraction(GameStatus* status);

	enum Interactions
	{
		BUY,
		SELL,
		LIFT,
		BUILD,
		PAY
	};

	friend std::ostream& operator <<(std::ostream& stream, Interactions interaction);
	friend std::string ToString(Interactions interaction);

	void Interact(Player& pl, Slot* s, Group* g, Report& report);
private:
	std::vector<PlayerPropertyInteraction::Interactions> GetInteractions(Player& pl, Slot* s);
	const void Buy(Player& pl, Slot* s, Report& report);
	const void Sell(Player& pl, int moneyToReach, Report& report);
	const void Build(Player& pl, Slot* s, Group* g, Report& report);
	const void Lift(Player& pl, Slot* s, Group* g, Report& report);
	const void Pay(Player& pl, Slot* s, Group* g, Report& report);

	GameStatus* status;
};