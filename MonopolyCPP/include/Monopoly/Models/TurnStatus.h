#pragma once

#include <map>
#include <Monopoly/Models/PlayerTurnStatus.h>
#include <Monopoly/Players/PlayerStamp.h>

struct TurnStatus
{
	std::map<PlayerStamp, PlayerTurnStatus> playerTurnsStatus;
};
