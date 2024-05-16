#pragma once

#include "r2bix_node_Node.h"

namespace psnake
{
	class CompanyScene
	{
	private:
		CompanyScene() = delete;

	public:
		static const char* const GetTitle() { return "Game : Snake( In Progress )"; }
		static r2bix_node::NodeUp Create( r2bix::Director& director );
	};
}