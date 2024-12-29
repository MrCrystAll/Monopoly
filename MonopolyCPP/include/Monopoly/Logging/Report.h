#pragma once

#include <vector>
#include <string>
#include <nlohmann/json.hpp>

#include <Monopoly/Players/Player.h>
#include <Monopoly/Slots/Slot.h>

struct Transaction {
	PlayerStamp sender, receiver;
	int money;

	NLOHMANN_DEFINE_TYPE_INTRUSIVE(Transaction, sender, receiver, money)
};

struct SellingAction {
	Slot* slot;
	int value;
	PlayerStamp seller;

	friend void to_json(nlohmann::json& nlohmann_json_j, const SellingAction& nlohmann_json_t) {
		json slot;
		nlohmann_json_t.slot->ToJson(slot);

		nlohmann_json_j["slot"] = slot; nlohmann_json_j["value"] = nlohmann_json_t.value; nlohmann_json_j["seller"] = nlohmann_json_t.seller;
	} friend void from_json(const nlohmann::json& nlohmann_json_j, SellingAction& nlohmann_json_t) {
		nlohmann_json_t.slot->FromJson(nlohmann_json_j); nlohmann_json_j.at("value").get_to(nlohmann_json_t.value); nlohmann_json_j.at("seller").get_to(nlohmann_json_t.seller);
	}
};

struct BuyingAction {
	Slot* slot;
	int buyPrice;
	PlayerStamp buyer;

	friend void to_json(nlohmann::json& nlohmann_json_j, const BuyingAction& nlohmann_json_t) {
		json slot;
		nlohmann_json_t.slot->ToJson(slot);

		nlohmann_json_j["slot"] = slot; nlohmann_json_j["buyPrice"] = nlohmann_json_t.buyPrice; nlohmann_json_j["buyer"] = nlohmann_json_t.buyer;
	} friend void from_json(const nlohmann::json& nlohmann_json_j, BuyingAction& nlohmann_json_t) {
		nlohmann_json_t.slot->FromJson(nlohmann_json_j); nlohmann_json_j.at("buyPrice").get_to(nlohmann_json_t.buyPrice); nlohmann_json_j.at("buyer").get_to(nlohmann_json_t.buyer);
	}
};

struct BuildAction {
	Slot* slot;
	int nHouses;
	PlayerStamp builder;

	friend void to_json(nlohmann::json& nlohmann_json_j, const BuildAction& nlohmann_json_t) {
		json slot;
		nlohmann_json_t.slot->ToJson(slot);

		nlohmann_json_j["slot"] = slot; nlohmann_json_j["nHouses"] = nlohmann_json_t.nHouses; nlohmann_json_j["builder"] = nlohmann_json_t.builder;
	} friend void from_json(const nlohmann::json& nlohmann_json_j, BuildAction& nlohmann_json_t) {
		nlohmann_json_t.slot->FromJson(nlohmann_json_j); nlohmann_json_j.at("nHouses").get_to(nlohmann_json_t.nHouses); nlohmann_json_j.at("builder").get_to(nlohmann_json_t.builder);
	}
};

struct MortgageAction {
	Slot* slot;
	PlayerStamp mortgager;

	friend void to_json(nlohmann::json& nlohmann_json_j, const MortgageAction& nlohmann_json_t) {
		json slot;
		nlohmann_json_t.slot->ToJson(slot);
		nlohmann_json_j["slot"] = slot; nlohmann_json_j["mortgager"] = nlohmann_json_t.mortgager;
	} friend void from_json(const nlohmann::json& nlohmann_json_j, MortgageAction& nlohmann_json_t) {
		nlohmann_json_t.slot->FromJson(nlohmann_json_j); nlohmann_json_j.at("mortgager").get_to(nlohmann_json_t.mortgager);
	}
};

struct LiftAction {
	Slot* slot;
	PlayerStamp lifter;

	friend void to_json(nlohmann::json& nlohmann_json_j, const LiftAction& nlohmann_json_t) {
		json slot;
		nlohmann_json_t.slot->ToJson(slot);
		nlohmann_json_j["slot"] = slot; nlohmann_json_j["lifter"] = nlohmann_json_t.lifter;
	} friend void from_json(const nlohmann::json& nlohmann_json_j, LiftAction& nlohmann_json_t) {
		nlohmann_json_t.slot->FromJson(nlohmann_json_j); nlohmann_json_j.at("lifter").get_to(nlohmann_json_t.lifter);
	}
};

struct PerTurnActions {
	std::vector<Transaction> transactions = {};
	std::vector<SellingAction> sellingActions = {};
	std::vector<BuyingAction> buyingActions = {};
	std::vector<BuildAction> buildActions = {};
	std::vector<MortgageAction> mortgageActions = {};
	std::vector<LiftAction> liftActions = {};

	NLOHMANN_DEFINE_TYPE_INTRUSIVE(PerTurnActions, transactions, sellingActions, buyingActions, buildActions, mortgageActions, liftActions)
};

struct Report {

	Report() = default;

	std::vector<Player> players = {};
	int turn;
	PerTurnActions actions = {};
	std::map<PlayerStamp, std::vector<Slot*>> slotsPerPlayer;

	void AddBuyingAction(BuyingAction action);
	void AddSellingAction(SellingAction action);
	void AddTransaction(Transaction action);
	void AddBuildAction(BuildAction action);
	void AddMortgageAction(MortgageAction action);
	void AddLiftAction(LiftAction action);

	friend void to_json(nlohmann::json& nlohmann_json_j, const Report& nlohmann_json_t) {
		json j;
		std::map<PlayerStamp, std::vector<json>> js_map = {};
		for (auto& [stamp, slots] : nlohmann_json_t.slotsPerPlayer) {
			std::vector<json> slots_f = {};
			for (Slot* slot : slots) {
				json slot_json;
				slot->ToJson(slot_json);
				slots_f.push_back(slot_json);
			}
			js_map[stamp] = slots_f;
		}
		nlohmann_json_j["players"] = nlohmann_json_t.players; nlohmann_json_j["turn"] = nlohmann_json_t.turn; nlohmann_json_j["actions"] = nlohmann_json_t.actions; nlohmann_json_j["slotsPerPlayer"] = js_map;
	}
}; 
