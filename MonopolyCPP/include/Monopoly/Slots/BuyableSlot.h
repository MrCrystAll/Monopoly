#pragma once

#include <Monopoly/Slots/Slot.h>

class BuyableSlot : public Slot {
public:
	BuyableSlot(std::string name, int buyPrice);
	BuyableSlot(Slot* slot, int buyPrice);

	#pragma region Stats

	virtual PlayerStamp GetOwner() const override;

	#pragma endregion

	#pragma region Buy

	virtual bool CanBuy() const override;
	virtual void Buy(PlayerStamp p) override;
	virtual int GetBuyPrice() const override;

	#pragma endregion

	#pragma region Sell

	virtual void Sell() override;
	virtual int GetValue() const override;

	#pragma endregion

	#pragma region Utils

	virtual Slot* Copy() const override;

	virtual void ToJson(nlohmann::json& nlohmann_json_j) const override;
	virtual void FromJson(const nlohmann::json& nlohmann_json_j) override;

	#pragma endregion

protected:
	int buyPrice;
	PlayerStamp pStamp = -1;
};
