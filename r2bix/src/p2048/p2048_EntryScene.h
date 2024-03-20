#pragma once

#include <memory>

#include "r2bix_node_Node.h"

namespace p2048
{
	class EntryScene : public r2bix_node::Node
	{
	private:
		EntryScene( r2bix::Director& director );

	public:
		static const char* const GetTitle() { return "Game : 2048( ...Zzz )"; }
		static r2bix_node::NodeUp Create( r2bix::Director& director );

	public:
		void Update( const float delta_time ) override;
	};
}