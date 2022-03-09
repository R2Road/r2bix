#pragma once

#include "base/r2base_Node.h"

namespace r2base
{
	class Director;
}

namespace r2node
{
	class LabelNode
	{
	private:
		LabelNode() = delete;

	public:
		static std::unique_ptr<r2base::Node> Create( r2base::Director& director );
	};
}