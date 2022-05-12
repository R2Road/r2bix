#include "TextureFrameAnimationTable4Test.h"

#include <utility>

#include "TextureTable4Test.h"

void TextureFrameAnimationTable4Test::Load()
{
	if( !mContainer.empty() )
	{
		return;
	}

	r2base::TextureFrameAnimationInfo::Animation animation;
	r2base::TextureFrameAnimationInfo::AnimationPackageT animation_package;

	//
	// 1
	//
	{
		// Idle_1
		{
			animation.Index = r2animation::eIndex::Idle_1;
			animation.Container.push_back( r2base::TextureFrameAnimationInfo::AnimationFrame{ 0.1f, TextureTable4Test::GetInstance().GetTextureFrame( "dguy_walk_1" ) } );

			animation_package.push_back( std::move( animation ) );
		}

		// Run_1
		{
			animation.Index = r2animation::eIndex::Run_1;
			animation.Container.push_back( r2base::TextureFrameAnimationInfo::AnimationFrame{ 0.25f, TextureTable4Test::GetInstance().GetTextureFrame( "dguy_walk_1" ) } );
			animation.Container.push_back( r2base::TextureFrameAnimationInfo::AnimationFrame{ 0.25f, TextureTable4Test::GetInstance().GetTextureFrame( "dguy_walk_2" ) } );
			animation.Container.push_back( r2base::TextureFrameAnimationInfo::AnimationFrame{ 0.25f, TextureTable4Test::GetInstance().GetTextureFrame( "dguy_walk_1" ) } );
			animation.Container.push_back( r2base::TextureFrameAnimationInfo::AnimationFrame{ 0.25f, TextureTable4Test::GetInstance().GetTextureFrame( "dguy_walk_3" ) } );

			animation_package.push_back( std::move( animation ) );
		}

		mContainer.emplace( 1, std::move( animation_package ) );
	}
}