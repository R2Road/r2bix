#pragma once

#include "base/r2base_Node.h"

namespace r2base
{
	class Director;
}

namespace r2component
{
	class TextureFrameRenderComponent;
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
		SpriteNode( r2base::Director& director );

	public:
		static std::unique_ptr<SpriteNode> Create( r2base::Director& director, r2render::TextureFrame* const texture_frame );

		//
		// Override
		//
	private:
		bool Init() override;

	public:
		r2component::TextureFrameRenderComponent* mTextureFrameRenderComponent;
	};
}