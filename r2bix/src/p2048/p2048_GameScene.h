#pragma once

#include "node/r2node_SceneNode.h"

namespace p2048
{
	class GameScene : public r2node::SceneNode
	{
	private:
		GameScene( r2base::Director& director );

	public:
		static r2node::SceneNodeUp Create( r2base::Director& director );

	private:
		bool Init() override;
	public:
		void Update( const float delta_time ) override;
	};
}