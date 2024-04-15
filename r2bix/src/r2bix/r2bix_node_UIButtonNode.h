#pragma once

#include "r2bix_node_Node.h"

namespace r2bix
{
	class Director;
}

namespace r2bix_node
{
	class UIButtonNode : public r2bix_node::Node
	{
	private:
		UIButtonNode() = delete;

	public:
		static r2bix_node::NodeUp Create( r2bix::Director& director );
	};
}