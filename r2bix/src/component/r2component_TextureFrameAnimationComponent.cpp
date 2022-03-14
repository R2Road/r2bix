#include "pch.h"
#include "r2component_TextureFrameAnimationComponent.h"

#include "r2component_TextureFrameRenderComponent.h"

namespace r2component
{
	TextureFrameAnimationComponent::TextureFrameAnimationComponent( r2base::Node& owner_node ) : r2base::Component( owner_node )
		, mTextureFrameRenderComponent( nullptr )
		, mAnimationPackage()
		, mCurrentAnimation( mAnimationPackage.end() )
		, mCurrentAnimationFrameIndex( 0u )
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

	void TextureFrameAnimationComponent::Update( const float delta_time )
	{
		if( mAnimationPackage.end() != mCurrentAnimation )
		{
			if( !mCurrentAnimation->Container[mCurrentAnimationFrameIndex].Timer.update( delta_time ) )
			{
				mCurrentAnimation->Container[mCurrentAnimationFrameIndex].Timer.reset();
				mCurrentAnimationFrameIndex = ( mCurrentAnimation->Container.size() > mCurrentAnimationFrameIndex + 1u ? mCurrentAnimationFrameIndex + 1u : 0u );

				mTextureFrameRenderComponent->SetTextureFrame( mCurrentAnimation->Container[mCurrentAnimationFrameIndex].Frame );
			}
		}
	}

	void TextureFrameAnimationComponent::LoadAnimation( const r2base::TextureFrameAnimationInfo& info )
	{
		StopAnimation();

		Animation animation;
		for( const auto& a : info.Get() )
		{
			animation.Index = a.Index;

			for( const auto& f : a.Container )
			{
				animation.Container.push_back( AnimationFrame{ { f.TimeLimit, true }, f.Frame } );
			}

			mAnimationPackage.emplace_back( std::move( animation ) );
		}

		mCurrentAnimation = mAnimationPackage.end();
	}
	bool TextureFrameAnimationComponent::HasAnimation( const r2animation::eIndex animation_index ) const
	{
		for( const auto& a : mAnimationPackage )
		{
			if( animation_index == a.Index )
			{
				return true;
			}
		}

		return false;
	}
	void TextureFrameAnimationComponent::RunAnimation( const r2animation::eIndex animation_index )
	{
		StopAnimation();

		for( auto cur = mAnimationPackage.begin(), end = mAnimationPackage.end(); end != cur; ++cur )
		{
			if( animation_index == cur->Index )
			{
				mCurrentAnimation = cur;
				mTextureFrameRenderComponent->SetTextureFrame( mCurrentAnimation->Container[mCurrentAnimationFrameIndex].Frame );
				break;
			}
		}
	}
	void TextureFrameAnimationComponent::StopAnimation()
	{
		mCurrentAnimation = mAnimationPackage.end();
		mCurrentAnimationFrameIndex = 0u;
	}

	const r2animation::eIndex TextureFrameAnimationComponent::GetCurrentAnimationIndex() const
	{
		if( mAnimationPackage.end() == mCurrentAnimation )
		{
			return r2animation::eIndex::None;
		}

		return mCurrentAnimation->Index;
	}
}