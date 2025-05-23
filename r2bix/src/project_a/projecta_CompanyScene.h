#pragma once

#include "r2bix_node_Node.h"

namespace projecta
{
	class CompanyScene
	{
	private:
		CompanyScene() = delete;

	public:
		static const char* const GetTitle() { return "Game : ProjectA"; }
		static r2bix_node::NodeUp Create( r2bix::Director& director );
	};
}