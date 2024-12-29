#include <Monopoly/Slots/BuildableSlot.h>

BuildableSlot::BuildableSlot(std::string name, int buyPrice, int baseRent, int mortgageValue, int maxHouses, int pricePerHouse): RentableSlot(name, buyPrice, baseRent, mortgageValue), pricePerHouse(pricePerHouse)
{
	if (maxHouses > MAX_HOUSES_TOTAL) {
		ERR("Cannot place more than " << MAX_HOUSES_TOTAL << " houses on one property");
	}

	this->prices[0] = baseRent;
	
	this->prices[1] = (int)(this->prices[0] * 4299 / 300);
	this->prices[2] = (int)(this->prices[0] * 2113 / 122);
	this->prices[3] = (int)(this->prices[0] * 2259 / 388);
	this->prices[4] = (int)(this->prices[0] * 58 / 43);
	this->prices[5] = (int)(this->prices[0] * 1213 / 859);

	this->maxHouses = maxHouses;
}

int BuildableSlot::GetMaxHouses() const
{
	return this->maxHouses;
}

int BuildableSlot::GetPricePerHouse() const
{
	return this->pricePerHouse;
}

int BuildableSlot::GetPriceFor(int nHouses) const
{
	if (nHouses > maxHouses) return -1;
	return this->prices[nHouses];
}

int BuildableSlot::GetNHouses() const
{
	return this->nHouses;
}

bool BuildableSlot::CanBuild() const
{
	return true;
}

int BuildableSlot::GetRent() const
{
	return this->GetPriceFor(this->nHouses);
}

int BuildableSlot::GetValue() const
{
	return RentableSlot::GetValue() + this->pricePerHouse * this->nHouses;
}

void BuildableSlot::Sell()
{
	RentableSlot::Sell();

	this->nHouses = 0;
}

void BuildableSlot::Build(int nHouses)
{
	this->nHouses += nHouses;
}

void BuildableSlot::Destroy(int nHouses)
{
	this->nHouses = std::max(this->nHouses - nHouses, 0);
}

Slot* BuildableSlot::Copy() const
{
	BuildableSlot* bSlot = new BuildableSlot(this->name, this->buyPrice, this->baseRent, this->mortgageValue, this->maxHouses, this->pricePerHouse);
	bSlot->nHouses = this->nHouses;
	return bSlot;
}

void BuildableSlot::ToJson(nlohmann::json& nlohmann_json_j) const
{
	RentableSlot::ToJson(nlohmann_json_j);
	nlohmann_json_j["pricePerHouse"] = this->pricePerHouse;
	nlohmann_json_j["maxHouses"] = this->maxHouses;
	nlohmann_json_j["nHouses"] = this->nHouses;
	nlohmann_json_j["prices"] = this->prices;
}

void BuildableSlot::FromJson(const nlohmann::json& nlohmann_json_j)
{
	RentableSlot::FromJson(nlohmann_json_j);
	nlohmann_json_j.at("pricePerHouse").get_to(this->pricePerHouse);
	nlohmann_json_j.at("maxHouses").get_to(this->maxHouses);
	nlohmann_json_j.at("nHouses").get_to(this->nHouses);
	nlohmann_json_j.at("prices").get_to(this->prices);
}
