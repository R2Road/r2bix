#include "r2bix_table_TextureFrameAnimationTableBase.h"

namespace r2bix_table
{
	TextureFrameAnimationTableBase::TextureFrameAnimationTableBase() : mContainer()
	{}

	const r2bix_table::TextureFrameAnimationInfo& TextureFrameAnimationTableBase::Get( const int index ) const
	{
		auto itr = mContainer.find( index );
		if( mContainer.end() != itr )
		{
			return itr->second;
		}

		static r2bix_table::TextureFrameAnimationInfo dummy_package( std::move( r2bix_table::TextureFrameAnimationInfo::AnimationPackageT() ) );
		return dummy_package;
	}
}