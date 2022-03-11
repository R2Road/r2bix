#include "pch.h"
#include "r2component_TextureFrameAnimationComponent.h"

#include "r2component_TextureFrameRenderComponent.h"

namespace r2component
{
	TextureFrameAnimationComponent::TextureFrameAnimationComponent( r2base::Node& owner_node ) : r2base::Component( owner_node )
		, mTextureFrameRenderComponent( nullptr )
		, mTextureFrameContainer()
		, mAnimationTimer( 1.f )
		, mAnimationIndex( 0 )
	{
		mAnimationTimer.update( 1.f ); // for first frame
	}

	std::unique_ptr<TextureFrameAnimationComponent> TextureFrameAnimationComponent::Create( r2base::Node& owner_node )
	{
		std::unique_ptr<TextureFrameAnimationComponent> ret( new ( std::nothrow ) TextureFrameAnimationComponent( owner_node ) );
		if( !ret || !ret->Init() )
		{
			ret.reset();
		}

		return ret;
	}

	void TextureFrameAnimationComponent::Update( const float delta_time )
	{
		if( mTextureFrameContainer.empty() )
		{
			return;
		}

		if( !mAnimationTimer.update( delta_time ) )
		{
			mAnimationTimer.reset();
			mAnimationIndex = mAnimationIndex + 1u >= mTextureFrameContainer.size() ? 0u : mAnimationIndex + 1u;

			mTextureFrameRenderComponent->SetTextureFrame( mTextureFrameContainer[mAnimationIndex] );
		}
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