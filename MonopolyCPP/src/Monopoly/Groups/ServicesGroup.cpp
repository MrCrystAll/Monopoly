#include <Monopoly/Groups/ServicesGroup.h>

ServicesGroup::ServicesGroup(std::vector<Slot*> slots) : Group(slots)
{
}

int ServicesGroup::GetRent(Slot* s, PlayerTurnStatus turnStatus) const
{
	int rent = s->GetRent();
	int nSimilar = 0;

	for (const Slot* slot : this->slots) {
		if (slot->GetOwner() == s->GetOwner()) nSimilar++;
	}

	return turnStatus.diceResult.sum * (rent * nSimilar);
}
