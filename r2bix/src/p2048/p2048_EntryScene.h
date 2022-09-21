#pragma once

#include <memory>

#include "r2bix/r2node_SceneNode.h"

namespace r2node
{
	class LabelSNode;
	class SpriteNode;
}

namespace p2048
{
	class EntryScene : public r2node::SceneNode
	{
	private:
		EntryScene( r2bix::Director& director );

	public:
		static const char* const GetTitle() { return "Game : 2048( ...Zzz )"; }
		static r2node::SceneNodeUp Create( r2bix::Director& director );

	public:
		void Update( const float delta_time ) override;
	};
}