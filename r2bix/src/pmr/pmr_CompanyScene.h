#pragma once

#include "r2bix_node_Node.h"

namespace pmr
{
	class CompanyScene
	{
	private:
		CompanyScene() = delete;

	public:
		static const char* const GetTitle() { return "Game : Mini Rogue( To do )"; }
		static r2bix_node::NodeUp Create( r2bix::Director& director );
	};
}