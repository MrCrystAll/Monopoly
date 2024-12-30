#include <MonopolyTests/SlotsUnitTests/SlotUnitTests.h>

TEST_CASE("Slot functions outputs the correct result", SLOT_TAG) {
	Slot* s = new Slot("A slot");

	CHECK(s->GetName() == "A slot");
}
