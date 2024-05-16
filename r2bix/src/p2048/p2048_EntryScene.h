#pragma once

#include "r2bix_node_Node.h"

namespace p2048
{
	class EntryScene
	{
	private:
		EntryScene() = delete;

	public:
		static const char* const GetTitle() { return "Game : 2048( ...Zzz )"; }
		static r2bix_node::NodeUp Create( r2bix::Director& director );
	};
}