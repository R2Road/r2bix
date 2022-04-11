#pragma once

#include <memory>

#include "node/r2node_SceneNode.h"

namespace r2node
{
	class LabelNode;
	class SpriteNode;
}

namespace p2048
{
	class EntryScene : public r2node::SceneNode
	{
	private:
		EntryScene( r2base::Director& director );

	public:
		static const char* const GetTitle() { return "Game : 2048( To do )"; }
		static r2node::SceneNodeUp Create( r2base::Director& director );

	public:
		void Update( const float delta_time ) override;
	};
}