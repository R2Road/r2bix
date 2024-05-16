#pragma once

#include "r2bix_node_Node.h"

namespace p_mini_adv
{
	class GameScene
	{
	private:
		GameScene() = delete;

	public:
		static const char* const GetTitle() { return "Game : Mini Adventure( In Progress )"; }
		static r2bix_node::NodeUp Create( r2bix::Director& director );
	};
}