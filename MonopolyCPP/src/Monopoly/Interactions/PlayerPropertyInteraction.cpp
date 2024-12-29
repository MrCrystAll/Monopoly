#include <Monopoly/Interactions/PlayerPropertyInteraction.h>

PlayerPropertyInteraction::PlayerPropertyInteraction(GameStatus* status): status(status)
{

}

void PlayerPropertyInteraction::Interact(Player& pl, Slot* s, Group* g, Report& report)
{
	std::vector<PlayerPropertyInteraction::Interactions> interactions = this->GetInteractions(pl, s);
	std::vector<Choice> choices = {};

	if (interactions.size() == 0) return;
	int choice = 0;

	if (interactions.size() > 1) {
		int in = 0;
		for (Interactions i : interactions) {
			choices.push_back({ in, ToString(i) });
			in += 1;
		}
		choice = pl.Ask(choices);
	}

	Interactions chosenInteraction = interactions[choice];

	switch (chosenInteraction) {
		case Interactions::BUY:
			this->Buy(pl, s, report);
			break;
		case Interactions::BUILD:
			this->Build(pl, s, g, report);
			break;
		case Interactions::LIFT:
			this->Lift(pl, s, g, report);
			break;
		case Interactions::PAY:
			this->Pay(pl, s, g, report);
			break;
		default:
			break;
	}
}

std::vector<PlayerPropertyInteraction::Interactions> PlayerPropertyInteraction::GetInteractions(Player& pl, Slot* s)
{
	std::vector<PlayerPropertyInteraction::Interactions> interactions = {};
	Group* g = this->status->GetBoard()->GetGroupOf(s);

	if (s->CanBuy() and s->GetOwner() < 0 and pl.GetMoney() >= s->GetBuyPrice()) interactions.push_back(Interactions::BUY);
	if (s->CanBuy() and s->GetOwner() == pl.GetStamp()) {
		if (s->IsMortgaged() and s->GetMortgageValue() <= pl.GetMoney()) interactions.push_back(Interactions::LIFT);
		if (g->CanPlayerBuildOn(s, pl.GetStamp()) and s->GetMaxHouses() > s->GetNHouses() and s->GetPricePerHouse() <= pl.GetMoney()) interactions.push_back(Interactions::BUILD);
	}
	if (s->CanRent() and s->GetOwner() != -1 and s->GetOwner() != pl.GetStamp()) interactions.push_back(Interactions::PAY);

	return interactions;
}

const void PlayerPropertyInteraction::Buy(Player& pl, Slot* s, Report& report)
{
	int choice = pl.Ask({ Choice(0, "Buy '" + s->GetName() + "'"), Choice(1, "Don't buy \'" + s->GetName() + "'")}, "Do you want to buy '" + s->GetName() + "' ?");
	if (choice == 0) {
		pl.WithdrawMoney(s->GetBuyPrice());
		s->Buy(pl.GetStamp());

		report.AddBuyingAction({
			.slot = s->Copy(),
			.buyPrice = s->GetBuyPrice(),
			.buyer = pl.GetStamp()
			});

		LOG((int)pl.GetStamp() << " bought " << s->GetName());
	}
}

