#include "pch.h"
#include "r2node_SpriteNode.h"

#include "base/r2base_Director.h"
#include "component/r2component_TextureFrameRenderComponent.h"
#include "component/r2component_TransformComponent.h"

namespace r2node
{
	SpriteNode::SpriteNode( r2base::Director& director ) : r2base::Node( director )
		, mTransformComponent( nullptr )
		, mTextureFrameRenderComponent( nullptr )
	{}

	std::unique_ptr<SpriteNode> SpriteNode::Create( r2base::Director& director, r2render::TextureFrame* const texture_frame )
	{
		std::unique_ptr<SpriteNode> ret( new ( std::nothrow ) SpriteNode( director ) );
		if( !ret || !ret->Init() )
		{
			ret.reset();
		}
		else
		{
			ret->mTextureFrameRenderComponent->SetTextureFrame( texture_frame );
		}

		return ret;
	}

	bool SpriteNode::Init()
	{
		{
			auto component = r2component::TransformComponent::Create( *this );
			mTransformComponent = component.get();
			AddComponent( std::move( component ) );
		}

		{
			auto component = r2component::TextureFrameRenderComponent::Create( *this );
			component->mTransformComponent = mTransformComponent;
			mTextureFrameRenderComponent = component.get();
			AddComponent( std::move( component ) );
		}

		return true;
	}
}