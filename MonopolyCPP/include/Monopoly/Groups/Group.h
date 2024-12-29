#pragma once
#include <Monopoly/Slots/Slot.h>
#include <Monopoly/Models/PlayerTurnStatus.h>

class Group {
public:
	Group(std::vector<Slot*> slots);

	#pragma region Rent

	virtual int GetRent(Slot* s, PlayerTurnStatus turnStatus) const;

	#pragma endregion

	#pragma region Sell

	virtual void Sell(Slot* s) const;
	virtual int GetValue(Slot* s) const;

	#pragma endregion

	#pragma region Build

	virtual bool CanPlayerBuildOn(Slot* s, PlayerStamp p) const;

	#pragma endregion

	#pragma region Mortgage

	virtual void Mortgage(Slot* s);
	virtual void Lift(Slot* s);

	#pragma endregion

	
	virtual std::vector<Slot*> GetSlots() const;
protected:
	std::vector<Slot*> slots;
};
