#include "p2048table_TextureFrameAnimationTable.h"

#include <utility>

#include "p2048table_TextureTable.h"

namespace p2048table
{
	void TextureFrameAnimationTable::Load()
	{
		if( !mContainer.empty() )
		{
			return;
		}

		r2bix_table::TextureFrameAnimationInfo::Animation animation;
		r2bix_table::TextureFrameAnimationInfo::AnimationPackageT animation_package;

		//
		// 1
		//
		{
			// Idle_1
			{
				animation.Index = r2bix_animation::eIndex::Idle_1;
				animation.Container.push_back( r2bix_table::TextureFrameAnimationInfo::AnimationFrame{ 0.1f, TextureTable::GetInstance().GetTextureFrame( "dguy_walk_1" ) } );

				animation_package.push_back( std::move( animation ) );
			}

			// Run_1
			{
				animation.Index = r2bix_animation::eIndex::Run_1;
				animation.Container.push_back( r2bix_table::TextureFrameAnimationInfo::AnimationFrame{ 0.25f, TextureTable::GetInstance().GetTextureFrame( "dguy_walk_2" ) } );
				animation.Container.push_back( r2bix_table::TextureFrameAnimationInfo::AnimationFrame{ 0.25f, TextureTable::GetInstance().GetTextureFrame( "dguy_walk_1" ) } );
				animation.Container.push_back( r2bix_table::TextureFrameAnimationInfo::AnimationFrame{ 0.25f, TextureTable::GetInstance().GetTextureFrame( "dguy_walk_3" ) } );
				animation.Container.push_back( r2bix_table::TextureFrameAnimationInfo::AnimationFrame{ 0.25f, TextureTable::GetInstance().GetTextureFrame( "dguy_walk_1" ) } );

				animation_package.push_back( std::move( animation ) );
			}

			mContainer.emplace( 1, std::move( animation_package ) );
		}
	}
}