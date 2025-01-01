#include <Monopoly/Slots/RentableSlot.h>

RentableSlot::RentableSlot(std::string name, int buyPrice, int baseRent, int mortgageValue) : BuyableSlot(name, buyPrice), baseRent(baseRent), mortgageValue(mortgageValue)
{
	this->isMortgaged = false;
}

RentableSlot::RentableSlot(BuyableSlot* buyableSlot, int baseRent, int mortgageValue): RentableSlot(buyableSlot->GetName(), buyableSlot->GetBuyPrice(), baseRent, mortgageValue)
{
}


bool RentableSlot::CanRent() const
{
	return true;
}

bool RentableSlot::CanMortgage() const
{
	return not this->isMortgaged;
}

int RentableSlot::GetMortgageValue() const
{
	return this->mortgageValue;
}

void RentableSlot::Sell()
{
	BuyableSlot::Sell();
	this->isMortgaged = false;
}

int RentableSlot::GetValue() const
{
	int mortgageMinus = this->IsMortgaged() ? this->mortgageValue : 0;
	return this->buyPrice - mortgageMinus;
}

bool RentableSlot::IsMortgaged() const
{
	return this->isMortgaged;
}

void RentableSlot::Mortgage()
{
	this->isMortgaged = true;
}

bool RentableSlot::CanLift() const
{
	return this->isMortgaged;
}

void RentableSlot::Lift()
{
	this->isMortgaged = false;
}

int RentableSlot::GetRent() const
{
	return this->IsMortgaged() ? 0 : this->baseRent;
}

Slot* RentableSlot::Copy() const
{
	return new RentableSlot(this->name, this->buyPrice, this->baseRent, this->mortgageValue);
}

void RentableSlot::ToJson(nlohmann::json& nlohmann_json_j) const
{
	BuyableSlot::ToJson(nlohmann_json_j);
	nlohmann_json_j["baseRent"] = this->baseRent;
	nlohmann_json_j["isMortgaged"] = this->isMortgaged;
	nlohmann_json_j["mortgageValue"] = this->mortgageValue;
}

void RentableSlot::FromJson(const nlohmann::json& nlohmann_json_j)
{
	BuyableSlot::FromJson(nlohmann_json_j);
	nlohmann_json_j.at("baseRent").get_to(this->baseRent);
	nlohmann_json_j.at("isMortgaged").get_to(this->isMortgaged);
	nlohmann_json_j.at("mortgageValue").get_to(this->mortgageValue);
}
