#include "pch.h"
#include "r2component_TextureFrameAnimationComponent.h"

namespace r2component
{
	TextureFrameAnimationComponent::TextureFrameAnimationComponent( r2base::Node& owner_node ) : r2base::Component( owner_node )
		, mTextureFrameContainer()
	{}

	std::unique_ptr<TextureFrameAnimationComponent> TextureFrameAnimationComponent::Create( r2base::Node& owner_node )
	{
		std::unique_ptr<TextureFrameAnimationComponent> ret( new ( std::nothrow ) TextureFrameAnimationComponent( owner_node ) );
		if( !ret || !ret->Init() )
		{
			ret.reset();
		}

		return ret;
	}

	void TextureFrameAnimationComponent::AddTextureFrame( const r2render::TextureFrame* const texture_frame )
	{
		if( nullptr == texture_frame )
		{
			return;
		}

		mTextureFrameContainer.push_back( texture_frame );
	}
}