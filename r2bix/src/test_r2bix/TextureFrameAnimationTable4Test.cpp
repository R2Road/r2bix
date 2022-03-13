#include "pch.h"
#include "TextureFrameAnimationTable4Test.h"

#include <utility>

#include "TextureTable4Test.h"

void TextureFrameAnimationTable4Test::Load()
{
	if( !mContainer.empty() )
	{
		return;
	}

	Animation animation;
	AnimationPackage animation_package;

	//
	// 1
	//
	{
		animation.Index = r2animation::eIndex::Run_1;
		animation.Container.push_back( AnimationFrame{ 0.1f, TextureTable4Test::GetInstance().GetTextureFrame( "dguy_walk_1" ) } );
		animation.Container.push_back( AnimationFrame{ 0.1f, TextureTable4Test::GetInstance().GetTextureFrame( "dguy_walk_2" ) } );
		animation.Container.push_back( AnimationFrame{ 0.1f, TextureTable4Test::GetInstance().GetTextureFrame( "dguy_walk_1" ) } );
		animation.Container.push_back( AnimationFrame{ 0.1f, TextureTable4Test::GetInstance().GetTextureFrame( "dguy_walk_3" ) } );

		animation_package.Container.push_back( std::move( animation ) );

		mContainer.emplace( 1, std::move( animation_package ) );
	}
}