#pragma once

#include "r2bix_node_Node.h"

namespace r2bix
{
	class Director;
}

namespace p2048
{
	class NumberNode
	{
	private:
		NumberNode() = delete;

	public:
		static r2bix_node::NodeUp Create( r2bix::Director& director );
	};
}