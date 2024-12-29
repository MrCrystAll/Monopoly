#include <Monopoly/Players/Player.h>


Player::Player(PlayerStamp stamp, int defaultMoney): stamp(stamp), money(defaultMoney)
{
	this->isInPrison = false;
}

const DiceResult Player::Roll()
{
	int dice1 = Random(1, 7);
	int dice2 = Random(1, 7);

	bool d = dice1 == dice2;

	return { dice1 + dice2, d };
}

const int Player::Ask(std::vector<Choice> choices, std::string question)
{
	/*if (not question.empty()) {
		LOG(question);
	}

	for (uint16_t i = 0; i < choices.size(); i++)
	{
		const Choice c = choices[i];
		LOG(c.id << " - " << c.description);
	}*/

	int random_choice = Random(0, (int)choices.size());
	return choices[random_choice].id;
}

void Player::AddMoney(int money)
{
	this->money += money;
}

void Player::WithdrawMoney(int money)
{
	this->money -= money;
}

bool Player::IsInPrison() const
{
	return this->isInPrison;
}

int Player::GetMoney() const
{
	return this->money;
}

PlayerStamp Player::GetStamp() const
{
	return this->stamp;
}

int Player::GetPosition() const
{
	return this->position;
}

void Player::SetPosition(int position)
{
	this->position = position;
}

bool Player::IsOut() const
{
	return this->isOut;
}

void Player::GoesOut()
{
	this->isOut = true;
}

bool operator==(Player p1, Player p2)
{
	return p1.GetStamp() == p2.GetStamp();
}
