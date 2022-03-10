#pragma once

#include "base/r2base_Node.h"

namespace r2base
{
	class Director;
}

namespace r2render
{
	class TextureFrame;
}

namespace r2node
{
	class LabelNode : public r2base::Node
	{
	private:
		LabelNode() = delete;

	public:
		static r2base::NodeUp Create( r2base::Director& director );
	};
}