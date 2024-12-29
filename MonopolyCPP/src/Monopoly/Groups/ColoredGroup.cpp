#include <Monopoly/Groups/ColoredGroup.h>

ColoredGroup::ColoredGroup(std::string color, std::vector<Slot*> slots) : Group(slots), color(color)
{
}

int ColoredGroup::GetRent(Slot* s, PlayerTurnStatus turnStatus) const
{
	if (HasPlayerAllSlots(s->GetOwner())) {
		for (const Slot* s_ : this->slots) {
			if (s_->CanBuild() and s->GetNHouses() > 0) {
				return s_->GetRent();
			}
		}
		return 2 * s->GetRent();
	}
	return s->GetRent();
}

bool ColoredGroup::CanPlayerBuildOn(Slot* s, PlayerStamp p) const
{
	return HasPlayerAllSlots(p) and s->CanBuild();
}

void ColoredGroup::Sell(Slot* s) const
{
	Group::Sell(s);
	for (Slot* s_ : this->slots) {
		if (s_->GetNHouses() > 0) {
			s_->Destroy(s->GetNHouses());
		}
	}
}

int ColoredGroup::GetValue(Slot* s) const
{
	int value = s->GetValue();
	for (Slot* s_ : this->slots) {
		value += s_->GetPricePerHouse() * s->GetNHouses();
	}
	
	return value;
}

bool ColoredGroup::HasPlayerAllSlots(PlayerStamp p) const
{
	for (const Slot* s : this->slots) {
		if (s->GetOwner() != p) return false;
	}
	return true;
}
