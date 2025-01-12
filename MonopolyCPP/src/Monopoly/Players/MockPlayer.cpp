#include <Monopoly/Players/MockPlayer.h>

MockPlayer::MockPlayer(PlayerStamp pStamp, int defaultMoney): Player(pStamp, defaultMoney)
{
}

DiceResult MockPlayer::Roll() const
{
	return this->nextDiceResult;
}

void MockPlayer::SetDiceResult(DiceResult result)
{
	this->nextDiceResult = result;
}

void MockPlayer::SetMoney(int money)
{
	this->money = money;
}
