#pragma once

#include <Monopoly/Slots/BuyableSlot.h>

class RentableSlot : public BuyableSlot {
public:
	RentableSlot(std::string name, int buyPrice, int baseRent, int mortgageValue);
	RentableSlot(BuyableSlot* buyableSlot, int baseRent, int mortgageValue);

	#pragma region Rent

	virtual bool CanRent() const override;
	virtual int GetRent() const override;

	#pragma endregion

	#pragma region Sell

	virtual void Sell() override;
	virtual int GetValue() const override;

	#pragma endregion

	#pragma region Mortgage

	virtual bool CanMortgage() const override;
	virtual int GetMortgageValue() const override;
	virtual void Mortgage() override;

	virtual bool CanLift() const override;
	virtual void Lift() override;

	virtual bool IsMortgaged() const;


	#pragma endregion

	#pragma region Utils

	virtual Slot* Copy() const override;

	virtual void ToJson(nlohmann::json& nlohmann_json_j) const override;
	virtual void FromJson(const nlohmann::json& nlohmann_json_j) override;

	#pragma endregion

protected:
	int baseRent;
	bool isMortgaged;

	int mortgageValue;
};
