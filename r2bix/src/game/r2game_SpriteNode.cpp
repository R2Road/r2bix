#include "pch.h"
#include "r2game_SpriteNode.h"

#include "base/r2base_Director.h"
#include "component/r2component_TextRenderComponent.h"
#include "component/r2component_TransformComponent.h"

namespace r2game
{
	SpriteNode::SpriteNode( r2base::Director& director ) : r2base::Node( director )
		, mTransformComponent( nullptr )
		, mTextRenderComponent( nullptr )
	{}

	std::unique_ptr<SpriteNode> SpriteNode::Create( r2base::Director& director )
	{
		std::unique_ptr<SpriteNode> ret( new ( std::nothrow ) SpriteNode( director ) );
		if( !ret || !ret->Init() )
		{
			ret.reset();
		}

		return ret;
	}

	bool SpriteNode::Init()
	{
		auto transform_component = r2component::TransformComponent::Create( *this );
		mTransformComponent = transform_component.get();
		AddComponent( std::move( transform_component ) );

		auto text_render_component = r2component::TextRenderComponent::Create( *this );
		text_render_component->mTransformComponent = mTransformComponent;
		mTextRenderComponent = text_render_component.get();
		AddComponent( std::move( text_render_component ) );

		return true;
	}
}