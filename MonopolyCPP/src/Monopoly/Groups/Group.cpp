#include <Monopoly/Groups/Group.h>

Group::Group(std::vector<Slot*> slots)
{
	this->slots = slots;
}

bool Group::CanPlayerBuildOn(Slot* s, PlayerStamp p) const
{
	return s->CanBuild();
}

void Group::Sell(Slot* s) const
{
	s->Sell();
}

int Group::GetRent(Slot* s, PlayerTurnStatus turnStatus) const
{
	return s->GetRent();
}

std::vector<Slot*> Group::GetSlots() const
{
	return this->slots;
}

int Group::GetValue(Slot* s) const
{
	return 0;
}

void Group::Mortgage(Slot* s)
{
	s->Mortgage();
}

void Group::Lift(Slot* s)
{
	s->Lift();
}
