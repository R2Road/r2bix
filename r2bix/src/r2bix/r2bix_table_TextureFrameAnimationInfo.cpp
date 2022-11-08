#include "r2bix_table_TextureFrameAnimationInfo.h"

#include <utility>

namespace r2base
{
	TextureFrameAnimationInfo::TextureFrameAnimationInfo( AnimationPackageT&& animation_package ) : mAnimationPackage( std::move( animation_package ) )
	{}
}