#pragma once

#include <Monopoly/Players/PlayerStamp.h>
#include <Monopoly/Utils.h>
#include <vector>
#include <Monopoly/Models/Results.h>

#include <nlohmann/json.hpp>

struct Choice {
	int id;
	std::string description = "";
};

class Player {
public:
	Player() = default;
	Player(PlayerStamp stamp, int defaultMoney = 2000);

	virtual const DiceResult Roll();
	virtual const int Ask(std::vector<Choice> choices, std::string question = "");

	virtual void AddMoney(int money);
	virtual void WithdrawMoney(int money);

	bool IsInPrison() const;
	int GetMoney() const;
	PlayerStamp GetStamp() const;

	int GetPosition() const;
	void SetPosition(int position);

	virtual bool IsOut() const;
	virtual void GoesOut();

	friend bool operator==(Player p1, Player p2);
protected:
	PlayerStamp stamp;
	bool isInPrison;
	int money;
	int position = 0;

	bool isOut = false;

	NLOHMANN_DEFINE_TYPE_INTRUSIVE(Player, stamp, isInPrison, money, position, isOut)
};
