#include "pch.h"
#include "r2node_SpriteNode.h"

#include "base/r2base_Director.h"
#include "component/r2component_TextureFrameRenderComponent.h"

namespace r2node
{
	SpriteNode::SpriteNode( r2base::Director& director ) : r2base::Node( director )
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
			ret->SetTextureFrame( texture_frame );
		}

		return ret;
	}

	bool SpriteNode::Init()
	{
		if( !r2base::Node::Init() )
		{
			return false;
		}

		//
		//
		//
		mTextureFrameRenderComponent = AddComponent<r2component::TextureFrameRenderComponent>();

		return true;
	}

	void SpriteNode::SetTextureFrame( r2render::TextureFrame* const texture_frame )
	{
		mTextureFrameRenderComponent->SetTextureFrame( texture_frame );
	}
}