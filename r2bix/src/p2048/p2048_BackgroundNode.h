#pragma once

#include "base/r2base_Node.h"

namespace r2base
{
	class Director;
}

namespace p2048
{
	class BackgroundNode : public r2base::Node
	{
	private:
		BackgroundNode() = delete;

	public:
		static r2base::NodeUp Create( r2base::Director& director );
	};
}