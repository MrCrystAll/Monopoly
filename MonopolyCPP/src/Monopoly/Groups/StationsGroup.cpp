#include <Monopoly/Groups/StationsGroup.h>

StationsGroup::StationsGroup(std::vector<Slot*> slots): Group(slots)
{
}

int StationsGroup::GetRent(Slot* s, PlayerTurnStatus turnStatus) const
{
	int nSimilar = 0;
	for (const Slot* s_ : this->slots) {
		if (s_->GetOwner() == s->GetOwner()) nSimilar++;
	}

	return s->GetRent() * nSimilar;
}
