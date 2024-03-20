#pragma once

#include "r2bix_node_Node.h"

namespace p2048
{
	class GameScene : public r2bix_node::Node
	{
	private:
		GameScene() = delete;

	public:
		static r2bix_node::NodeUp Create( r2bix::Director& director );
	};
}