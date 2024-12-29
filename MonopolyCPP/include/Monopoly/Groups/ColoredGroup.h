#pragma once

#include <Monopoly/Groups/Group.h>

class ColoredGroup : public Group {
public:
	ColoredGroup(std::string color, std::vector<Slot*> slots);
	virtual int GetRent(Slot* s, PlayerTurnStatus turnStatus) const override;
	virtual bool CanPlayerBuildOn(Slot* s, PlayerStamp p) const override;
	virtual void Sell(Slot* s) const override;
	virtual int GetValue(Slot* s) const override;
protected:
	virtual bool HasPlayerAllSlots(PlayerStamp p) const;

	std::string color;
};
