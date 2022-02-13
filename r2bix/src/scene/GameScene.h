#pragma once

#include "game/r2game_Node.h"

namespace r2base
{
	class Director;
}

class GameScene : public r2game::Node
{
public:
	GameScene( r2base::Director& director );

	bool Do() override;
};