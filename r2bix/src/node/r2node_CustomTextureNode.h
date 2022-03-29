#pragma once

#include "base/r2base_Node.h"

namespace r2base
{
	class Director;
}

namespace r2node
{
	class CustomTextureNode : public r2base::Node
	{
	private:
		CustomTextureNode() = delete;

	public:
		static r2base::NodeUp Create( r2base::Director& director );
	};
}