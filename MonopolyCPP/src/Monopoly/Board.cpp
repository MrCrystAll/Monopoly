#include <Monopoly/Board.h>
#include <iostream>
//#include <Monopoly/Groups/Group.h>

Board::Board(int n_slots)
{
	this->n_slots = n_slots;
	this->slots = std::vector<Slot*>(n_slots);

	this->slots[0] = new Slot("Start");
	this->slots[1] = new BuildableSlot("Mediterranean Avenue", 60, 2, 50, 5, 50);
	this->slots[2] = new Slot("Community");
	this->slots[3] = new BuildableSlot("Baltic Avenue", 60, 4, 50, 5, 50);
	this->slots[4] = new Slot("Taxes");
	this->slots[5] = new RentableSlot("Reading Railroad", 200, 50, 100);
	this->slots[6] = new BuildableSlot("Oriental Avenue", 100, 6, 50, 5, 50);
	this->slots[7] = new Slot("Chance");
	this->slots[8] = new BuildableSlot("Vermont Avenue", 100, 6, 50, 5, 50);
	this->slots[9] = new BuildableSlot("Connecticut Avenue", 120, 8, 50, 5, 50);
	this->slots[10] = new Slot("Prison");
	this->slots[11] = new BuildableSlot("St. Charles Place", 140, 10, 100, 5, 100);
	this->slots[12] = new RentableSlot("Electricity", 150, 10, 80);
	this->slots[13] = new BuildableSlot("States Avenue", 140, 10, 100, 5, 100);
	this->slots[14] = new BuildableSlot("Virginia Avenue", 160, 12, 100, 5, 100);
	this->slots[15] = new RentableSlot("Pennsylvania Railroad", 200, 50, 100);
	this->slots[16] = new BuildableSlot("St.James Place", 180, 14, 100, 5, 100);
	this->slots[17] = new Slot("Community");
	this->slots[18] = new BuildableSlot("Tennessee Avenue", 180, 14, 100, 5, 100);
	this->slots[19] = new BuildableSlot("New York Avenue", 200, 16, 100, 5, 100);
	this->slots[20] = new Slot("Free parking");
	this->slots[21] = new BuildableSlot("Kentucky Avenue", 220, 18, 150, 5, 100);
	this->slots[22] = new Slot("Chance");
	this->slots[23] = new BuildableSlot("Indiana Avenue", 220, 18, 150, 5, 150);
	this->slots[24] = new BuildableSlot("Illinois Avenue", 240, 20, 150, 5, 150);
	this->slots[25] = new RentableSlot("B. & O. Railroad", 200, 50, 100);
	this->slots[26] = new BuildableSlot("Atlantic Avenue", 260, 22, 150, 5, 150);
	this->slots[27] = new BuildableSlot("Ventnor Avenue", 260, 22, 150, 5, 150);
	this->slots[28] = new RentableSlot("Water", 150, 10, 80);
	this->slots[29] = new BuildableSlot("Marvin Gardens", 280, 24, 150, 5, 150);
	this->slots[30] = new Slot("Go to prison");
	this->slots[31] = new BuildableSlot("Pacific Avenue", 300, 26, 200, 5, 200);
	this->slots[32] = new BuildableSlot("North Carolina Avenue", 300, 26, 200, 5, 200);
	this->slots[33] = new Slot("Community");
	this->slots[34] = new BuildableSlot("Pennsylvania Avenue", 320, 28, 200, 5, 200);
	this->slots[35] = new RentableSlot("Short Line", 200, 50, 100);
	this->slots[33] = new Slot("Chance");
	this->slots[36] = new BuildableSlot("Park Place", 350, 35, 200, 5, 200);
	this->slots[37] = new Slot("Taxes");
	this->slots[38] = new BuildableSlot("Boardwalk", 500, 50, 200, 5, 200);

	this->groups.push_back(new ColoredGroup(
		"pink",
		{ this->slots[1], this->slots[3] }
	));

	this->groups.push_back(new ColoredGroup(
		"light blue",
		{ this->slots[6], this->slots[8], this->slots[9] }
	));

	this->groups.push_back(new ColoredGroup(
		"purple",
		{ this->slots[11], this->slots[13], this->slots[14] }
	));

	this->groups.push_back(new ColoredGroup(
		"orange",
		{ this->slots[16], this->slots[18], this->slots[19] }
	));

	this->groups.push_back(new ColoredGroup(
		"red",
		{ this->slots[21], this->slots[23], this->slots[24] }
	));

	this->groups.push_back(new ColoredGroup(
		"yellow",
		{ this->slots[26], this->slots[27], this->slots[29] }
	));

	this->groups.push_back(new ColoredGroup(
		"green",
		{ this->slots[31], this->slots[32], this->slots[34] }
	));

	this->groups.push_back(new ColoredGroup(
		"dark blue",
		{ this->slots[36], this->slots[38] }
	));

	this->groups.push_back(new StationsGroup(
		{ this->slots[5], this->slots[15], this->slots[25], this->slots[35]}
	));

	this->groups.push_back(new ServicesGroup(
		{ this->slots[12], this->slots[28] }
	));

	//Group brown = Group(true, true);
}

void Board::Display() const
{
	for (Slot* s : this->slots) {
		LOG(s->GetName());
	}
}

Slot* Board::GetSlotAt(uint16_t n) const
{
	if (n >= this->n_slots) {
		ERR("Trying to access slot " << n << ". But there are only " << this->n_slots - 1 << " slots");
	}
	return this->slots[n];
}

uint16_t Board::GetBoardLength() const
{
	return this->n_slots;
}

std::vector<Slot*> Board::GetPropertiesOf(PlayerStamp pStamp) const
{
	std::vector<Slot*> slots = {};
	for (Slot* s : this->slots) {
		if (s->GetOwner() == pStamp) slots.push_back(s);
	}
	return slots;
}

Group* Board::GetGroupOf(Slot* s) const
{
	for (Group* g : this->groups) {
		for (const Slot* s_ : g->GetSlots()) {
			if (s_->GetName() == s->GetName()) return g;
		}
	}

	return nullptr;
}
