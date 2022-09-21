#pragma once

#include "r2bix/r2node_SceneNode.h"

namespace p2048
{
	class GameScene : public r2node::SceneNode
	{
	private:
		GameScene() = delete;

	public:
		static r2node::SceneNodeUp Create( r2bix::Director& director );
	};
}