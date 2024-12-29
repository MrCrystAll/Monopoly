#include <Monopoly/Logging/Report.h>

void Report::AddBuyingAction(BuyingAction action)
{
	this->actions.buyingActions.push_back(action);
}

void Report::AddSellingAction(SellingAction action)
{
	this->actions.sellingActions.push_back(action);
}

void Report::AddTransaction(Transaction action)
{
	this->actions.transactions.push_back(action);
}

void Report::AddBuildAction(BuildAction action)
{
	this->actions.buildActions.push_back(action);
}

void Report::AddMortgageAction(MortgageAction action)
{
	this->actions.mortgageActions.push_back(action);
}

void Report::AddLiftAction(LiftAction action)
{
	this->actions.liftActions.push_back(action);
}
