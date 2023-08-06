#pragma once

#include "r2bix_node_SceneNode.h"

namespace p2048
{
	class GameScene : public r2bix_node::SceneNode
	{
	private:
		GameScene() = delete;

	public:
		static r2bix_node::SceneNodeUp Create( r2bix::Director& director );
	};
}