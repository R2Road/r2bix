#include "r2bix_table_TextureFrameAnimationInfo.h"

#include <utility>

namespace r2bix_table
{
	TextureFrameAnimationInfo::TextureFrameAnimationInfo( AnimationPackageT&& animation_package ) : mAnimationPackage( std::move( animation_package ) )
	{}
}