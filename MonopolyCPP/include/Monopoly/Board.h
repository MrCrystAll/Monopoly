#pragma once

#include <vector>
#include <Monopoly/Slots/Slot.h>
#include <Monopoly/Slots/BuyableSlot.h>
#include <Monopoly/Slots/RentableSlot.h>
#include <Monopoly/Slots/BuildableSlot.h>

#include <Monopoly/Groups/Group.h>
#include <Monopoly/Groups/ColoredGroup.h>
#include <Monopoly/Groups/StationsGroup.h>
#include <Monopoly/Groups/ServicesGroup.h>

#include <nlohmann/json.hpp>

using json = nlohmann::json;

class Board {
public:
	Board(int n_slots = 40);
	void Display() const;

	Slot* GetSlotAt(uint16_t n) const;
	uint16_t GetBoardLength() const;
	std::vector<Slot*> GetPropertiesOf(PlayerStamp pStamp) const;
	Group* GetGroupOf(Slot* s) const;

	friend void to_json(nlohmann::json& nlohmann_json_j, const Board& nlohmann_json_t) {
		std::vector<json> slots_f = {};
		for (Slot* slot : nlohmann_json_t.slots) {
			json slot_json;
			slot->ToJson(slot_json);
			slots_f.push_back(slot_json);
		}
		nlohmann_json_j["n_slots"] = nlohmann_json_t.n_slots; nlohmann_json_j["slots"] = slots_f;
	}
private:
	uint16_t n_slots;
	std::vector<Slot*> slots;
	std::vector<Group*> groups;
};
