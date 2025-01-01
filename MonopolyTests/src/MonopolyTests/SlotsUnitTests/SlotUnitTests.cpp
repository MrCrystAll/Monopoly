#include <MonopolyTests/SlotsUnitTests/SlotUnitTests.h>

TEST_CASE("Slot functions outputs the correct result", SLOT_TAG) {
	Slot* s = new Slot("A slot");

	SECTION("Slot values") {
		CHECK(s->GetName() == "A slot");
		CHECK(not s->CanBuy());
		CHECK(not s->CanRent());
		CHECK(not s->CanBuild());
		CHECK(not s->CanLift());
		CHECK(not s->CanMortgage());
	}

	BuyableSlot* bSlot = new BuyableSlot(s, 150);

	SECTION("Buyable slot values") {
		CHECK(bSlot->GetName() == "A slot");
		CHECK(bSlot->CanBuy());
		CHECK(not bSlot->CanRent());
		CHECK(not bSlot->CanBuild());
		CHECK(not bSlot->CanLift());
		CHECK(not bSlot->CanMortgage());

		CHECK(bSlot->GetBuyPrice() == 150);
		CHECK(bSlot->GetValue() == 150);
	}

	RentableSlot* rSlot = new RentableSlot(bSlot, 10, 90);

	SECTION("Rentable slot values") {
		CHECK(rSlot->GetName() == "A slot");
		CHECK(rSlot->CanBuy());
		CHECK(rSlot->CanRent());
		CHECK(not rSlot->CanBuild());
		CHECK(not rSlot->CanLift());
		CHECK(rSlot->CanMortgage());

		CHECK(rSlot->GetRent() == 10);
		CHECK(rSlot->GetMortgageValue() == 90);
		CHECK(not rSlot->IsMortgaged());
	}

	BuildableSlot* buildSlot = new BuildableSlot(rSlot, 5, 50);

	SECTION("Buildable slot values") {
		CHECK(buildSlot->GetName() == "A slot");
		CHECK(buildSlot->CanBuy());
		CHECK(buildSlot->CanRent());
		CHECK(buildSlot->CanBuild());

		CHECK(not buildSlot->CanLift());
		CHECK(buildSlot->CanMortgage());

		CHECK(buildSlot->GetNHouses() == 0);
		CHECK(buildSlot->GetMaxHouses() == 5);
		CHECK(buildSlot->GetPricePerHouse() == 50);
	}
}
