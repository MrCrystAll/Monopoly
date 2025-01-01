#pragma once

#include <Monopoly/Slots/RentableSlot.h>

#define MAX_HOUSES_TOTAL 16

class BuildableSlot : public RentableSlot {
public:
	BuildableSlot(std::string name, int buyPrice, int baseRent, int mortgageValue, int maxHouses, int pricePerHouse);
	BuildableSlot(RentableSlot* rentableSlot, int maxHouses, int pricePerHouse);

	#pragma region Rent

	virtual int GetRent() const override;

	#pragma endregion

	#pragma region Sell

	virtual void Sell() override;
	virtual int GetValue() const override;

	#pragma endregion

	#pragma region Build

	virtual int GetMaxHouses() const override;
	virtual int GetPricePerHouse() const override;
	virtual int GetPriceFor(int nHouses) const override;
	virtual int GetNHouses() const override;
	virtual bool CanBuild() const override;
	virtual void Build(int nHouses) override;
	virtual void Destroy(int nHouses) override;

	#pragma endregion

	#pragma region Utils

	virtual Slot* Copy() const override;

	virtual void ToJson(nlohmann::json& nlohmann_json_j) const override;
	virtual void FromJson(const nlohmann::json& nlohmann_json_j) override;

	#pragma endregion

protected:
	int maxHouses;
	int pricePerHouse;
	int prices[MAX_HOUSES_TOTAL];
	int nHouses = 0;
};
