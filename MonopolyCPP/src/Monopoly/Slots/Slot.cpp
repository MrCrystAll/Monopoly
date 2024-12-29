#include <Monopoly/Slots/Slot.h>

Slot::Slot(std::string name): name(name)
{
}

std::string Slot::GetName() const
{
	return this->name;
}

bool Slot::CanBuy() const
{
	return false;
}

bool Slot::CanRent() const
{
	return false;
}

bool Slot::CanBuild() const
{
	return false;
}

bool Slot::CanMortgage() const
{
	return false;
}

void Slot::Buy(PlayerStamp stamp)
{
	
}

void Slot::Sell()
{
}

PlayerStamp Slot::GetOwner() const
{
	return -1;
}

int Slot::GetBuyPrice() const
{
	return 0;
}

int Slot::GetValue() const
{
	return 0;
}

int Slot::GetMortgageValue() const
{
	return 0;
}

int Slot::GetRent() const
{
	return -1;
}

void Slot::Build(int nHouses)
{
}

void Slot::Destroy(int nHouses)
{
}

void Slot::Mortgage()
{
}

bool Slot::CanLift() const
{
	return false;
}

void Slot::Lift()
{
}

bool Slot::IsMortgaged() const
{
	return false;
}

int Slot::GetMaxHouses() const
{
	return 0;
}

int Slot::GetPricePerHouse() const
{
	return 0;
}

int Slot::GetPriceFor(int nHouses) const
{
	return 0;
}

int Slot::GetNHouses() const
{
	return 0;
}

Slot* Slot::Copy() const
{
	return new Slot(this->name);
}

void Slot::ToJson(nlohmann::json& nlohmann_json_j) const
{
	nlohmann_json_j["name"] = this->name;
}

void Slot::FromJson(const nlohmann::json& nlohmann_json_j)
{
	nlohmann_json_j.at("name").get_to(this->name);
}

