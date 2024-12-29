#pragma once

#include <Monopoly/Groups/Group.h>

class StationsGroup : public Group {
public:
	StationsGroup(std::vector<Slot*> slots);
	virtual int GetRent(Slot* s, PlayerTurnStatus turnStatus) const override;
};
