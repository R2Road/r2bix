#pragma once

#include "base/r2base_Node.h"

namespace r2base
{
	class Director;
}

namespace r2component
{
	class TextRenderComponent;
	class TransformComponent;
}

namespace r2node
{
	class SpriteNode : public r2base::Node
	{
	private:
		SpriteNode( r2base::Director& director );

	public:
		static std::unique_ptr<SpriteNode> Create( r2base::Director& director );

		//
		// Override
		//
	private:
		bool Init() override;

	public:
		r2component::TransformComponent* mTransformComponent;
		r2component::TextRenderComponent* mTextRenderComponent;
	};
}