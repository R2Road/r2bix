#pragma once

#include "game/r2game_Node.h"

namespace r2base
{
	class Director;
}

namespace r2game
{
	class Scene : public r2game::Node
	{
	public:
		Scene( r2base::Director& director );

		void Update() override;
	};
}