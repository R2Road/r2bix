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
	class SpriteNode : public r2base::Node
	{
	private:
		SpriteNode() = delete;

	public:
		static r2base::NodeUp Create( r2base::Director& director, r2render::TextureFrame* const texture_frame );
	};
}