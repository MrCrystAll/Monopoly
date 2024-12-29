#pragma once

#include <Monopoly/Groups/Group.h>

class ServicesGroup : public Group {
public:
	ServicesGroup(std::vector<Slot*> slots);
	virtual int GetRent(Slot* s, PlayerTurnStatus turnStatus) const override;
};
