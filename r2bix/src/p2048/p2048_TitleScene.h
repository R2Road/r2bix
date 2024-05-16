#pragma once

#include "r2bix_node_Node.h"

namespace p2048
{
	class TitleScene
	{
	private:
		TitleScene() = delete;

	public:
		static r2bix_node::NodeUp Create( r2bix::Director& director );
	};
}