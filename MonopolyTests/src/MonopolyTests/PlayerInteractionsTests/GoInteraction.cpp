#include <MonopolyTests/PlayerInteractionsTests/GoInteraction.h>

TEST_CASE("Go interaction", PLAYER_INTERACTION_TAG) {

	MockPlayer* p = new MockPlayer(0, 2000);

	CHECK(p->GetMoney() == 2000);

	p->SetPosition(36);

	GameSetup setup = GameSetup(
		0, { p }, true, 1
	);

	Game g = Game(setup);
	p->SetDiceResult({
		.sum = 3,
		.isDouble = false
		});

	g.Turn();

	CHECK(p->GetMoney() == 2200);
	
}
