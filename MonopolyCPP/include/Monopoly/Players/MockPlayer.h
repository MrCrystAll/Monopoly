#pragma once

#include <Monopoly/Players/Player.h>

class MockPlayer : public Player {
public:
	MockPlayer(PlayerStamp pStamp, int defaultMoney = 2000);
	virtual DiceResult Roll() const override;

	virtual void SetDiceResult(DiceResult result);
	virtual void SetMoney(int money);

protected:
	DiceResult nextDiceResult;
};
