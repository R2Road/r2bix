#include "pch.h"
#include "r2base_TextureFrameAnimationTableBase.h"

namespace r2base
{
	TextureFrameAnimationTableBase::TextureFrameAnimationTableBase() : mContainer()
	{}

	const TextureFrameAnimationTableBase::AnimationPackage& TextureFrameAnimationTableBase::Get( const int index ) const
	{
		auto itr = mContainer.find( index );
		if( mContainer.end() != itr )
		{
			return itr->second;
		}

		static TextureFrameAnimationTableBase::AnimationPackage dummy_package;
		return dummy_package;
	}
}