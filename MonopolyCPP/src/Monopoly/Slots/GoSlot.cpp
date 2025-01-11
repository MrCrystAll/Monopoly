#include <Monopoly/Slots/GoSlot.h>

GoSlot::GoSlot(std::string name) : Slot(name)
{
}

GoSlot::GoSlot(Slot* s): Slot(s->GetName())
{
}

bool GoSlot::IsGo() const
{
	return true;
}
