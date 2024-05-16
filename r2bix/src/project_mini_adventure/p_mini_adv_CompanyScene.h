#pragma once

#include "r2bix_node_Node.h"

namespace p_mini_adv
{
	class CompanyScene
	{
	private:
		CompanyScene() = delete;

	public:
		static const char* const GetTitle() { return "Game : Mini Adventure( To do )"; }
		static r2bix_node::NodeUp Create( r2bix::Director& director );
	};
}