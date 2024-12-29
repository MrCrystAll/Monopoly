#pragma once

#include <string>
#include <Monopoly/Players/PlayerStamp.h>
#include <Monopoly/Utils.h>

#include <nlohmann/json.hpp>

using json = nlohmann::json;

class Slot {
public:
	Slot(std::string name);

	#pragma region Stats

	virtual std::string GetName() const;
	virtual PlayerStamp GetOwner() const;

	#pragma endregion

	#pragma region Buy

	virtual bool CanBuy() const;
	virtual void Buy(PlayerStamp stamp);
	virtual int GetBuyPrice() const;

	#pragma endregion

	#pragma region Rent

	virtual bool CanRent() const;
	virtual int GetRent() const;

	#pragma endregion

	#pragma region Sell

	virtual void Sell();
	virtual int GetValue() const;

	#pragma endregion

	#pragma region Build

	virtual bool CanBuild() const;
	virtual void Build(int nHouses);
	virtual void Destroy(int nHouses);

	virtual int GetMaxHouses() const;
	virtual int GetPricePerHouse() const;
	virtual int GetPriceFor(int nHouses) const;
	virtual int GetNHouses() const;

	#pragma endregion

	#pragma region Mortgage

	virtual bool CanMortgage() const;
	virtual int GetMortgageValue() const;
	virtual void Mortgage();

	virtual bool CanLift() const;
	virtual void Lift();

	virtual bool IsMortgaged() const;

	#pragma endregion

	#pragma region Utils

	virtual Slot* Copy() const;

	virtual void ToJson(nlohmann::json& nlohmann_json_j) const;
	virtual void FromJson(const nlohmann::json& nlohmann_json_j);

	#pragma endregion

protected:
	std::string name;
};
