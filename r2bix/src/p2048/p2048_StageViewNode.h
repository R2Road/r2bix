#pragma once

#include "r2bix/r2base_Node.h"

namespace r2base
{
	class Director;
}

namespace p2048
{
	class StageViewNode : public r2base::Node
	{
	private:
		StageViewNode() = delete;

	public:
		static r2base::NodeUp Create( r2base::Director& director );
	};
}