const void PlayerPropertyInteraction::Sell(Player& pl, int moneyToReach, Report& report)
{
	std::vector<Slot*> slots = this->status->GetBoard()->GetPropertiesOf(pl.GetStamp());
	std::vector<Choice> choices = {};

	int sumOfAll = 0;

	int n = 0;
	for (Slot* s : slots) {
		choices.push_back({ n++, s->GetName() });
		Group* g = this->status->GetBoard()->GetGroupOf(s);
		sumOfAll += g->GetValue(s);
	}

	if (pl.GetMoney() + sumOfAll < moneyToReach) {
		LOG("Player " << pl.GetStamp() << " goes out. Couldn't pay " << moneyToReach << " (Money: " << pl.GetMoney() << ", value: " << sumOfAll << ")");
		pl.GoesOut();
		return;
	}


	while (pl.GetMoney() < moneyToReach) {
		int choice = pl.Ask(choices, "What do you sell ? Remains: " + (moneyToReach - pl.GetMoney()));

		//Sells that one
		Slot* chosenSlot = slots[choice];
		Group* g = this->status->GetBoard()->GetGroupOf(chosenSlot);

		Slot* copySlot = chosenSlot->Copy();

		if (chosenSlot->IsMortgaged()) {
			int slotValue = chosenSlot->GetValue();

			g->Sell(chosenSlot);
			pl.AddMoney(slotValue);

			report.AddSellingAction({
			.slot = copySlot,
			.value = slotValue,
			.seller = pl.GetStamp()
				});

			LOG(pl.GetStamp() << " sold " << chosenSlot->GetName() << " (Value: " << slotValue << ")");
		}
		else {
			std::vector<Choice> sellOrMortgage = {
				{0, "Sell"},
				{1, "Mortgage"}
			};

			choice = pl.Ask(sellOrMortgage, "Sell or mortgage ?");

			Group* g = this->status->GetBoard()->GetGroupOf(chosenSlot);


			if (choice == 0) {
				int slotValue = chosenSlot->GetValue();

				g->Sell(chosenSlot);
				pl.AddMoney(slotValue);

				report.AddSellingAction({
						.slot = copySlot,
						.value = slotValue,
						.seller = pl.GetStamp()
					});

				LOG(pl.GetStamp() << " sold " << chosenSlot->GetName() << " (Value: " << slotValue << ")");
			}
			else if (choice == 1) {
				int slotValue = chosenSlot->GetMortgageValue();

				g->Mortgage(chosenSlot);
				LOG(pl.GetStamp() << " mortgaged " << chosenSlot->GetName() << " (Value: " << slotValue << ")");

				report.AddMortgageAction({
					.slot = chosenSlot->Copy(),
					.mortgager = pl.GetStamp()
					});

			}
		}

		sumOfAll = 0;
		choices.clear();
		slots = this->status->GetBoard()->GetPropertiesOf(pl.GetStamp());

		//Build all choices
		n = 0;
		for (Slot* s : slots) {
			choices.push_back({ n++, s->GetName() });
			Group* g = this->status->GetBoard()->GetGroupOf(s);
			sumOfAll += g->GetValue(s);
		}

		if (sumOfAll + pl.GetMoney() < moneyToReach) {
			pl.GoesOut();
			return;
		}
	}
}

const void PlayerPropertyInteraction::Build(Player& pl, Slot* s, Group* g, Report& report)
{
	int nCanBuild = pl.GetMoney() / s->GetPricePerHouse();
	nCanBuild = std::min(nCanBuild, s->GetMaxHouses() - s->GetNHouses());

	if (nCanBuild == 0) return;

	std::vector<Choice> choices = {};

	for (int i = 0; i <= nCanBuild; i++) {
		choices.push_back({ i, "Build " + i });
	}

	int nHouses = pl.Ask(choices);
	if (nHouses == 0) return;

	pl.WithdrawMoney(s->GetPricePerHouse() * nHouses);
	s->Build(nHouses);

	report.AddBuildAction({
		.slot = s->Copy(),
		.nHouses = nHouses,
		.builder = pl.GetStamp()
		});

	LOG(pl.GetStamp() << " built " << nHouses << " house(s) on " << s->GetName());
}

const void PlayerPropertyInteraction::Lift(Player& pl, Slot* s, Group* g, Report& report)
{
	g->Lift(s);
	pl.WithdrawMoney(s->GetMortgageValue());

	report.AddLiftAction({
		.slot = s->Copy(),
		.lifter = pl.GetStamp()
		});

	LOG(pl.GetStamp() << " lifted " << s->GetName() << "'s mortgage");
}

const void PlayerPropertyInteraction::Pay(Player& pl, Slot* s, Group* g, Report& report)
{
	for (Player* p : this->status->GetPlayers()) {
		if (p->GetStamp() == s->GetOwner()) {
			int rent = g->GetRent(s, this->status->GetTurnStatus()->playerTurnsStatus[pl.GetStamp()]);
			if (pl.GetMoney() - rent < 0) {
				LOG(pl.GetStamp() << " started to sell for " << s->GetName());
				this->Sell(pl, rent, report);
			}

			if (pl.IsOut()) {
				return;
			}

			pl.WithdrawMoney(rent);
			p->AddMoney(rent);

			report.AddTransaction({
				.sender = pl.GetStamp(),
				.receiver = p->GetStamp(),
				.money = rent
				});

			LOG(pl.GetStamp() << " paid " << rent << " to " << p->GetStamp() << " on " << s->GetName());
		}
	}
}

std::ostream& operator<<(std::ostream& stream, PlayerPropertyInteraction::Interactions interaction)
{
	std::string value = ToString(interaction);
	stream << value;
	return stream;
}

std::string ToString(PlayerPropertyInteraction::Interactions interaction)
{
	std::string value = "";
	if (interaction == PlayerPropertyInteraction::Interactions::BUY) value = "Buy";
	if (interaction == PlayerPropertyInteraction::Interactions::BUILD) value = "Build";
	if (interaction == PlayerPropertyInteraction::Interactions::LIFT) value = "Lift mortgage";
	if (interaction == PlayerPropertyInteraction::Interactions::PAY) value = "Pay";
	if (interaction == PlayerPropertyInteraction::Interactions::SELL) value = "Sell";
	return value;
}
