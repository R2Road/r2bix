#include "pch.h"
#include "r2component_TextureFrameAnimationComponent.h"

#include "r2component_TextureFrameRenderComponent.h"

namespace r2component
{
	TextureFrameAnimationComponent::TextureFrameAnimationComponent( r2base::Node& owner_node ) : r2base::Component( owner_node )
		, mTextureFrameRenderComponent( nullptr )
		, mAnimationPackage( 0 )
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
	}

	void TextureFrameAnimationComponent::LoadAnimation( const r2base::TextureFrameAnimationInfo& info )
	{
		Animation animation;
		for( const auto& a : info.Get() )
		{
			animation.Index = a.Index;

			for( const auto& f : a.Container )
			{
				animation.Container.push_back( AnimationFrame{ f.TimeLimit, f.Frame } );
			}

			mAnimationPackage.emplace_back( std::move( animation ) );
		}
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
}