#include <Monopoly/Slots/BuyableSlot.h>

BuyableSlot::BuyableSlot(std::string name, int buyPrice): Slot(name), buyPrice(buyPrice)
{
}

bool BuyableSlot::CanBuy() const
{
	return true;
}

void BuyableSlot::Buy(PlayerStamp p)
{
	this->pStamp = p;
}

int BuyableSlot::GetBuyPrice() const
{
	return this->buyPrice;
}

PlayerStamp BuyableSlot::GetOwner() const
{
	return this->pStamp;
}

void BuyableSlot::Sell()
{
	this->pStamp = -1;
}

int BuyableSlot::GetValue() const
{
	return this->buyPrice;
}

Slot* BuyableSlot::Copy() const
{
	return new BuyableSlot(this->name, this->buyPrice);
}

void BuyableSlot::ToJson(nlohmann::json& nlohmann_json_j) const
{
	Slot::ToJson(nlohmann_json_j);
	nlohmann_json_j["buyPrice"] = this->buyPrice;
}

void BuyableSlot::FromJson(const nlohmann::json& nlohmann_json_j)
{
	Slot::FromJson(nlohmann_json_j);
	nlohmann_json_j.at("buyPrice").get_to(this->buyPrice);
}
