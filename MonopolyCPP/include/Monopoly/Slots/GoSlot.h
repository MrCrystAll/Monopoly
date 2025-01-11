#pragma once

#include <Monopoly/Slots/Slot.h>

class GoSlot: public Slot{
public:
	GoSlot(std::string name);
	GoSlot(Slot* s);
	virtual bool IsGo() const;
};
