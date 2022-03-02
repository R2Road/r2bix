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
	class LabelNode : public r2base::Node
	{
	private:
		LabelNode( r2base::Director& director );

	public:
		static std::unique_ptr<LabelNode> Create( r2base::Director& director );

		//
		// Override
		//
	private:
		bool Init() override;

	public:
		//
		//
		//
		void SetRect( const int x, const int y, const int width, const int height );
		void SetString( const std::string_view str );

	public:
		r2component::TransformComponent* mTransformComponent;
		r2component::TextRenderComponent* mTextRenderComponent;
	};
}